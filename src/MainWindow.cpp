#include "MainWindow.h"
#include <QFileDialog>
#include <QShortcut>
#include "TerrainSizeInputDialog.h"
#include "ScenarioGenerationDialog.h"
#include "GenerateBlocksDlg.h"
#include "ParameterControlDlg.h"
#include "ChangeFovDlg.h"
#include "ImageOBBDlg.h"
#include "GraphUtil.h"
#include "Util.h"
#include "caffe_wrapper.h"
#include "Regression.h"
#include <QInputDialog>
#include <Python.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
	std::cout << "Going to MainWindow" << std::endl;
	ui.setupUi(this);

	QActionGroup* group = new QActionGroup(this);
	group->addAction(ui.actionView2D);
	group->addAction(ui.actionView3D);
	ui.actionView2D->setChecked(true);
	ui.actionView3D->setChecked(false);

	// setup the docking widgets
	controlWidget = new ControlWidget(this);

	// register the menu's action handlers
	connect(ui.actionLoadZone, SIGNAL(triggered()), this, SLOT(onLoadZone()));
	connect(ui.actionNewTerrain, SIGNAL(triggered()), this, SLOT(onNewTerrain()));
	connect(ui.actionOpenTerrain, SIGNAL(triggered()), this, SLOT(onLoadTerrain()));
	connect(ui.actionSaveTerrain, SIGNAL(triggered()), this, SLOT(onSaveTerrain()));
	connect(ui.actionLoadRoads, SIGNAL(triggered()), this, SLOT(onLoadRoads()));
	connect(ui.actionLoadOSMRoads, SIGNAL(triggered()), this, SLOT(onLoadOSMRoads()));
	connect(ui.actionSaveRoads, SIGNAL(triggered()), this, SLOT(onSaveRoads()));
	connect(ui.actionLoadParcels, SIGNAL(triggered()), this, SLOT(onLoadParcels()));
	connect(ui.actionSaveParcels, SIGNAL(triggered()), this, SLOT(onSaveParcels()));
	connect(ui.actionLoadBuildings, SIGNAL(triggered()), this, SLOT(onLoadBuildings()));
	connect(ui.actionSaveBuildings, SIGNAL(triggered()), this, SLOT(onSaveBuildings()));
	connect(ui.actionClear, SIGNAL(triggered()), this, SLOT(onClear()));

	connect(ui.actionSaveImage, SIGNAL(triggered()), this, SLOT(onSaveImage()));
	connect(ui.actionSaveImageHD, SIGNAL(triggered()), this, SLOT(onSaveImageHD()));
	connect(ui.actionLoadCamera, SIGNAL(triggered()), this, SLOT(onLoadCamera()));
	connect(ui.actionLoadCameraFre, SIGNAL(triggered()), this, SLOT(onLoadCameraFre()));
	connect(ui.actionSaveCamera, SIGNAL(triggered()), this, SLOT(onSaveCamera()));
	connect(ui.actionResetCamera, SIGNAL(triggered()), this, SLOT(onResetCamera()));
	connect(ui.actionExit, SIGNAL(triggered()), this, SLOT(close()));

	connect(ui.actionGenerateRoads, SIGNAL(triggered()), this, SLOT(onGenerateRoads()));
	connect(ui.actionGenerateBlocks, SIGNAL(triggered()), this, SLOT(onGenerateBlocks()));
	connect(ui.actionGenerateParcels, SIGNAL(triggered()), this, SLOT(onGenerateParcels()));
	connect(ui.actionGenerateBuildings, SIGNAL(triggered()), this, SLOT(onGenerateBuildings()));
	connect(ui.actionGenerateVegetation, SIGNAL(triggered()), this, SLOT(onGenerateVegetation()));
	connect(ui.actionGenerateAll, SIGNAL(triggered()), this, SLOT(onGenerateAll()));

	connect(ui.actionGenerateScenarios, SIGNAL(triggered()), this, SLOT(onGenerateScenarios()));

	connect(ui.actionView2D, SIGNAL(triggered()), this, SLOT(onViewChanged()));
	connect(ui.actionView3D, SIGNAL(triggered()), this, SLOT(onViewChanged()));
	connect(ui.actionShowWater, SIGNAL(triggered()), this, SLOT(onShowWater()));
	connect(ui.actionSeaLevel, SIGNAL(triggered()), this, SLOT(onSeaLevel()));
	connect(ui.actionControlWidget, SIGNAL(triggered()), this, SLOT(onShowControlWidget()));

	connect(ui.actionGenerate_Blocks, SIGNAL(triggered()), this, SLOT(onToolGenerateBlocks()));
	connect(ui.actionImage_OBB, SIGNAL(triggered()), this, SLOT(onToolImageOBB()));
	connect(ui.actionParcelClassifer, SIGNAL(triggered()), this, SLOT(onParcelClassifer()));
	connect(ui.actionCallPython, SIGNAL(triggered()), this, SLOT(onCallPython()));
	connect(ui.actionNNAnalysis, SIGNAL(triggered()), this, SLOT(onNNanalysis())); 
	connect(ui.actionNN, SIGNAL(triggered()), this, SLOT(onNNtest()));
	connect(ui.actionEstimateFromNN, SIGNAL(triggered()), this, SLOT(onEstimate()));
	connect(ui.actionTestNN, SIGNAL(triggered()), this, SLOT(actionTestBlock()));
	connect(ui.actionParameterControl, SIGNAL(triggered()), this, SLOT(onParaControl()));
	connect(ui.actionChange_Fov, SIGNAL(triggered()), this, SLOT(onChangeFov())); 
	connect(ui.actionComputeSVF, SIGNAL(triggered()), this, SLOT(onComputeSVF()));
	connect(ui.actionTestSVF, SIGNAL(triggered()), this, SLOT(onTestSVF())); 
	connect(ui.actionTest_QPainter, SIGNAL(triggered()), this, SLOT(onGenerateSVFImage()));
	connect(ui.actionGenerate_Height_Map, SIGNAL(triggered()), this, SLOT(onGenerateHeightImage()));

	connect(ui.actionLoadGeoInfo, SIGNAL(triggered()), this, SLOT(onLoadLoadGeoInfo()));
	connect(ui.actionLoadSegmentedImage, SIGNAL(triggered()), this, SLOT(onLoadSegmentedImage()));
	connect(ui.actionLoadHeightTiff, SIGNAL(triggered()), this, SLOT(onLoadHeightInfo()));
	connect(ui.actionLoadPopulationTiff, SIGNAL(triggered()), this, SLOT(onLoadPopulationInfo()));
	connect(ui.actionLoadParcelImage, SIGNAL(triggered()), this, SLOT(onLoadParcelImage()));
	connect(ui.actionLoadGroundTruth, SIGNAL(triggered()), this, SLOT(onLoadGroundTruth()));
	connect(ui.actionLoadWholeImage, SIGNAL(triggered()), this, SLOT(onLoadWholeImage()));
	connect(ui.actionSateLoadOSMRoads, SIGNAL(triggered()), this, SLOT(onSateLoadOSMRoads()));
	connect(ui.actionSateLayout, SIGNAL(triggered()), this, SLOT(onSateLayout()));

	connect(ui.actionLoadROI, SIGNAL(triggered()), this, SLOT(onDemoLoadROI()));
	connect(ui.actionGenerate_ROI_Layout, SIGNAL(triggered()), this, SLOT(onDemoLayout()));

	// setup the GL widget
	glWidget = new GLWidget3D(this);
	setCentralWidget(glWidget);

	//controlWidget->show();
	//addDockWidget(Qt::LeftDockWidgetArea, controlWidget);

	//urbanGeometry = new UrbanGeometry(this);
}

MainWindow::~MainWindow() {
}

void MainWindow::setParameters() {
	G::global()["avenueAvgSegmentLength"] = controlWidget->ui.lineEditAvenueSegmentLength->text().toFloat();
	G::global()["road_base_orientation"] = controlWidget->ui.lineEditRoadBaseOrientation->text().toFloat();
	G::global()["road_curvature"] = controlWidget->ui.lineEditRoadCurvature->text().toFloat();
	G::global()["major_road_width"] = controlWidget->ui.lineEditMajorRoadWidth->text().toFloat();
	G::global()["minor_road_width"] = controlWidget->ui.lineEditMinorRoadWidth->text().toFloat();
	G::global()["use_elevation_for_road_generation"] = controlWidget->ui.checkBoxUseElevation->isChecked();
	G::global()["parksRatio"] = controlWidget->ui.lineEditParkRatio->text().toFloat();
	G::global()["parcel_area_mean"] = controlWidget->ui.lineEditParcelArea->text().toFloat();
	G::global()["parcel_area_deviation"] = controlWidget->ui.lineEditParcelAreaDev->text().toFloat();
	G::global()["parcel_setback_front"] = controlWidget->ui.lineEditSetbackFront->text().toFloat();
	G::global()["parcel_setback_rear"] = controlWidget->ui.lineEditSetbackRear->text().toFloat();
	G::global()["parcel_setback_sides"] = controlWidget->ui.lineEditSetbackSide->text().toFloat();
	G::global()["building_stories_min"] = controlWidget->ui.lineEditNumStoriesMin->text().toFloat();
	G::global()["building_stories_max"] = controlWidget->ui.lineEditNumStoriesMax->text().toFloat();
	G::global()["building_min_dimension"] = controlWidget->ui.lineEditMinBuildingDim->text().toFloat();
}

void MainWindow::setBlocksParameters(){
	G::global()["parksRatio"] = 0.0f;
}

void MainWindow::keyPressEvent(QKeyEvent* e) {
	glWidget->keyPressEvent(e);
}

void MainWindow::keyReleaseEvent(QKeyEvent* e) {
	glWidget->keyReleaseEvent(e);
}

void MainWindow::onLoadZone() {
	QString filename = QFileDialog::getOpenFileName(this, tr("Load zone..."), "", tr("Shapefiles (*.shp)"));
	if (filename.isEmpty()) return;

	urbanGeometry->loadZone(filename.toUtf8().constData());
	glWidget->updateGL();
}

void MainWindow::onNewTerrain() {
	TerrainSizeInputDialog dlg(this);
	if (dlg.exec() == QDialog::Accepted) {
		glWidget->vboRenderManager.changeTerrainDimensions(glm::vec2(dlg.side, dlg.side));
		glWidget->shadow.makeShadowMap(glWidget);
		glWidget->updateGL();
	}
}

void MainWindow::onLoadTerrain() {
	QString filename = QFileDialog::getOpenFileName(this, tr("Load DEM file..."), "", tr("DEM Files (*.tif)"));
	if (filename.isEmpty()) return;

	urbanGeometry->loadTerrain(filename.toUtf8().constData());
	glWidget->shadow.makeShadowMap(glWidget);
	glWidget->updateGL();
}

void MainWindow::onSaveTerrain() {
	QString filename = QFileDialog::getSaveFileName(this, tr("Save Terrain file..."), "", tr("Terrain Files (*.png)"));
	if (filename.isEmpty()) return;
	glWidget->vboRenderManager.vboTerrain.saveTerrain(filename);
}

void MainWindow::onLoadRoads() {
	QString filename = QFileDialog::getOpenFileName(this, tr("Load roads..."), "", tr("Shapefiles (*.shp)"));
	if (filename.isEmpty()) return;

	urbanGeometry->clear();
	urbanGeometry->loadRoads(filename.toUtf8().constData());
	glWidget->shadow.makeShadowMap(glWidget);
	glWidget->updateGL();
}

void MainWindow::onLoadOSMRoads() {
	QString filename = QFileDialog::getOpenFileName(this, tr("Load roads..."), "", tr("OSM files (*.osm)"));
	if (filename.isEmpty()) return;
	glWidget->vboRenderManager.changeTerrainDimensions(glm::vec2(2500, 2500));
	urbanGeometry->clear();
	urbanGeometry->loadOSMRoads(filename.toUtf8().constData());
	glWidget->shadow.makeShadowMap(glWidget);
	glWidget->updateGL();
}

void MainWindow::onSateLoadOSMRoads(){
	glWidget->vboRenderManager.changeTerrainDimensions(glm::vec2(2500, 2500));
	QString filename = QFileDialog::getOpenFileName(this, tr("Load roads..."), "", tr("OSM files (*.osm)"));
	if (filename.isEmpty()) return;

	urbanGeometry->clear();
	urbanGeometry->loadOSMRoads(filename.toUtf8().constData());
	glWidget->shadow.makeShadowMap(glWidget);
	glWidget->updateGL();
}

