/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../MainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[18];
    char stringdata0[389];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 10), // "slotDoExit"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 26), // "on_actionRefresh_triggered"
QT_MOC_LITERAL(4, 50, 26), // "on_btnClearConsole_clicked"
QT_MOC_LITERAL(5, 77, 21), // "on_btnRefresh_clicked"
QT_MOC_LITERAL(6, 99, 30), // "on_txtLocation_editingFinished"
QT_MOC_LITERAL(7, 130, 23), // "on_actionOpen_triggered"
QT_MOC_LITERAL(8, 154, 23), // "on_actionHelp_triggered"
QT_MOC_LITERAL(9, 178, 23), // "on_btnAddVarget_clicked"
QT_MOC_LITERAL(10, 202, 33), // "on_cbxVargets_currentIndexCha..."
QT_MOC_LITERAL(11, 236, 5), // "index"
QT_MOC_LITERAL(12, 242, 23), // "on_actionSave_triggered"
QT_MOC_LITERAL(13, 266, 22), // "on_btnAddLabel_clicked"
QT_MOC_LITERAL(14, 289, 22), // "on_btnAddTitle_clicked"
QT_MOC_LITERAL(15, 312, 26), // "on_actionSave_as_triggered"
QT_MOC_LITERAL(16, 339, 23), // "on_btnExportLog_clicked"
QT_MOC_LITERAL(17, 363, 25) // "on_action_About_triggered"

    },
    "MainWindow\0slotDoExit\0\0"
    "on_actionRefresh_triggered\0"
    "on_btnClearConsole_clicked\0"
    "on_btnRefresh_clicked\0"
    "on_txtLocation_editingFinished\0"
    "on_actionOpen_triggered\0on_actionHelp_triggered\0"
    "on_btnAddVarget_clicked\0"
    "on_cbxVargets_currentIndexChanged\0"
    "index\0on_actionSave_triggered\0"
    "on_btnAddLabel_clicked\0on_btnAddTitle_clicked\0"
    "on_actionSave_as_triggered\0"
    "on_btnExportLog_clicked\0"
    "on_action_About_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x08 /* Private */,
       3,    0,   90,    2, 0x08 /* Private */,
       4,    0,   91,    2, 0x08 /* Private */,
       5,    0,   92,    2, 0x08 /* Private */,
       6,    0,   93,    2, 0x08 /* Private */,
       7,    0,   94,    2, 0x08 /* Private */,
       8,    0,   95,    2, 0x08 /* Private */,
       9,    0,   96,    2, 0x08 /* Private */,
      10,    1,   97,    2, 0x08 /* Private */,
      12,    0,  100,    2, 0x08 /* Private */,
      13,    0,  101,    2, 0x08 /* Private */,
      14,    0,  102,    2, 0x08 /* Private */,
      15,    0,  103,    2, 0x08 /* Private */,
      16,    0,  104,    2, 0x08 /* Private */,
      17,    0,  105,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->slotDoExit(); break;
        case 1: _t->on_actionRefresh_triggered(); break;
        case 2: _t->on_btnClearConsole_clicked(); break;
        case 3: _t->on_btnRefresh_clicked(); break;
        case 4: _t->on_txtLocation_editingFinished(); break;
        case 5: _t->on_actionOpen_triggered(); break;
        case 6: _t->on_actionHelp_triggered(); break;
        case 7: _t->on_btnAddVarget_clicked(); break;
        case 8: _t->on_cbxVargets_currentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->on_actionSave_triggered(); break;
        case 10: _t->on_btnAddLabel_clicked(); break;
        case 11: _t->on_btnAddTitle_clicked(); break;
        case 12: _t->on_actionSave_as_triggered(); break;
        case 13: _t->on_btnExportLog_clicked(); break;
        case 14: _t->on_action_About_triggered(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
struct qt_meta_stringdata_Varget_t {
    QByteArrayData data[5];
    char stringdata0[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Varget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Varget_t qt_meta_stringdata_Varget = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Varget"
QT_MOC_LITERAL(1, 7, 22), // "on_clicked_button_down"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 20), // "on_clicked_button_up"
QT_MOC_LITERAL(4, 52, 24) // "on_clicked_button_delete"

    },
    "Varget\0on_clicked_button_down\0\0"
    "on_clicked_button_up\0on_clicked_button_delete"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Varget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x08 /* Private */,
       3,    0,   30,    2, 0x08 /* Private */,
       4,    0,   31,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Varget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Varget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_clicked_button_down(); break;
        case 1: _t->on_clicked_button_up(); break;
        case 2: _t->on_clicked_button_delete(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject Varget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_Varget.data,
    qt_meta_data_Varget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Varget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Varget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Varget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Varget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
