/****************************************************************************
** Meta object code from reading C++ file 'camerawidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Camera/src/camerawidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'camerawidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CameraWidget_t {
    QByteArrayData data[18];
    char stringdata0[219];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CameraWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CameraWidget_t qt_meta_stringdata_CameraWidget = {
    {
QT_MOC_LITERAL(0, 0, 12), // "CameraWidget"
QT_MOC_LITERAL(1, 13, 10), // "InitCamera"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 15), // "SltClearMessage"
QT_MOC_LITERAL(4, 41, 14), // "on_takePicture"
QT_MOC_LITERAL(5, 56, 17), // "on_clieckBackhome"
QT_MOC_LITERAL(6, 74, 15), // "readyForCapture"
QT_MOC_LITERAL(7, 90, 5), // "ready"
QT_MOC_LITERAL(8, 96, 10), // "imageSaved"
QT_MOC_LITERAL(9, 107, 2), // "id"
QT_MOC_LITERAL(10, 110, 8), // "fileName"
QT_MOC_LITERAL(11, 119, 20), // "processCapturedImage"
QT_MOC_LITERAL(12, 140, 9), // "requestId"
QT_MOC_LITERAL(13, 150, 3), // "img"
QT_MOC_LITERAL(14, 154, 19), // "displayCaptureError"
QT_MOC_LITERAL(15, 174, 26), // "QCameraImageCapture::Error"
QT_MOC_LITERAL(16, 201, 5), // "error"
QT_MOC_LITERAL(17, 207, 11) // "errorString"

    },
    "CameraWidget\0InitCamera\0\0SltClearMessage\0"
    "on_takePicture\0on_clieckBackhome\0"
    "readyForCapture\0ready\0imageSaved\0id\0"
    "fileName\0processCapturedImage\0requestId\0"
    "img\0displayCaptureError\0"
    "QCameraImageCapture::Error\0error\0"
    "errorString"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CameraWidget[] = {

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
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    1,   58,    2, 0x08 /* Private */,
       8,    2,   61,    2, 0x08 /* Private */,
      11,    2,   66,    2, 0x08 /* Private */,
      14,    3,   71,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    7,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    9,   10,
    QMetaType::Void, QMetaType::Int, QMetaType::QImage,   12,   13,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 15, QMetaType::QString,    9,   16,   17,

       0        // eod
};

void CameraWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CameraWidget *_t = static_cast<CameraWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->InitCamera(); break;
        case 1: _t->SltClearMessage(); break;
        case 2: _t->on_takePicture(); break;
        case 3: _t->on_clieckBackhome(); break;
        case 4: _t->readyForCapture((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->imageSaved((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 6: _t->processCapturedImage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QImage(*)>(_a[2]))); break;
        case 7: _t->displayCaptureError((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QCameraImageCapture::Error(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 7:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QCameraImageCapture::Error >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CameraWidget::staticMetaObject = {
    { &QtAnimationWidget::staticMetaObject, qt_meta_stringdata_CameraWidget.data,
      qt_meta_data_CameraWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *CameraWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CameraWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CameraWidget.stringdata0))
        return static_cast<void*>(this);
    return QtAnimationWidget::qt_metacast(_clname);
}

int CameraWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