void MainWindow::onDemoLoadROI(){
	// For Toulouse
	//int terrainSize_x = 2100;
	//int terrainSize_y = 1200;
	// for chicago
	int terrainSize_x = 2500;
	int terrainSize_y = 2500;
	// for new orleans
	//int terrainSize_x = 2500;
	//int terrainSize_y = 2500;
	// for paris
	//int terrainSize_x = 2200;
	//int terrainSize_y = 2900;
	// for Dublin
	//int terrainSize_x = 2400;
	//int terrainSize_y = 2100;
	// for HK
	//int terrainSize_x = 1000;
	//int terrainSize_y = 1000;
	// small chicago
	//int terrainSize_x = 500;
	//int terrainSize_y = 500;
	int resize_factor = 4;
	// Load the directory for ROI
	QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
	if (dir.isEmpty()) return;
	std::cout <<"ROI dir is " << dir.toUtf8().data() << std::endl;

	// Load OSM road
	glWidget->vboRenderManager.changeTerrainDimensions(glm::vec2(terrainSize_x, terrainSize_y));
	//QString filename = dir + "/Streets.osm";
	QString filename = dir + "/Whole.osm";
	if (!QFile(filename).exists()) {
		return;
	}
	urbanGeometry->clear();
	urbanGeometry->loadOSMRoads(filename.toUtf8().constData());
	glWidget->shadow.makeShadowMap(glWidget);
	glWidget->updateGL();
	std::cout << "Finish loading OSM road!!" << std::endl;

	// Load autoLabeled image
	//QString filename_tif = dir + "/Truth.tif";
	QString filename_tif = dir + "/labeled.tif";
	if (!QFile(filename_tif).exists()) {
		return;
	}
	std::vector<double> result = Util::getGeoInfo(filename_tif.toUtf8().data());
	G::global()["origin_long"] = result.at(0);
	G::global()["origin_lat"] = result.at(1);
	G::global()["pixel_size_long"] = result.at(2);
	G::global()["pixel_size_lat"] = result.at(3);
	std::cout << "Finish loading Geo Info for the segmented image!!" << std::endl;

	// load the labeled image
	//QString filename_labeled = dir + "/Truth.png";
	QString filename_labeled = dir + "/labeled.png";
	if (!QFile(filename_labeled).exists())  return;
	G::global()["segmented_image"] = filename_labeled;
	std::cout << "Finish loading labeled image!!" << std::endl;

	// load the height tif
	QString filename_height = dir + "/building_heights.tiff";
	if (QFile(filename_height).exists()){
		G::global()["height_tif"] = filename_height;
		std::cout << "Finish loading height image!!" << std::endl;
	}

	// load the building type tif
	QString filename_building_type = dir + "/building_types.tiff";
	if (QFile(filename_building_type).exists()){
		G::global()["building_type_tif"] = filename_building_type;
		std::cout << "Finish loading building type image!!" << std::endl;
	}

	// get long/lat coordinate for terrian corners
	QVector2D bot_left = Util::getLongLatCoord(-resize_factor * terrainSize_x / 2.0f, -resize_factor * terrainSize_y / 2.0f);
	QVector2D bot_right = Util::getLongLatCoord(resize_factor * terrainSize_x / 2.0f, -resize_factor * terrainSize_y / 2.0f);
	QVector2D up_left = Util::getLongLatCoord(-resize_factor * terrainSize_x / 2.0f, resize_factor * terrainSize_y / 2.0f);
	QVector2D up_right = Util::getLongLatCoord(resize_factor * terrainSize_x / 2.0f, resize_factor * terrainSize_y / 2.0f);
	{
		std::cout << "Terrian bot_left is (" << bot_left.x() << ", " << bot_left.y() << ")" << std::endl;
		std::cout << "Terrian bot_right is (" << bot_right.x() << ", " << bot_right.y() << ")" << std::endl;
		std::cout << "Terrian up_left is (" << up_left.x() << ", " << up_left.y() << ")" << std::endl;
		std::cout << "Terrian up_right is (" << up_right.x() << ", " << up_right.y() << ")" << std::endl;
	}
}

void MainWindow::onSaveRoads() {
	QString filename = QFileDialog::getSaveFileName(this, tr("Save roads..."), "", tr("Shapefiles Files (*.shp)"));
	if (filename.isEmpty()) return;

	QApplication::setOverrideCursor(Qt::WaitCursor);

	urbanGeometry->saveRoads(filename.toUtf8().constData());

	QApplication::restoreOverrideCursor();
}

void MainWindow::onLoadParcels() {
	QString filename = QFileDialog::getOpenFileName(this, tr("Load parcels..."), "", tr("Shapefiles (*.shp)"));
	if (filename.isEmpty()) return;

	urbanGeometry->loadParcels(filename.toUtf8().constData());
	glWidget->updateGL();
}

void MainWindow::onSaveParcels() {
	QString filename = QFileDialog::getSaveFileName(this, tr("Save parcels..."), "", tr("Shapefiles (*.shp)"));
	if (filename.isEmpty()) return;

	urbanGeometry->saveParcels(filename.toUtf8().constData());
	glWidget->updateGL();
}

void MainWindow::onLoadBuildings() {
	QString filename = QFileDialog::getOpenFileName(this, tr("Load buildings..."), "", tr("Shapefiles (*.shp)"));
	if (filename.isEmpty()) return;

	urbanGeometry->loadBuildings(filename.toUtf8().constData());
	glWidget->updateGL();
}

void MainWindow::onSaveBuildings() {
	QString filename = QFileDialog::getSaveFileName(this, tr("Load buildings..."), "", tr("Shapefiles (*.shp)"));
	if (filename.isEmpty()) return;

	urbanGeometry->saveBuildings(filename.toUtf8().constData());
	glWidget->updateGL();
}

void MainWindow::onClear() {
	urbanGeometry->clear();
	glWidget->shadow.makeShadowMap(glWidget);
	glWidget->updateGL();
}

void MainWindow::onSaveImage() {
	if (!QDir("screenshots").exists()) QDir().mkdir("screenshots");
	QString fileName = "screenshots/" + QDate::currentDate().toString("yyMMdd") + "_" + QTime::currentTime().toString("HHmmss") + ".png";
	glWidget->grabFrameBuffer().save(fileName);
}

void MainWindow::onSaveImageHD() {
	if (!QDir("screenshots").exists()) QDir().mkdir("screenshots");
	QString fileName = "screenshots/" + QDate::currentDate().toString("yyMMdd") + "_" + QTime::currentTime().toString("HHmmss") + "_HD.png";
	int cH = glWidget->height();
	int cW = glWidget->width();
	glWidget->resize(cW * 10, cH * 10);
	glWidget->updateGL();
	glWidget->grabFrameBuffer().save(fileName);
	glWidget->resize(cW,cH);
	glWidget->updateGL();
}

void MainWindow::onLoadCameraFre() {
	QString filename = QFileDialog::getOpenFileName(this, tr("Open Camera file..."), "", tr("Camera files (*.txt)"));
	if (filename.isEmpty()) return;
	std::ifstream in(filename.toUtf8().constData());

	std::string line;
	float x, y, z;
	int index = 0;
	std::vector<std::string> last;
	if (in.is_open())
	{
		while (getline(in, line))
		{
			std::cout << "cam view is " << line << std::endl;
			std::stringstream ss(line);
			std::string token;
			std::vector<std::string> paras;
			while (std::getline(ss, token, ',')) {
				//paras.push_back(stof(token));
				paras.push_back(token);
			}
			if (index != 0)
			{
				if (paras == last)
					continue;
			}
			//rot
			x = stof(paras.at(0));
			y = stof(paras.at(1));
			z = stof(paras.at(2));
			glWidget->camera.rot = QVector3D(x, y, z);
			//pos
			x = stof(paras.at(3));
			y = stof(paras.at(4));
			z = stof(paras.at(5));
			glWidget->camera.pos = QVector3D(x, y, z);
			//
			x = stof(paras.at(6));
			y = stof(paras.at(7));
			z = stof(paras.at(8));
			glWidget->camera.lookAt = QVector3D(x, y, z);
			//update
			glWidget->updateCamera();
			glWidget->updateGL();
			// copu paras to last
			last = paras;
			//save images
			QString fileName = "screenshots/" + QString::number(index) + ".png";
			int cH = glWidget->height();
			int cW = glWidget->width();
			glWidget->resize(cW * 2, cH * 2);
			glWidget->updateGL();
			glWidget->grabFrameBuffer().save(fileName);
			glWidget->resize(cW, cH);
			glWidget->updateGL();
			index++;
		}
		in.close();
	}
}

void MainWindow::onLoadCamera(){
	QString filename = QFileDialog::getOpenFileName(this, tr("Open Camera file..."), "", tr("Camera files (*.cam)"));
	if (filename.isEmpty()) return;
	glWidget->camera.loadCameraPose(filename.toUtf8().constData());
	glWidget->updateCamera();
	glWidget->updateGL();

}

void MainWindow::onSaveCamera() {
	QString filename = QFileDialog::getSaveFileName(this, tr("Save Camera file..."), "", tr("Camera files (*.cam)"));
	if (filename.isEmpty()) return;
	
	glWidget->camera.saveCameraPose(filename.toUtf8().constData());
}

void MainWindow::onResetCamera() {
	glWidget->camera.resetCamera();
	glWidget->updateCamera();
	glWidget->updateGL();
}

void MainWindow::onGenerateRoads() {
	setParameters();
	urbanGeometry->generateRoads();
	glWidget->shadow.makeShadowMap(glWidget);
	glWidget->updateGL();
}

void MainWindow::onGenerateBlocks() {
	setParameters();
	urbanGeometry->generateBlocks();
	glWidget->shadow.makeShadowMap(glWidget);
	glWidget->updateGL();
}

void MainWindow::onGenerateParcels() {
	setParameters();
	urbanGeometry->generateParcels();
	glWidget->shadow.makeShadowMap(glWidget);
	glWidget->updateGL();
}

void MainWindow::onSateLayout(){
	// blocks
	setBlocksParameters();
	urbanGeometry->sateGetBlocks();
	glWidget->shadow.makeShadowMap(glWidget);
	glWidget->updateGL();
	// parcels
	urbanGeometry->sateGetParcels(300.0, 570, -1, true);
	glWidget->shadow.makeShadowMap(glWidget);
	glWidget->updateGL();
	// buildings
	urbanGeometry->sateGetBuildings(1.0f);
	glWidget->shadow.makeShadowMap(glWidget);
	glWidget->updateGL();
}

void MainWindow::onDemoLayout(){
	// blocks
	setBlocksParameters();
	urbanGeometry->sateGetBlocks();
	glWidget->shadow.makeShadowMap(glWidget);
	glWidget->updateGL();

	// extrude buildings testing
	/*{
		urbanGeometry->sateGetParcelsAndBuildings();
		glWidget->shadow.makeShadowMap(glWidget);
		glWidget->updateGL();
	}*/
	// parcels
	// small chicago
	//urbanGeometry->sateGetParcels(300.0, 570, -1, false);
	// chicago
	urbanGeometry->sateGetParcels(222.507, 471.776, -1, false);
	// chicago comparison
	//urbanGeometry->sateGetParcels(222.79, 463.082, -1, false);
	// new orleans	
	//urbanGeometry->sateGetParcels(388.2096, 888.4954, -1, false);
	//Toulouse
	//urbanGeometry->sateGetParcels(369.322, 914.775, -1, false);
	//Toulouse comparison
	//urbanGeometry->sateGetParcels(416.653, 626.061, -1, false);
	//Paris
	//urbanGeometry->sateGetParcels(499.928, 1058, -1, false);
	// Dublin
	//urbanGeometry->sateGetParcels(427.728, 589.543, -1, false);
	// HK
	//urbanGeometry->sateGetParcels(223.697, 502.541, -1, false);
	glWidget->shadow.makeShadowMap(glWidget);
	glWidget->updateGL();

	// buildings
	// small chicago
	//urbanGeometry->sateGetBuildings(1.0f);
	//chicago
	urbanGeometry->sateGetBuildings(0.784858f);
	//chicago comparison
	//urbanGeometry->sateGetBuildings(1.36151f);
	//urbanGeometry->sateGetBuildings(1.2f);
	// new orleans 1.16197
	//urbanGeometry->sateGetBuildings(1.16197f);
	//Toulouse
	//urbanGeometry->sateGetBuildings(0.368552);
	//Toulouse comparison
	//urbanGeometry->sateGetBuildings(0.54514f);
	//Paris
	//urbanGeometry->sateGetBuildings(0.377203);
	// Dublin
	//urbanGeometry->sateGetBuildings(0.506804);
	// HK
	//urbanGeometry->sateGetBuildings(1.02586);
	glWidget->shadow.makeShadowMap(glWidget);
	glWidget->updateGL();
	/*
	// buildings
	int height = -50;
	int step = 1;
	int total = abs(height) / step + 20;
	QString filename = "source/base_level.txt";
	for (int i = 0; i < total; i++){
		//first rewrite base_level.txt file
		if (!filename.isEmpty()){
			QTextStream out(stdout);
			QFile file(filename);
			if (file.open(QIODevice::WriteOnly)) {

				QTextStream out(&file);
				out << height << endl;
			}
			else{
				break;
			}
			file.close();
		}
		urbanGeometry->sateGetBuildings(1.0f);
		glWidget->shadow.makeShadowMap(glWidget);
		glWidget->updateGL();
		// choose 3D
		G::global()["shader2D"] = false;
		glWidget->vboRenderManager.changeTerrainShader(1);
		urbanGeometry->update(glWidget->vboRenderManager);
		glWidget->shadow.makeShadowMap(glWidget);
		glWidget->updateGL();
		// save image
		QString filename_cam = "camera/birdEye.txt";
		std::ifstream in(filename_cam.toUtf8().constData());

		std::string line;
		float x, y, z;
		std::vector<std::string> last;
		if (in.is_open())
		{
			while (getline(in, line))
			{
				std::cout << "cam view is " << line << std::endl;
				std::stringstream ss(line);
				std::string token;
				std::vector<std::string> paras;
				while (std::getline(ss, token, ',')) {
					//paras.push_back(stof(token));
					paras.push_back(token);
				}
				//rot
				x = stof(paras.at(0));
				y = stof(paras.at(1));
				z = stof(paras.at(2));
				glWidget->camera.rot = QVector3D(x, y, z);
				//pos
				x = stof(paras.at(3));
				y = stof(paras.at(4));
				z = stof(paras.at(5));
				glWidget->camera.pos = QVector3D(x, y, z);
				//
				x = stof(paras.at(6));
				y = stof(paras.at(7));
				z = stof(paras.at(8));
				glWidget->camera.lookAt = QVector3D(x, y, z);
				//update
				glWidget->updateCamera();
				glWidget->updateGL();
				// copu paras to last
				last = paras;
				//save images
				QString fileName = "screenshots/" + QString::number(i) + ".png";
				int cH = glWidget->height();
				int cW = glWidget->width();
				glWidget->resize(cW * 2, cH * 2);
				glWidget->updateGL();
				glWidget->grabFrameBuffer().save(fileName);
				glWidget->resize(cW, cH);
				glWidget->updateGL();
			}
			in.close();
		}
		height += step;
	}
	*/
	// Vegetation
	//urbanGeometry->generateVegetation();
	//glWidget->shadow.makeShadowMap(glWidget);
	//glWidget->updateGL();
	urbanGeometry->getBuildingTotalArea();
}

