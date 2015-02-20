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
    QByteArrayData data[15];
    char stringdata[358];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Configure_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Configure_t qt_meta_stringdata_Configure = {
    {
QT_MOC_LITERAL(0, 0, 9), // "Configure"
QT_MOC_LITERAL(1, 10, 22), // "returnToPreviousValues"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 35), // "on_pushButton_edit_material_c..."
QT_MOC_LITERAL(4, 70, 26), // "on_pushButton_done_clicked"
QT_MOC_LITERAL(5, 97, 13), // "populateLists"
QT_MOC_LITERAL(6, 111, 13), // "setupMatTable"
QT_MOC_LITERAL(7, 125, 25), // "on_pushButton_add_clicked"
QT_MOC_LITERAL(8, 151, 28), // "on_pushButton_remove_clicked"
QT_MOC_LITERAL(9, 180, 27), // "on_pushButton_order_clicked"
QT_MOC_LITERAL(10, 208, 32), // "on_tableWidget_build_cellClicked"
QT_MOC_LITERAL(11, 241, 38), // "on_pushButton_add_new_materia..."
QT_MOC_LITERAL(12, 280, 37), // "on_listWidget_known_materials..."
QT_MOC_LITERAL(13, 318, 31), // "on_spinBox_nLayers_valueChanged"
QT_MOC_LITERAL(14, 350, 7) // "nLayers"

    },
    "Configure\0returnToPreviousValues\0\0"
    "on_pushButton_edit_material_clicked\0"
    "on_pushButton_done_clicked\0populateLists\0"
    "setupMatTable\0on_pushButton_add_clicked\0"
    "on_pushButton_remove_clicked\0"
    "on_pushButton_order_clicked\0"
    "on_tableWidget_build_cellClicked\0"
    "on_pushButton_add_new_material_clicked\0"
    "on_listWidget_known_materials_clicked\0"
    "on_spinBox_nLayers_valueChanged\0nLayers"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Configure[] = {

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
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    1,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,

       0        // eod
};

void Configure::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Configure *_t = static_cast<Configure *>(_o);
        switch (_id) {
        case 0: _t->returnToPreviousValues(); break;
        case 1: _t->on_pushButton_edit_material_clicked(); break;
        case 2: _t->on_pushButton_done_clicked(); break;
        case 3: _t->populateLists(); break;
        case 4: _t->setupMatTable(); break;
        case 5: _t->on_pushButton_add_clicked(); break;
        case 6: _t->on_pushButton_remove_clicked(); break;
        case 7: _t->on_pushButton_order_clicked(); break;
        case 8: _t->on_tableWidget_build_cellClicked(); break;
        case 9: _t->on_pushButton_add_new_material_clicked(); break;
        case 10: _t->on_listWidget_known_materials_clicked(); break;
        case 11: _t->on_spinBox_nLayers_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
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
QT_END_MOC_NAMESPACE
