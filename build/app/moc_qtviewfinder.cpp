/****************************************************************************
** Meta object code from reading C++ file 'qtviewfinder.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../Camera/src/qtviewfinder.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtviewfinder.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QtViewFinder_t {
    QByteArrayData data[16];
    char stringdata0[197];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtViewFinder_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtViewFinder_t qt_meta_stringdata_QtViewFinder = {
    {
QT_MOC_LITERAL(0, 0, 12), // "QtViewFinder"
QT_MOC_LITERAL(1, 13, 24), // "returnbtn_clicked_signal"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 19), // "take_picture_signal"
QT_MOC_LITERAL(4, 59, 20), // "on_returnbtn_clicked"
QT_MOC_LITERAL(5, 80, 7), // "clicked"
QT_MOC_LITERAL(6, 88, 15), // "on_take_picture"
QT_MOC_LITERAL(7, 104, 14), // "on_show_config"
QT_MOC_LITERAL(8, 119, 13), // "on_hide_image"
QT_MOC_LITERAL(9, 133, 9), // "loadImage"
QT_MOC_LITERAL(10, 143, 10), // "image_path"
QT_MOC_LITERAL(11, 154, 14), // "setEnabledTake"
QT_MOC_LITERAL(12, 169, 6), // "enable"
QT_MOC_LITERAL(13, 176, 7), // "setSize"
QT_MOC_LITERAL(14, 184, 5), // "width"
QT_MOC_LITERAL(15, 190, 6) // "height"

    },
    "QtViewFinder\0returnbtn_clicked_signal\0"
    "\0take_picture_signal\0on_returnbtn_clicked\0"
    "clicked\0on_take_picture\0on_show_config\0"
    "on_hide_image\0loadImage\0image_path\0"
    "setEnabledTake\0enable\0setSize\0width\0"
    "height"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtViewFinder[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x06 /* Public */,
       3,    0,   60,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   61,    2, 0x08 /* Private */,
       6,    0,   64,    2, 0x08 /* Private */,
       7,    0,   65,    2, 0x08 /* Private */,
       8,    0,   66,    2, 0x08 /* Private */,
       9,    1,   67,    2, 0x0a /* Public */,
      11,    1,   70,    2, 0x0a /* Public */,
      13,    2,   73,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::Bool,   12,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   14,   15,

       0        // eod
};

void QtViewFinder::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<QtViewFinder *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->returnbtn_clicked_signal(); break;
        case 1: _t->take_picture_signal(); break;
        case 2: _t->on_returnbtn_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->on_take_picture(); break;
        case 4: _t->on_show_config(); break;
        case 5: _t->on_hide_image(); break;
        case 6: _t->loadImage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 7: _t->setEnabledTake((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->setSize((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (QtViewFinder::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtViewFinder::returnbtn_clicked_signal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (QtViewFinder::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&QtViewFinder::take_picture_signal)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QtViewFinder::staticMetaObject = { {
    QMetaObject::SuperData::link<QCameraViewfinder::staticMetaObject>(),
    qt_meta_stringdata_QtViewFinder.data,
    qt_meta_data_QtViewFinder,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *QtViewFinder::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtViewFinder::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QtViewFinder.stringdata0))
        return static_cast<void*>(this);
    return QCameraViewfinder::qt_metacast(_clname);
}

int QtViewFinder::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QCameraViewfinder::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void QtViewFinder::returnbtn_clicked_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void QtViewFinder::take_picture_signal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