void MainWindow::onGenerateBuildings() {
	setParameters();
	urbanGeometry->generateBuildings();
	glWidget->shadow.makeShadowMap(glWidget);
	glWidget->updateGL();
}

void MainWindow::onGenerateVegetation() {
	setParameters();
	urbanGeometry->generateVegetation();
	glWidget->shadow.makeShadowMap(glWidget);
	glWidget->updateGL();
}

void MainWindow::onGenerateAll() {
	setParameters();
	urbanGeometry->generateAll(true);
	glWidget->shadow.makeShadowMap(glWidget);
	glWidget->updateGL();
}

void MainWindow::onGenerateCity() {
	std::cout << "Generating a city...";

	urbanGeometry->clear();

	// set the parameter values
	setParameters();

	urbanGeometry->generateAll(true);
	glWidget->shadow.makeShadowMap(glWidget);
	glWidget->updateGL();

	std::cout << " Done." << std::endl;
}

void MainWindow::onGenerateScenarios() {
	ScenarioGenerationDialog dlg;
	if (!dlg.exec()) return;

	QString zone_file = dlg.ui.lineEditZone->text();
	QString terrain_file = dlg.ui.lineEditTerrain->text();
	int numScenarios = dlg.ui.lineEditNumScenarios->text().toInt();
	QString output_dir = dlg.ui.lineEditOutputDirectory->text();
	bool use_flood_simulator = dlg.ui.checkBoxUseSimulator->isChecked();
	QString flood_simulator_dir = dlg.ui.lineEditSimulatorDirectory->text();
	std::pair<float, float> avenueSegmentLengthRange = std::make_pair(dlg.ui.lineEditAvenueSegmentLengthMin->text().toFloat(), dlg.ui.lineEditAvenueSegmentLengthMax->text().toFloat());
	std::pair<float, float> roadBaseOrientationRange = std::make_pair(dlg.ui.lineEditRoadBaseOrientationMin->text().toFloat(), dlg.ui.lineEditRoadBaseOrientationMax->text().toFloat());
	std::pair<float, float> roadCurvatureRange = std::make_pair(dlg.ui.lineEditRoadCurvatureMin->text().toFloat(), dlg.ui.lineEditRoadCurvatureMax->text().toFloat());
	std::pair<float, float> majorRoadWidthRange = std::make_pair(dlg.ui.lineEditMajorRoadWidthMin->text().toFloat(), dlg.ui.lineEditMajorRoadWidthMax->text().toFloat());
	std::pair<float, float> minorRoadWidthRange = std::make_pair(dlg.ui.lineEditMinorRoadWidthMin->text().toFloat(), dlg.ui.lineEditMinorRoadWidthMax->text().toFloat());
	std::pair<float, float> parkRatioRange = std::make_pair(dlg.ui.lineEditParkRatioMin->text().toFloat(), dlg.ui.lineEditParkRatioMax->text().toFloat());
	std::pair<float, float> pacelAreaRange = std::make_pair(dlg.ui.lineEditParcelAreaMin->text().toFloat(), dlg.ui.lineEditParcelAreaMax->text().toFloat());
	float parcelAreaDev = dlg.ui.lineEditParcelAreaDev->text().toFloat();
	std::pair<float, float> setbackFrontRange = std::make_pair(dlg.ui.lineEditSetbackFrontMin->text().toFloat(), dlg.ui.lineEditSetbackFrontMax->text().toFloat());
	std::pair<float, float> setbackRearRange = std::make_pair(dlg.ui.lineEditSetbackRearMin->text().toFloat(), dlg.ui.lineEditSetbackRearMax->text().toFloat());
	std::pair<float, float> setbackSideRange = std::make_pair(dlg.ui.lineEditSetbackSideMin->text().toFloat(), dlg.ui.lineEditSetbackSideMax->text().toFloat());
	std::pair<int, int> numStoriesRange = std::make_pair(dlg.ui.lineEditNumStoriesMin->text().toInt(), dlg.ui.lineEditNumStoriesMax->text().toInt());
	std::pair<float, float> minBuildingDimRange = std::make_pair(dlg.ui.lineEditMinBuildingDimMin->text().toFloat(), dlg.ui.lineEditMinBuildingDimMax->text().toFloat());
	bool useBuildingCoverage = dlg.ui.checkBoxBuildingCoverage->isChecked();
	std::pair<float, float> buildingCoverageRange = std::make_pair(dlg.ui.lineEditBuildingCoverageMin->text().toFloat() / 100.0f, dlg.ui.lineEditBuildingCoverageMax->text().toFloat() / 100.0f);
	bool generate_building_footprints_image = dlg.ui.checkBoxGenerateBuildingFootprintsImage->isChecked();
	int building_footprints_image_size = dlg.ui.lineEditBuildingFootprintsImageSize->text().toInt();

	G::global()["use_elevation_for_road_generation"] = dlg.ui.checkBoxUseElevation->isChecked();


	// 2016/11/10
	// We decided to remove randomness
	// random seed
	//srand(random_seed);

	// load zone
	urbanGeometry->loadZone(zone_file.toUtf8().constData());

	// load terrain
	urbanGeometry->loadTerrain(terrain_file.toUtf8().constData());

	// generate scenarios
	urbanGeometry->generateScenarios(numScenarios, output_dir, use_flood_simulator, flood_simulator_dir, avenueSegmentLengthRange, roadBaseOrientationRange, roadCurvatureRange, majorRoadWidthRange, minorRoadWidthRange, parkRatioRange, pacelAreaRange, parcelAreaDev, setbackFrontRange, setbackRearRange, setbackSideRange, numStoriesRange, minBuildingDimRange, useBuildingCoverage, buildingCoverageRange, generate_building_footprints_image, building_footprints_image_size);
}

void MainWindow::onToolGenerateBlocks(){
	GenerateBlocksDlg dlg;
	if (!dlg.exec()) return;

	int numScenarios = dlg.ui.lineEditNumScenarios->text().toInt();
	QString output_dir = dlg.ui.lineEditOutputDirectory->text();
	QString batch_num = dlg.ui.lineEditBatchNum->text();
	std::pair<float, float> blockWidthRange = std::make_pair(dlg.ui.lineEditBlocksWidthMin->text().toFloat(), dlg.ui.lineEditBlocksWidthMax->text().toFloat());
	std::pair<float, float> blockHeightRange = std::make_pair(dlg.ui.lineEditBlocksHeightMin->text().toFloat(), dlg.ui.lineEditBlocksHeightMax->text().toFloat());
	std::pair<float, float> parkRatioRange = std::make_pair(0, 0);
	std::pair<float, float> parcelAreaRange = std::make_pair(dlg.ui.lineEditParcelAreaMin->text().toFloat(), dlg.ui.lineEditParcelAreaMax->text().toFloat());
	float parcelAreaDev = dlg.ui.lineEditParcelAreaDev->text().toFloat();
	std::pair<float, float> setbackFrontRange = std::make_pair(dlg.ui.lineEditSetbackFrontMin->text().toFloat(), dlg.ui.lineEditSetbackFrontMax->text().toFloat());
	std::pair<float, float> setbackRearRange = std::make_pair(dlg.ui.lineEditSetbackRearMin->text().toFloat(), dlg.ui.lineEditSetbackRearMax->text().toFloat());
	std::pair<float, float> setbackSideRange = std::make_pair(dlg.ui.lineEditSetbackSideMin->text().toFloat(), dlg.ui.lineEditSetbackSideMax->text().toFloat());
	std::pair<int, int> numStoriesRange = std::make_pair(2, 8);
	std::pair<float, float> minBuildingDimRange = std::make_pair(2, 2);

	int blocks_footprints_image_size = dlg.ui.lineEditBuildingFootprintsImageSize->text().toInt();

	urbanGeometry->generateToolBlocks(numScenarios, output_dir, batch_num, blockWidthRange, blockHeightRange, parkRatioRange, parcelAreaRange, parcelAreaDev, setbackFrontRange, setbackRearRange, setbackSideRange, numStoriesRange, minBuildingDimRange, blocks_footprints_image_size);

}

void MainWindow::onParaControl(){
	ParameterControlDlg dlg;
	if (!dlg.exec()) return;
	// blocks
	setBlocksParameters();
	urbanGeometry->sateGetBlocks();
	glWidget->shadow.makeShadowMap(glWidget);
	glWidget->updateGL();
	// parcels
	urbanGeometry->sateGetParcels(dlg.ui.lineEditSmMid->text().toFloat(), dlg.ui.lineEditMidLg->text().toFloat(), - 1, false);
	glWidget->shadow.makeShadowMap(glWidget);
	glWidget->updateGL();
	// buildings
	urbanGeometry->sateGetBuildings(dlg.ui.lineEditSetback->text().toFloat());
	glWidget->shadow.makeShadowMap(glWidget);
	glWidget->updateGL();

	urbanGeometry->generateVegetation();
	glWidget->shadow.makeShadowMap(glWidget);
	glWidget->updateGL();
}
	//// compute
	//urbanGeometry->getBuildingTotalArea();

void MainWindow::onChangeFov(){
	ChangeFovDlg dlg;
	if (!dlg.exec()) return;
	glWidget->camera.fovy = dlg.ui.lineEditFov->text().toFloat();
	//glWidget->updateGL();
}

void MainWindow::onComputeSVF(){
	int cH = glWidget->height();
	int cW = glWidget->width();
	//glWidget->resize(cW * 5, cH * 5);
	//glWidget->updateGL();
	//glWidget->grabFrameBuffer().save(fileName);
	//glWidget->resize(cW, cH);
	//glWidget->updateGL();
	std::cout << "cH is " << cH << std::endl;
	std::cout << "cW is " << cW << std::endl;

	std::vector<std::vector<glm::vec3>> points_set;
	urbanGeometry->getCoordsForSvf(points_set);
	std::vector<std::vector<float>> svf_set;
	svf_set.resize(points_set.size());
	for (int i = 0; i < points_set.size(); i++){
		svf_set[i].resize(points_set[i].size());
		for (int j = 0; j < points_set[i].size() - 1; j++){
			//std::cout << "z is " << points_set[i][j].z << std::endl;
			float mid_x = (points_set[i][j].x + points_set[i][j + 1].x) * 0.5;
			float mid_y = (points_set[i][j].y + points_set[i][j + 1].y) * 0.5;
			float mid_z = (points_set[i][j].z + 5 + points_set[i][j + 1].z + 5) * 0.5;
			glWidget->camera.fovy = 170.0;
			//glWidget->camera.setTranslation(points_set[i][j].x, points_set[i][j].y, points_set[i][j].z);
			glWidget->camera.setTranslation(mid_x, mid_y, mid_z);
			glWidget->camera.setRotation(180, 0, 0);
			glWidget->updateGL();
			//glWidget->grabFrameBuffer().save("source/HK_svf/" + QString::number(i) +"_" +QString::number(j)+".png");
			//glWidget->grabFrameBuffer().save("source/HK_svf/" + QString::number(i) + "_" + QString::number(j) + "_mid.png");
			//glWidget->grabFrameBuffer().save("source/Toulouse_svf/" + QString::number(i) + "_" + QString::number(j) + "_mid.png");
			glWidget->grabFrameBuffer().save("source/Dublin_svf/" + QString::number(i) + "_" + QString::number(j) + "_mid.png");
		}
	}
}

