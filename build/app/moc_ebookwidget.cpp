/****************************************************************************
** Meta object code from reading C++ file 'ebookwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../EBook/src/ebookwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ebookwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TextBrowser_t {
    QByteArrayData data[3];
    char stringdata0[27];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TextBrowser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TextBrowser_t qt_meta_stringdata_TextBrowser = {
    {
QT_MOC_LITERAL(0, 0, 11), // "TextBrowser"
QT_MOC_LITERAL(1, 12, 13), // "signalClicked"
QT_MOC_LITERAL(2, 26, 0) // ""

    },
    "TextBrowser\0signalClicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TextBrowser[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,

       0        // eod
};

void TextBrowser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TextBrowser *_t = static_cast<TextBrowser *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TextBrowser::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TextBrowser::signalClicked)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject TextBrowser::staticMetaObject = {
    { &QTextBrowser::staticMetaObject, qt_meta_stringdata_TextBrowser.data,
      qt_meta_data_TextBrowser,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *TextBrowser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TextBrowser::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TextBrowser.stringdata0))
        return static_cast<void*>(this);
    return QTextBrowser::qt_metacast(_clname);
}

int TextBrowser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextBrowser::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}

// SIGNAL 0
void TextBrowser::signalClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_EBookWidget_t {
    QByteArrayData data[18];
    char stringdata0[229];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_EBookWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_EBookWidget_t qt_meta_stringdata_EBookWidget = {
    {
QT_MOC_LITERAL(0, 0, 11), // "EBookWidget"
QT_MOC_LITERAL(1, 12, 10), // "SltBtnBack"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 13), // "SltLoadEbooks"
QT_MOC_LITERAL(4, 38, 11), // "SltAddEbool"
QT_MOC_LITERAL(5, 50, 21), // "SltCurrentItemClicked"
QT_MOC_LITERAL(6, 72, 21), // "QtPageListWidgetItem*"
QT_MOC_LITERAL(7, 94, 4), // "item"
QT_MOC_LITERAL(8, 99, 18), // "SltFontSizeChanged"
QT_MOC_LITERAL(9, 118, 4), // "size"
QT_MOC_LITERAL(10, 123, 15), // "SltColorChanged"
QT_MOC_LITERAL(11, 139, 5), // "color"
QT_MOC_LITERAL(12, 145, 15), // "SltClosePalette"
QT_MOC_LITERAL(13, 161, 15), // "SltFileSelected"
QT_MOC_LITERAL(14, 177, 8), // "fileName"
QT_MOC_LITERAL(15, 186, 18), // "SltFileDialogClose"
QT_MOC_LITERAL(16, 205, 17), // "SltToolBtnClicked"
QT_MOC_LITERAL(17, 223, 5) // "index"

    },
    "EBookWidget\0SltBtnBack\0\0SltLoadEbooks\0"
    "SltAddEbool\0SltCurrentItemClicked\0"
    "QtPageListWidgetItem*\0item\0"
    "SltFontSizeChanged\0size\0SltColorChanged\0"
    "color\0SltClosePalette\0SltFileSelected\0"
    "fileName\0SltFileDialogClose\0"
    "SltToolBtnClicked\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_EBookWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x08 /* Private */,
       3,    0,   65,    2, 0x08 /* Private */,
       4,    0,   66,    2, 0x08 /* Private */,
       5,    1,   67,    2, 0x08 /* Private */,
       8,    1,   70,    2, 0x08 /* Private */,
      10,    1,   73,    2, 0x08 /* Private */,
      12,    0,   76,    2, 0x08 /* Private */,
      13,    1,   77,    2, 0x08 /* Private */,
      15,    0,   80,    2, 0x08 /* Private */,
      16,    1,   81,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::QColor,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   14,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   17,

       0        // eod
};

void EBookWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        EBookWidget *_t = static_cast<EBookWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SltBtnBack(); break;
        case 1: _t->SltLoadEbooks(); break;
        case 2: _t->SltAddEbool(); break;
        case 3: _t->SltCurrentItemClicked((*reinterpret_cast< QtPageListWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->SltFontSizeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->SltColorChanged((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 6: _t->SltClosePalette(); break;
        case 7: _t->SltFileSelected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->SltFileDialogClose(); break;
        case 9: _t->SltToolBtnClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject EBookWidget::staticMetaObject = {
    { &QtAnimationWidget::staticMetaObject, qt_meta_stringdata_EBookWidget.data,
      qt_meta_data_EBookWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *EBookWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *EBookWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_EBookWidget.stringdata0))
        return static_cast<void*>(this);
    return QtAnimationWidget::qt_metacast(_clname);
}

int EBookWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtAnimationWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
