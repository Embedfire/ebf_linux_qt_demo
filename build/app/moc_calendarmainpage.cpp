/****************************************************************************
** Meta object code from reading C++ file 'calendarmainpage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Calendar/src/calendarmainpage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'calendarmainpage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CalendarMainPage_t {
    QByteArrayData data[10];
    char stringdata0[123];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CalendarMainPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CalendarMainPage_t qt_meta_stringdata_CalendarMainPage = {
    {
QT_MOC_LITERAL(0, 0, 16), // "CalendarMainPage"
QT_MOC_LITERAL(1, 17, 17), // "changeCurrentPage"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 5), // "index"
QT_MOC_LITERAL(4, 42, 9), // "direction"
QT_MOC_LITERAL(5, 52, 18), // "signalChangeApMode"
QT_MOC_LITERAL(6, 71, 2), // "on"
QT_MOC_LITERAL(7, 74, 16), // "changeClockStyle"
QT_MOC_LITERAL(8, 91, 25), // "QtClockWidget::ClockStyle"
QT_MOC_LITERAL(9, 117, 5) // "style"

    },
    "CalendarMainPage\0changeCurrentPage\0\0"
    "index\0direction\0signalChangeApMode\0"
    "on\0changeClockStyle\0QtClockWidget::ClockStyle\0"
    "style"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CalendarMainPage[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,
       5,    1,   34,    2, 0x06 /* Public */,
       7,    1,   37,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void, 0x80000000 | 8,    9,

       0        // eod
};

void CalendarMainPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CalendarMainPage *_t = static_cast<CalendarMainPage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeCurrentPage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->signalChangeApMode((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->changeClockStyle((*reinterpret_cast< QtClockWidget::ClockStyle(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CalendarMainPage::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CalendarMainPage::changeCurrentPage)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CalendarMainPage::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CalendarMainPage::signalChangeApMode)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CalendarMainPage::*)(QtClockWidget::ClockStyle );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CalendarMainPage::changeClockStyle)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CalendarMainPage::staticMetaObject = {
    { &QtWidgetBase::staticMetaObject, qt_meta_stringdata_CalendarMainPage.data,
      qt_meta_data_CalendarMainPage,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CalendarMainPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CalendarMainPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CalendarMainPage.stringdata0))
        return static_cast<void*>(this);
    return QtWidgetBase::qt_metacast(_clname);
}

int CalendarMainPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtWidgetBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CalendarMainPage::changeCurrentPage(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CalendarMainPage::signalChangeApMode(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CalendarMainPage::changeClockStyle(QtClockWidget::ClockStyle _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