void MainWindow::onTestSVF(){
	QImage img("source/0_0.png");
	int white_color_pixel = 0;
	for (int row = 0; row < img.height(); ++row)
		for (int col = 0; col < img.width(); ++col)
		{
			QColor clrCurrent(img.pixel(col, row));
			if (clrCurrent.red() == 255 && clrCurrent.green() == 255 && clrCurrent.blue() == 255)
				white_color_pixel++;
		}
	std::cout << "white_color_pixel is " << white_color_pixel << std::endl;
	std::cout << "SVF is " << white_color_pixel * 1.0 / (img.height() * img.width()) << std::endl;
	// draw the outline of road
	//cv::Mat img = cv::Mat::zeros(cv::Size(cW, cH), CV_8UC3);
	//for (int i = 0; i < points_set.size(); i++){
	//	std::vector<cv::Point> contour_line;
	//	for (int j = 0; j < points_set[i].size(); j++){
	//		contour_line.push_back(cv::Point(points_set[i][j].x + cW / 2, points_set[i][j].y + cH/2));
	//	}
	//	const cv::Point *pts = (const cv::Point*) cv::Mat(contour_line).data;
	//	int npts = cv::Mat(contour_line).rows;
	//	polylines(img, &pts, &npts, 1,
	//		false, 			// draw closed contour (i.e. joint end to start) 
	//		cv::Scalar(0, 0, 255),// colour RGB ordering (here = green) 
	//		3, 		        // line thickness
	//		CV_AA, 0);

	//}
	//cv::imwrite("source/test_polyline.png",img);
}

void MainWindow::onGenerateSVFImage(){
	int cH = glWidget->height();
	int cW = glWidget->width();
	std::cout << "cH is " << cH << std::endl;
	std::cout << "cW is " << cW << std::endl;

	std::vector<std::vector<glm::vec3>> points_set;
	urbanGeometry->getCoordsForSvf(points_set);
	std::vector<std::vector<float>> svf_set;
	svf_set.resize(points_set.size());
	for (int i = 0; i < points_set.size(); i++){
		svf_set[i].resize(points_set[i].size()-1);
		for (int j = 0; j < points_set[i].size()-1; j++){
			//compute the svf
			//QImage img("source/HK_svf/" + QString::number(i) + "_" + QString::number(j) + ".png");
			//QImage img("source/HK_svf/" + QString::number(i) + "_" + QString::number(j) + "_mid.png");
			//QImage img("source/Toulouse_svf/" + QString::number(i) + "_" + QString::number(j) + "_mid.png");
			QImage img("source/Dublin_svf/" + QString::number(i) + "_" + QString::number(j) + "_mid.png");
			int white_color_pixel = 0;
			for (int row = 0; row < img.height(); ++row){
				for (int col = 0; col < img.width(); ++col)
				{
					QColor clrCurrent(img.pixel(col, row));
					if (clrCurrent.red() == 255 && clrCurrent.green() == 255 && clrCurrent.blue() == 255)
						white_color_pixel++;
				}
			}
			float svf_value = white_color_pixel * 1.0 / (img.height() * img.width());
			svf_set[i][j] = svf_value;
			std::cout << "svf_value is " << svf_value << std::endl;
		}
	}
	// generate the image
	// color map
	QColor c1 = QColor(232, 16, 20);
	QColor c2 = QColor(242, 86, 34);
	QColor c3 = QColor(250, 133, 50);
	QColor c4 = QColor(252, 179, 68);
	QColor c5 = QColor(252, 228, 91);
	QColor c6 = QColor(231, 237, 114);
	QColor c7 = QColor(191, 212, 138);
	QColor c8 = QColor(149, 189, 159);
	QColor c9 = QColor(104, 166, 179);
	QColor c10 = QColor(40, 146, 199);
	int line_w = 2;
	QPen p1 = QPen(c1, line_w);
	QPen p2 = QPen(c2, line_w);
	QPen p3 = QPen(c3, line_w);
	QPen p4 = QPen(c4, line_w);
	QPen p5 = QPen(c5, line_w);
	QPen p6 = QPen(c6, line_w);
	QPen p7 = QPen(c7, line_w);
	QPen p8 = QPen(c8, line_w);
	QPen p9 = QPen(c9, line_w);
	QPen p10 = QPen(c10, line_w);
	// projected coords
	//glWidget->camera.fovy = 60;
	//glWidget->updateGL();
	//glWidget->camera.resetCamera();
	//glWidget->updateGL();
	//HK
	//glWidget->camera.setTranslation(0, 0, 3200);
	//Toulouse
	//glWidget->camera.setTranslation(0, 0, 5500);
	//Dublin
	glWidget->camera.setTranslation(0, 0, 7360);
	QMatrix4x4 proj_matrix = glWidget->camera.mvpMatrix;
	//glWidget->updateGL();
	//glWidget->grabFrameBuffer().save("source/back_ground.png");
	QPixmap pixmap;
	QPainter painter;
	pixmap.load("source/back_ground.png");
	painter.begin(&pixmap);
	for (int i = 0; i < points_set.size(); i++){
		for (int j = 0; j < points_set[i].size() - 1; j++){
			// start point
			float w_x = points_set[i][j].x;
			float w_y = points_set[i][j].y;
			float w_z = points_set[i][j].z;
			QVector4D w_coord(w_x, w_y, w_z, 1.0f);
			QVector4D pro_coord = proj_matrix * w_coord;
			float p_x = pro_coord.x() / pro_coord.w();
			float p_y = pro_coord.y() / pro_coord.w();
			int image_x_1 = (p_x + 1) * cW / 2;
			int image_y_1 = (1 - p_y) * cH / 2;
			// end point
			w_x = points_set[i][j + 1].x;
			w_y = points_set[i][j + 1].y;
			w_z = points_set[i][j + 1].z;
			w_coord = QVector4D(w_x, w_y, w_z, 1.0f);
			pro_coord = proj_matrix * w_coord;
			p_x = pro_coord.x() / pro_coord.w();
			p_y = pro_coord.y() / pro_coord.w();
			int image_x_2 = (p_x + 1) * cW / 2;
			int image_y_2 = (1 - p_y) * cH / 2;
			// set Pen color to the color of the start point
			float svf_value = svf_set[i][j];
			if (svf_value <= 0.1)
				painter.setPen(p1);
			else if (svf_value <= 0.2)
				painter.setPen(p2);
			else if (svf_value <= 0.3)
				painter.setPen(p3);
			else if (svf_value <= 0.4)
				painter.setPen(p4);
			else if (svf_value <= 0.5)
				painter.setPen(p5);
			else if (svf_value <= 0.6)
				painter.setPen(p6);
			else if (svf_value <= 0.7)
				painter.setPen(p7);
			else if (svf_value <= 0.8)
				painter.setPen(p8);
			else if (svf_value <= 0.9)
				painter.setPen(p9);
			else
				painter.setPen(p10);
			painter.drawLine(image_x_1, image_y_1, image_x_2, image_y_2);
		}
	}
	painter.end();
	pixmap.save("source/back_ground_svf.png");

	// 0.3
	{
		QPixmap pixmap;
		QPainter painter;
		pixmap.load("source/back_ground.png");
		painter.begin(&pixmap);
		for (int i = 0; i < points_set.size(); i++){
			for (int j = 0; j < points_set[i].size() - 1; j++){
				// start point
				float w_x = points_set[i][j].x;
				float w_y = points_set[i][j].y;
				float w_z = points_set[i][j].z;
				QVector4D w_coord(w_x, w_y, w_z, 1.0f);
				QVector4D pro_coord = proj_matrix * w_coord;
				float p_x = pro_coord.x() / pro_coord.w();
				float p_y = pro_coord.y() / pro_coord.w();
				int image_x_1 = (p_x + 1) * cW / 2;
				int image_y_1 = (1 - p_y) * cH / 2;
				// end point
				w_x = points_set[i][j + 1].x;
				w_y = points_set[i][j + 1].y;
				w_z = points_set[i][j + 1].z;
				w_coord = QVector4D(w_x, w_y, w_z, 1.0f);
				pro_coord = proj_matrix * w_coord;
				p_x = pro_coord.x() / pro_coord.w();
				p_y = pro_coord.y() / pro_coord.w();
				int image_x_2 = (p_x + 1) * cW / 2;
				int image_y_2 = (1 - p_y) * cH / 2;
				// set Pen color to the color of the start point
				float svf_value = pow(svf_set[i][j], 0.3);
				if (svf_value <= 0.1)
					painter.setPen(p1);
				else if (svf_value <= 0.2)
					painter.setPen(p2);
				else if (svf_value <= 0.3)
					painter.setPen(p3);
				else if (svf_value <= 0.4)
					painter.setPen(p4);
				else if (svf_value <= 0.5)
					painter.setPen(p5);
				else if (svf_value <= 0.6)
					painter.setPen(p6);
				else if (svf_value <= 0.7)
					painter.setPen(p7);
				else if (svf_value <= 0.8)
					painter.setPen(p8);
				else if (svf_value <= 0.9)
					painter.setPen(p9);
				else
					painter.setPen(p10);
				painter.drawLine(image_x_1, image_y_1, image_x_2, image_y_2);
			}
		}
		painter.end();
		pixmap.save("source/back_ground_svf_0.3.png");
	}
}

void MainWindow::onGenerateHeightImage(){
	int cH = glWidget->height();
	int cW = glWidget->width();
	std::cout << "cH is " << cH << std::endl;
	std::cout << "cW is " << cW << std::endl;
	std::vector<float> blds_height;
	std::vector<std::vector<glm::vec3>> blds_contour;
	urbanGeometry->getCoordsForHeight(blds_height, blds_contour);
	float max_height = *std::max_element(blds_height.begin(), blds_height.end());
	std::cout << "max_height is " << max_height << std::endl;
	std::cout << "blds size is " << blds_height.size() << std::endl;
	// generate the image
	// color map
	QColor c1 = QColor(232, 16, 20);
	QColor c2 = QColor(242, 86, 34);
	QColor c3 = QColor(250, 133, 50);
	QColor c4 = QColor(252, 179, 68);
	QColor c5 = QColor(252, 228, 91);
	QColor c6 = QColor(231, 237, 114);
	QColor c7 = QColor(191, 212, 138);
	QColor c8 = QColor(149, 189, 159);
	QColor c9 = QColor(104, 166, 179);
	QColor c10 = QColor(40, 146, 199);
	int line_w = 1;
	QPen p1 = QPen(c1, line_w);
	QPen p2 = QPen(c2, line_w);
	QPen p3 = QPen(c3, line_w);
	QPen p4 = QPen(c4, line_w);
	QPen p5 = QPen(c5, line_w);
	QPen p6 = QPen(c6, line_w);
	QPen p7 = QPen(c7, line_w);
	QPen p8 = QPen(c8, line_w);
	QPen p9 = QPen(c9, line_w);
	QPen p10 = QPen(c10, line_w);
	//
	QBrush  b1 = QBrush(c1);
	QBrush  b2 = QBrush(c2);
	QBrush  b3 = QBrush(c3);
	QBrush  b4 = QBrush(c4);
	QBrush  b5 = QBrush(c5);
	QBrush  b6 = QBrush(c6);
	QBrush  b7 = QBrush(c7);
	QBrush  b8 = QBrush(c8);
	QBrush  b9 = QBrush(c9);
	QBrush  b10 = QBrush(c10);
	// projected coords
	//HK
	//glWidget->camera.setTranslation(0, 0, 3200);
	//Toulouse
	glWidget->camera.setTranslation(0, 0, 5500);
	// Dublin
	//glWidget->camera.setTranslation(0, 0, 7360);
	QMatrix4x4 proj_matrix = glWidget->camera.mvpMatrix;
	//glWidget->updateGL();
	//glWidget->grabFrameBuffer().save("source/back_ground.png");
	QPixmap pixmap;
	QPainter painter;
	pixmap.load("source/back_ground.png");
	painter.begin(&pixmap);
	QPoint points[30] = {};
	for (int i = 0; i < blds_contour.size(); i++){
		//HK
		//std::cout << "blds_contour size  is " << i << ", " <<blds_contour[i].size() << std::endl;
		QPainterPath path;
		int last_x = 0;
		int last_y = 0;
		for (int j = 0; j < blds_contour[i].size(); j++){
			// start point
			float w_x = blds_contour[i][j].x;
			float w_y = blds_contour[i][j].y;
			float w_z = blds_contour[i][j].z;
			QVector4D w_coord(w_x, w_y, w_z, 1.0f);
			QVector4D pro_coord = proj_matrix * w_coord;
			float p_x = pro_coord.x() / pro_coord.w();
			float p_y = pro_coord.y() / pro_coord.w();
			int image_x = (p_x + 1) * cW / 2;
			int image_y = (1 - p_y) * cH / 2;
			//if (j != 0){
			//	if (abs(image_x - last_x) <= 1 && abs(image_y - last_y) <= 1)
			//		continue;
			//	else
			//		points[j] = QPoint(image_x, image_y);
			//}
			//else
			//	points[j] = QPoint(image_x, image_y);
			points[j] = QPoint(image_x, image_y);
			last_x = image_x;
			last_y = image_y;
			//if (j == 0)
			//	path.moveTo(image_x, image_y);
		}
		float ratio_value = blds_height[i] / max_height;
		painter.setPen(Qt::NoPen);
		if (ratio_value <= 0.1)
			painter.setBrush(b1);
		else if (ratio_value <= 0.2)
			painter.setBrush(b2);
		else if (ratio_value <= 0.3)
			painter.setBrush(b3);
		else if (ratio_value <= 0.4)
			painter.setBrush(b4);
		else if (ratio_value <= 0.5)
			painter.setBrush(b5);
		else if (ratio_value <= 0.6)
			painter.setBrush(b6);
		else if (ratio_value <= 0.7)
			painter.setBrush(b7);
		else if (ratio_value <= 0.8)
			painter.setBrush(b8);
		else if (ratio_value <= 0.9)
			painter.setBrush(b9);
		else
			painter.setBrush(b10);

		painter.drawPolygon(points, blds_contour[i].size());
	}
	painter.end();
	pixmap.save("source/back_ground_height.png");
}

