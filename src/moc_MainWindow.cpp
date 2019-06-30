/****************************************************************************
** Meta object code from reading C++ file 'MainWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "MainWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MainWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[57];
    char stringdata0[846];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 10), // "onLoadZone"
QT_MOC_LITERAL(2, 22, 0), // ""
QT_MOC_LITERAL(3, 23, 12), // "onNewTerrain"
QT_MOC_LITERAL(4, 36, 13), // "onLoadTerrain"
QT_MOC_LITERAL(5, 50, 13), // "onSaveTerrain"
QT_MOC_LITERAL(6, 64, 11), // "onLoadRoads"
QT_MOC_LITERAL(7, 76, 14), // "onLoadOSMRoads"
QT_MOC_LITERAL(8, 91, 11), // "onSaveRoads"
QT_MOC_LITERAL(9, 103, 13), // "onLoadParcels"
QT_MOC_LITERAL(10, 117, 13), // "onSaveParcels"
QT_MOC_LITERAL(11, 131, 15), // "onLoadBuildings"
QT_MOC_LITERAL(12, 147, 15), // "onSaveBuildings"
QT_MOC_LITERAL(13, 163, 7), // "onClear"
QT_MOC_LITERAL(14, 171, 11), // "onSaveImage"
QT_MOC_LITERAL(15, 183, 13), // "onSaveImageHD"
QT_MOC_LITERAL(16, 197, 12), // "onLoadCamera"
QT_MOC_LITERAL(17, 210, 15), // "onLoadCameraFre"
QT_MOC_LITERAL(18, 226, 12), // "onSaveCamera"
QT_MOC_LITERAL(19, 239, 13), // "onResetCamera"
QT_MOC_LITERAL(20, 253, 15), // "onGenerateRoads"
QT_MOC_LITERAL(21, 269, 16), // "onGenerateBlocks"
QT_MOC_LITERAL(22, 286, 17), // "onGenerateParcels"
QT_MOC_LITERAL(23, 304, 19), // "onGenerateBuildings"
QT_MOC_LITERAL(24, 324, 20), // "onGenerateVegetation"
QT_MOC_LITERAL(25, 345, 13), // "onGenerateAll"
QT_MOC_LITERAL(26, 359, 14), // "onGenerateCity"
QT_MOC_LITERAL(27, 374, 19), // "onGenerateScenarios"
QT_MOC_LITERAL(28, 394, 13), // "onViewChanged"
QT_MOC_LITERAL(29, 408, 11), // "onShowWater"
QT_MOC_LITERAL(30, 420, 10), // "onSeaLevel"
QT_MOC_LITERAL(31, 431, 19), // "onShowControlWidget"
QT_MOC_LITERAL(32, 451, 20), // "onToolGenerateBlocks"
QT_MOC_LITERAL(33, 472, 14), // "onToolImageOBB"
QT_MOC_LITERAL(34, 487, 17), // "onParcelClassifer"
QT_MOC_LITERAL(35, 505, 20), // "onLoadSegmentedImage"
QT_MOC_LITERAL(36, 526, 17), // "onLoadParcelImage"
QT_MOC_LITERAL(37, 544, 17), // "onLoadGroundTruth"
QT_MOC_LITERAL(38, 562, 16), // "onLoadWholeImage"
QT_MOC_LITERAL(39, 579, 18), // "onSateLoadOSMRoads"
QT_MOC_LITERAL(40, 598, 12), // "onSateLayout"
QT_MOC_LITERAL(41, 611, 17), // "onLoadLoadGeoInfo"
QT_MOC_LITERAL(42, 629, 16), // "onLoadHeightInfo"
QT_MOC_LITERAL(43, 646, 20), // "onLoadPopulationInfo"
QT_MOC_LITERAL(44, 667, 13), // "onDemoLoadROI"
QT_MOC_LITERAL(45, 681, 12), // "onDemoLayout"
QT_MOC_LITERAL(46, 694, 12), // "onCallPython"
QT_MOC_LITERAL(47, 707, 12), // "onNNanalysis"
QT_MOC_LITERAL(48, 720, 8), // "onNNtest"
QT_MOC_LITERAL(49, 729, 10), // "onEstimate"
QT_MOC_LITERAL(50, 740, 15), // "actionTestBlock"
QT_MOC_LITERAL(51, 756, 13), // "onParaControl"
QT_MOC_LITERAL(52, 770, 11), // "onChangeFov"
QT_MOC_LITERAL(53, 782, 12), // "onComputeSVF"
QT_MOC_LITERAL(54, 795, 9), // "onTestSVF"
QT_MOC_LITERAL(55, 805, 18), // "onGenerateSVFImage"
QT_MOC_LITERAL(56, 824, 21) // "onGenerateHeightImage"

    },
    "MainWindow\0onLoadZone\0\0onNewTerrain\0"
    "onLoadTerrain\0onSaveTerrain\0onLoadRoads\0"
    "onLoadOSMRoads\0onSaveRoads\0onLoadParcels\0"
    "onSaveParcels\0onLoadBuildings\0"
    "onSaveBuildings\0onClear\0onSaveImage\0"
    "onSaveImageHD\0onLoadCamera\0onLoadCameraFre\0"
    "onSaveCamera\0onResetCamera\0onGenerateRoads\0"
    "onGenerateBlocks\0onGenerateParcels\0"
    "onGenerateBuildings\0onGenerateVegetation\0"
    "onGenerateAll\0onGenerateCity\0"
    "onGenerateScenarios\0onViewChanged\0"
    "onShowWater\0onSeaLevel\0onShowControlWidget\0"
    "onToolGenerateBlocks\0onToolImageOBB\0"
    "onParcelClassifer\0onLoadSegmentedImage\0"
    "onLoadParcelImage\0onLoadGroundTruth\0"
    "onLoadWholeImage\0onSateLoadOSMRoads\0"
    "onSateLayout\0onLoadLoadGeoInfo\0"
    "onLoadHeightInfo\0onLoadPopulationInfo\0"
    "onDemoLoadROI\0onDemoLayout\0onCallPython\0"
    "onNNanalysis\0onNNtest\0onEstimate\0"
    "actionTestBlock\0onParaControl\0onChangeFov\0"
    "onComputeSVF\0onTestSVF\0onGenerateSVFImage\0"
    "onGenerateHeightImage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      55,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  289,    2, 0x0a /* Public */,
       3,    0,  290,    2, 0x0a /* Public */,
       4,    0,  291,    2, 0x0a /* Public */,
       5,    0,  292,    2, 0x0a /* Public */,
       6,    0,  293,    2, 0x0a /* Public */,
       7,    0,  294,    2, 0x0a /* Public */,
       8,    0,  295,    2, 0x0a /* Public */,
       9,    0,  296,    2, 0x0a /* Public */,
      10,    0,  297,    2, 0x0a /* Public */,
      11,    0,  298,    2, 0x0a /* Public */,
      12,    0,  299,    2, 0x0a /* Public */,
      13,    0,  300,    2, 0x0a /* Public */,
      14,    0,  301,    2, 0x0a /* Public */,
      15,    0,  302,    2, 0x0a /* Public */,
      16,    0,  303,    2, 0x0a /* Public */,
      17,    0,  304,    2, 0x0a /* Public */,
      18,    0,  305,    2, 0x0a /* Public */,
      19,    0,  306,    2, 0x0a /* Public */,
      20,    0,  307,    2, 0x0a /* Public */,
      21,    0,  308,    2, 0x0a /* Public */,
      22,    0,  309,    2, 0x0a /* Public */,
      23,    0,  310,    2, 0x0a /* Public */,
      24,    0,  311,    2, 0x0a /* Public */,
      25,    0,  312,    2, 0x0a /* Public */,
      26,    0,  313,    2, 0x0a /* Public */,
      27,    0,  314,    2, 0x0a /* Public */,
      28,    0,  315,    2, 0x0a /* Public */,
      29,    0,  316,    2, 0x0a /* Public */,
      30,    0,  317,    2, 0x0a /* Public */,
      31,    0,  318,    2, 0x0a /* Public */,
      32,    0,  319,    2, 0x0a /* Public */,
      33,    0,  320,    2, 0x0a /* Public */,
      34,    0,  321,    2, 0x0a /* Public */,
      35,    0,  322,    2, 0x0a /* Public */,
      36,    0,  323,    2, 0x0a /* Public */,
      37,    0,  324,    2, 0x0a /* Public */,
      38,    0,  325,    2, 0x0a /* Public */,
      39,    0,  326,    2, 0x0a /* Public */,
      40,    0,  327,    2, 0x0a /* Public */,
      41,    0,  328,    2, 0x0a /* Public */,
      42,    0,  329,    2, 0x0a /* Public */,
      43,    0,  330,    2, 0x0a /* Public */,
      44,    0,  331,    2, 0x0a /* Public */,
      45,    0,  332,    2, 0x0a /* Public */,
      46,    0,  333,    2, 0x0a /* Public */,
      47,    0,  334,    2, 0x0a /* Public */,
      48,    0,  335,    2, 0x0a /* Public */,
      49,    0,  336,    2, 0x0a /* Public */,
      50,    0,  337,    2, 0x0a /* Public */,
      51,    0,  338,    2, 0x0a /* Public */,
      52,    0,  339,    2, 0x0a /* Public */,
      53,    0,  340,    2, 0x0a /* Public */,
      54,    0,  341,    2, 0x0a /* Public */,
      55,    0,  342,    2, 0x0a /* Public */,
      56,    0,  343,    2, 0x0a /* Public */,

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

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onLoadZone(); break;
        case 1: _t->onNewTerrain(); break;
        case 2: _t->onLoadTerrain(); break;
        case 3: _t->onSaveTerrain(); break;
        case 4: _t->onLoadRoads(); break;
        case 5: _t->onLoadOSMRoads(); break;
        case 6: _t->onSaveRoads(); break;
        case 7: _t->onLoadParcels(); break;
        case 8: _t->onSaveParcels(); break;
        case 9: _t->onLoadBuildings(); break;
        case 10: _t->onSaveBuildings(); break;
        case 11: _t->onClear(); break;
        case 12: _t->onSaveImage(); break;
        case 13: _t->onSaveImageHD(); break;
        case 14: _t->onLoadCamera(); break;
        case 15: _t->onLoadCameraFre(); break;
        case 16: _t->onSaveCamera(); break;
        case 17: _t->onResetCamera(); break;
        case 18: _t->onGenerateRoads(); break;
        case 19: _t->onGenerateBlocks(); break;
        case 20: _t->onGenerateParcels(); break;
        case 21: _t->onGenerateBuildings(); break;
        case 22: _t->onGenerateVegetation(); break;
        case 23: _t->onGenerateAll(); break;
        case 24: _t->onGenerateCity(); break;
        case 25: _t->onGenerateScenarios(); break;
        case 26: _t->onViewChanged(); break;
        case 27: _t->onShowWater(); break;
        case 28: _t->onSeaLevel(); break;
        case 29: _t->onShowControlWidget(); break;
        case 30: _t->onToolGenerateBlocks(); break;
        case 31: _t->onToolImageOBB(); break;
        case 32: _t->onParcelClassifer(); break;
        case 33: _t->onLoadSegmentedImage(); break;
        case 34: _t->onLoadParcelImage(); break;
        case 35: _t->onLoadGroundTruth(); break;
        case 36: _t->onLoadWholeImage(); break;
        case 37: _t->onSateLoadOSMRoads(); break;
        case 38: _t->onSateLayout(); break;
        case 39: _t->onLoadLoadGeoInfo(); break;
        case 40: _t->onLoadHeightInfo(); break;
        case 41: _t->onLoadPopulationInfo(); break;
        case 42: _t->onDemoLoadROI(); break;
        case 43: _t->onDemoLayout(); break;
        case 44: _t->onCallPython(); break;
        case 45: _t->onNNanalysis(); break;
        case 46: _t->onNNtest(); break;
        case 47: _t->onEstimate(); break;
        case 48: _t->actionTestBlock(); break;
        case 49: _t->onParaControl(); break;
        case 50: _t->onChangeFov(); break;
        case 51: _t->onComputeSVF(); break;
        case 52: _t->onTestSVF(); break;
        case 53: _t->onGenerateSVFImage(); break;
        case 54: _t->onGenerateHeightImage(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, nullptr, nullptr}
};


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
        if (_id < 55)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 55;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 55)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 55;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
