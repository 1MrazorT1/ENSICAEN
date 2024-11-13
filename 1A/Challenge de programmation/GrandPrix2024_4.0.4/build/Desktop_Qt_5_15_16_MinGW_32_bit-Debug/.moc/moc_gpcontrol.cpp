/****************************************************************************
** Meta object code from reading C++ file 'gpcontrol.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../include/gpcontrol.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gpcontrol.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GPControl_t {
    QByteArrayData data[21];
    char stringdata0[236];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GPControl_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GPControl_t qt_meta_stringdata_GPControl = {
    {
QT_MOC_LITERAL(0, 0, 9), // "GPControl"
QT_MOC_LITERAL(1, 10, 8), // "carMoved"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 3), // "car"
QT_MOC_LITERAL(4, 24, 17), // "carMovedWithBoost"
QT_MOC_LITERAL(5, 42, 13), // "driverTimeout"
QT_MOC_LITERAL(6, 56, 13), // "driverCrashed"
QT_MOC_LITERAL(7, 70, 13), // "driverStopped"
QT_MOC_LITERAL(8, 84, 11), // "invalidMove"
QT_MOC_LITERAL(9, 96, 12), // "Acceleration"
QT_MOC_LITERAL(10, 109, 11), // "syntaxError"
QT_MOC_LITERAL(11, 121, 3), // "end"
QT_MOC_LITERAL(12, 125, 3), // "res"
QT_MOC_LITERAL(13, 129, 13), // "newStderrData"
QT_MOC_LITERAL(14, 143, 11), // "setFirstCar"
QT_MOC_LITERAL(15, 155, 8), // "nextMove"
QT_MOC_LITERAL(16, 164, 8), // "setSteps"
QT_MOC_LITERAL(17, 173, 5), // "steps"
QT_MOC_LITERAL(18, 179, 23), // "readyReadStandardOutput"
QT_MOC_LITERAL(19, 203, 24), // "onReadyReadStandardError"
QT_MOC_LITERAL(20, 228, 7) // "timeout"

    },
    "GPControl\0carMoved\0\0car\0carMovedWithBoost\0"
    "driverTimeout\0driverCrashed\0driverStopped\0"
    "invalidMove\0Acceleration\0syntaxError\0"
    "end\0res\0newStderrData\0setFirstCar\0"
    "nextMove\0setSteps\0steps\0readyReadStandardOutput\0"
    "onReadyReadStandardError\0timeout"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GPControl[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   94,    2, 0x06 /* Public */,
       4,    1,   97,    2, 0x06 /* Public */,
       5,    0,  100,    2, 0x06 /* Public */,
       6,    1,  101,    2, 0x06 /* Public */,
       7,    1,  104,    2, 0x06 /* Public */,
       8,    1,  107,    2, 0x06 /* Public */,
      10,    0,  110,    2, 0x06 /* Public */,
      11,    1,  111,    2, 0x06 /* Public */,
      13,    1,  114,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    0,  117,    2, 0x0a /* Public */,
      15,    0,  118,    2, 0x0a /* Public */,
      16,    1,  119,    2, 0x0a /* Public */,
      16,    0,  122,    2, 0x2a /* Public | MethodCloned */,
      18,    0,  123,    2, 0x08 /* Private */,
      19,    1,  124,    2, 0x08 /* Private */,
      20,    0,  127,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

       0        // eod
};

void GPControl::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GPControl *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->carMoved((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->carMovedWithBoost((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->driverTimeout(); break;
        case 3: _t->driverCrashed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->driverStopped((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->invalidMove((*reinterpret_cast< Acceleration(*)>(_a[1]))); break;
        case 6: _t->syntaxError(); break;
        case 7: _t->end((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->newStderrData((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->setFirstCar(); break;
        case 10: _t->nextMove(); break;
        case 11: _t->setSteps((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->setSteps(); break;
        case 13: _t->readyReadStandardOutput(); break;
        case 14: _t->onReadyReadStandardError((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->timeout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GPControl::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPControl::carMoved)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GPControl::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPControl::carMovedWithBoost)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GPControl::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPControl::driverTimeout)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GPControl::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPControl::driverCrashed)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (GPControl::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPControl::driverStopped)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (GPControl::*)(Acceleration );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPControl::invalidMove)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (GPControl::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPControl::syntaxError)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (GPControl::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPControl::end)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (GPControl::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GPControl::newStderrData)) {
                *result = 8;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GPControl::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_GPControl.data,
    qt_meta_data_GPControl,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GPControl::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GPControl::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GPControl.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GPControl::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void GPControl::carMoved(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GPControl::carMovedWithBoost(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GPControl::driverTimeout()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void GPControl::driverCrashed(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void GPControl::driverStopped(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void GPControl::invalidMove(Acceleration _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void GPControl::syntaxError()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void GPControl::end(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void GPControl::newStderrData(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