void MainWindow::onToolImageOBB(){
	ImageOBBDlg dlg;
	if (!dlg.exec()) return;
	QString src_image_filename = dlg.ui.lineEditImageOBBSrc->text();
	QString des_dir = dlg.ui.lineEditImageOBBDes->text();
	if (src_image_filename.isEmpty() || des_dir.isEmpty()){
		std::cout << "The path is empty!!" << std::endl;
		return;
	}
	if (!QDir("predict").exists()){
		QDir().mkpath("predict");
	}
	// Train to get paras
	int image_width = 227;
	int image_height = 227;
	cv::Mat src;
	src = cv::imread(src_image_filename.toUtf8().data(), CV_LOAD_IMAGE_COLOR);
	//remove roads
	for (int i = 0; i < src.size().height; i++){
		for (int j = 0; j < src.size().width; j++){
			//noise
			if (src.at<cv::Vec3b>(i, j)[2] == 255){
				src.at<cv::Vec3b>(i, j)[0] = 0;
				src.at<cv::Vec3b>(i, j)[1] = 255;
				src.at<cv::Vec3b>(i, j)[2] = 0;
			}
		}
	}
	QString tmp_path = "predict/without_roads.png";
	cv::imwrite(tmp_path.toUtf8().data(), src);
	// make sure the longer side is the width
	if (src.size().width < src.size().height){
		cv::transpose(src, src);
		cv::flip(src, src, 0);
	}
	// resize the width
	float resize_factor = 0.0f;
	cv::Mat img;
	resize_factor = 1.0 * image_width / src.size().width;
	// also resize the height by the same factor to keep the aspect ratio
	cv::resize(src, img, cv::Size(image_width, src.size().height * resize_factor), 0, 0, cv::INTER_NEAREST);
	tmp_path = "classifer/resize_width.png";
	cv::imwrite(tmp_path.toUtf8().data(), img);
	// if the height is beyond 227, then resize the height agaon. (This won't happen. But just in case)
	if (src.size().height > 227){
		cv::resize(img, img, cv::Size(image_width, image_height), 0, 0, cv::INTER_NEAREST);
		tmp_path = "classifer/resize_height.png";
		cv::imwrite(tmp_path.toUtf8().data(), img);
	}
	// resize to 227 * 227
	cv::Mat output(cv::Size(image_width, image_height), CV_8UC3, cv::Scalar(0, 255, 0));
	img.copyTo(output(cv::Rect(0, 227 - img.size().height, img.size().width, img.size().height)));

	tmp_path = "classifer/output.png";
	cv::imwrite(tmp_path.toUtf8().data(), output);

	cv::Mat tmp[3];
	cv::split(output, tmp);
	//transfer img
	cv::equalizeHist(tmp[0], tmp[0]);
	cv::equalizeHist(tmp[1], tmp[1]);
	cv::equalizeHist(tmp[2], tmp[2]);
	cv::merge(tmp, 3, output);
	Regression * parcel_regression = new Regression("models/block_parcel/deploy.prototxt", "models/block_parcel/parcel.caffemodel");
	std::vector<float> pred = parcel_regression->get_pred(output);
	// output
	std::pair<float, float> parcelMeanArea = std::make_pair(100.0f, 300.0f);
	// Set paras
	if (pred[1] < 0){
		std::cout << "pred[1]" << pred[1] << std::endl;
		pred[1] = 0.0;
	}
	float parcel_area = (pred[1] * (parcelMeanArea.second - parcelMeanArea.first) + parcelMeanArea.first) / (resize_factor * resize_factor);
	//
	urbanGeometry->generateToolImageOBB(parcel_area, src.size().width, src.size().height, des_dir);
	
}


void MainWindow::onParcelClassifer(){
	// load the image
	QString filename = QFileDialog::getOpenFileName(this, tr("Open Image file..."), "", tr("Image Files *.png"));
	if (filename.isEmpty()) return;
	// Train to get paras
	int image_width = 227;
	int image_height = 227;
	cv::Mat src;
	src = cv::imread(filename.toUtf8().data(), CV_LOAD_IMAGE_COLOR);
	//remove roads
	for (int i = 0; i < src.size().height; i++){
		for (int j = 0; j < src.size().width; j++){
			//noise
			if (src.at<cv::Vec3b>(i, j)[2] == 255){
				src.at<cv::Vec3b>(i, j)[0] = 0;
				src.at<cv::Vec3b>(i, j)[1] = 255;
				src.at<cv::Vec3b>(i, j)[2] = 0;
			}
		}
	}
	QString tmp_path = "classifer/without_roads.png";
	cv::imwrite(tmp_path.toUtf8().data(), src);
	// make sure the longer side is the width
	if (src.size().width < src.size().height){
		cv::transpose(src, src);
		cv::flip(src, src, 0);
	}
	// resize the width
	float resize_factor = 0.0f;
	cv::Mat img;
	resize_factor = 1.0 * image_width / src.size().width;
	// also resize the height by the same factor to keep the aspect ratio
	cv::resize(src, img, cv::Size(image_width, src.size().height * resize_factor), 0, 0, cv::INTER_NEAREST);
	tmp_path = "classifer/resize_width.png";
	cv::imwrite(tmp_path.toUtf8().data(), img);
	// if the height is beyond 227, then resize the height agaon. (This won't happen. But just in case)
	if (src.size().height > 227){
		cv::resize(img, img, cv::Size(image_width, image_height), 0, 0, cv::INTER_NEAREST);
		tmp_path = "classifer/resize_height.png";
		cv::imwrite(tmp_path.toUtf8().data(), img);
	}
	// resize to 227 * 227
	cv::Mat output(cv::Size(image_width, image_height), CV_8UC3, cv::Scalar(0, 255, 0));
	img.copyTo(output(cv::Rect(0, 227 - img.size().height, img.size().width, img.size().height)));

	tmp_path = "classifer/output.png";
	cv::imwrite(tmp_path.toUtf8().data(), output);

	cv::Mat tmp[3];
	cv::split(output, tmp);
	//transfer img
	cv::equalizeHist(tmp[0], tmp[0]);
	cv::equalizeHist(tmp[1], tmp[1]);
	cv::equalizeHist(tmp[2], tmp[2]);
	cv::merge(tmp, 3, output);
	CaffeWrapper *caffe_parcel_type = new CaffeWrapper("models/parcel_type/deploy.prototxt", "models/parcel_type/parcel_type.caffemodel",
		"models/parcel_type/mean.binaryproto");
	std::vector<float> pred = caffe_parcel_type->get_pred(output);
	QString result("parel type : ");
	result += QString::number(pred[0], 'f', 3);
	result += ",  " + QString::number(pred[1], 'f', 3);
	result += ",  " + QString::number(pred[2], 'f', 3);
	ui.statusBar->showMessage(result);
	Regression * parcel_small = new Regression("models/parcel_small/deploy.prototxt", "models/parcel_small/parcel.caffemodel");
	Regression * parcel_median = new Regression("models/parcel_median/deploy.prototxt", "models/parcel_median/parcel.caffemodel");
	Regression * parcel_big = new Regression("models/parcel_big/deploy.prototxt", "models/parcel_big/parcel.caffemodel");
	// predict the parcel type
	int parcel_type = 0;
	{
		int index = 0;
		float max_tmp = 0.0f;
		for (int iter = 0; iter < 3; iter++){
			if (pred[iter] > max_tmp){
				max_tmp = pred[iter];
				index = iter;
			}
		}
		parcel_type = index;
		std::cout << "parcel type is " << parcel_type << std::endl;
	}
	// go to appropriate parcel regression model
	std::pair<float, float> parcelMeanArea;
	std::vector<float> pred_parcel;
	float parcel_size = 0.0f;
	if (parcel_type == 0){
		pred_parcel.clear();
		// output
		parcelMeanArea = std::make_pair(80.0f, 300.0f);
		pred_parcel = parcel_small->get_pred(output);
		// Set paras
		if (pred_parcel[1] < 0){
			std::cout << "pred[1]" << pred_parcel[1] << std::endl;
			pred_parcel[1] = 0.0;
		}
		// resize back
		parcel_size = (pred_parcel[1] * (parcelMeanArea.second - parcelMeanArea.first) + parcelMeanArea.first) / (resize_factor * resize_factor);
	}
	else if (parcel_type == 1){
		pred_parcel.clear();
		// output
		parcelMeanArea = std::make_pair(300.0f, 570.0f);
		pred_parcel = parcel_median->get_pred(output);
		// Set paras
		if (pred_parcel[1] < 0){
			std::cout << "pred[1]" << pred_parcel[1] << std::endl;
			pred_parcel[1] = 0.0;
		}
		// resize back
		parcel_size = (pred_parcel[1] * (parcelMeanArea.second - parcelMeanArea.first) + parcelMeanArea.first) / (resize_factor * resize_factor);
	}
	else if (parcel_type == 2){
		pred_parcel.clear();
		// output
		parcelMeanArea = std::make_pair(570.0f, 10000.0f);
		pred_parcel = parcel_big->get_pred(output);
		// Set paras
		if (pred_parcel[1] < 0){
			std::cout << "pred[1]" << pred_parcel[1] << std::endl;
			pred_parcel[1] = 0.0;
		}
		parcel_size = (pred_parcel[1] * (parcelMeanArea.second - parcelMeanArea.first) + parcelMeanArea.first) / (resize_factor * resize_factor);
	}
	else{
	}
	std::cout << "resize_factor is " << resize_factor << std::endl;
	std::cout << "parcel_size is " << parcel_size << std::endl;
	return;
}

void MainWindow::onEstimate(){
	
}

void MainWindow::actionTestBlock(){
	QString filename = QFileDialog::getOpenFileName(this, tr("Open Image file..."), "", tr("Image Files *.txt"));
	if (filename.isEmpty()) return;
	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly)) {
		return;
	}

	QTextStream in(&file);
	QTextStream out(stdout);
	QString line("");
	QStringList fields;
	while (!in.atEnd()) {
		line = in.readLine();
		fields = line.split(",");
	}
	file.close();
	QStringListIterator it(fields);
	std::vector<int> tmp;
	int index = 0;
	while (it.hasNext()) {
		tmp.push_back(it.next().trimmed().toInt());
	}
	int testbN = tmp.at(0);
	std::cout << "TestbN is " << testbN << std::endl;
	// blocks
	setBlocksParameters();
	urbanGeometry->sateGetBlocks();
	glWidget->shadow.makeShadowMap(glWidget);
	glWidget->updateGL();
	// parcels
	urbanGeometry->sateGetParcels(300.0, 570.0, testbN, false);
	glWidget->shadow.makeShadowMap(glWidget);
	glWidget->updateGL();
	// buildings
	urbanGeometry->sateGetBuildings(1.0f);
	glWidget->shadow.makeShadowMap(glWidget);
	glWidget->updateGL();
}

