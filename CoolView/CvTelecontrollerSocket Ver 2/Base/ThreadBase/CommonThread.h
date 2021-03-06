/*
 * 线程操作类声明文件 By Lzy
 * 2012-06-28	V2.0.0.2	修正ReleaseCS函数没把CRITICAL_SECTION对象释放的问题
 * 2011-12-08   V2.0.0.1    1、把CreateCS,ReleaseCS,EnterCS,ExitCS函数设置为内联函数
 *                          2、创建线程管理对象时允许设置是否线程运行完后自动释放，同时线程执行容器函数中增加相应支持
 * 2011-12-05   V2.0.0.0    把原来用类封装改成用命名空间封装，省去了线程链的维护
 * 2011-04-13   V0.0.0.0    创建文件
 */

#ifndef COMMONTHREAD_H
#define COMMONTHREAD_H

#ifdef LINUX
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
typedef pthread_t HANDLE;
typedef pthread_mutex_t CRITICAL_SECTION;
#endif
#ifdef WIN32
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif

#include <windows.h>
#include <process.h>
#endif

namespace thread_operation
{
    //------线程操作函数------
    void *CreateThreadManager(void*(*fTargetFunP)(void *),bool bAutoRelease,void *pParam = NULL,bool bSuspend = false);//创建新的线程管理对象
    bool Start_Thread(void *pThreadManager,bool bRestartWhenRunning = false);//启动指定线程
    void *Join_Thread(void *pThreadManager);//等待指定线程结束运行
    bool Terminate_Thread(void *pThreadManager,void *pThreadReturn);//中断指定线程执行
    inline void Sleep_Thread(unsigned long lMs);//使当前线程休眠指定的时间
    void ReleaseThreadManager(void *pThreadManager);//释放指定线程管理对象

    //------临界区操作函数------
    inline CRITICAL_SECTION *CreateCS();//创建新的临界区
    inline void ReleaseCS(CRITICAL_SECTION *pSectionLock);//释放临界区
    inline bool EnterCS(CRITICAL_SECTION *pSectionLock);//进入临界区
    bool TryEnterCS(CRITICAL_SECTION *pSectionLock,bool &rExitFlag,unsigned long lWaitMs = 5);//尝试进入临界区，并在特定条件下停止尝试
    bool TryEnterCS(CRITICAL_SECTION *pSectionLock,unsigned int nTryCount = 1,unsigned long lWaitMs = 5);//尝试进入临界区，当尝试次数达nTryCount时退出
    inline void ExitCS(CRITICAL_SECTION *pSectionLock);//退出临界区
};

/*********************************************空间中的内联函数定义*************************************************/

/*
 * 【公开】【内联】创建新的临界区
 * @return CRITICAL_SECTION *,返回临界区对象指针
 */
CRITICAL_SECTION *thread_operation::CreateCS()
{
    CRITICAL_SECTION *pNewCS = new CRITICAL_SECTION;
#ifdef LINUX
    if (pthread_mutex_init(pNewCS,NULL) != 0)
    {
        delete pNewCS;
        pNewCS = NULL;
    }
#endif
#ifdef WIN32
    InitializeCriticalSection(pNewCS);
#endif
    return pNewCS;
}

/*
 * 【公开】【内联】释放临界区
 * @param CRITICAL_SECTION *pSectionLock,临界区对象指针
 * @return void
 */
void thread_operation::ReleaseCS(CRITICAL_SECTION *pSectionLock)
{
    if (pSectionLock != NULL)
    {
#ifdef LINUX
        pthread_mutex_destroy(pSectionLock);
#endif
#ifdef WIN32
        DeleteCriticalSection(pSectionLock);
#endif
		delete pSectionLock;
    }
}

/*
 * 【公开】【内联】进入临界区
 * @param CRITICAL_SECTION *pSectionLock,临界区对象指针
 * @return bool,对于Win32这里恒返回true，linux下则可能返回false
 */
bool thread_operation::EnterCS(CRITICAL_SECTION *pSectionLock)
{
    if (pSectionLock != NULL)
    {
#ifdef LINUX
        return !(pthread_mutex_lock(pSectionLock));
#endif
#ifdef WIN32
        EnterCriticalSection(pSectionLock);
        return true;
#endif
    }
    return false;
}

/*
 * 【公开】【内联】退出临界区
 * @param CRITICAL_SECTION *pSectionLock,临界区对象指针
 * @return void
 */
void thread_operation::ExitCS(CRITICAL_SECTION *pSectionLock)
{
    if (pSectionLock != NULL)
    {
#ifdef LINUX
        pthread_mutex_unlock(pSectionLock);
#endif
#ifdef WIN32
        LeaveCriticalSection(pSectionLock);
#endif
    }
}

#endif
