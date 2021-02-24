/****************************************************************************
** Meta object code from reading C++ file 'videoplaylistwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../VideoPlayer/src/videoplaylistwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'videoplaylistwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VideoPlayListWidget_t {
    QByteArrayData data[1];
    char stringdata0[20];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VideoPlayListWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VideoPlayListWidget_t qt_meta_stringdata_VideoPlayListWidget = {
    {
QT_MOC_LITERAL(0, 0, 19) // "VideoPlayListWidget"

    },
    "VideoPlayListWidget"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VideoPlayListWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void VideoPlayListWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject VideoPlayListWidget::staticMetaObject = {
    { &QtListWidget::staticMetaObject, qt_meta_stringdata_VideoPlayListWidget.data,
      qt_meta_data_VideoPlayListWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *VideoPlayListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VideoPlayListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VideoPlayListWidget.stringdata0))
        return static_cast<void*>(this);
    return QtListWidget::qt_metacast(_clname);
}

int VideoPlayListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtListWidget::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_MediaPlayListWidget_t {
    QByteArrayData data[6];
    char stringdata0[75];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MediaPlayListWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MediaPlayListWidget_t qt_meta_stringdata_MediaPlayListWidget = {
    {
QT_MOC_LITERAL(0, 0, 19), // "MediaPlayListWidget"
QT_MOC_LITERAL(1, 20, 18), // "signalMediaChanged"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 8), // "fileName"
QT_MOC_LITERAL(4, 49, 19), // "SltCurrMediaChanged"
QT_MOC_LITERAL(5, 69, 5) // "index"

    },
    "MediaPlayListWidget\0signalMediaChanged\0"
    "\0fileName\0SltCurrMediaChanged\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MediaPlayListWidget[] = {

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
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   27,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    5,

       0        // eod
};

void MediaPlayListWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MediaPlayListWidget *_t = static_cast<MediaPlayListWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalMediaChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->SltCurrMediaChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MediaPlayListWidget::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MediaPlayListWidget::signalMediaChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MediaPlayListWidget::staticMetaObject = {
    { &QtAnimationWidget::staticMetaObject, qt_meta_stringdata_MediaPlayListWidget.data,
      qt_meta_data_MediaPlayListWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *MediaPlayListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MediaPlayListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MediaPlayListWidget.stringdata0))
        return static_cast<void*>(this);
    return QtAnimationWidget::qt_metacast(_clname);
}

int MediaPlayListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtAnimationWidget::qt_metacall(_c, _id, _a);
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
void MediaPlayListWidget::signalMediaChanged(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
