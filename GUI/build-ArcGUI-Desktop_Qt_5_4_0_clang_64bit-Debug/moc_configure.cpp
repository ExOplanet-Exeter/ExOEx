/****************************************************************************
** Meta object code from reading C++ file 'configure.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.4.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../ArcGUI/configure.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'configure.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.4.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Configure_t {
    QByteArrayData data[12];
    char stringdata[229];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Configure_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Configure_t qt_meta_stringdata_Configure = {
    {
QT_MOC_LITERAL(0, 0, 9), // "Configure"
QT_MOC_LITERAL(1, 10, 35), // "on_pushButton_edit_material_c..."
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 26), // "on_pushButton_done_clicked"
QT_MOC_LITERAL(4, 74, 13), // "populateLists"
QT_MOC_LITERAL(5, 88, 13), // "setupMatTable"
QT_MOC_LITERAL(6, 102, 25), // "on_pushButton_add_clicked"
QT_MOC_LITERAL(7, 128, 28), // "on_pushButton_remove_clicked"
QT_MOC_LITERAL(8, 157, 27), // "on_pushButton_order_clicked"
QT_MOC_LITERAL(9, 185, 32), // "on_tableWidget_build_cellClicked"
QT_MOC_LITERAL(10, 218, 3), // "row"
QT_MOC_LITERAL(11, 222, 6) // "column"

    },
    "Configure\0on_pushButton_edit_material_clicked\0"
    "\0on_pushButton_done_clicked\0populateLists\0"
    "setupMatTable\0on_pushButton_add_clicked\0"
    "on_pushButton_remove_clicked\0"
    "on_pushButton_order_clicked\0"
    "on_tableWidget_build_cellClicked\0row\0"
    "column"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Configure[] = {

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
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    2,   61,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::Int,   10,   11,

       0        // eod
};

void Configure::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Configure *_t = static_cast<Configure *>(_o);
        switch (_id) {
        case 0: _t->on_pushButton_edit_material_clicked(); break;
        case 1: _t->on_pushButton_done_clicked(); break;
        case 2: _t->populateLists(); break;
        case 3: _t->setupMatTable(); break;
        case 4: _t->on_pushButton_add_clicked(); break;
        case 5: _t->on_pushButton_remove_clicked(); break;
        case 6: _t->on_pushButton_order_clicked(); break;
        case 7: _t->on_tableWidget_build_cellClicked((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    }
}

const QMetaObject Configure::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_Configure.data,
      qt_meta_data_Configure,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Configure::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Configure::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Configure.stringdata))
        return static_cast<void*>(const_cast< Configure*>(this));
    return QDialog::qt_metacast(_clname);
}

int Configure::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
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
QT_END_MOC_NAMESPACE