void MainWindow::onNNanalysis(){
	// get images files
	std::vector<std::string> scene1_files = get_all_files_names_within_folder("NN_analysis/input/Scene1");
	std::vector<std::string> scene2_files = get_all_files_names_within_folder("NN_analysis/input/Scene2");
	std::vector<std::string> scene3_files = get_all_files_names_within_folder("NN_analysis/input/Scene3");
	std::vector<float> scene1_gt;
	std::vector<float> scene2_gt;
	std::vector<float> scene3_gt;
	// get ground truth values
	std::string txt_extentsion = ".txt";
	for (int i = 0; i < scene1_files.size(); i++){
		QString str = QString::fromStdString(scene1_files.at(i));
		str.replace("buildings_image_", "parameter_");
		str.replace(".png", ".txt");
		QString paras_path = QString("NN_analysis/labels/Scene1/") + str;
		QFile file(paras_path);
		if (!file.open(QIODevice::ReadOnly)) {
			return;
		}

		QTextStream in(&file);
		QTextStream out(stdout);
		QString line("");
		QStringList fields;
		in.readLine();
		while (!in.atEnd()) {
			line = in.readLine();
			fields = line.split(",");
		}
		file.close();
		QStringListIterator it(fields);
		std::vector<float> tmp;
		std::vector<float> paras;
		std::vector<int> stories;
		int index = 0;
		while (it.hasNext()) {
			tmp.push_back(it.next().trimmed().toFloat());
			//std::cout << tmp.at(index++) << std::endl;
		}
		scene1_gt.push_back(tmp.at(3));
	}

	for (int i = 0; i < scene2_files.size(); i++){
		QString str = QString::fromStdString(scene2_files.at(i));
		str.replace("buildings_image_", "parameter_");
		str.replace(".png", ".txt");
		QString paras_path = QString("NN_analysis/labels/Scene2/") + str;
		QFile file(paras_path);
		if (!file.open(QIODevice::ReadOnly)) {
			return;
		}

		QTextStream in(&file);
		QTextStream out(stdout);
		QString line("");
		QStringList fields;
		in.readLine();
		while (!in.atEnd()) {
			line = in.readLine();
			fields = line.split(",");
		}
		file.close();
		QStringListIterator it(fields);
		std::vector<float> tmp;
		std::vector<float> paras;
		std::vector<int> stories;
		int index = 0;
		while (it.hasNext()) {
			tmp.push_back(it.next().trimmed().toFloat());
			//std::cout << tmp.at(index++) << std::endl;
		}
		scene2_gt.push_back(tmp.at(3));
	}

	for (int i = 0; i < scene3_files.size(); i++){
		QString str = QString::fromStdString(scene3_files.at(i));
		str.replace("buildings_image_", "parameter_");
		str.replace(".png", ".txt");
		QString paras_path = QString("NN_analysis/labels/Scene3/") + str;
		QFile file(paras_path);
		if (!file.open(QIODevice::ReadOnly)) {
			return;
		}

		QTextStream in(&file);
		QTextStream out(stdout);
		QString line("");
		QStringList fields;
		in.readLine();
		while (!in.atEnd()) {
			line = in.readLine();
			fields = line.split(",");
		}
		file.close();
		QStringListIterator it(fields);
		std::vector<float> tmp;
		std::vector<float> paras;
		std::vector<int> stories;
		int index = 0;
		while (it.hasNext()) {
			tmp.push_back(it.next().trimmed().toFloat());
			//std::cout << tmp.at(index++) << std::endl;
		}
		scene3_gt.push_back(tmp.at(3));
	}
	// generate predict txt file from whole model 
	std::vector<float> scene1_whole;
	std::vector<float> scene2_whole;
	std::vector<float> scene3_whole;
	std::pair<float, float> parcelArea_whole = std::make_pair(0.8, 200);
	Regression * parcel_whole = new Regression("NN_analysis/models/whole/deploy.prototxt", "NN_analysis/models/whole/parcel.caffemodel");
	for (int i = 0; i < scene1_files.size(); i++){
		// get input image
		QString image_path = QString("NN_analysis/input/Scene1/") + QString::fromStdString(scene1_files.at(i));
		cv::Mat src;
		src = cv::imread(image_path.toUtf8().data(), CV_LOAD_IMAGE_COLOR);
		cv::Mat tmp[3];
		cv::split(src, tmp);
		//transfer img
		cv::equalizeHist(tmp[0], tmp[0]);
		cv::equalizeHist(tmp[1], tmp[1]);
		cv::equalizeHist(tmp[2], tmp[2]);
		cv::merge(tmp, 3, src);
		std::vector<float> pred_paras = parcel_whole->get_pred(src);
		if (pred_paras[1] < 0){
			pred_paras[1] = 0.0;
		}
		scene1_whole.push_back((pred_paras[1] * (parcelArea_whole.second - parcelArea_whole.first) + parcelArea_whole.first));
	}
	for (int i = 0; i < scene2_files.size(); i++){
		// get input image
		QString image_path = QString("NN_analysis/input/Scene2/") + QString::fromStdString(scene2_files.at(i));
		cv::Mat src;
		src = cv::imread(image_path.toUtf8().data(), CV_LOAD_IMAGE_COLOR);
		cv::Mat tmp[3];
		cv::split(src, tmp);
		//transfer img
		cv::equalizeHist(tmp[0], tmp[0]);
		cv::equalizeHist(tmp[1], tmp[1]);
		cv::equalizeHist(tmp[2], tmp[2]);
		cv::merge(tmp, 3, src);
		std::vector<float> pred_paras = parcel_whole->get_pred(src);
		if (pred_paras[1] < 0){
			pred_paras[1] = 0.0;
		}
		scene2_whole.push_back((pred_paras[1] * (parcelArea_whole.second - parcelArea_whole.first) + parcelArea_whole.first));
	}
	for (int i = 0; i < scene3_files.size(); i++){
		// get input image
		QString image_path = QString("NN_analysis/input/Scene3/") + QString::fromStdString(scene3_files.at(i));
		cv::Mat src;
		src = cv::imread(image_path.toUtf8().data(), CV_LOAD_IMAGE_COLOR);
		cv::Mat tmp[3];
		cv::split(src, tmp);
		//transfer img
		cv::equalizeHist(tmp[0], tmp[0]);
		cv::equalizeHist(tmp[1], tmp[1]);
		cv::equalizeHist(tmp[2], tmp[2]);
		cv::merge(tmp, 3, src);
		std::vector<float> pred_paras = parcel_whole->get_pred(src);
		if (pred_paras[1] < 0){
			pred_paras[1] = 0.0;
		}
		scene3_whole.push_back((pred_paras[1] * (parcelArea_whole.second - parcelArea_whole.first) + parcelArea_whole.first));
	}
	// generate predict txt file from 3 NNs
	std::vector<float> scene1_pre;
	std::vector<float> scene2_pre;
	std::vector<float> scene3_pre;
	std::vector<float> scene1_no_classifer;
	std::vector<float> scene2_no_classifer;
	std::vector<float> scene3_no_classifer;
	std::vector<int> scene1_type;
	std::vector<int> scene2_type;
	std::vector<int> scene3_type;
	std::pair<float, float> parcelArea_first = std::make_pair(0.8, 3);
	std::pair<float, float> parcelArea_second = std::make_pair(3, 5.7);
	std::pair<float, float> parcelArea_third = std::make_pair(5.7, 200);
	CaffeWrapper *caffe_parcel_type = new CaffeWrapper("NN_analysis/models/parcel_type/deploy.prototxt", "NN_analysis/models/parcel_type/parcel_type.caffemodel",
		"NN_analysis/models/parcel_type/mean.binaryproto");
	Regression * parcel_small = new Regression("NN_analysis/models/three/deploy.prototxt", "NN_analysis/models/three/parcel_first.caffemodel");
	Regression * parcel_median = new Regression("NN_analysis/models/three/deploy.prototxt", "NN_analysis/models/three/parcel_second.caffemodel");
	Regression * parcel_big = new Regression("NN_analysis/models/three/deploy.prototxt", "NN_analysis/models/three/parcel_third.caffemodel");
	
	for (int i = 0; i < scene1_files.size(); i++){
		// get input image
		QString image_path = QString("NN_analysis/input/Scene1/") + QString::fromStdString(scene1_files.at(i));
		cv::Mat src;
		src = cv::imread(image_path.toUtf8().data(), CV_LOAD_IMAGE_COLOR);
		cv::Mat tmp[3];
		cv::split(src, tmp);
		//transfer img
		cv::equalizeHist(tmp[0], tmp[0]);
		cv::equalizeHist(tmp[1], tmp[1]);
		cv::equalizeHist(tmp[2], tmp[2]);
		cv::merge(tmp, 3, src);
		// get parcel type
		std::vector<float> pred = caffe_parcel_type->get_pred(src);
		// predict the parcel type
		int parcel_type = 0;
		{
			int index = 0;
			float max_tmp = 0.0f;
			for (int iter = 0; iter < 3; iter++){
				if (pred[iter] > max_tmp){
					max_tmp = pred[iter];
					index = iter;
				}
			}
			parcel_type = index;
		}
		scene1_type.push_back(parcel_type);
		// predict
		if (parcel_type == 0){
			std::vector<float> pred_paras = parcel_small->get_pred(src);
			scene1_pre.push_back((pred_paras[1] * (parcelArea_first.second - parcelArea_first.first) + parcelArea_first.first));
		}
		else if (parcel_type == 1){
			std::vector<float> pred_paras = parcel_median->get_pred(src);
			scene1_pre.push_back((pred_paras[1] * (parcelArea_second.second - parcelArea_second.first) + parcelArea_second.first));
		}
		else{
			std::vector<float> pred_paras = parcel_big->get_pred(src);
			scene1_pre.push_back((pred_paras[1] * (parcelArea_third.second - parcelArea_third.first) + parcelArea_third.first));
		}
		// predict without classifer
		std::vector<float> pred_paras_tmp = parcel_small->get_pred(src);
		scene1_no_classifer.push_back((pred_paras_tmp[1] * (parcelArea_first.second - parcelArea_first.first) + parcelArea_first.first));
	}

	for (int i = 0; i < scene2_files.size(); i++){
		// get input image
		QString image_path = QString("NN_analysis/input/Scene2/") + QString::fromStdString(scene2_files.at(i));
		cv::Mat src;
		src = cv::imread(image_path.toUtf8().data(), CV_LOAD_IMAGE_COLOR);
		cv::Mat tmp[3];
		cv::split(src, tmp);
		//transfer img
		cv::equalizeHist(tmp[0], tmp[0]);
		cv::equalizeHist(tmp[1], tmp[1]);
		cv::equalizeHist(tmp[2], tmp[2]);
		cv::merge(tmp, 3, src);
		// get parcel type
		std::vector<float> pred = caffe_parcel_type->get_pred(src);
		// predict the parcel type
		int parcel_type = 0;
		{
			int index = 0;
			float max_tmp = 0.0f;
			for (int iter = 0; iter < 3; iter++){
				if (pred[iter] > max_tmp){
					max_tmp = pred[iter];
					index = iter;
				}
			}
			parcel_type = index;
		}
		scene2_type.push_back(parcel_type);
		// predict
		if (parcel_type == 0){
			std::vector<float> pred_paras = parcel_small->get_pred(src);
			scene2_pre.push_back((pred_paras[1] * (parcelArea_first.second - parcelArea_first.first) + parcelArea_first.first));
		}
		else if (parcel_type == 1){
			std::vector<float> pred_paras = parcel_median->get_pred(src);
			scene2_pre.push_back((pred_paras[1] * (parcelArea_second.second - parcelArea_second.first) + parcelArea_second.first));
		}
		else{
			std::vector<float> pred_paras = parcel_big->get_pred(src);
			scene2_pre.push_back((pred_paras[1] * (parcelArea_third.second - parcelArea_third.first) + parcelArea_third.first));
		}
		// predict without classifer
		std::vector<float> pred_paras_tmp = parcel_median->get_pred(src);
		scene2_no_classifer.push_back((pred_paras_tmp[1] * (parcelArea_second.second - parcelArea_second.first) + parcelArea_second.first));
	}

	for (int i = 0; i < scene3_files.size(); i++){
		// get input image
		QString image_path = QString("NN_analysis/input/Scene3/") + QString::fromStdString(scene3_files.at(i));
		cv::Mat src;
		src = cv::imread(image_path.toUtf8().data(), CV_LOAD_IMAGE_COLOR);
		cv::Mat tmp[3];
		cv::split(src, tmp);
		//transfer img
		cv::equalizeHist(tmp[0], tmp[0]);
		cv::equalizeHist(tmp[1], tmp[1]);
		cv::equalizeHist(tmp[2], tmp[2]);
		cv::merge(tmp, 3, src);
		// get parcel type
		std::vector<float> pred = caffe_parcel_type->get_pred(src);
		// predict the parcel type
		int parcel_type = 0;
		{
			int index = 0;
			float max_tmp = 0.0f;
			for (int iter = 0; iter < 3; iter++){
				if (pred[iter] > max_tmp){
					max_tmp = pred[iter];
					index = iter;
				}
			}
			parcel_type = index;
		}
		scene3_type.push_back(parcel_type);
		// predict
		if (parcel_type == 0){
			std::vector<float> pred_paras = parcel_small->get_pred(src);
			scene3_pre.push_back((pred_paras[1] * (parcelArea_first.second - parcelArea_first.first) + parcelArea_first.first));
		}
		else if (parcel_type == 1){
			std::vector<float> pred_paras = parcel_median->get_pred(src);
			scene3_pre.push_back((pred_paras[1] * (parcelArea_second.second - parcelArea_second.first) + parcelArea_second.first));
		}
		else{
			std::vector<float> pred_paras = parcel_big->get_pred(src);
			scene3_pre.push_back((pred_paras[1] * (parcelArea_third.second - parcelArea_third.first) + parcelArea_third.first));
		}
		std::vector<float> pred_paras_tmp = parcel_big->get_pred(src);
		scene3_no_classifer.push_back((pred_paras_tmp[1] * (parcelArea_third.second - parcelArea_third.first) + parcelArea_third.first));
	}


	// save results
	QFile file_gt_params(QString("NN_analysis/gt.txt"));
	if (!file_gt_params.open(QIODevice::WriteOnly)) {
		std::cerr << "Cannot open file for writing: " << file_gt_params.fileName().toUtf8().constData() << std::endl;
		return;
	}
	QTextStream out_gt_params(&file_gt_params);

	QFile file_three_pre_params(QString("NN_analysis/three_pre.txt"));
	if (!file_three_pre_params.open(QIODevice::WriteOnly)) {
		std::cerr << "Cannot open file for writing: " << file_three_pre_params.fileName().toUtf8().constData() << std::endl;
		return;
	}
	QTextStream out_three_pre_params(&file_three_pre_params);

	QFile file_three_pre_no_classifer_params(QString("NN_analysis/three_no_classifer.txt"));
	if (!file_three_pre_no_classifer_params.open(QIODevice::WriteOnly)) {
		std::cerr << "Cannot open file for writing: " << file_three_pre_no_classifer_params.fileName().toUtf8().constData() << std::endl;
		return;
	}
	QTextStream out_three_pre_no_classifer_params(&file_three_pre_no_classifer_params);

	QFile file_whole_pre_params(QString("NN_analysis/whole_pre.txt"));
	if (!file_whole_pre_params.open(QIODevice::WriteOnly)) {
		std::cerr << "Cannot open file for writing: " << file_whole_pre_params.fileName().toUtf8().constData() << std::endl;
		return;
	}
	QTextStream out_whole_pre_params(&file_whole_pre_params);

	QFile file_whole_params(QString("NN_analysis/error_whole.txt"));
	if (!file_whole_params.open(QIODevice::WriteOnly)) {
		std::cerr << "Cannot open file for writing: " << file_whole_params.fileName().toUtf8().constData() << std::endl;
		return;
	}
	QTextStream out_whole_params(&file_whole_params);

	QFile file_three_params(QString("NN_analysis/error_bins_classifer.txt"));
	if (!file_three_params.open(QIODevice::WriteOnly)) {
		std::cerr << "Cannot open file for writing: " << file_three_params.fileName().toUtf8().constData() << std::endl;
		return;
	}
	QTextStream out_three_params(&file_three_params);

	QFile file_three_no_classifer_params(QString("NN_analysis/error_bins_no_classifer.txt"));
	if (!file_three_no_classifer_params.open(QIODevice::WriteOnly)) {
		std::cerr << "Cannot open file for writing: " << file_three_no_classifer_params.fileName().toUtf8().constData() << std::endl;
		return;
	}
	QTextStream out_three_no_classifer_params(&file_three_no_classifer_params);

	int count = 0;
	for (int i = 0; i < scene1_files.size(); i++){
		out_gt_params << scene1_gt.at(i) << "\n";
		out_gt_params.flush();

		out_three_pre_params << scene1_pre.at(i) << "\n";
		out_three_pre_params.flush();

		out_whole_pre_params << scene1_whole.at(i) << "\n";
		out_whole_pre_params.flush();

		out_three_pre_no_classifer_params << scene1_no_classifer.at(i) << "\n";
		out_three_pre_no_classifer_params.flush();

		out_whole_params << abs(scene1_gt.at(i) - scene1_whole.at(i)) / scene1_gt.at(i) << "\n";
		out_whole_params.flush();

		out_three_params << abs(scene1_gt.at(i) - scene1_pre.at(i)) / scene1_gt.at(i) << "\n";
		out_three_params.flush();

		out_three_no_classifer_params << abs(scene1_gt.at(i) - scene1_no_classifer.at(i)) / scene1_gt.at(i) << "\n";
		out_three_no_classifer_params.flush();

		if (scene1_type.at(i) == 0)
			count++;
	}

	for (int i = 0; i < scene2_files.size(); i++){
		out_gt_params << scene2_gt.at(i) << "\n";
		out_gt_params.flush();

		out_three_pre_params << scene2_pre.at(i) << "\n";
		out_three_pre_params.flush();

		out_whole_pre_params << scene2_whole.at(i) << "\n";
		out_whole_pre_params.flush();

		out_three_pre_no_classifer_params << scene2_no_classifer.at(i) << "\n";
		out_three_pre_no_classifer_params.flush();

		out_whole_params << abs(scene2_gt.at(i) - scene2_whole.at(i)) / scene2_gt.at(i) << "\n";
		out_whole_params.flush();

		out_three_params << abs(scene2_gt.at(i) - scene2_pre.at(i)) / scene2_gt.at(i) << "\n";
		out_three_params.flush();

		out_three_no_classifer_params << abs(scene2_gt.at(i) - scene2_no_classifer.at(i)) / scene2_gt.at(i) << "\n";
		out_three_no_classifer_params.flush();

		if (scene2_type.at(i) == 1)
			count++;
	}

	for (int i = 0; i < scene3_files.size(); i++){
		out_gt_params << scene3_gt.at(i) << "\n";
		out_gt_params.flush();

		out_three_pre_params << scene3_pre.at(i) << "\n";
		out_three_pre_params.flush();

		out_whole_pre_params << scene3_whole.at(i) << "\n";
		out_whole_pre_params.flush();

		out_three_pre_no_classifer_params << scene3_no_classifer.at(i) << "\n";
		out_three_pre_no_classifer_params.flush();

		out_whole_params << abs(scene3_gt.at(i) - scene3_whole.at(i)) / scene3_gt.at(i) << "\n";
		out_whole_params.flush();

		out_three_params << abs(scene3_gt.at(i) - scene3_pre.at(i)) / scene3_gt.at(i) << "\n";
		out_three_params.flush();

		out_three_no_classifer_params << abs(scene3_gt.at(i) - scene3_no_classifer.at(i)) / scene3_gt.at(i) << "\n";
		out_three_no_classifer_params.flush();

		if (scene3_type.at(i) == 2)
			count++;
	}

	file_whole_params.close();
	file_three_params.close();
	file_gt_params.close();
	file_whole_pre_params.close();
	file_three_pre_params.close();
	file_three_no_classifer_params.close();
	file_three_pre_no_classifer_params.close();
	std::cout << "Accuracy is ." << (1.0 * count) / (scene1_files.size() + scene2_files.size() + scene3_files.size()) << std::endl;
	std::cout << "NNanalysis has completed." << std::endl;
}

