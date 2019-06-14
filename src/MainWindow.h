#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "glew.h"
#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include "ControlWidget.h"
#include "GLWidget3D.h"
#include "UrbanGeometry.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	Ui::MainWindow ui;
	ControlWidget* controlWidget;
	GLWidget3D* glWidget;
	UrbanGeometry* urbanGeometry;
	int thresh;
	int max_thresh;
	cv::RNG rng;

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

	void setParameters();
	void setBlocksParameters();
	std::vector<std::string> get_all_files_names_within_folder(std::string folder);
	void testOneNN(int index);

protected:
	void keyPressEvent(QKeyEvent* e);
	void keyReleaseEvent(QKeyEvent* e);

public slots:
	void onLoadZone();
	void onNewTerrain();
	void onLoadTerrain();
	void onSaveTerrain();
	void onLoadRoads();
	void onLoadOSMRoads();
	void onSaveRoads();
	void onLoadParcels();
	void onSaveParcels();
	void onLoadBuildings();
	void onSaveBuildings();
	void onClear();

	void onSaveImage();
	void onSaveImageHD();
	void onLoadCamera();
	void onLoadCameraFre();
	void onSaveCamera();
	void onResetCamera();

	void onGenerateRoads();
	void onGenerateBlocks();
	void onGenerateParcels();
	void onGenerateBuildings();
	void onGenerateVegetation();
	void onGenerateAll();

	void onGenerateCity();
	void onGenerateScenarios();

	void onViewChanged();
	void onShowWater();
	void onSeaLevel();
	void onShowControlWidget();

	void onToolGenerateBlocks();
	void onToolImageOBB();
	void onParcelClassifer();
	void onLoadSegmentedImage();
	void onLoadParcelImage();
	void onLoadGroundTruth();
	void onLoadWholeImage();

	void onSateLoadOSMRoads();
	void onSateLayout();
	void onLoadLoadGeoInfo();
	void onLoadHeightInfo();
	void onLoadPopulationInfo();

	// demo
	void onDemoLoadROI();
	void onDemoLayout();

	//
	void onCallPython();
	void onNNanalysis();
	void onNNtest();
	void onEstimate();
	void actionTestBlock();
	void onParaControl();
	void onChangeFov();
	void onComputeSVF();
	void onTestSVF();
	void onGenerateSVFImage();
	void onGenerateHeightImage();
};

#endif // MAINWINDOW_H
