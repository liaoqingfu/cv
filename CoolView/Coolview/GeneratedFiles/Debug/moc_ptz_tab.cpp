/****************************************************************************
** Meta object code from reading C++ file 'ptz_tab.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ptz_tab.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ptz_tab.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_PtzTab_t {
    QByteArrayData data[16];
    char stringdata[227];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PtzTab_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PtzTab_t qt_meta_stringdata_PtzTab = {
    {
QT_MOC_LITERAL(0, 0, 6), // "PtzTab"
QT_MOC_LITERAL(1, 7, 25), // "setCameraAddressLedSignal"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 5), // "index"
QT_MOC_LITERAL(4, 40, 20), // "setPtzProtocolSignal"
QT_MOC_LITERAL(5, 61, 13), // "protocol_type"
QT_MOC_LITERAL(6, 75, 13), // "openComSignal"
QT_MOC_LITERAL(7, 89, 14), // "closeComSignal"
QT_MOC_LITERAL(8, 104, 11), // "setNumOfCam"
QT_MOC_LITERAL(9, 116, 7), // "openCom"
QT_MOC_LITERAL(10, 124, 8), // "closeCom"
QT_MOC_LITERAL(11, 133, 17), // "showComIsOpenSlot"
QT_MOC_LITERAL(12, 151, 16), // "showComErrorSlot"
QT_MOC_LITERAL(13, 168, 28), // "QSerialPort::SerialPortError"
QT_MOC_LITERAL(14, 197, 5), // "error"
QT_MOC_LITERAL(15, 203, 23) // "showComSettingErrorSlot"

    },
    "PtzTab\0setCameraAddressLedSignal\0\0"
    "index\0setPtzProtocolSignal\0protocol_type\0"
    "openComSignal\0closeComSignal\0setNumOfCam\0"
    "openCom\0closeCom\0showComIsOpenSlot\0"
    "showComErrorSlot\0QSerialPort::SerialPortError\0"
    "error\0showComSettingErrorSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PtzTab[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    1,   67,    2, 0x06 /* Public */,
       6,    0,   70,    2, 0x06 /* Public */,
       7,    0,   71,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   72,    2, 0x08 /* Private */,
       9,    0,   75,    2, 0x08 /* Private */,
      10,    0,   76,    2, 0x08 /* Private */,
      11,    0,   77,    2, 0x08 /* Private */,
      12,    1,   78,    2, 0x08 /* Private */,
      15,    0,   81,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::UChar,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void,

       0        // eod
};

void PtzTab::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PtzTab *_t = static_cast<PtzTab *>(_o);
        switch (_id) {
        case 0: _t->setCameraAddressLedSignal((*reinterpret_cast< unsigned char(*)>(_a[1]))); break;
        case 1: _t->setPtzProtocolSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->openComSignal(); break;
        case 3: _t->closeComSignal(); break;
        case 4: _t->setNumOfCam((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->openCom(); break;
        case 6: _t->closeCom(); break;
        case 7: _t->showComIsOpenSlot(); break;
        case 8: _t->showComErrorSlot((*reinterpret_cast< QSerialPort::SerialPortError(*)>(_a[1]))); break;
        case 9: _t->showComSettingErrorSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PtzTab::*_t)(unsigned char );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PtzTab::setCameraAddressLedSignal)) {
                *result = 0;
            }
        }
        {
            typedef void (PtzTab::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PtzTab::setPtzProtocolSignal)) {
                *result = 1;
            }
        }
        {
            typedef void (PtzTab::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PtzTab::openComSignal)) {
                *result = 2;
            }
        }
        {
            typedef void (PtzTab::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PtzTab::closeComSignal)) {
                *result = 3;
            }
        }
    }
}

const QMetaObject PtzTab::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_PtzTab.data,
      qt_meta_data_PtzTab,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *PtzTab::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PtzTab::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_PtzTab.stringdata))
        return static_cast<void*>(const_cast< PtzTab*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int PtzTab::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void PtzTab::setCameraAddressLedSignal(unsigned char _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PtzTab::setPtzProtocolSignal(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PtzTab::openComSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void PtzTab::closeComSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