void MainWindow::testOneNN(int index){
	// get images files
	std::vector<std::string> bin_files;
	QString label_tmp;
	QString input_tmp;
	std::string bin_deploy;
	std::string bin_model;
	std::string bin_classifer_deploy;
	std::string bin_classifer_model;
	std::string bin_mean;
	std::pair<float, float> parcelArea_whole;
	float mis_value = 0.0f;
	if (index == 1){
		bin_files = get_all_files_names_within_folder("NN_analysis/bin1/input/Scene1");
		input_tmp = QString("NN_analysis/bin1/input/Scene1/");
		label_tmp = QString("NN_analysis/bin1/labels/Scene1/");
		bin_deploy = "NN_analysis/models/bin1/deploy.prototxt";
		bin_model = "NN_analysis/models/bin1/parcel.caffemodel";
		parcelArea_whole = std::make_pair(0.8, 200);
	}
	else if (index == 2){
		bin_files = get_all_files_names_within_folder("NN_analysis/bin2/input/Scene1");
		input_tmp = QString("NN_analysis/bin2/input/Scene1/");
		label_tmp = QString("NN_analysis/bin2/labels/Scene1/");
		bin_deploy = "NN_analysis/models/bin2/deploy.prototxt";
		bin_model = "NN_analysis/models/bin2/parcel.caffemodel";
		bin_classifer_deploy = "NN_analysis/models/bin2/deploy_classifer.prototxt";
		bin_classifer_model = "NN_analysis/models/bin2/parcel_classifer.caffemodel";
		bin_mean = "NN_analysis/models/bin2/mean.binaryproto";
		parcelArea_whole = std::make_pair(0.8, 4.3);
		mis_value = 10;
	}
	else if (index == 3){
		bin_files = get_all_files_names_within_folder("NN_analysis/bin3/input/Scene1");
		input_tmp = QString("NN_analysis/bin3/input/Scene1/");
		label_tmp = QString("NN_analysis/bin3/labels/Scene1/");
		bin_deploy = "NN_analysis/models/bin3/deploy.prototxt";
		bin_model = "NN_analysis/models/bin3/parcel.caffemodel";
		bin_classifer_deploy = "NN_analysis/models/bin3/deploy_classifer.prototxt";
		bin_classifer_model = "NN_analysis/models/bin3/parcel_classifer.caffemodel";
		bin_mean = "NN_analysis/models/bin3/mean.binaryproto";
		parcelArea_whole = std::make_pair(0.8, 3.0);
		mis_value = 4.35;
	}
	else if (index == 4){
		bin_files = get_all_files_names_within_folder("NN_analysis/bin4/input/Scene1");
		input_tmp = QString("NN_analysis/bin4/input/Scene1/");
		label_tmp = QString("NN_analysis/bin4/labels/Scene1/");
		bin_deploy = "NN_analysis/models/bin4/deploy.prototxt";
		bin_model = "NN_analysis/models/bin4/parcel.caffemodel";
		bin_classifer_deploy = "NN_analysis/models/bin4/deploy_classifer.prototxt";
		bin_classifer_model = "NN_analysis/models/bin4/parcel_classifer.caffemodel";
		bin_mean = "NN_analysis/models/bin4/mean.binaryproto";
		parcelArea_whole = std::make_pair(0.8, 2.7);
		mis_value = 3.5;
	}
	else if (index == 5){
		bin_files = get_all_files_names_within_folder("NN_analysis/bin5/input/Scene1");
		input_tmp = QString("NN_analysis/bin5/input/Scene1/");
		label_tmp = QString("NN_analysis/bin5/labels/Scene1/");
		bin_deploy = "NN_analysis/models/bin5/deploy.prototxt";
		bin_model = "NN_analysis/models/bin5/parcel.caffemodel";
		bin_classifer_deploy = "NN_analysis/models/bin5/deploy_classifer.prototxt";
		bin_classifer_model = "NN_analysis/models/bin5/parcel_classifer.caffemodel";
		bin_mean = "NN_analysis/models/bin5/mean.binaryproto";
		parcelArea_whole = std::make_pair(0.8, 2.4);
		mis_value = 2.95;
	}
	else if (index == 6){
		bin_files = get_all_files_names_within_folder("NN_analysis/bin6/input/Scene1");
		input_tmp = QString("NN_analysis/bin6/input/Scene1/");
		label_tmp = QString("NN_analysis/bin6/labels/Scene1/");
		bin_deploy = "NN_analysis/models/bin6/deploy.prototxt";
		bin_model = "NN_analysis/models/bin6/parcel.caffemodel";
		bin_classifer_deploy = "NN_analysis/models/bin6/deploy_classifer.prototxt";
		bin_classifer_model = "NN_analysis/models/bin6/parcel_classifer.caffemodel";
		bin_mean = "NN_analysis/models/bin6/mean.binaryproto";
		parcelArea_whole = std::make_pair(0.8, 2.2);
	}
	else{
		return;
	}
	std::vector<float> bin_gt;
	// get ground truth values
	std::string txt_extentsion = ".txt";
	for (int i = 0; i < bin_files.size(); i++){
		QString str = QString::fromStdString(bin_files.at(i));
		str.replace("buildings_image_", "parameter_");
		str.replace(".png", ".txt");
		QString paras_path = label_tmp + str;
		QFile file(paras_path);
		if (!file.open(QIODevice::ReadOnly)) {
			return;
		}

		QTextStream in(&file);
		QTextStream out(stdout);
		QString line("");
		QStringList fields;
		in.readLine();
		while (!in.atEnd()) {
			line = in.readLine();
			fields = line.split(",");
		}
		file.close();
		QStringListIterator it(fields);
		std::vector<float> tmp;
		std::vector<float> paras;
		std::vector<int> stories;
		int index = 0;
		while (it.hasNext()) {
			tmp.push_back(it.next().trimmed().toFloat());
			//std::cout << tmp.at(index++) << std::endl;
		}
		bin_gt.push_back(tmp.at(3));
	}
	CaffeWrapper *caffe_parcel_type;
	if (index != 1){
		caffe_parcel_type = new CaffeWrapper(bin_classifer_deploy, bin_classifer_model,
			bin_mean);
	}
	Regression * parcel_small;
	Regression * parcel_median;
	Regression * parcel_big;
	if (index == 3){
		parcel_small = new Regression("NN_analysis/models/three/deploy.prototxt", "NN_analysis/models/three/parcel_first.caffemodel");
		parcel_median = new Regression("NN_analysis/models/three/deploy.prototxt", "NN_analysis/models/three/parcel_second.caffemodel");
		parcel_big = new Regression("NN_analysis/models/three/deploy.prototxt", "NN_analysis/models/three/parcel_third.caffemodel");
	}
	// predict
	// generate predict txt file from whole model 
	std::vector<float> bin_pre;
	Regression * parcel_model = new Regression(bin_deploy, bin_model);
	int mis_classifer_num = 0;
	for (int i = 0; i < bin_files.size(); i++){
		// get input image
		QString image_path = input_tmp + QString::fromStdString(bin_files.at(i));
		cv::Mat src;
		src = cv::imread(image_path.toUtf8().data(), CV_LOAD_IMAGE_COLOR);
		cv::Mat tmp[3];
		cv::split(src, tmp);
		//transfer img
		cv::equalizeHist(tmp[0], tmp[0]);
		cv::equalizeHist(tmp[1], tmp[1]);
		cv::equalizeHist(tmp[2], tmp[2]);
		cv::merge(tmp, 3, src);
		int parcel_type = 0;
		bool bcorrect = true;
		if (index != 1){
			// get parcel type
			std::vector<float> pred = caffe_parcel_type->get_pred(src);
			// predict the parcel type
			{
				int index_tmp = 0;
				float max_tmp = 0.0f;
				for (int iter = 0; iter < index; iter++){
					if (pred[iter] > max_tmp){
						max_tmp = pred[iter];
						index_tmp = iter;
					}
				}
				parcel_type = index_tmp;
			}
			if (parcel_type != 0){
				bcorrect = true;
				mis_classifer_num++;
			}
		}
		if (bcorrect){
			std::vector<float> pred_paras_tmp = parcel_model->get_pred(src);
			if (pred_paras_tmp[1] < 0)
				pred_paras_tmp[1] = 0;
			bin_pre.push_back((pred_paras_tmp[1] * (parcelArea_whole.second - parcelArea_whole.first) + parcelArea_whole.first));
		}
		else{
			if (index == 3){
				if (parcel_type == 0){
					std::vector<float> pred_paras = parcel_small->get_pred(src);
					bin_pre.push_back((pred_paras[1] * (3.0 - 0.8) + 0.8));
				}
				else if (parcel_type == 1){
					std::vector<float> pred_paras = parcel_median->get_pred(src);
					bin_pre.push_back((pred_paras[1] * (5.7 - 3.0) + 3.0));
				}
				else{
					std::vector<float> pred_paras = parcel_big->get_pred(src);
					bin_pre.push_back((pred_paras[1] * (200.0 - 5.7) + 5.7));
				}

			}
			else 
				bin_pre.push_back(mis_value);
		}
	}

	// save

	// save results
	QFile file_gt_params(QString("NN_analysis/gt.txt"));
	if (!file_gt_params.open(QIODevice::WriteOnly)) {
		std::cerr << "Cannot open file for writing: " << file_gt_params.fileName().toUtf8().constData() << std::endl;
		return;
	}
	QTextStream out_gt_params(&file_gt_params);

	QFile file_pre_params(QString("NN_analysis/pre.txt"));
	if (!file_pre_params.open(QIODevice::WriteOnly)) {
		std::cerr << "Cannot open file for writing: " << file_pre_params.fileName().toUtf8().constData() << std::endl;
		return;
	}
	QTextStream out_pre_params(&file_pre_params);

	QFile file_error_params(QString("NN_analysis/relative_error.txt"));
	if (!file_error_params.open(QIODevice::WriteOnly)) {
		std::cerr << "Cannot open file for writing: " << file_error_params.fileName().toUtf8().constData() << std::endl;
		return;
	}
	QTextStream out_error_params(&file_error_params);

	QFile file_abs_error_params(QString("NN_analysis/abs_error.txt"));
	if (!file_abs_error_params.open(QIODevice::WriteOnly)) {
		std::cerr << "Cannot open file for writing: " << file_abs_error_params.fileName().toUtf8().constData() << std::endl;
		return;
	}
	QTextStream out_abs_error_params(&file_abs_error_params);

	for (int i = 0; i < bin_files.size(); i++){
		out_gt_params << bin_gt.at(i) << "\n";
		out_gt_params.flush();

		out_pre_params << bin_pre.at(i) << "\n";
		out_pre_params.flush();

		out_error_params << abs(bin_gt.at(i) - bin_pre.at(i)) / bin_gt.at(i) << "\n";
		out_error_params.flush();

		out_abs_error_params << abs(bin_gt.at(i) - bin_pre.at(i)) * 100 << "\n";
		out_abs_error_params.flush();
	}

	file_gt_params.close();
	file_pre_params.close();
	file_error_params.close();
	std::cout << "mis classifer number is " << mis_classifer_num << std::endl;
	std::cout << "NNanalysis has completed." << std::endl;
}

