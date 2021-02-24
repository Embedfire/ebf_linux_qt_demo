/****************************************************************************
** Meta object code from reading C++ file 'versionupdatepage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Settings/src/versionupdatepage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'versionupdatepage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VersionUpdatePage_t {
    QByteArrayData data[12];
    char stringdata0[150];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VersionUpdatePage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VersionUpdatePage_t qt_meta_stringdata_VersionUpdatePage = {
    {
QT_MOC_LITERAL(0, 0, 17), // "VersionUpdatePage"
QT_MOC_LITERAL(1, 18, 19), // "SltDownloadProgress"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 13), // "bytesReceived"
QT_MOC_LITERAL(4, 53, 10), // "bytesTotal"
QT_MOC_LITERAL(5, 64, 13), // "SltDownloadOk"
QT_MOC_LITERAL(6, 78, 4), // "name"
QT_MOC_LITERAL(7, 83, 14), // "SltVersionInfo"
QT_MOC_LITERAL(8, 98, 6), // "verNum"
QT_MOC_LITERAL(9, 105, 7), // "verInfo"
QT_MOC_LITERAL(10, 113, 18), // "SltCheckAppVersion"
QT_MOC_LITERAL(11, 132, 17) // "SltDownloadNewApp"

    },
    "VersionUpdatePage\0SltDownloadProgress\0"
    "\0bytesReceived\0bytesTotal\0SltDownloadOk\0"
    "name\0SltVersionInfo\0verNum\0verInfo\0"
    "SltCheckAppVersion\0SltDownloadNewApp"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VersionUpdatePage[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x08 /* Private */,
       5,    1,   44,    2, 0x08 /* Private */,
       7,    2,   47,    2, 0x08 /* Private */,
      10,    0,   52,    2, 0x08 /* Private */,
      11,    0,   53,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    8,    9,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void VersionUpdatePage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VersionUpdatePage *_t = static_cast<VersionUpdatePage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SltDownloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 1: _t->SltDownloadOk((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->SltVersionInfo((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 3: _t->SltCheckAppVersion(); break;
        case 4: _t->SltDownloadNewApp(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VersionUpdatePage::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_VersionUpdatePage.data,
      qt_meta_data_VersionUpdatePage,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *VersionUpdatePage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VersionUpdatePage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VersionUpdatePage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int VersionUpdatePage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
