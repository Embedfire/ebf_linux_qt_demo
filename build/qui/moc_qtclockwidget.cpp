/****************************************************************************
** Meta object code from reading C++ file 'qtclockwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QtUi/src/qtclockwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtclockwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QtClockWidget_t {
    QByteArrayData data[10];
    char stringdata0[112];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtClockWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtClockWidget_t qt_meta_stringdata_QtClockWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "QtClockWidget"
QT_MOC_LITERAL(1, 14, 13), // "signalClicked"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 5), // "index"
QT_MOC_LITERAL(4, 35, 9), // "direction"
QT_MOC_LITERAL(5, 45, 6), // "resize"
QT_MOC_LITERAL(6, 52, 13), // "SetClockStyle"
QT_MOC_LITERAL(7, 66, 25), // "QtClockWidget::ClockStyle"
QT_MOC_LITERAL(8, 92, 5), // "style"
QT_MOC_LITERAL(9, 98, 13) // "SltUpdateTime"

    },
    "QtClockWidget\0signalClicked\0\0index\0"
    "direction\0resize\0SetClockStyle\0"
    "QtClockWidget::ClockStyle\0style\0"
    "SltUpdateTime"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtClockWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   44,    2, 0x06 /* Public */,
       1,    2,   51,    2, 0x26 /* Public | MethodCloned */,
       1,    1,   56,    2, 0x26 /* Public | MethodCloned */,
       1,    0,   59,    2, 0x26 /* Public | MethodCloned */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   60,    2, 0x0a /* Public */,
       9,    0,   63,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::Int,    3,    4,    5,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,

       0        // eod
};

void QtClockWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QtClockWidget *_t = static_cast<QtClockWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->signalClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->signalClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->signalClicked(); break;
        case 4: _t->SetClockStyle((*reinterpret_cast< QtClockWidget::ClockStyle(*)>(_a[1]))); break;
        case 5: _t->SltUpdateTime(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QtClockWidget::*)(int , int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtClockWidget::signalClicked)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QtClockWidget::staticMetaObject = {
    { &QtWidgetBase::staticMetaObject, qt_meta_stringdata_QtClockWidget.data,
      qt_meta_data_QtClockWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QtClockWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtClockWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QtClockWidget.stringdata0))
        return static_cast<void*>(this);
    return QtWidgetBase::qt_metacast(_clname);
}

int QtClockWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtWidgetBase::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void QtClockWidget::signalClicked(int _t1, int _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
