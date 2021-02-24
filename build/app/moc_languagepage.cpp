/****************************************************************************
** Meta object code from reading C++ file 'languagepage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Settings/src/languagepage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'languagepage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LanguagePage_t {
    QByteArrayData data[7];
    char stringdata0[88];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LanguagePage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LanguagePage_t qt_meta_stringdata_LanguagePage = {
    {
QT_MOC_LITERAL(0, 0, 12), // "LanguagePage"
QT_MOC_LITERAL(1, 13, 20), // "signalChangeLanguage"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 6), // "qmFile"
QT_MOC_LITERAL(4, 42, 22), // "SltCurrentIndexClicked"
QT_MOC_LITERAL(5, 65, 17), // "QtListWidgetItem*"
QT_MOC_LITERAL(6, 83, 4) // "item"

    },
    "LanguagePage\0signalChangeLanguage\0\0"
    "qmFile\0SltCurrentIndexClicked\0"
    "QtListWidgetItem*\0item"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LanguagePage[] = {

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
    QMetaType::Void, 0x80000000 | 5,    6,

       0        // eod
};

void LanguagePage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LanguagePage *_t = static_cast<LanguagePage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalChangeLanguage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->SltCurrentIndexClicked((*reinterpret_cast< QtListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LanguagePage::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LanguagePage::signalChangeLanguage)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject LanguagePage::staticMetaObject = {
    { &QtListWidget::staticMetaObject, qt_meta_stringdata_LanguagePage.data,
      qt_meta_data_LanguagePage,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *LanguagePage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LanguagePage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LanguagePage.stringdata0))
        return static_cast<void*>(this);
    return QtListWidget::qt_metacast(_clname);
}

int LanguagePage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtListWidget::qt_metacall(_c, _id, _a);
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
void LanguagePage::signalChangeLanguage(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
