/****************************************************************************
** Meta object code from reading C++ file 'threadservice.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.10)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../myTicketSalesSystem_Version/QTServer_V3/threadservice.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'threadservice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.10. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ThreadService_t {
    QByteArrayData data[10];
    char stringdata0[118];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ThreadService_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ThreadService_t qt_meta_stringdata_ThreadService = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ThreadService"
QT_MOC_LITERAL(1, 14, 21), // "informOpThreadDealMsg"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 11), // "QTcpSocket&"
QT_MOC_LITERAL(4, 49, 6), // "client"
QT_MOC_LITERAL(5, 56, 12), // "InfoProcess&"
QT_MOC_LITERAL(6, 69, 11), // "infoProcess"
QT_MOC_LITERAL(7, 81, 16), // "TicketOperation&"
QT_MOC_LITERAL(8, 98, 8), // "ticketOp"
QT_MOC_LITERAL(9, 107, 10) // "dealNewMsg"

    },
    "ThreadService\0informOpThreadDealMsg\0"
    "\0QTcpSocket&\0client\0InfoProcess&\0"
    "infoProcess\0TicketOperation&\0ticketOp\0"
    "dealNewMsg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ThreadService[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   31,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 5, 0x80000000 | 7,    4,    6,    8,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void ThreadService::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ThreadService *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->informOpThreadDealMsg((*reinterpret_cast< QTcpSocket(*)>(_a[1])),(*reinterpret_cast< InfoProcess(*)>(_a[2])),(*reinterpret_cast< TicketOperation(*)>(_a[3]))); break;
        case 1: _t->dealNewMsg(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ThreadService::*)(QTcpSocket & , InfoProcess & , TicketOperation & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ThreadService::informOpThreadDealMsg)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ThreadService::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_ThreadService.data,
    qt_meta_data_ThreadService,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ThreadService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ThreadService::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ThreadService.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ThreadService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ThreadService::informOpThreadDealMsg(QTcpSocket & _t1, InfoProcess & _t2, TicketOperation & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