void MainWindow::onNNtest(){
	//testOneNN(1);
	//testOneNN(2);
	//testOneNN(3);
	testOneNN(4);
	//testOneNN(5);
	//testOneNN(6);
}

void MainWindow::onCallPython(){
	
	PyObject *pName, *pModule, *pDict, *pFunc;
	PyObject *pArgs, *pValue;
	Py_Initialize();
	pName = PyString_FromString("ComputeCityStats");

	pModule = PyImport_Import(pName);
	Py_DECREF(pName);

	if (pModule != NULL) {
		pFunc = PyObject_GetAttrString(pModule, "getCityStats");
		/* pFunc is a new reference */

		if (pFunc && PyCallable_Check(pFunc)) {
			pArgs = PyTuple_New(2);
			pValue = PyString_FromString("../x64/Release/Chicago");
			PyTuple_SetItem(pArgs, 0, pValue);
			pValue = PyInt_FromLong(0);
			PyTuple_SetItem(pArgs, 1, pValue);
			pValue = PyObject_CallObject(pFunc, pArgs);
			Py_DECREF(pArgs);
			if (pValue != NULL) {
				printf("Result of call: %s\n", PyString_AsString(pValue));
				Py_DECREF(pValue);
			}
			else {
				Py_DECREF(pFunc);
				Py_DECREF(pModule);
				PyErr_Print();
				fprintf(stderr, "Call failed\n");
				return;
			}
		}
		else {
			if (PyErr_Occurred())
				PyErr_Print();
			fprintf(stderr, "Cannot find function \"%s\"\n", "getCityStats");
		}
		Py_XDECREF(pFunc);
		Py_DECREF(pModule);
	}
	else {
		PyErr_Print();
		fprintf(stderr, "Failed to load \"%s\"\n", "ComputeCityStats");
		return;
	}
	Py_Finalize();
}

void MainWindow::onLoadLoadGeoInfo(){
	// load the image
	QString filename_src = QFileDialog::getOpenFileName(this, tr("Open Image file..."), "", tr("Image Files (*.tiff *.tif)"));
	if (filename_src.isEmpty()) return;
	std::vector<double> result = Util::getGeoInfo(filename_src.toUtf8().data());
	//std::cout << "geo 0 is " << result.at(0) << std::endl;
	//std::cout << "geo 1 is " << result.at(1) << std::endl;
	//std::cout << "geo 2 is " << result.at(2) << std::endl;
	//std::cout << "geo 3 is " << result.at(3) << std::endl;
	G::global()["origin_long"] = result.at(0);
	G::global()["origin_lat"] = result.at(1);
	G::global()["pixel_size_long"] = result.at(2);
	G::global()["pixel_size_lat"] = result.at(3);
	std::cout << "Finish loading Geo Info for the segmented image!!" << std::endl;
}

void MainWindow::onLoadHeightInfo(){
	// load the image
	QString filename_src = QFileDialog::getOpenFileName(this, tr("Open Image file..."), "", tr("Image Files (*.tiff *.tif)"));
	if (filename_src.isEmpty()) return;
	G::global()["height_tif"] = filename_src;
	std::cout << "Finish onLoadHeightInfo!!" << std::endl;
}

void MainWindow::onLoadPopulationInfo(){
	// load the image
	QString filename_src = QFileDialog::getOpenFileName(this, tr("Open Image file..."), "", tr("Image Files (*.tiff *.tif)"));
	if (filename_src.isEmpty()) return;
	G::global()["population_tif"] = filename_src;
	std::cout << "Finish onLoadHeightInfo!!" << std::endl;
}

void MainWindow::onLoadParcelImage(){
	// load the image
	QString filename_src = QFileDialog::getOpenFileName(this, tr("Open Image file..."), "", tr("Image Files (*.png *.jpg *.bmp)"));
	if (filename_src.isEmpty()) return;
	G::global()["parcel_image"] = filename_src;
	std::cout << "Finish method onLoadParcelImage!!" << std::endl;
}

void MainWindow::onLoadSegmentedImage(){
	// load the image
	QString filename_src = QFileDialog::getOpenFileName(this, tr("Open Image file..."), "", tr("Image Files (*.png *.jpg *.bmp)"));
	if (filename_src.isEmpty()) return;
	G::global()["segmented_image"] = filename_src;
	std::cout << "Finish method onLoadSegmentedImage!!" << std::endl;
	//cv::Mat src;
	//cv::Mat src_gray;
	///// Load source image and convert it to gray
	//src = cv::imread(filename_src.toUtf8().data(), CV_LOAD_IMAGE_COLOR);

	//cv::Scalar lowerb = cv::Scalar(0, 0, 255);
	//cv::Scalar upperb = cv::Scalar(0, 0, 255);
	//cv::inRange(src, lowerb, upperb, src_gray);

	//cv::Mat threshold_output;
	//std::vector<std::vector<cv::Point> > contours;
	//std::vector<cv::Vec4i> hierarchy;

	///// Detect edges using Threshold
	//threshold(src_gray, threshold_output, thresh, 255, cv::THRESH_BINARY);
	///// Find contours
	//findContours(threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));

	///// Approximate contours to polygons + get bounding rects and circles
	//std::vector<std::vector<cv::Point> > contours_poly(contours.size());
	//std::vector<cv::Rect> boundRect(contours.size());
	//std::vector<cv::Point2f>center(contours.size());
	//std::vector<float>radius(contours.size());

	//for (int i = 0; i < contours.size(); i++)
	//{
	//	cv::approxPolyDP(cv::Mat(contours[i]), contours_poly[i], 3, true);
	//	boundRect[i] = cv::boundingRect(cv::Mat(contours_poly[i]));
	//	cv::minEnclosingCircle((cv::Mat)contours_poly[i], center[i], radius[i]);
	//}

	///// Draw polygonal contour + bonding rects + circles
	//if (QDir("blocks").exists()) {
	//	std::cout << "Removing existing files in the output directory...";
	//	QDir("blocks").removeRecursively();
	//	std::cout << " done." << std::endl;
	//}
	//if (!QDir("blocks").exists()){
	//	QDir().mkpath("blocks");
	//}
	//cv::Mat drawing = cv::Mat::zeros(threshold_output.size(), CV_8UC3);
	//float block_area = 0.0f;
	//float block_parcel_area = 0.0f;
	//QString filename = "blocks/parasInfo.txt";
	//QFile file_params(filename);
	//if (!file_params.open(QIODevice::WriteOnly)) {
	//	std::cerr << "Cannot open file for writing: " << file_params.fileName().toUtf8().constData() << std::endl;
	//	return;
	//}
	//// write the header to the file
	//QTextStream out_params(&file_params);
	//out_params << "block_num" << ",";
	//out_params << "center_x" << ",";
	//out_params << "center_y" << ",";
	//out_params << "bb_x" << ",";
	//out_params << "bb_y" << ",";
	//out_params << "bb_width" << ",";
	//out_params << "bb_height" << "\n";
	////
	//for (int i = 0; i< contours.size(); i++)
	//{
	//	block_area = cv::contourArea(contours_poly[i]);
	//	if (block_area < 3000 || block_area > 100000)
	//		continue;
	//	block_parcel_area = compute_parcel_area(src(boundRect[i]));
	//	if (block_parcel_area / (boundRect[i].width * boundRect[i].height) < 0.15)
	//		continue;
	//	if (boundRect[i].height < 30)
	//		continue;
	//	cv::Mat crop = src(boundRect[i]);
	//	QString filename("blocks/" + QString::number(i)  + ".png");
	//	cv::imwrite(filename.toUtf8().data(), crop);
	//	// results
	//	out_params << i << ",";
	//	out_params << center[i].x << ",";
	//	out_params << center[i].y << ",";
	//	out_params << boundRect[i].x << ",";
	//	out_params << boundRect[i].y << ",";
	//	out_params << boundRect[i].width << ",";
	//	out_params << boundRect[i].height << "\n";
	//	out_params.flush();
	//}
	//file_params.close();
	std::cout << "Finish loading segmented image!" << std::endl;
	return;
}

void MainWindow::onLoadGroundTruth(){
	// load the image
	QString filename_src = QFileDialog::getOpenFileName(this, tr("Open Image file..."), "", tr("Image Files (*.png *.jpg *.bmp)"));
	if (filename_src.isEmpty()) return;
	G::global()["ground_truth_image"] = filename_src;
	std::cout << "Finish loading ground truth image!" << std::endl;
	return;
}

void MainWindow::onLoadWholeImage(){
	// load the image
	QString filename_src = QFileDialog::getOpenFileName(this, tr("Open Image file..."), "", tr("Image Files (*.png *.jpg *.bmp)"));
	if (filename_src.isEmpty()) return;
	G::global()["gt_whole_image"] = filename_src;
	std::cout << "Finish loading gt whole image!" << std::endl;
	return;
}

void MainWindow::onViewChanged() {
	G::global()["shader2D"] = ui.actionView2D->isChecked();

	int terrainMode;
	if (ui.actionView2D->isChecked()) {
		terrainMode = 0;

		// change to top view
		glWidget->camera.resetCamera();
	}
	else  {
		terrainMode = 1;
	}

	glWidget->vboRenderManager.changeTerrainShader(terrainMode);
	urbanGeometry->update(glWidget->vboRenderManager);
	glWidget->shadow.makeShadowMap(glWidget);
	glWidget->updateGL();
}

void MainWindow::onShowWater() {
	G::global()["show_water"] = ui.actionShowWater->isChecked();
	glWidget->updateGL();
}

void MainWindow::onSeaLevel() {
	bool ok;

	QInputDialog dlg;
	dlg.setOptions(QInputDialog::NoButtons);
		
	QString text = dlg.getText(NULL, "Sea Level", "Enter sea level", QLineEdit::Normal,	QString::number(G::getFloat("sea_level")), &ok);
	
	if (ok && !text.isEmpty()) {
		G::global()["sea_level"] = text.toFloat();
		glWidget->updateGL();
	}
}

void MainWindow::onShowControlWidget() {
	controlWidget->show();
	addDockWidget(Qt::LeftDockWidgetArea, controlWidget);
}

std::vector<std::string> MainWindow::get_all_files_names_within_folder(std::string folder)
{
	std::vector<std::string> names;
	std::string search_path = folder + "/*.*";
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path.c_str(), &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				names.push_back(fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}