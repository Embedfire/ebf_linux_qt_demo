/****************************************************************************
** Meta object code from reading C++ file 'qtplaytoolbar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../VideoPlayer/src/qtplaytoolbar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtplaytoolbar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PlayTitleBarWidget_t {
    QByteArrayData data[5];
    char stringdata0[44];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlayTitleBarWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlayTitleBarWidget_t qt_meta_stringdata_PlayTitleBarWidget = {
    {
QT_MOC_LITERAL(0, 0, 18), // "PlayTitleBarWidget"
QT_MOC_LITERAL(1, 19, 10), // "signalBack"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 7), // "SetText"
QT_MOC_LITERAL(4, 39, 4) // "text"

    },
    "PlayTitleBarWidget\0signalBack\0\0SetText\0"
    "text"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlayTitleBarWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   25,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    4,

       0        // eod
};

void PlayTitleBarWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PlayTitleBarWidget *_t = static_cast<PlayTitleBarWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalBack(); break;
        case 1: _t->SetText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PlayTitleBarWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayTitleBarWidget::signalBack)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PlayTitleBarWidget::staticMetaObject = {
    { &QtToolBar::staticMetaObject, qt_meta_stringdata_PlayTitleBarWidget.data,
      qt_meta_data_PlayTitleBarWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PlayTitleBarWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlayTitleBarWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PlayTitleBarWidget.stringdata0))
        return static_cast<void*>(this);
    return QtToolBar::qt_metacast(_clname);
}

int PlayTitleBarWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtToolBar::qt_metacall(_c, _id, _a);
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
void PlayTitleBarWidget::signalBack()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_PlayerBarWidget_t {
    QByteArrayData data[13];
    char stringdata0[146];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PlayerBarWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PlayerBarWidget_t qt_meta_stringdata_PlayerBarWidget = {
    {
QT_MOC_LITERAL(0, 0, 15), // "PlayerBarWidget"
QT_MOC_LITERAL(1, 16, 13), // "buttonClicked"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 5), // "index"
QT_MOC_LITERAL(4, 37, 10), // "signalPlay"
QT_MOC_LITERAL(5, 48, 3), // "bOk"
QT_MOC_LITERAL(6, 52, 12), // "signalVolume"
QT_MOC_LITERAL(7, 65, 21), // "currentPostionChanged"
QT_MOC_LITERAL(8, 87, 7), // "postion"
QT_MOC_LITERAL(9, 95, 10), // "signalNext"
QT_MOC_LITERAL(10, 106, 10), // "signalPrev"
QT_MOC_LITERAL(11, 117, 14), // "signalMuenList"
QT_MOC_LITERAL(12, 132, 13) // "SltBtnClicked"

    },
    "PlayerBarWidget\0buttonClicked\0\0index\0"
    "signalPlay\0bOk\0signalVolume\0"
    "currentPostionChanged\0postion\0signalNext\0"
    "signalPrev\0signalMuenList\0SltBtnClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlayerBarWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    1,   57,    2, 0x06 /* Public */,
       6,    0,   60,    2, 0x06 /* Public */,
       7,    1,   61,    2, 0x06 /* Public */,
       9,    0,   64,    2, 0x06 /* Public */,
      10,    0,   65,    2, 0x06 /* Public */,
      11,    0,   66,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    1,   67,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void PlayerBarWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PlayerBarWidget *_t = static_cast<PlayerBarWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->buttonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->signalPlay((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->signalVolume(); break;
        case 3: _t->currentPostionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->signalNext(); break;
        case 5: _t->signalPrev(); break;
        case 6: _t->signalMuenList(); break;
        case 7: _t->SltBtnClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PlayerBarWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerBarWidget::buttonClicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PlayerBarWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerBarWidget::signalPlay)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PlayerBarWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerBarWidget::signalVolume)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (PlayerBarWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerBarWidget::currentPostionChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (PlayerBarWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerBarWidget::signalNext)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (PlayerBarWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerBarWidget::signalPrev)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (PlayerBarWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PlayerBarWidget::signalMuenList)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PlayerBarWidget::staticMetaObject = {
    { &QtToolBar::staticMetaObject, qt_meta_stringdata_PlayerBarWidget.data,
      qt_meta_data_PlayerBarWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PlayerBarWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlayerBarWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PlayerBarWidget.stringdata0))
        return static_cast<void*>(this);
    return QtToolBar::qt_metacast(_clname);
}

int PlayerBarWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtToolBar::qt_metacall(_c, _id, _a);
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
void PlayerBarWidget::buttonClicked(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PlayerBarWidget::signalPlay(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void PlayerBarWidget::signalVolume()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void PlayerBarWidget::currentPostionChanged(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void PlayerBarWidget::signalNext()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void PlayerBarWidget::signalPrev()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void PlayerBarWidget::signalMuenList()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
