/*
 * 线程操作类定义文件 By Lzy
 * 2011-12-08   V2.0.0.1    1、把CreateCS,ReleaseCS,EnterCS,ExitCS函数设置为内联函数
 *                          2、创建线程管理对象时允许设置是否线程运行完后自动释放，同时线程执行容器函数中增加相应支持
 * 2011-12-05   V2.0.0.0    By Lzy  把原来用类封装改成用命名空间封装，省去了线程链的维护
 * 2011-04-13   V0.0.0.0    By Lzy  创建文件
 */

#include "CommonThread.h"

namespace thread_operation
{
    struct SThreadObject//线程结构
    {
        //------枚举类型定义------
        enum EThreadState
        {
            THREAD_UNCREATE,//线程尚未创建
            THREAD_RUNNING,//线程执行中
            THREAD_FINISH,//线程执行完成（此时线程句柄已无效，重新执行需要重新创建线程）
            THREAD_TERMINAL,//线程执行被中断（此时线程句柄已无效，重新执行需要重新创建线程）
        };
        //------变量------
        HANDLE m_hThreadHandle;//线程标识
        EThreadState m_eThreadState;//线程状态
        void *(*m_fExeFunc)(void *);//线程执行函数指针
        bool m_bAutoRelease;//自动释放标记
        void *m_pParam;//传递给线程执行函数的参数指针
        void *m_pReturn;//线程执行完成后的返回值，从线程运行完后到下一次线程被重新创建运行前该值都有效
    };

