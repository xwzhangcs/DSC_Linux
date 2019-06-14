/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNewTerrain;
    QAction *actionOpenTerrain;
    QAction *actionExit;
    QAction *actionControlWidget;
    QAction *actionSaveTerrain;
    QAction *actionSaveRoads;
    QAction *actionPropertyWidget;
    QAction *actionLoadRoads;
    QAction *actionClear;
    QAction *actionSaveImage;
    QAction *actionLoadCamera;
    QAction *actionSaveCamera;
    QAction *actionSaveImageHD;
    QAction *actionResetCamera;
    QAction *actionGenerateBlocks;
    QAction *actionGenerateParcels;
    QAction *actionGenerateBuildings;
    QAction *actionGenerateVegetation;
    QAction *actionGenerateAll;
    QAction *actionLoadParcels;
    QAction *actionLoadBuildings;
    QAction *actionGenerateRoads;
    QAction *actionLoadZone;
    QAction *actionSaveParcels;
    QAction *actionSaveBuildings;
    QAction *actionGenerateScenarios;
    QAction *actionView2D;
    QAction *actionView3D;
    QAction *actionSeaLevel;
    QAction *actionShowWater;
    QAction *actionLoadOSMRoads;
    QAction *actionGenerate_Blocks;
    QAction *actionImage_OBB;
    QAction *actionParcelClassifer;
    QAction *actionSateLoadOSMRoads;
    QAction *actionSateGetBlocks;
    QAction *actionSateLayout;
    QAction *actionSateGetBuildings;
    QAction *actionLoadSegmentedImage;
    QAction *actionLoadGeoInfo;
    QAction *actionLoadGroundTruth;
    QAction *actionLoadParcelImage;
    QAction *actionLoadHeightTiff;
    QAction *actionLoadPopulationTiff;
    QAction *actionLoadWholeImage;
    QAction *actionLoadROI;
    QAction *actionLoad_ROI_Image;
    QAction *actionGenerate_ROI_Layout;
    QAction *actionCallPython;
    QAction *actionNNAnalysis;
    QAction *actionNN;
    QAction *actionTestNN;
    QAction *actionParameterControl;
    QAction *actionEstimateFromNN;
    QAction *actionLoadCameraFre;
    QAction *actionChange_Fov;
    QAction *actionComputeSVF;
    QAction *actionTestSVF;
    QAction *actionTest_QPainter;
    QAction *actionGenerate_Height_Map;
    QWidget *centralWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuWindow;
    QMenu *menuPM;
    QMenu *menuView;
    QMenu *menuTools;
    QMenu *menuSatelliate_Image;
    QMenu *menuDemo;
    QToolBar *fileToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1006, 800);
        MainWindow->setMinimumSize(QSize(1000, 800));
        actionNewTerrain = new QAction(MainWindow);
        actionNewTerrain->setObjectName(QStringLiteral("actionNewTerrain"));
        actionOpenTerrain = new QAction(MainWindow);
        actionOpenTerrain->setObjectName(QStringLiteral("actionOpenTerrain"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionControlWidget = new QAction(MainWindow);
        actionControlWidget->setObjectName(QStringLiteral("actionControlWidget"));
        actionSaveTerrain = new QAction(MainWindow);
        actionSaveTerrain->setObjectName(QStringLiteral("actionSaveTerrain"));
        actionSaveRoads = new QAction(MainWindow);
        actionSaveRoads->setObjectName(QStringLiteral("actionSaveRoads"));
        actionPropertyWidget = new QAction(MainWindow);
        actionPropertyWidget->setObjectName(QStringLiteral("actionPropertyWidget"));
        actionLoadRoads = new QAction(MainWindow);
        actionLoadRoads->setObjectName(QStringLiteral("actionLoadRoads"));
        actionClear = new QAction(MainWindow);
        actionClear->setObjectName(QStringLiteral("actionClear"));
        actionSaveImage = new QAction(MainWindow);
        actionSaveImage->setObjectName(QStringLiteral("actionSaveImage"));
        actionLoadCamera = new QAction(MainWindow);
        actionLoadCamera->setObjectName(QStringLiteral("actionLoadCamera"));
        actionSaveCamera = new QAction(MainWindow);
        actionSaveCamera->setObjectName(QStringLiteral("actionSaveCamera"));
        actionSaveImageHD = new QAction(MainWindow);
        actionSaveImageHD->setObjectName(QStringLiteral("actionSaveImageHD"));
        actionResetCamera = new QAction(MainWindow);
        actionResetCamera->setObjectName(QStringLiteral("actionResetCamera"));
        actionGenerateBlocks = new QAction(MainWindow);
        actionGenerateBlocks->setObjectName(QStringLiteral("actionGenerateBlocks"));
        actionGenerateParcels = new QAction(MainWindow);
        actionGenerateParcels->setObjectName(QStringLiteral("actionGenerateParcels"));
        actionGenerateBuildings = new QAction(MainWindow);
        actionGenerateBuildings->setObjectName(QStringLiteral("actionGenerateBuildings"));
        actionGenerateVegetation = new QAction(MainWindow);
        actionGenerateVegetation->setObjectName(QStringLiteral("actionGenerateVegetation"));
        actionGenerateAll = new QAction(MainWindow);
        actionGenerateAll->setObjectName(QStringLiteral("actionGenerateAll"));
        actionLoadParcels = new QAction(MainWindow);
        actionLoadParcels->setObjectName(QStringLiteral("actionLoadParcels"));
        actionLoadBuildings = new QAction(MainWindow);
        actionLoadBuildings->setObjectName(QStringLiteral("actionLoadBuildings"));
        actionGenerateRoads = new QAction(MainWindow);
        actionGenerateRoads->setObjectName(QStringLiteral("actionGenerateRoads"));
        actionLoadZone = new QAction(MainWindow);
        actionLoadZone->setObjectName(QStringLiteral("actionLoadZone"));
        actionSaveParcels = new QAction(MainWindow);
        actionSaveParcels->setObjectName(QStringLiteral("actionSaveParcels"));
        actionSaveBuildings = new QAction(MainWindow);
        actionSaveBuildings->setObjectName(QStringLiteral("actionSaveBuildings"));
        actionGenerateScenarios = new QAction(MainWindow);
        actionGenerateScenarios->setObjectName(QStringLiteral("actionGenerateScenarios"));
        actionView2D = new QAction(MainWindow);
        actionView2D->setObjectName(QStringLiteral("actionView2D"));
        actionView2D->setCheckable(true);
        actionView3D = new QAction(MainWindow);
        actionView3D->setObjectName(QStringLiteral("actionView3D"));
        actionView3D->setCheckable(true);
        actionSeaLevel = new QAction(MainWindow);
        actionSeaLevel->setObjectName(QStringLiteral("actionSeaLevel"));
        actionSeaLevel->setEnabled(false);
        actionSeaLevel->setVisible(false);
        actionShowWater = new QAction(MainWindow);
        actionShowWater->setObjectName(QStringLiteral("actionShowWater"));
        actionShowWater->setCheckable(true);
        actionShowWater->setEnabled(false);
        actionShowWater->setVisible(false);
        actionLoadOSMRoads = new QAction(MainWindow);
        actionLoadOSMRoads->setObjectName(QStringLiteral("actionLoadOSMRoads"));
        actionGenerate_Blocks = new QAction(MainWindow);
        actionGenerate_Blocks->setObjectName(QStringLiteral("actionGenerate_Blocks"));
        actionImage_OBB = new QAction(MainWindow);
        actionImage_OBB->setObjectName(QStringLiteral("actionImage_OBB"));
        actionParcelClassifer = new QAction(MainWindow);
        actionParcelClassifer->setObjectName(QStringLiteral("actionParcelClassifer"));
        actionSateLoadOSMRoads = new QAction(MainWindow);
        actionSateLoadOSMRoads->setObjectName(QStringLiteral("actionSateLoadOSMRoads"));
        actionSateGetBlocks = new QAction(MainWindow);
        actionSateGetBlocks->setObjectName(QStringLiteral("actionSateGetBlocks"));
        actionSateLayout = new QAction(MainWindow);
        actionSateLayout->setObjectName(QStringLiteral("actionSateLayout"));
        actionSateGetBuildings = new QAction(MainWindow);
        actionSateGetBuildings->setObjectName(QStringLiteral("actionSateGetBuildings"));
        actionLoadSegmentedImage = new QAction(MainWindow);
        actionLoadSegmentedImage->setObjectName(QStringLiteral("actionLoadSegmentedImage"));
        actionLoadGeoInfo = new QAction(MainWindow);
        actionLoadGeoInfo->setObjectName(QStringLiteral("actionLoadGeoInfo"));
        actionLoadGroundTruth = new QAction(MainWindow);
        actionLoadGroundTruth->setObjectName(QStringLiteral("actionLoadGroundTruth"));
        actionLoadParcelImage = new QAction(MainWindow);
        actionLoadParcelImage->setObjectName(QStringLiteral("actionLoadParcelImage"));
        actionLoadHeightTiff = new QAction(MainWindow);
        actionLoadHeightTiff->setObjectName(QStringLiteral("actionLoadHeightTiff"));
        actionLoadPopulationTiff = new QAction(MainWindow);
        actionLoadPopulationTiff->setObjectName(QStringLiteral("actionLoadPopulationTiff"));
        actionLoadWholeImage = new QAction(MainWindow);
        actionLoadWholeImage->setObjectName(QStringLiteral("actionLoadWholeImage"));
        actionLoadROI = new QAction(MainWindow);
        actionLoadROI->setObjectName(QStringLiteral("actionLoadROI"));
        actionLoad_ROI_Image = new QAction(MainWindow);
        actionLoad_ROI_Image->setObjectName(QStringLiteral("actionLoad_ROI_Image"));
        actionGenerate_ROI_Layout = new QAction(MainWindow);
        actionGenerate_ROI_Layout->setObjectName(QStringLiteral("actionGenerate_ROI_Layout"));
        actionCallPython = new QAction(MainWindow);
        actionCallPython->setObjectName(QStringLiteral("actionCallPython"));
        actionNNAnalysis = new QAction(MainWindow);
        actionNNAnalysis->setObjectName(QStringLiteral("actionNNAnalysis"));
        actionNN = new QAction(MainWindow);
        actionNN->setObjectName(QStringLiteral("actionNN"));
        actionTestNN = new QAction(MainWindow);
        actionTestNN->setObjectName(QStringLiteral("actionTestNN"));
        actionParameterControl = new QAction(MainWindow);
        actionParameterControl->setObjectName(QStringLiteral("actionParameterControl"));
        actionEstimateFromNN = new QAction(MainWindow);
        actionEstimateFromNN->setObjectName(QStringLiteral("actionEstimateFromNN"));
        actionLoadCameraFre = new QAction(MainWindow);
        actionLoadCameraFre->setObjectName(QStringLiteral("actionLoadCameraFre"));
        actionChange_Fov = new QAction(MainWindow);
        actionChange_Fov->setObjectName(QStringLiteral("actionChange_Fov"));
        actionComputeSVF = new QAction(MainWindow);
        actionComputeSVF->setObjectName(QStringLiteral("actionComputeSVF"));
        actionTestSVF = new QAction(MainWindow);
        actionTestSVF->setObjectName(QStringLiteral("actionTestSVF"));
        actionTest_QPainter = new QAction(MainWindow);
        actionTest_QPainter->setObjectName(QStringLiteral("actionTest_QPainter"));
        actionGenerate_Height_Map = new QAction(MainWindow);
        actionGenerate_Height_Map->setObjectName(QStringLiteral("actionGenerate_Height_Map"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1006, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuWindow = new QMenu(menuBar);
        menuWindow->setObjectName(QStringLiteral("menuWindow"));
        menuPM = new QMenu(menuBar);
        menuPM->setObjectName(QStringLiteral("menuPM"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QStringLiteral("menuView"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QStringLiteral("menuTools"));
        menuSatelliate_Image = new QMenu(menuBar);
        menuSatelliate_Image->setObjectName(QStringLiteral("menuSatelliate_Image"));
        menuDemo = new QMenu(menuBar);
        menuDemo->setObjectName(QStringLiteral("menuDemo"));
        MainWindow->setMenuBar(menuBar);
        fileToolBar = new QToolBar(MainWindow);
        fileToolBar->setObjectName(QStringLiteral("fileToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, fileToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuPM->menuAction());
        menuBar->addAction(menuWindow->menuAction());
        menuBar->addAction(menuSatelliate_Image->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuDemo->menuAction());
        menuFile->addAction(actionLoadZone);
        menuFile->addAction(actionOpenTerrain);
        menuFile->addAction(actionSaveTerrain);
        menuFile->addSeparator();
        menuFile->addAction(actionLoadRoads);
        menuFile->addAction(actionLoadOSMRoads);
        menuFile->addAction(actionSaveRoads);
        menuFile->addSeparator();
        menuFile->addAction(actionLoadParcels);
        menuFile->addAction(actionSaveParcels);
        menuFile->addSeparator();
        menuFile->addAction(actionLoadBuildings);
        menuFile->addAction(actionSaveBuildings);
        menuFile->addSeparator();
        menuFile->addAction(actionClear);
        menuFile->addSeparator();
        menuFile->addAction(actionSaveImage);
        menuFile->addAction(actionSaveImageHD);
        menuFile->addSeparator();
        menuFile->addAction(actionLoadCamera);
        menuFile->addAction(actionLoadCameraFre);
        menuFile->addAction(actionSaveCamera);
        menuFile->addAction(actionResetCamera);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuWindow->addAction(actionControlWidget);
        menuPM->addAction(actionGenerateRoads);
        menuPM->addAction(actionGenerateBlocks);
        menuPM->addAction(actionGenerateParcels);
        menuPM->addAction(actionGenerateBuildings);
        menuPM->addAction(actionGenerateVegetation);
        menuPM->addAction(actionGenerateAll);
        menuPM->addSeparator();
        menuPM->addAction(actionGenerateScenarios);
        menuView->addAction(actionView2D);
        menuView->addAction(actionView3D);
        menuView->addSeparator();
        menuView->addAction(actionShowWater);
        menuView->addAction(actionSeaLevel);
        menuTools->addAction(actionGenerate_Blocks);
        menuTools->addAction(actionImage_OBB);
        menuTools->addAction(actionParcelClassifer);
        menuTools->addAction(actionCallPython);
        menuTools->addAction(actionNNAnalysis);
        menuTools->addAction(actionTestNN);
        menuTools->addAction(actionNN);
        menuTools->addAction(actionParameterControl);
        menuTools->addAction(actionEstimateFromNN);
        menuTools->addAction(actionChange_Fov);
        menuTools->addAction(actionTestSVF);
        menuTools->addAction(actionComputeSVF);
        menuTools->addAction(actionTest_QPainter);
        menuTools->addAction(actionGenerate_Height_Map);
        menuSatelliate_Image->addAction(actionLoadGeoInfo);
        menuSatelliate_Image->addAction(actionLoadHeightTiff);
        menuSatelliate_Image->addAction(actionLoadPopulationTiff);
        menuSatelliate_Image->addAction(actionLoadSegmentedImage);
        menuSatelliate_Image->addAction(actionLoadParcelImage);
        menuSatelliate_Image->addAction(actionLoadWholeImage);
        menuSatelliate_Image->addAction(actionLoadGroundTruth);
        menuSatelliate_Image->addAction(actionSateLoadOSMRoads);
        menuSatelliate_Image->addAction(actionSateLayout);
        menuDemo->addAction(actionLoadROI);
        menuDemo->addAction(actionGenerate_ROI_Layout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Simple Cities", Q_NULLPTR));
        actionNewTerrain->setText(QApplication::translate("MainWindow", "New Terrain", Q_NULLPTR));
        actionNewTerrain->setShortcut(QString());
        actionOpenTerrain->setText(QApplication::translate("MainWindow", "Open Terrain", Q_NULLPTR));
        actionOpenTerrain->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", Q_NULLPTR));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", Q_NULLPTR));
        actionControlWidget->setText(QApplication::translate("MainWindow", "Control Widget", Q_NULLPTR));
        actionSaveTerrain->setText(QApplication::translate("MainWindow", "Save Terrain", Q_NULLPTR));
        actionSaveTerrain->setShortcut(QString());
        actionSaveRoads->setText(QApplication::translate("MainWindow", "Save Roads", Q_NULLPTR));
        actionPropertyWidget->setText(QApplication::translate("MainWindow", "Property Widget", Q_NULLPTR));
        actionLoadRoads->setText(QApplication::translate("MainWindow", "Load Roads", Q_NULLPTR));
        actionClear->setText(QApplication::translate("MainWindow", "Clear", Q_NULLPTR));
        actionClear->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", Q_NULLPTR));
        actionSaveImage->setText(QApplication::translate("MainWindow", "Save Image", Q_NULLPTR));
        actionSaveImage->setShortcut(QApplication::translate("MainWindow", "Ctrl+L", Q_NULLPTR));
        actionLoadCamera->setText(QApplication::translate("MainWindow", "Load Camera", Q_NULLPTR));
        actionLoadCamera->setShortcut(QApplication::translate("MainWindow", "Ctrl+1", Q_NULLPTR));
        actionSaveCamera->setText(QApplication::translate("MainWindow", "Save Camera", Q_NULLPTR));
        actionSaveCamera->setShortcut(QApplication::translate("MainWindow", "Ctrl+2", Q_NULLPTR));
        actionSaveImageHD->setText(QApplication::translate("MainWindow", "Save Image HD", Q_NULLPTR));
        actionSaveImageHD->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", Q_NULLPTR));
        actionResetCamera->setText(QApplication::translate("MainWindow", "Reset Camera", Q_NULLPTR));
        actionGenerateBlocks->setText(QApplication::translate("MainWindow", "Generate Blocks", Q_NULLPTR));
        actionGenerateParcels->setText(QApplication::translate("MainWindow", "Generate Parcels", Q_NULLPTR));
        actionGenerateBuildings->setText(QApplication::translate("MainWindow", "Generate Buildings", Q_NULLPTR));
        actionGenerateVegetation->setText(QApplication::translate("MainWindow", "Generate Vegetation", Q_NULLPTR));
        actionGenerateAll->setText(QApplication::translate("MainWindow", "Generate All", Q_NULLPTR));
        actionLoadParcels->setText(QApplication::translate("MainWindow", "Load Parcels", Q_NULLPTR));
        actionLoadBuildings->setText(QApplication::translate("MainWindow", "Load Buildings", Q_NULLPTR));
        actionGenerateRoads->setText(QApplication::translate("MainWindow", "Generate Roads", Q_NULLPTR));
        actionGenerateRoads->setShortcut(QApplication::translate("MainWindow", "Ctrl+R", Q_NULLPTR));
        actionLoadZone->setText(QApplication::translate("MainWindow", "Load Zone", Q_NULLPTR));
        actionSaveParcels->setText(QApplication::translate("MainWindow", "Save Parcels", Q_NULLPTR));
        actionSaveBuildings->setText(QApplication::translate("MainWindow", "Save Buildings", Q_NULLPTR));
        actionGenerateScenarios->setText(QApplication::translate("MainWindow", "Generate Scenarios", Q_NULLPTR));
        actionView2D->setText(QApplication::translate("MainWindow", "2D", Q_NULLPTR));
        actionView3D->setText(QApplication::translate("MainWindow", "3D", Q_NULLPTR));
        actionSeaLevel->setText(QApplication::translate("MainWindow", "Sea Level", Q_NULLPTR));
        actionShowWater->setText(QApplication::translate("MainWindow", "Show Water", Q_NULLPTR));
        actionLoadOSMRoads->setText(QApplication::translate("MainWindow", "Load OSM Roads", Q_NULLPTR));
        actionGenerate_Blocks->setText(QApplication::translate("MainWindow", "Generate Blocks", Q_NULLPTR));
        actionImage_OBB->setText(QApplication::translate("MainWindow", "Image OBB", Q_NULLPTR));
        actionParcelClassifer->setText(QApplication::translate("MainWindow", "Parcel Classifer", Q_NULLPTR));
        actionSateLoadOSMRoads->setText(QApplication::translate("MainWindow", "Load OSM Roads", Q_NULLPTR));
        actionSateGetBlocks->setText(QApplication::translate("MainWindow", "Get Blocks", Q_NULLPTR));
        actionSateLayout->setText(QApplication::translate("MainWindow", "Generate Urban Layout", Q_NULLPTR));
        actionSateGetBuildings->setText(QApplication::translate("MainWindow", "Get Buildings", Q_NULLPTR));
        actionLoadSegmentedImage->setText(QApplication::translate("MainWindow", "Load Segmented Image", Q_NULLPTR));
        actionLoadGeoInfo->setText(QApplication::translate("MainWindow", "Load GeoTiff Image", Q_NULLPTR));
        actionLoadGroundTruth->setText(QApplication::translate("MainWindow", "Load Ground Truth", Q_NULLPTR));
        actionLoadParcelImage->setText(QApplication::translate("MainWindow", "Load Parcel Image", Q_NULLPTR));
        actionLoadHeightTiff->setText(QApplication::translate("MainWindow", "Load Height Tiff", Q_NULLPTR));
        actionLoadPopulationTiff->setText(QApplication::translate("MainWindow", "Load Population Tiff", Q_NULLPTR));
        actionLoadWholeImage->setText(QApplication::translate("MainWindow", "Load Whole Image", Q_NULLPTR));
        actionLoadROI->setText(QApplication::translate("MainWindow", "Load Road Network", Q_NULLPTR));
        actionLoad_ROI_Image->setText(QApplication::translate("MainWindow", "Load ROI Image", Q_NULLPTR));
        actionGenerate_ROI_Layout->setText(QApplication::translate("MainWindow", "Generate Urban Layout", Q_NULLPTR));
        actionCallPython->setText(QApplication::translate("MainWindow", "Call Python", Q_NULLPTR));
        actionNNAnalysis->setText(QApplication::translate("MainWindow", "NN Analysis", Q_NULLPTR));
        actionNN->setText(QApplication::translate("MainWindow", "TestOneNN", Q_NULLPTR));
        actionTestNN->setText(QApplication::translate("MainWindow", "FilterBlock", Q_NULLPTR));
        actionParameterControl->setText(QApplication::translate("MainWindow", "ParameterControl", Q_NULLPTR));
        actionEstimateFromNN->setText(QApplication::translate("MainWindow", "EstimateFromNN", Q_NULLPTR));
        actionLoadCameraFre->setText(QApplication::translate("MainWindow", "Load Camera Frequency", Q_NULLPTR));
        actionChange_Fov->setText(QApplication::translate("MainWindow", "Change Fov", Q_NULLPTR));
        actionComputeSVF->setText(QApplication::translate("MainWindow", "Compute SVF", Q_NULLPTR));
        actionTestSVF->setText(QApplication::translate("MainWindow", "Test SVF", Q_NULLPTR));
        actionTest_QPainter->setText(QApplication::translate("MainWindow", "Generate SVF Map", Q_NULLPTR));
        actionGenerate_Height_Map->setText(QApplication::translate("MainWindow", "Generate Height Map", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuWindow->setTitle(QApplication::translate("MainWindow", "Window", Q_NULLPTR));
        menuPM->setTitle(QApplication::translate("MainWindow", "PM", Q_NULLPTR));
        menuView->setTitle(QApplication::translate("MainWindow", "View", Q_NULLPTR));
        menuTools->setTitle(QApplication::translate("MainWindow", "Tools", Q_NULLPTR));
        menuSatelliate_Image->setTitle(QApplication::translate("MainWindow", "Satelliate Image", Q_NULLPTR));
        menuDemo->setTitle(QApplication::translate("MainWindow", "Demo", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
