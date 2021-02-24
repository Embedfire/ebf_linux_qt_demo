/****************************************************************************
** Meta object code from reading C++ file 'qtvideowidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../VideoPlayer/src/qtvideowidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'qtvideowidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QtVideoWidget_t {
    QByteArrayData data[13];
    char stringdata0[175];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QtVideoWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QtVideoWidget_t qt_meta_stringdata_QtVideoWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "QtVideoWidget"
QT_MOC_LITERAL(1, 14, 19), // "SltAutoCloseToolBar"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 14), // "SltBackClicked"
QT_MOC_LITERAL(4, 50, 17), // "SltBtnPlayClicked"
QT_MOC_LITERAL(5, 68, 3), // "bOk"
QT_MOC_LITERAL(6, 72, 17), // "SltPostionChanged"
QT_MOC_LITERAL(7, 90, 7), // "postion"
QT_MOC_LITERAL(8, 98, 18), // "SltDurationChanged"
QT_MOC_LITERAL(9, 117, 8), // "duration"
QT_MOC_LITERAL(10, 126, 16), // "SltChangePostion"
QT_MOC_LITERAL(11, 143, 15), // "SltShowMenuList"
QT_MOC_LITERAL(12, 159, 15) // "SltChangeVolume"

    },
    "QtVideoWidget\0SltAutoCloseToolBar\0\0"
    "SltBackClicked\0SltBtnPlayClicked\0bOk\0"
    "SltPostionChanged\0postion\0SltDurationChanged\0"
    "duration\0SltChangePostion\0SltShowMenuList\0"
    "SltChangeVolume"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QtVideoWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    1,   56,    2, 0x08 /* Private */,
       6,    1,   59,    2, 0x08 /* Private */,
       8,    1,   62,    2, 0x08 /* Private */,
      10,    1,   65,    2, 0x08 /* Private */,
      11,    0,   68,    2, 0x08 /* Private */,
      12,    0,   69,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::LongLong,    7,
    QMetaType::Void, QMetaType::LongLong,    9,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void QtVideoWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QtVideoWidget *_t = static_cast<QtVideoWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SltAutoCloseToolBar(); break;
        case 1: _t->SltBackClicked(); break;
        case 2: _t->SltBtnPlayClicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->SltPostionChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 4: _t->SltDurationChanged((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 5: _t->SltChangePostion((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->SltShowMenuList(); break;
        case 7: _t->SltChangeVolume(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject QtVideoWidget::staticMetaObject = {
    { &QtWidgetBase::staticMetaObject, qt_meta_stringdata_QtVideoWidget.data,
      qt_meta_data_QtVideoWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QtVideoWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QtVideoWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QtVideoWidget.stringdata0))
        return static_cast<void*>(this);
    return QtWidgetBase::qt_metacast(_clname);
}

int QtVideoWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtWidgetBase::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
