/****************************************************************************
** Meta object code from reading C++ file 'ParameterControlDlg.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ParameterControlDlg.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ParameterControlDlg.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ParameterControlDlg_t {
    QByteArrayData data[10];
    char stringdata0[210];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ParameterControlDlg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ParameterControlDlg_t qt_meta_stringdata_ParameterControlDlg = {
    {
QT_MOC_LITERAL(0, 0, 19), // "ParameterControlDlg"
QT_MOC_LITERAL(1, 20, 4), // "onOK"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 8), // "onCancel"
QT_MOC_LITERAL(4, 35, 29), // "onSliderParcelSmallMidChanged"
QT_MOC_LITERAL(5, 65, 28), // "onLineEditParcelSmMidChanged"
QT_MOC_LITERAL(6, 94, 29), // "onSliderParcelMidLargeChanged"
QT_MOC_LITERAL(7, 124, 31), // "onLineEditParcelMidLargeChanged"
QT_MOC_LITERAL(8, 156, 25), // "onSliderCorrectionChanged"
QT_MOC_LITERAL(9, 182, 27) // "onLineEditCorrectionChanged"

    },
    "ParameterControlDlg\0onOK\0\0onCancel\0"
    "onSliderParcelSmallMidChanged\0"
    "onLineEditParcelSmMidChanged\0"
    "onSliderParcelMidLargeChanged\0"
    "onLineEditParcelMidLargeChanged\0"
    "onSliderCorrectionChanged\0"
    "onLineEditCorrectionChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ParameterControlDlg[] = {

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
       1,    0,   54,    2, 0x0a /* Public */,
       3,    0,   55,    2, 0x0a /* Public */,
       4,    1,   56,    2, 0x0a /* Public */,
       5,    0,   59,    2, 0x0a /* Public */,
       6,    1,   60,    2, 0x0a /* Public */,
       7,    0,   63,    2, 0x0a /* Public */,
       8,    1,   64,    2, 0x0a /* Public */,
       9,    0,   67,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

       0        // eod
};

void ParameterControlDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ParameterControlDlg *_t = static_cast<ParameterControlDlg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onOK(); break;
        case 1: _t->onCancel(); break;
        case 2: _t->onSliderParcelSmallMidChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->onLineEditParcelSmMidChanged(); break;
        case 4: _t->onSliderParcelMidLargeChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->onLineEditParcelMidLargeChanged(); break;
        case 6: _t->onSliderCorrectionChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->onLineEditCorrectionChanged(); break;
        default: ;
        }
    }
}

const QMetaObject ParameterControlDlg::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ParameterControlDlg.data,
      qt_meta_data_ParameterControlDlg,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ParameterControlDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ParameterControlDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ParameterControlDlg.stringdata0))
        return static_cast<void*>(const_cast< ParameterControlDlg*>(this));
    return QDialog::qt_metacast(_clname);
}

int ParameterControlDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
