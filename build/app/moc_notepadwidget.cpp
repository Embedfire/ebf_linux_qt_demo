/****************************************************************************
** Meta object code from reading C++ file 'notepadwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../NotePad/src/notepadwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'notepadwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_TextEdit_t {
    QByteArrayData data[3];
    char stringdata0[24];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TextEdit_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TextEdit_t qt_meta_stringdata_TextEdit = {
    {
QT_MOC_LITERAL(0, 0, 8), // "TextEdit"
QT_MOC_LITERAL(1, 9, 13), // "signalClicked"
QT_MOC_LITERAL(2, 23, 0) // ""

    },
    "TextEdit\0signalClicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TextEdit[] = {

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

void TextEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TextEdit *_t = static_cast<TextEdit *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TextEdit::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TextEdit::signalClicked)) {
                *result = 0;
                return;
            }
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject TextEdit::staticMetaObject = {
    { &QTextEdit::staticMetaObject, qt_meta_stringdata_TextEdit.data,
      qt_meta_data_TextEdit,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *TextEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TextEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_TextEdit.stringdata0))
        return static_cast<void*>(this);
    return QTextEdit::qt_metacast(_clname);
}

int TextEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextEdit::qt_metacall(_c, _id, _a);
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
void TextEdit::signalClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
struct qt_meta_stringdata_NotePadWidget_t {
    QByteArrayData data[20];
    char stringdata0[248];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NotePadWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NotePadWidget_t qt_meta_stringdata_NotePadWidget = {
    {
QT_MOC_LITERAL(0, 0, 13), // "NotePadWidget"
QT_MOC_LITERAL(1, 14, 11), // "SltBackHome"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 18), // "SltActionTriggered"
QT_MOC_LITERAL(4, 46, 8), // "QAction*"
QT_MOC_LITERAL(5, 55, 6), // "action"
QT_MOC_LITERAL(6, 62, 19), // "SltSetPaletteConfig"
QT_MOC_LITERAL(7, 82, 18), // "SltFontSizeChanged"
QT_MOC_LITERAL(8, 101, 4), // "size"
QT_MOC_LITERAL(9, 106, 15), // "SltColorChanged"
QT_MOC_LITERAL(10, 122, 5), // "color"
QT_MOC_LITERAL(11, 128, 15), // "SltClosePalette"
QT_MOC_LITERAL(12, 144, 15), // "SltFileSelected"
QT_MOC_LITERAL(13, 160, 8), // "fileName"
QT_MOC_LITERAL(14, 169, 18), // "SltFileDialogClose"
QT_MOC_LITERAL(15, 188, 17), // "SltToolBtnClicked"
QT_MOC_LITERAL(16, 206, 5), // "index"
QT_MOC_LITERAL(17, 212, 10), // "ActionOpen"
QT_MOC_LITERAL(18, 223, 11), // "NewDocument"
QT_MOC_LITERAL(19, 235, 12) // "SaveDocument"

    },
    "NotePadWidget\0SltBackHome\0\0"
    "SltActionTriggered\0QAction*\0action\0"
    "SltSetPaletteConfig\0SltFontSizeChanged\0"
    "size\0SltColorChanged\0color\0SltClosePalette\0"
    "SltFileSelected\0fileName\0SltFileDialogClose\0"
    "SltToolBtnClicked\0index\0ActionOpen\0"
    "NewDocument\0SaveDocument"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NotePadWidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    1,   75,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    1,   79,    2, 0x08 /* Private */,
       9,    1,   82,    2, 0x08 /* Private */,
      11,    0,   85,    2, 0x08 /* Private */,
      12,    1,   86,    2, 0x08 /* Private */,
      14,    0,   89,    2, 0x08 /* Private */,
      15,    1,   90,    2, 0x08 /* Private */,
      17,    0,   93,    2, 0x08 /* Private */,
      18,    0,   94,    2, 0x08 /* Private */,
      19,    0,   95,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::QColor,   10,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void NotePadWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NotePadWidget *_t = static_cast<NotePadWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SltBackHome(); break;
        case 1: _t->SltActionTriggered((*reinterpret_cast< QAction*(*)>(_a[1]))); break;
        case 2: _t->SltSetPaletteConfig(); break;
        case 3: _t->SltFontSizeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->SltColorChanged((*reinterpret_cast< const QColor(*)>(_a[1]))); break;
        case 5: _t->SltClosePalette(); break;
        case 6: _t->SltFileSelected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->SltFileDialogClose(); break;
        case 8: _t->SltToolBtnClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->ActionOpen(); break;
        case 10: _t->NewDocument(); break;
        case 11: _t->SaveDocument(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NotePadWidget::staticMetaObject = {
    { &QtAnimationWidget::staticMetaObject, qt_meta_stringdata_NotePadWidget.data,
      qt_meta_data_NotePadWidget,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *NotePadWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NotePadWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NotePadWidget.stringdata0))
        return static_cast<void*>(this);
    return QtAnimationWidget::qt_metacast(_clname);
}

int NotePadWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QtAnimationWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
