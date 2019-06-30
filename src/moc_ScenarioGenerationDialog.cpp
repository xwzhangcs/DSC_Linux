/****************************************************************************
** Meta object code from reading C++ file 'ScenarioGenerationDialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ScenarioGenerationDialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ScenarioGenerationDialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ScenarioGenerationDialog_t {
    QByteArrayData data[11];
    char stringdata0[164];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScenarioGenerationDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScenarioGenerationDialog_t qt_meta_stringdata_ScenarioGenerationDialog = {
    {
QT_MOC_LITERAL(0, 0, 24), // "ScenarioGenerationDialog"
QT_MOC_LITERAL(1, 25, 6), // "onZone"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 9), // "onTerrain"
QT_MOC_LITERAL(4, 43, 17), // "onOutputDirectory"
QT_MOC_LITERAL(5, 61, 14), // "onUseSimulator"
QT_MOC_LITERAL(6, 76, 20), // "onSimulatorDirectory"
QT_MOC_LITERAL(7, 97, 18), // "onBuildingCoverage"
QT_MOC_LITERAL(8, 116, 33), // "onGenerateBuildingFootprintsI..."
QT_MOC_LITERAL(9, 150, 4), // "onOK"
QT_MOC_LITERAL(10, 155, 8) // "onCancel"

    },
    "ScenarioGenerationDialog\0onZone\0\0"
    "onTerrain\0onOutputDirectory\0onUseSimulator\0"
    "onSimulatorDirectory\0onBuildingCoverage\0"
    "onGenerateBuildingFootprintsImage\0"
    "onOK\0onCancel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScenarioGenerationDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x0a /* Public */,
       3,    0,   60,    2, 0x0a /* Public */,
       4,    0,   61,    2, 0x0a /* Public */,
       5,    0,   62,    2, 0x0a /* Public */,
       6,    0,   63,    2, 0x0a /* Public */,
       7,    0,   64,    2, 0x0a /* Public */,
       8,    0,   65,    2, 0x0a /* Public */,
       9,    0,   66,    2, 0x0a /* Public */,
      10,    0,   67,    2, 0x0a /* Public */,

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

       0        // eod
};

void ScenarioGenerationDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ScenarioGenerationDialog *_t = static_cast<ScenarioGenerationDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onZone(); break;
        case 1: _t->onTerrain(); break;
        case 2: _t->onOutputDirectory(); break;
        case 3: _t->onUseSimulator(); break;
        case 4: _t->onSimulatorDirectory(); break;
        case 5: _t->onBuildingCoverage(); break;
        case 6: _t->onGenerateBuildingFootprintsImage(); break;
        case 7: _t->onOK(); break;
        case 8: _t->onCancel(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject ScenarioGenerationDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ScenarioGenerationDialog.data,
      qt_meta_data_ScenarioGenerationDialog,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ScenarioGenerationDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScenarioGenerationDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ScenarioGenerationDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ScenarioGenerationDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