    /*
     * 【仅本文件内使用】【线程函数】作为线程执行容器的函数，所有线程执行函数都被包在此函数中运行
     * @param void *pParam,传入指向SThreadObject结构的指针
     * @reutrn usigned int(WIN32下)/ void*(LINUX下),返回值没意义
     */
    #ifdef LINUX
    void *_ThreadContainerFun(void *pParam)
    #endif
    #ifdef WIN32
    unsigned int __stdcall _ThreadContainerFun(void *pParam)
    #endif
    {
    #ifdef LINUX
        //为使中断线程的操作有效而做的设置
        pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);//允许退出线程 
        pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);//设置立即取消
    #endif
        SThreadObject *pThreadManager = (SThreadObject *)pParam;
        pThreadManager->m_pReturn = pThreadManager->m_fExeFunc(pThreadManager->m_pParam);//运行用户定义的函数
        pThreadManager->m_eThreadState = SThreadObject::THREAD_FINISH;
        if (pThreadManager->m_bAutoRelease == true)
            delete pThreadManager;
    #ifdef LINUX
        return NULL;
    #endif
    #ifdef WIN32
        return 0;
    #endif
    }

    /*
     * 【仅本文件内使用】创建新线程并运行
     * @param SThreadObject *pThreadManager,有效的线程管理对象指针
     * @return bool,返回是否成功创建线程并执行
     */
    bool _CreateAndRunThread(SThreadObject *pThreadManager)
    {
    #ifdef LINUX
        pthread_attr_t oAttr;
        pthread_attr_init(&oAttr);
        pthread_attr_setdetachstate(&oAttr,PTHREAD_CREATE_DETACHED);
        int nResule = pthread_create(&(pThreadManager->m_hThreadHandle),&oAttr,_ThreadContainerFun,pThreadManager);
        pthread_attr_destroy(&oAttr);
        if (nResult == 0)
        {
            pThreadManager->m_eThreadState = SThreadObject::THREAD_RUNNING;
            return true;
        }
        else
            return false;
    #endif
    #ifdef WIN32
        pThreadManager->m_hThreadHandle = (HANDLE)_beginthreadex(NULL,0,_ThreadContainerFun,pThreadManager,0,NULL);
        if (pThreadManager->m_hThreadHandle != 0)
        {
            pThreadManager->m_eThreadState = SThreadObject::THREAD_RUNNING;
            return true;
        }
        else
            return false;
    #endif
    }

    /*
     * 【仅本文件内使用】【Win32下为内联函数】中断指定线程运行
     * @param SThreadObject *pThreadManager,有效的线程管理对象指针
     * @return bool,返回是否成功中断线程执行（如果线程本身未创建或执行完成，返回false）
     */
    #ifdef WIN32
    inline 
    #endif
        bool _Terminate_Thread(SThreadObject *pThreadManager)
    {
        if (pThreadManager->m_eThreadState != SThreadObject::THREAD_RUNNING)
            return false;
    #ifdef LINUX
        if (pthread_cancel(pThreadManager->m_hThreadHandle) == 0)
        {
            void *pRes;
            if (pthread_join(pThreadManager->m_hThreadHandle,&pRes) == 0 && pRes == PTHREAD_CANCELED)
            {
                pThreadManager->m_eThreadState = SThreadObject::THREAD_TERMINAL;
                return true;
            }
        }
        return false;
    #endif
    #ifdef WIN32
        if (TerminateThread(pThreadManager->m_hThreadHandle,0) != false)
        {
            pThreadManager->m_eThreadState = SThreadObject::THREAD_TERMINAL;
            return true;
        }
        else
            return false;
    #endif
    }

    /*
     * 【公开】创建新的线程管理对象
     * @param void*(*fTargetFunP)(void *),线程执行函数指针
     * @param bool bAutoRelease,是否在线程执行完成后自动释放线程管理对象，如果没打算对本函数创建的对象进行其它操作，此参数一定要设置为true，否则会造成内存泄漏
     * @parma void *pParam = NULL,传入给线程的参数指针
     * @parma bool bSuspend = false,是否创建对象后先不执行线程，默认为否
     * @return void *,返回创建的线程管理结构指针，创建失败返回NULL
     */
    void *CreateThreadManager(void*(*fTargetFunP)(void *),bool bAutoRelease,void *pParam,bool bSuspend)
    {
        SThreadObject *pNewThreadObject = new SThreadObject;
        if (pNewThreadObject == NULL)//对旧式代码new分配失败返回NULL这一处理的兼容
            return NULL;
        pNewThreadObject->m_fExeFunc = fTargetFunP;
        pNewThreadObject->m_pParam = pParam;
        pNewThreadObject->m_eThreadState = SThreadObject::THREAD_UNCREATE;
        pNewThreadObject->m_bAutoRelease = bAutoRelease;
        pNewThreadObject->m_pReturn = NULL;
        //线程管理对象创建后的处理
        if (bSuspend == false && _CreateAndRunThread(pNewThreadObject) == false)
        {
            delete pNewThreadObject;
            return NULL;
        }
        else
            return pNewThreadObject;
    }

    /*
     * 【公开】【内联】使当前线程休眠指定的时间
     * @param unsigned long lMs,休眠的毫秒数
     * @return void
     */
    void Sleep_Thread(unsigned long lMs)
    {
    #ifdef LINUX
        usleep(lMs * 1000);
    #endif
    #ifdef WIN32
        Sleep(lMs);
    #endif
    }

    /*
     * 【公开】启动指定线程
     * @param void *pThreadManager,要操作线程对应的线程管理对象指针
     * @param bool bRestartWhenRunning = false,指定当线程已在运行中时，是否中断当前运行重新开始，默认为否
     * @return bool,返回启动结果，当线程成功运行（包括bRestartWhenRunning = false时线程正在运行中的情况）后返回true
     */
    bool Start_Thread(void *pThreadManager,bool bRestartWhenRunning)
    {
        if (pThreadManager == NULL)
            return false;
        SThreadObject *pThreadM = (SThreadObject *)pThreadManager;
        if (bRestartWhenRunning == true && pThreadM->m_eThreadState == SThreadObject::THREAD_RUNNING)
            _Terminate_Thread(pThreadM);
        if (pThreadM->m_eThreadState != SThreadObject::THREAD_RUNNING)
        {
            if (_CreateAndRunThread(pThreadM) == true)
                return true;
            else
                return false;
        }
        else
            return true;
    }

    /*
     * 【公开】等待指定线程结束运行
     * @param void *pThreadManager,要操作线程对应的线程管理对象指针
     * @param void *,返回指定线程执行完成时的返回数据
     */
    void *Join_Thread(void *pThreadManager)
    {
        if (pThreadManager == NULL)
            return false;
        SThreadObject *pThreadM = (SThreadObject *)pThreadManager;
        while (pThreadM->m_eThreadState == SThreadObject::THREAD_RUNNING)
            Sleep_Thread(5);
        return pThreadM->m_pReturn;
    }

    /*
     * 【公开】中断指定线程执行，此函数并不会释放线程管理资源，必须调用ReleaseThreadManager释放
     * @param void *pThreadManager,要操作线程对应的线程管理对象指针
     * @param void *pThreadReturn,线程中断后返回的数据，该设置的数据可通过Join_Thread函数获取
     * @param bool,返回是否成功中断指定线程
     */
    bool Terminate_Thread(void *pThreadManager,void *pThreadReturn)
    {
        if (pThreadManager == NULL)
            return false;
        SThreadObject *pThreadM = (SThreadObject *)pThreadManager;
        if (pThreadM->m_eThreadState == SThreadObject::THREAD_RUNNING && _Terminate_Thread(pThreadM) == true)
        {
            pThreadM->m_pReturn = pThreadReturn;
            return true;
        }
        else
            return false;
    }

    /*
     * 【公开】释放指定线程管理对象
     * @param void *pThreadManager,要操作线程对应的线程管理对象指针
     * @return void
     */
    void ReleaseThreadManager(void *pThreadManager)
    {
        if (pThreadManager != NULL)
        {
            SThreadObject *pThreadM = (SThreadObject *)pThreadManager;
            if (pThreadM->m_eThreadState == SThreadObject::THREAD_RUNNING)
                _Terminate_Thread(pThreadM);
            delete pThreadM;
        }
    }

    /*
     * 【公开】尝试进入临界区，并在特定条件下停止尝试
     * @param CRITICAL_SECTION *pSectionLock,临界区对象指针
     * @param bool &rExitFlag,控制函数退出条件的变量，当此变量为true时还未能成功进入临界区，则将终止尝试，函数退出
     * @param unsigned long lWaitMs = 5,两次尝试间的等待间隔
     * @return bool,返回进入结果，成功进入返回true
     */
    bool TryEnterCS(CRITICAL_SECTION *pSectionLock,bool &rExitFlag,unsigned long lWaitMs)
    {
        if (pSectionLock != NULL)
        {
            while (rExitFlag == false)
            {
    #ifdef LINUX
                if (pthread_mutex_trylock(pSectionLock) == 0)
    #endif
    #ifdef WIN32
                if (TryEnterCriticalSection(pSectionLock) != false)
    #endif
                    return true;
                else
                    Sleep_Thread(lWaitMs);
            }
        }
        return false;
    }

    /*
     * 【公开】尝试进入临界区，当尝试次数达nTryCount时退出
     * @param CRITICAL_SECTION *pSectionLock,临界区对象指针
     * @param unsigned int nTryCount = 1,尝试进入临界区的尝试次数，设置值必须大于1
     * @param unsigned long lWaitMs = 5,两次尝试间的等待间隔
     * @return bool,返回进入结果，成功进入返回true
     */
    bool TryEnterCS(CRITICAL_SECTION *pSectionLock,unsigned int nTryCount,unsigned long lWaitMs)
    {
        if (pSectionLock != NULL)
        {
            while (nTryCount > 0)
            {
    #ifdef LINUX
                if (pthread_mutex_trylock(pSectionLock) == 0)
    #endif
    #ifdef WIN32
                if (TryEnterCriticalSection(pSectionLock) != false)
    #endif
                    return true;
                Sleep_Thread(lWaitMs);
                --nTryCount;
            }
        }
        return false;
    }
};
