/****************************************************************************
** Meta object code from reading C++ file 'calendarwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Calendar/src/calendarwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'calendarwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CalendarWidget_t {
    QByteArrayData data[15];
    char stringdata0[210];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CalendarWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CalendarWidget_t qt_meta_stringdata_CalendarWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "CalendarWidget"
QT_MOC_LITERAL(1, 15, 16), // "changeClockStyle"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 25), // "QtClockWidget::ClockStyle"
QT_MOC_LITERAL(4, 59, 5), // "style"
QT_MOC_LITERAL(5, 65, 21), // "SltCurrentPageChanged"
QT_MOC_LITERAL(6, 87, 5), // "index"
QT_MOC_LITERAL(7, 93, 13), // "SltChangePage"
QT_MOC_LITERAL(8, 107, 9), // "direction"
QT_MOC_LITERAL(9, 117, 17), // "SltBtnBackClicked"
QT_MOC_LITERAL(10, 135, 13), // "SltBtnSetting"
QT_MOC_LITERAL(11, 149, 21), // "SltCurrentDateChanged"
QT_MOC_LITERAL(12, 171, 4), // "date"
QT_MOC_LITERAL(13, 176, 19), // "SltChangeClockStyle"
QT_MOC_LITERAL(14, 196, 13) // "SltBtnClicked"

    },
    "CalendarWidget\0changeClockStyle\0\0"
    "QtClockWidget::ClockStyle\0style\0"
    "SltCurrentPageChanged\0index\0SltChangePage\0"
    "direction\0SltBtnBackClicked\0SltBtnSetting\0"
    "SltCurrentDateChanged\0date\0"
    "SltChangeClockStyle\0SltBtnClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CalendarWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   57,    2, 0x08 /* Private */,
       7,    2,   60,    2, 0x08 /* Private */,
       9,    0,   65,    2, 0x08 /* Private */,
      10,    0,   66,    2, 0x08 /* Private */,
      11,    1,   67,    2, 0x08 /* Private */,
      13,    1,   70,    2, 0x08 /* Private */,
      14,    1,   73,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    6,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QDate,   12,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    6,

       0        // eod
};

void CalendarWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CalendarWidget *_t = static_cast<CalendarWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeClockStyle((*reinterpret_cast< QtClockWidget::ClockStyle(*)>(_a[1]))); break;
        case 1: _t->SltCurrentPageChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->SltChangePage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 3: _t->SltBtnBackClicked(); break;
        case 4: _t->SltBtnSetting(); break;
        case 5: _t->SltCurrentDateChanged((*reinterpret_cast< const QDate(*)>(_a[1]))); break;
        case 6: _t->SltChangeClockStyle((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->SltBtnClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CalendarWidget::*)(QtClockWidget::ClockStyle );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CalendarWidget::changeClockStyle)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CalendarWidget::staticMetaObject = {
    { &QtAnimationWidget::staticMetaObject, qt_meta_stringdata_CalendarWidget.data,
      qt_meta_data_CalendarWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CalendarWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CalendarWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CalendarWidget.stringdata0))
        return static_cast<void*>(this);
    return QtAnimationWidget::qt_metacast(_clname);
}

int CalendarWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtAnimationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void CalendarWidget::changeClockStyle(QtClockWidget::ClockStyle _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
