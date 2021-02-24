/****************************************************************************
** Meta object code from reading C++ file 'settingmainpage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Settings/src/settingmainpage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'settingmainpage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SettingMainPage_t {
    QByteArrayData data[9];
    char stringdata0[123];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SettingMainPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SettingMainPage_t qt_meta_stringdata_SettingMainPage = {
    {
QT_MOC_LITERAL(0, 0, 15), // "SettingMainPage"
QT_MOC_LITERAL(1, 16, 16), // "signalChangePage"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 5), // "index"
QT_MOC_LITERAL(4, 40, 23), // "signalChangeCursorShape"
QT_MOC_LITERAL(5, 64, 15), // "Qt::CursorShape"
QT_MOC_LITERAL(6, 80, 16), // "SltSwitchClicked"
QT_MOC_LITERAL(7, 97, 2), // "on"
QT_MOC_LITERAL(8, 100, 22) // "SltCurrentIndexClicked"

    },
    "SettingMainPage\0signalChangePage\0\0"
    "index\0signalChangeCursorShape\0"
    "Qt::CursorShape\0SltSwitchClicked\0on\0"
    "SltCurrentIndexClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SettingMainPage[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    1,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   40,    2, 0x08 /* Private */,
       8,    1,   43,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 5,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void SettingMainPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SettingMainPage *_t = static_cast<SettingMainPage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalChangePage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->signalChangeCursorShape((*reinterpret_cast< Qt::CursorShape(*)>(_a[1]))); break;
        case 2: _t->SltSwitchClicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->SltCurrentIndexClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SettingMainPage::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingMainPage::signalChangePage)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SettingMainPage::*)(Qt::CursorShape );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SettingMainPage::signalChangeCursorShape)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SettingMainPage::staticMetaObject = {
    { &QtListWidget::staticMetaObject, qt_meta_stringdata_SettingMainPage.data,
      qt_meta_data_SettingMainPage,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *SettingMainPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SettingMainPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SettingMainPage.stringdata0))
        return static_cast<void*>(this);
    return QtListWidget::qt_metacast(_clname);
}

int SettingMainPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtListWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void SettingMainPage::signalChangePage(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SettingMainPage::signalChangeCursorShape(Qt::CursorShape _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
