/****************************************************************************
** Meta object code from reading C++ file 'downloadnetworkmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Settings/src/downloadnetworkmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'downloadnetworkmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DownloadNetworkManager_t {
    QByteArrayData data[19];
    char stringdata0[236];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DownloadNetworkManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DownloadNetworkManager_t qt_meta_stringdata_DownloadNetworkManager = {
    {
QT_MOC_LITERAL(0, 0, 22), // "DownloadNetworkManager"
QT_MOC_LITERAL(1, 23, 16), // "downloadProgress"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 13), // "bytesReceived"
QT_MOC_LITERAL(4, 55, 10), // "bytesTotal"
QT_MOC_LITERAL(5, 66, 13), // "replyFinished"
QT_MOC_LITERAL(6, 80, 6), // "status"
QT_MOC_LITERAL(7, 87, 8), // "fileName"
QT_MOC_LITERAL(8, 96, 4), // "name"
QT_MOC_LITERAL(9, 101, 17), // "signalVersionInfo"
QT_MOC_LITERAL(10, 119, 6), // "appVer"
QT_MOC_LITERAL(11, 126, 4), // "info"
QT_MOC_LITERAL(12, 131, 16), // "signalDownFinish"
QT_MOC_LITERAL(13, 148, 12), // "sltReadFiles"
QT_MOC_LITERAL(14, 161, 14), // "QNetworkReply*"
QT_MOC_LITERAL(15, 176, 5), // "reply"
QT_MOC_LITERAL(16, 182, 23), // "onAuthenticationRequest"
QT_MOC_LITERAL(17, 206, 15), // "QAuthenticator*"
QT_MOC_LITERAL(18, 222, 13) // "authenticator"

    },
    "DownloadNetworkManager\0downloadProgress\0"
    "\0bytesReceived\0bytesTotal\0replyFinished\0"
    "status\0fileName\0name\0signalVersionInfo\0"
    "appVer\0info\0signalDownFinish\0sltReadFiles\0"
    "QNetworkReply*\0reply\0onAuthenticationRequest\0"
    "QAuthenticator*\0authenticator"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DownloadNetworkManager[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,
       5,    1,   59,    2, 0x06 /* Public */,
       7,    1,   62,    2, 0x06 /* Public */,
       9,    2,   65,    2, 0x06 /* Public */,
      12,    1,   70,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    0,   73,    2, 0x08 /* Private */,
       5,    1,   74,    2, 0x08 /* Private */,
      16,    2,   77,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    3,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   10,   11,
    QMetaType::Void, QMetaType::QString,    8,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 14, 0x80000000 | 17,    2,   18,

       0        // eod
};

void DownloadNetworkManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        DownloadNetworkManager *_t = static_cast<DownloadNetworkManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->downloadProgress((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 1: _t->replyFinished((*reinterpret_cast< const int(*)>(_a[1]))); break;
        case 2: _t->fileName((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->signalVersionInfo((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->signalDownFinish((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->sltReadFiles(); break;
        case 6: _t->replyFinished((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 7: _t->onAuthenticationRequest((*reinterpret_cast< QNetworkReply*(*)>(_a[1])),(*reinterpret_cast< QAuthenticator*(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DownloadNetworkManager::*)(qint64 , qint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DownloadNetworkManager::downloadProgress)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DownloadNetworkManager::*)(const int & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DownloadNetworkManager::replyFinished)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DownloadNetworkManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DownloadNetworkManager::fileName)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (DownloadNetworkManager::*)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DownloadNetworkManager::signalVersionInfo)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (DownloadNetworkManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DownloadNetworkManager::signalDownFinish)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DownloadNetworkManager::staticMetaObject = {
    { &QNetworkAccessManager::staticMetaObject, qt_meta_stringdata_DownloadNetworkManager.data,
      qt_meta_data_DownloadNetworkManager,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *DownloadNetworkManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DownloadNetworkManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DownloadNetworkManager.stringdata0))
        return static_cast<void*>(this);
    return QNetworkAccessManager::qt_metacast(_clname);
}

int DownloadNetworkManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QNetworkAccessManager::qt_metacall(_c, _id, _a);
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
void DownloadNetworkManager::downloadProgress(qint64 _t1, qint64 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DownloadNetworkManager::replyFinished(const int & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DownloadNetworkManager::fileName(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DownloadNetworkManager::signalVersionInfo(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void DownloadNetworkManager::signalDownFinish(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
