/****************************************************************************
** Meta object code from reading C++ file 'widgettoolbar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../MusicPlayer/src/widgettoolbar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widgettoolbar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WidgetToolBar_t {
    QByteArrayData data[15];
    char stringdata0[154];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WidgetToolBar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WidgetToolBar_t qt_meta_stringdata_WidgetToolBar = {
    {
QT_MOC_LITERAL(0, 0, 13), // "WidgetToolBar"
QT_MOC_LITERAL(1, 14, 4), // "play"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 4), // "stop"
QT_MOC_LITERAL(4, 25, 5), // "pause"
QT_MOC_LITERAL(5, 31, 4), // "next"
QT_MOC_LITERAL(6, 36, 8), // "previous"
QT_MOC_LITERAL(7, 45, 18), // "currentMuteChanged"
QT_MOC_LITERAL(8, 64, 5), // "value"
QT_MOC_LITERAL(9, 70, 14), // "toolBarClicked"
QT_MOC_LITERAL(10, 85, 5), // "index"
QT_MOC_LITERAL(11, 91, 21), // "currentPostionChanged"
QT_MOC_LITERAL(12, 113, 8), // "postiion"
QT_MOC_LITERAL(13, 122, 17), // "SltBtnPlayClicked"
QT_MOC_LITERAL(14, 140, 13) // "SltBtnClicket"

    },
    "WidgetToolBar\0play\0\0stop\0pause\0next\0"
    "previous\0currentMuteChanged\0value\0"
    "toolBarClicked\0index\0currentPostionChanged\0"
    "postiion\0SltBtnPlayClicked\0SltBtnClicket"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WidgetToolBar[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    0,   65,    2, 0x06 /* Public */,
       4,    0,   66,    2, 0x06 /* Public */,
       5,    0,   67,    2, 0x06 /* Public */,
       6,    0,   68,    2, 0x06 /* Public */,
       7,    1,   69,    2, 0x06 /* Public */,
       9,    1,   72,    2, 0x06 /* Public */,
      11,    1,   75,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,   78,    2, 0x08 /* Private */,
      14,    1,   79,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   12,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,

       0        // eod
};

void WidgetToolBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        WidgetToolBar *_t = static_cast<WidgetToolBar *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->play(); break;
        case 1: _t->stop(); break;
        case 2: _t->pause(); break;
        case 3: _t->next(); break;
        case 4: _t->previous(); break;
        case 5: _t->currentMuteChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->toolBarClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->currentPostionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->SltBtnPlayClicked(); break;
        case 9: _t->SltBtnClicket((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WidgetToolBar::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WidgetToolBar::play)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WidgetToolBar::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WidgetToolBar::stop)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WidgetToolBar::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WidgetToolBar::pause)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (WidgetToolBar::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WidgetToolBar::next)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (WidgetToolBar::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WidgetToolBar::previous)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (WidgetToolBar::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WidgetToolBar::currentMuteChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (WidgetToolBar::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WidgetToolBar::toolBarClicked)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (WidgetToolBar::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WidgetToolBar::currentPostionChanged)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WidgetToolBar::staticMetaObject = {
    { &QtWidgetBase::staticMetaObject, qt_meta_stringdata_WidgetToolBar.data,
      qt_meta_data_WidgetToolBar,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *WidgetToolBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WidgetToolBar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WidgetToolBar.stringdata0))
        return static_cast<void*>(this);
    return QtWidgetBase::qt_metacast(_clname);
}

int WidgetToolBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtWidgetBase::qt_metacall(_c, _id, _a);
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
void WidgetToolBar::play()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void WidgetToolBar::stop()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void WidgetToolBar::pause()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void WidgetToolBar::next()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void WidgetToolBar::previous()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void WidgetToolBar::currentMuteChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void WidgetToolBar::toolBarClicked(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void WidgetToolBar::currentPostionChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
