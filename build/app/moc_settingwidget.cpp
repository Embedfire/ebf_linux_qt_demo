/****************************************************************************
** Meta object code from reading C++ file 'settingwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Settings/src/settingwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settingwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SettingWidget_t {
    QByteArrayData data[9];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SettingWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SettingWidget_t qt_meta_stringdata_SettingWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "SettingWidget"
QT_MOC_LITERAL(1, 14, 23), // "signalChangeCursorShape"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 15), // "Qt::CursorShape"
QT_MOC_LITERAL(4, 55, 17), // "SltToolBtnClicked"
QT_MOC_LITERAL(5, 73, 5), // "index"
QT_MOC_LITERAL(6, 79, 17), // "SltBtnBackClicked"
QT_MOC_LITERAL(7, 97, 21), // "SltCurrentPageChanged"
QT_MOC_LITERAL(8, 119, 13) // "SltChangePage"

    },
    "SettingWidget\0signalChangeCursorShape\0"
    "\0Qt::CursorShape\0SltToolBtnClicked\0"
    "index\0SltBtnBackClicked\0SltCurrentPageChanged\0"
    "SltChangePage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SettingWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   42,    2, 0x08 /* Private */,
       6,    0,   45,    2, 0x08 /* Private */,
       7,    1,   46,    2, 0x08 /* Private */,
       8,    1,   49,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::Int,    5,

       0        // eod
};

void SettingWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SettingWidget *_t = static_cast<SettingWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalChangeCursorShape((*reinterpret_cast< Qt::CursorShape(*)>(_a[1]))); break;
        case 1: _t->SltToolBtnClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->SltBtnBackClicked(); break;
        case 3: _t->SltCurrentPageChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->SltChangePage((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SettingWidget::*)(Qt::CursorShape );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingWidget::signalChangeCursorShape)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SettingWidget::staticMetaObject = {
    { &QtAnimationWidget::staticMetaObject, qt_meta_stringdata_SettingWidget.data,
      qt_meta_data_SettingWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SettingWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SettingWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SettingWidget.stringdata0))
        return static_cast<void*>(this);
    return QtAnimationWidget::qt_metacast(_clname);
}

int SettingWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtAnimationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void SettingWidget::signalChangeCursorShape(Qt::CursorShape _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
