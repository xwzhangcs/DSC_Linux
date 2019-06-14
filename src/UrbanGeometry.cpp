#include "UrbanGeometry.h"
#include <limits>
#include <iostream>
#include <QFile>
#include "common.h"
#include "global.h"
#include "GraphUtil.h"
#include "MainWindow.h"
#include "Util.h"
#include "RoadMeshGenerator.h"
#include "BlockMeshGenerator.h"
#include "Pm.h"
#include "PmBlocks.h"
#include "PmParcels.h"
#include "SateBlocks.h"
#include "SateParcels.h"
#include "PmBuildings.h"
#include "SateBuildings.h"
#include "SateParcelsAndBuildings.h"
#include "PmVegetation.h"
#include "GShapefile.h"
#include "GraphUtil.h"
#include "PMRoadGenerator.h"
#include <QDir>
#include <QProcess>
#include <QTest>
#include "OSMRoadsParser.h"

int UrbanGeometry::width;
int UrbanGeometry::depth;
MainWindow* UrbanGeometry::mainWin;
RoadGraph UrbanGeometry::roads;
BlockSet UrbanGeometry::blocks;
glm::vec2 UrbanGeometry::minBound;
glm::vec2 UrbanGeometry::maxBound;
Polygon2D UrbanGeometry::zone;
std::vector<Block> UrbanGeometry::myBlocks;
VBORenderManager UrbanGeometry::myRenderManager;

ShapefileStats UrbanGeometry::truthStats;

UrbanGeometry::UrbanGeometry(MainWindow* mainWin) {
	this->mainWin = mainWin;

	// load a default zone and terrain
	//loadZone("../3D/new_zone.shp");
	//loadZone("../3D/Zone.shp");
	loadZone("../3D/Zone_new.shp");
	mainWin->glWidget->vboRenderManager.vboTerrain.init(&mainWin->glWidget->vboRenderManager, glm::vec2(5000, 5000));
}

void UrbanGeometry::generateRoads() {
	clear();

	PMRoadGenerator generator(mainWin, roads, &mainWin->glWidget->vboRenderManager, zone);
	generator.generateRoadNetwork();
	update(mainWin->glWidget->vboRenderManager);
}

void UrbanGeometry::generateBlocks() {
	PmBlocks::generateBlocks(&mainWin->glWidget->vboRenderManager, roads, blocks);
	update(mainWin->glWidget->vboRenderManager);
}

void UrbanGeometry::sateGetBlocks() {
	SateBlocks::generateBlocks(&mainWin->glWidget->vboRenderManager, roads, blocks);
	//update(mainWin->glWidget->vboRenderManager);
}

void UrbanGeometry::generateParcels() {
	PmParcels::generateParcels(mainWin->glWidget->vboRenderManager, blocks.blocks);
	update(mainWin->glWidget->vboRenderManager);
}

void UrbanGeometry::sateGetParcels(float boundary_v1, float boundary_v2, int testbN, bool bTest) {
	SateParcels::generateParcels(mainWin->glWidget->vboRenderManager, blocks.blocks, boundary_v1, boundary_v2, testbN, bTest);
	update(mainWin->glWidget->vboRenderManager);
}

void UrbanGeometry::sateGetBuildings(float correction){
	SateBuildings::generateBuildings(mainWin->glWidget->vboRenderManager, blocks.blocks, correction);
	update(mainWin->glWidget->vboRenderManager);
}

void UrbanGeometry::sateGetParcelsAndBuildings(){
	SateParcelsAndBuildings::generateParcelsAndBuildings(mainWin->glWidget->vboRenderManager, blocks.blocks);
	update(mainWin->glWidget->vboRenderManager);
}

void UrbanGeometry::generateBuildings() {
	PmBuildings::generateBuildings(mainWin->glWidget->vboRenderManager, blocks.blocks);
	update(mainWin->glWidget->vboRenderManager);
}

void UrbanGeometry::generateVegetation() {
	PmVegetation::generateVegetation(mainWin->glWidget->vboRenderManager, blocks.blocks);
	update(mainWin->glWidget->vboRenderManager);
}

float UrbanGeometry::generateAll(bool updateGeometry) {
	clear();

	// 2016/11/10
	// We decided to remove randomness.
	srand(0);

	// warm up the random numbers
	for (int i = 0; i < 100; ++i) rand();

	PMRoadGenerator generator(mainWin, roads, &mainWin->glWidget->vboRenderManager, zone);
	generator.generateRoadNetwork();
	PmBlocks::generateBlocks(&mainWin->glWidget->vboRenderManager, roads, blocks);
	PmParcels::generateParcels(mainWin->glWidget->vboRenderManager, blocks.blocks);
	PmBuildings::generateBuildings(mainWin->glWidget->vboRenderManager, blocks.blocks);
	
	// compute the building coverage
	float buildingCoverageRatio = 0.0f;
	for (int i = 0; i < blocks.size(); ++i) {
		if (blocks[i].isPark) continue;
		for (int j = 0; j < blocks[i].parcels.size(); ++j) {
			if (blocks[i].parcels[j].isPark) continue;
			if (blocks[i].parcels[j].building.buildingFootprint.size() < 3) continue;
			buildingCoverageRatio += blocks[i].parcels[j].building.buildingFootprint.area();

		}
	}
	buildingCoverageRatio /= zone.area();

	if (updateGeometry) {
		update(mainWin->glWidget->vboRenderManager);
	}

	return buildingCoverageRatio;
}

void UrbanGeometry::generateToolAll(const QString & filename, int image_size){
	clear();

	// 2016/11/10
	// We decided to remove randomness.
	//srand(0);

	// warm up the random numbers
	for (int i = 0; i < 100; ++i) rand();

	//
	int blockWidth = G::getFloat("blockWidth");
	int blockHeight = G::getFloat("blockHeight");
	float x_min = -blockWidth / 2;
	float x_min_third = -blockWidth / 6;
	float x_max = blockWidth / 2;
	float x_max_third = blockWidth / 6;
	float y_min = -blockHeight / 2;
	float y_min_third = -blockHeight / 6;
	float y_max = blockHeight / 2;
	float y_max_third = -blockHeight / 6;
	//std::cout << "x_min is " << x_min << std::endl;
	//std::cout << "y_min is " << y_min << std::endl;

	std::vector<Block> blocks;
	Block block;
	std::vector<Polygon3D> blockContours;
	Polygon3D loop;
	{
		QVector3D p1(x_min, y_min, 0.0f);
		QVector3D p2(x_min_third, y_min, 0.0f);
		QVector3D p3(x_max_third, y_min, 0.0f);
		QVector3D p4(x_max, y_min, 0.0f);

		QVector3D p5(x_max, y_min_third, 0.0f);
		QVector3D p6(x_max, y_max_third, 0.0f);

		QVector3D p7(x_max, y_max, 0.0f);
		QVector3D p8(x_max_third, y_max, 0.0f);
		QVector3D p9(x_min_third, y_max, 0.0f);
		QVector3D p10(x_min, y_max, 0.0f);

		QVector3D p11(x_min, y_max_third, 0.0f);
		QVector3D p12(x_min, y_min_third, 0.0f);

		loop.push_back(p1);
		loop.push_back(p2);
		loop.push_back(p3);
		loop.push_back(p4);
		loop.push_back(p5);
		loop.push_back(p6);
		loop.push_back(p7);
		loop.push_back(p8);
		loop.push_back(p9);
		loop.push_back(p10);
		loop.push_back(p11);
		loop.push_back(p12);
	}
	{
		blockContours.push_back(loop);
		block.blockContours = blockContours;
		block.isPark = false;
		blocks.push_back(block);
	}

	PmParcels::generateParcels(mainWin->glWidget->vboRenderManager, blocks);
	PmBuildings::generateBuildings(mainWin->glWidget->vboRenderManager, blocks);
	std::vector<cv::Point> points;

	//save to an image
	{
		cv::Mat img(image_size, blockWidth, CV_8UC3, cv::Scalar(0, 255, 0));
		std::cout << "img row  is " << img.rows << std::endl;
		//std::cout << "height is " << img.size().height << std::endl;
		float offset_x = blockWidth * 0.5;
		float offset_y = blockHeight * 0.5;
		// draw parcels
		for (int bn = 0; bn < blocks.size(); bn++){
			for (int i = 0; i < blocks[bn].parcels.size(); i++){
				if (blocks[bn].parcels.at(i).isPark)
					continue;
				//for (int pn = 0; pn < blocks[bn].parcels.at(i).parcelContour.size(); pn++) {
				//	int next = (pn + 1) % blocks[bn].parcels.at(i).parcelContour.size();
				//	int x1 = blocks[bn].parcels.at(i).parcelContour[pn].x();
				//	int y1 = blocks[bn].parcels.at(i).parcelContour[pn].y();
				//	int x2 = blocks[bn].parcels.at(i).parcelContour[next].x();
				//	int y2 = blocks[bn].parcels.at(i).parcelContour[next].y();
				//	cv::line(img, cv::Point(x1 + offset_x, image_size - (y1 + offset_y)), cv::Point((x2 + offset_x), image_size - (y2 + offset_y)), cv::Scalar(0, 0, 0), 1);
				//}

				for (int j = 0; j < blocks[bn].parcels.at(i).building.buildingFootprint.size(); j++) {
					//std::cout << block.parcels.at(i).building.buildingFootprint.size() << std::endl;
					int next = (j + 1) % blocks[bn].parcels.at(i).building.buildingFootprint.size();
					int x1 = blocks[bn].parcels.at(i).building.buildingFootprint[j].x();
					int y1 = blocks[bn].parcels.at(i).building.buildingFootprint[j].y();
					int x2 = blocks[bn].parcels.at(i).building.buildingFootprint[next].x();
					int y2 = blocks[bn].parcels.at(i).building.buildingFootprint[next].y();
					//cv::line(img, cv::Point((x1 + offset_x) * scale_x, (y1 + offset_y) * scale_y), cv::Point((x2 + offset_x) * scale_x, (y2 + offset_y) * scale_y), cv::Scalar(255, 0, 0), 1);
					points.push_back(cv::Point((x1 + offset_x), image_size - (y1 + offset_y)));
				}
				cv::fillConvexPoly(img,               //Image to be drawn on
					points,                 //C-Style array of points
					cv::Scalar(255, 0, 0),  //Color , BGR form
					8,             // connectedness, 4 or 8
					0);
				points.clear();
			}

		}
		cv::imwrite(filename.toUtf8().constData(), img);
	}
}

bool UrbanGeometry::generateScenarios(int numScenarios, const QString& output_dir, bool useSimulator, const QString& flood_simulator_dir, const std::pair<float, float>& avenueSegmentLengthRange, const std::pair<float, float>& roadBaseOrientationRange, const std::pair<float, float>& roadCurvatureRange, const std::pair<float, float>& majorRoadWidthRange, const std::pair<float, float>& minorRoadWidthRange, const std::pair<float, float>& parkRatioRange, const std::pair<float, float>& parcelAreaRange, float parcelAreaDev, const std::pair<float, float>& setbackFrontRange, const std::pair<float, float>& setbackRearRange, const std::pair<float, float>& setbackSideRange, const std::pair<int, int>& numStoriesRange, const std::pair<int, int>& minBuildingDimRange, bool useBuildingCoverage, const std::pair<float, float>& buildingCoverageRange, bool generate_building_footprints_image, int building_footprints_image_size) {
	if (QDir(output_dir).exists()) {
		std::cout << "Removing existing files in the output directory...";
		QDir(output_dir).removeRecursively();
		std::cout << " done." << std::endl;
	}
	QDir().mkpath(output_dir);

	// open a file to save the parameter values
	QFile file_params(output_dir + "/parameters.txt");
	if (!file_params.open(QIODevice::WriteOnly)) {
		std::cerr << "Cannot open file for writing: " << file_params.fileName().toUtf8().constData() << std::endl;
		return false;
	}
	QTextStream out_params(&file_params);

	QFile file_indicators(output_dir + "/indicators.txt");
	QTextStream out_indicators;
	if (useSimulator) {
		if (!file_indicators.open(QIODevice::WriteOnly)) {
			std::cerr << "Cannot open file for writing: " << file_indicators.fileName().toUtf8().constData() << std::endl;
			return false;
		}
		out_indicators.setDevice(&file_indicators);
		out_indicators.setRealNumberPrecision(10);
	}

	// write the header to the file
	out_params << "No." << ",";
	out_params << "avenueAvgSegmentLength" << ",";
	out_params << "road_base_orientation" << ",";
	out_params << "road_curvature" << ",";
	out_params << "major_road_width" << ",";
	out_params << "minor_road_width" << ",";
	out_params << "parksRatio" << ",";
	out_params << "parcel_area_mean" << ",";
	out_params << "parcel_area_deviation" << ",";
	out_params << "parcel_setback_front" << ",";
	out_params << "parcel_setback_rear" << ",";
	out_params << "parcel_setback_sides" << ",";
	out_params << "building_stories_min" << ",";
	out_params << "building_stories_max" << ",";
	out_params << "building_min_dimension" << ",";
	out_params << "building_coverage" << "\n";

	for (int iter = 0; iter < numScenarios; ++iter) {
		std::cout << "Generating scenarios: " << iter + 1 << std::endl;

		// set random seed
		srand((unsigned)time(NULL) + iter);

		// warm up the random numbers
		for (int i = 0; i < 100; ++i) rand();

		float buildingCoverageRatio = 0.0f;
		int retry_count = 0;

		while (true) {
			// set the parameter values
			G::global()["avenueAvgSegmentLength"] = Util::genRand(avenueSegmentLengthRange.first, avenueSegmentLengthRange.second);
			G::global()["road_base_orientation"] = Util::genRand(roadBaseOrientationRange.first, roadBaseOrientationRange.second);
			G::global()["road_curvature"] = Util::genRand(roadCurvatureRange.first, roadCurvatureRange.second);
			G::global()["major_road_width"] = Util::genRand(majorRoadWidthRange.first, majorRoadWidthRange.second);
			G::global()["minor_road_width"] = Util::genRand(minorRoadWidthRange.first, minorRoadWidthRange.second);
			G::global()["parksRatio"] = Util::genRand(parkRatioRange.first, parkRatioRange.second);
			G::global()["parcel_area_mean"] = Util::genRand(parcelAreaRange.first, parcelAreaRange.second);
			G::global()["parcel_area_deviation"] = parcelAreaDev;
			G::global()["parcel_setback_front"] = Util::genRand(setbackFrontRange.first, setbackFrontRange.second);
			G::global()["parcel_setback_rear"] = Util::genRand(setbackRearRange.first, setbackRearRange.second);
			G::global()["parcel_setback_sides"] = Util::genRand(setbackSideRange.first, setbackSideRange.second);
			G::global()["building_stories_min"] = numStoriesRange.first;
			G::global()["building_stories_max"] = numStoriesRange.second;
			G::global()["building_min_dimension"] = Util::genRand(minBuildingDimRange.first, minBuildingDimRange.second);
			
			// generate a city
			buildingCoverageRatio = generateAll(false);

			// if the building coverage range is specified, check it and if not satisfied, regenerate a city layout.
			if (!useBuildingCoverage || (buildingCoverageRatio >= buildingCoverageRange.first && buildingCoverageRatio <= buildingCoverageRange.second)) break;

			retry_count++;
			if (retry_count >= 1000) {
				file_params.close();
				std::cerr << "Invalid parameter ranges. No city layout can be generated." << std::endl;
				return false;
			}
		}

		std::cout << "  avenueAvgSegmentLength: " << G::getFloat("avenueAvgSegmentLength") << std::endl;
		std::cout << "  road_base_orientation: " << G::getFloat("road_base_orientation") << std::endl;
		std::cout << "  road_curvature: " << G::getFloat("road_curvature") << std::endl;
		std::cout << "  major_road_width: " << G::getFloat("major_road_width") << std::endl;
		std::cout << "  minor_road_width: " << G::getFloat("minor_road_width") << std::endl;
		std::cout << "  parksRatio: " << G::getFloat("parksRatio") << std::endl;
		std::cout << "  parcel_area_mean: " << G::getFloat("parcel_area_mean") << std::endl;
		std::cout << "  parcel_area_deviation: " << G::getFloat("parcel_area_deviation") << std::endl;
		std::cout << "  parcel_setback_front: " << G::getFloat("parcel_setback_front") << std::endl;
		std::cout << "  parcel_setback_rear: " << G::getFloat("parcel_setback_rear") << std::endl;
		std::cout << "  parcel_setback_sides: " << G::getFloat("parcel_setback_sides") << std::endl;
		std::cout << "  building_stories_min: " << G::getInt("building_stories_min") << std::endl;
		std::cout << "  building_stories_max: " << G::getInt("building_stories_max") << std::endl;
		std::cout << "  building_min_dimension: " << G::getFloat("building_min_dimension") << std::endl;
		std::cout << "  building_coverage: " << buildingCoverageRatio << std::endl;
		std::cout << std::endl;

		// save roads
		QString filename_roads = output_dir + QString("/roads_%1.shp").arg(iter + 1, 6, 10, QChar('0'));
		saveRoads(filename_roads.toUtf8().constData());

		// save parcels
		QString filename_parcels = output_dir + QString("/parcels_%1.shp").arg(iter + 1, 6, 10, QChar('0'));
		saveParcels(filename_parcels.toUtf8().constData());

		// save building footprints
		QString filename_buildings = output_dir + QString("/buildings_%1.shp").arg(iter + 1, 6, 10, QChar('0'));
		saveBuildings(filename_buildings.toUtf8().constData());
		if (useSimulator) {
			saveBuildings((flood_simulator_dir + "/Bu1.shp").toUtf8().constData());
		}

		if (generate_building_footprints_image) {
			// save building footprints image
			cv::Mat img(building_footprints_image_size, building_footprints_image_size, CV_8UC3, cv::Scalar(255, 255, 255));
			float offset_x = (maxBound.x - minBound.x) * 0.5;
			float offset_y = (maxBound.y - minBound.y) * 0.5;
			float scale_x = (float)building_footprints_image_size / (maxBound.x - minBound.x);
			float scale_y = (float)building_footprints_image_size / (maxBound.y - minBound.y);
			for (int bN = 0; bN < blocks.size(); ++bN) {
				if (blocks[bN].isPark) continue;
				for (int pN = 0; pN < blocks[bN].parcels.size(); ++pN) {
					if (blocks[bN].parcels[pN].isPark) continue;
					Loop3D& contour = blocks[bN].parcels[pN].building.buildingFootprint.contour;
					if (contour.size() < 3) continue;

					for (int fN = 0; fN < contour.size(); ++fN) {
						int next = (fN + 1) % contour.size();
						
						cv::line(img, cv::Point((contour[fN].x() + offset_x) * scale_x, (contour[fN].y() + offset_y) * scale_y),
							cv::Point((contour[next].x() + offset_x) * scale_x, (contour[next].y() + offset_y) * scale_y),
							cv::Scalar(0, 0, 0), 1, cv::LINE_AA);
					}
				}
			}
			QString filename_buildings_image = output_dir + QString("/buildings_image_%1.png").arg(iter + 1, 6, 10, QChar('0'));
			cv::flip(img, img, 0);
			cv::imwrite(filename_buildings_image.toUtf8().constData(), img);
		}

		// save the parameter values
		out_params << iter + 1 << ",";
		out_params << G::getFloat("avenueAvgSegmentLength") << ",";
		out_params << G::getFloat("road_base_orientation") << ",";
		out_params << G::getFloat("road_curvature") << ",";
		out_params << G::getFloat("major_road_width") << ",";
		out_params << G::getFloat("minor_road_width") << ",";
		out_params << G::getFloat("parksRatio") << ",";
		out_params << G::getFloat("parcel_area_mean") << ",";
		out_params << G::getFloat("parcel_area_deviation") << ",";
		out_params << G::getFloat("parcel_setback_front") << ",";
		out_params << G::getFloat("parcel_setback_rear") << ",";
		out_params << G::getFloat("parcel_setback_sides") << ",";
		out_params << G::getFloat("building_stories_min") << ",";
		out_params << G::getFloat("building_stories_max") << ",";
		out_params << G::getFloat("building_min_dimension") << ",";
		out_params << buildingCoverageRatio << "\n";
		out_params.flush();

		if (useSimulator) {
			QFile file_ind(flood_simulator_dir + "/indicators");
			if (file_ind.exists()) file_ind.remove();

			QProcess process(mainWin);
			process.start("cmd " + flood_simulator_dir + "/Urbannetwork.exe");
			if (process.waitForStarted(-1)) {
				std::cout << "Running simulator..." << std::endl;

				if (process.waitForFinished(-1)) {
					QString output(process.readAllStandardOutput());
					std::cout << output.toUtf8().constData() << std::endl;

					while (!file_ind.exists()) {
						QTest::qSleep(1000);
					}

					std::cout << "Done." << std::endl;
					std::cout << process.exitStatus() << std::endl;

					QFile file_ind(flood_simulator_dir + "/indicators");
					if (file_ind.open(QIODevice::ReadOnly)) {
						QTextStream in(&file_ind);
						int cnt = 0;
						while (!in.atEnd()) {
							double value = in.readLine().toDouble();
							if (cnt > 0) out_indicators << ",";
							out_indicators << value;
							cnt++;
						}
						out_indicators << "\n";
						file_ind.close();
					}
				}
				else {
					std::cout << "Stopped with errors." << std::endl;
				}
			}
			else {
				std::cout << "The simulator could not start." << std::endl;
			}
		}
	}

	file_params.close();
	if (useSimulator) {
		file_indicators.close();
	}
	
	std::cout << "Generation has completed." << std::endl;

	return true;
}

bool UrbanGeometry::generateToolBlocks(int numScenarios, const QString& output_dir, const QString& batch_num, const std::pair<float, float>& blockWidthRange, const std::pair<float, float>& blockHeightRange, const std::pair<float, float>& parkRatioRange, const std::pair<float, float>& parcelAreaRange, float parcelAreaDev, const std::pair<float, float>& setbackFrontRange, const std::pair<float, float>& setbackRearRange, const std::pair<float, float>& setbackSideRange, const std::pair<int, int>& numStoriesRange, const std::pair<int, int>& minBuildingDimRange, int building_footprints_image_size){
	QString image_path(output_dir + "/input" + "/Scene" + batch_num);
	QString label_path(output_dir + "/labels" + "/Scene" + batch_num);
	if (QDir(image_path).exists()) {
		std::cout << "Removing existing files in the output directory...";
		QDir(image_path).removeRecursively();
		std::cout << " done." << std::endl;
	}
	QDir().mkpath(image_path);

	if (QDir(label_path).exists()) {
		std::cout << "Removing existing files in the output directory...";
		QDir(label_path).removeRecursively();
		std::cout << " done." << std::endl;
	}
	QDir().mkpath(label_path);

	for (int iter = 0; iter < numScenarios; ++iter) {
		std::cout << "Generating scenarios: " << iter + 1 << std::endl;

		// open a file to save the parameter values
		QFile file_params(label_path + QString("/parameter_%1.txt").arg(iter + 1, 6, 10, QChar('0')));
		if (!file_params.open(QIODevice::WriteOnly)) {
			std::cerr << "Cannot open file for writing: " << file_params.fileName().toUtf8().constData() << std::endl;
			return false;
		}
		QTextStream out_params(&file_params);
		// write the header to the file
		out_params << "No." << ",";
		out_params << "block_width" << ",";
		out_params << "block_height" << ",";
		out_params << "parcel_area_mean" << ",";
		out_params << "parcel_area_deviation" << ",";
		out_params << "parcel_setback_front" << ",";
		out_params << "parcel_setback_rear" << ",";
		out_params << "parcel_setback_sides" << ",";
		out_params << "building_stories_min" << ",";
		out_params << "building_stories_max" << ",";
		out_params << "building_min_dimension" << "\n";

		// set random seed
		srand((unsigned)time(NULL) + iter);

		// warm up the random numbers
		for (int i = 0; i < 100; ++i) rand();

		float buildingCoverageRatio = 0.0f;
		int retry_count = 0;

		// set the parameter values
		G::global()["blockWidth"] = Util::genRand(blockWidthRange.first, blockWidthRange.second);
		G::global()["blockHeight"] = Util::genRand(blockHeightRange.first, blockHeightRange.second);
		G::global()["parksRatio"] = Util::genRand(parkRatioRange.first, parkRatioRange.second);
		// unit is 100
		G::global()["parcel_area_mean"] = 100 * Util::genRand(parcelAreaRange.first, parcelAreaRange.second);
		G::global()["parcel_area_deviation"] = parcelAreaDev;
		G::global()["parcel_setback_front"] = Util::genRand(setbackFrontRange.first, setbackFrontRange.second);
		G::global()["parcel_setback_rear"] = Util::genRand(setbackRearRange.first, setbackRearRange.second);
		G::global()["parcel_setback_sides"] = Util::genRand(setbackSideRange.first, setbackSideRange.second);
		G::global()["building_stories_min"] = numStoriesRange.first;
		G::global()["building_stories_max"] = numStoriesRange.second;
		G::global()["building_min_dimension"] = Util::genRand(minBuildingDimRange.first, minBuildingDimRange.second);

		// generate a city
		QString filename_buildings_image = image_path + QString("/buildings_image_%1.png").arg(iter + 1, 6, 10, QChar('0'));
		generateToolAll(filename_buildings_image, building_footprints_image_size);

		std::cout << "  block_width: " << G::getFloat("blockWidth") << std::endl;
		std::cout << "  block_height: " << G::getFloat("blockHeight") << std::endl;
		std::cout << "  parcel_area_mean: " << G::getFloat("parcel_area_mean") << std::endl;
		std::cout << "  parcel_area_deviation: " << G::getFloat("parcel_area_deviation") << std::endl;
		std::cout << "  parcel_setback_front: " << G::getFloat("parcel_setback_front") << std::endl;
		std::cout << "  parcel_setback_rear: " << G::getFloat("parcel_setback_rear") << std::endl;
		std::cout << "  parcel_setback_sides: " << G::getFloat("parcel_setback_sides") << std::endl;
		std::cout << "  building_stories_min: " << G::getInt("building_stories_min") << std::endl;
		std::cout << "  building_stories_max: " << G::getInt("building_stories_max") << std::endl;
		std::cout << "  building_min_dimension: " << G::getFloat("building_min_dimension") << std::endl;
		std::cout << std::endl;
		//float block_width = (G::getFloat("blockWidth") - blockWidthRange.first) / (blockWidthRange.second - blockWidthRange.first);
		float block_height = G::getFloat("blockHeight");
		float parcel_area_mean = G::getFloat("parcel_area_mean") / 100;
		/*		float parcel_setback_front = (G::getFloat("parcel_setback_front") - setbackFrontRange.first) / (setbackFrontRange.second - setbackFrontRange.first);
		float parcel_setback_rear = (G::getFloat("parcel_setback_rear") - setbackRearRange.first) / (setbackRearRange.second - setbackRearRange.first);
		float parcel_setback_sides = (G::getFloat("parcel_setback_sides") - setbackSideRange.first) / (setbackSideRange.second - setbackSideRange.first);*/
		//float building_min_dimension = 0;

		// save the parameter values
		out_params << iter + 1 << ",";
		out_params << G::getFloat("blockWidth") << ",";
		out_params << block_height << ",";
		out_params << parcel_area_mean << ",";
		out_params << G::getFloat("parcel_area_deviation") << ",";
		out_params << G::getFloat("parcel_setback_front") << ",";
		out_params << G::getFloat("parcel_setback_rear") << ",";
		out_params << G::getFloat("parcel_setback_sides") << ",";
		out_params << G::getFloat("building_stories_min") << ",";
		out_params << G::getFloat("building_stories_max") << ",";
		out_params << G::getFloat("building_min_dimension") << "\n";
		out_params.flush();
		file_params.close();

	}

	std::cout << "Generation has completed." << std::endl;

	return true;
}

float UrbanGeometry::compute_mean_parcel_area(const QString& src_image_filename){
	int thresh = 100;
	int max_thresh = 255;
	cv::RNG rng(12345);
	cv::Mat src;
	cv::Mat src_gray;
	/// Load source image and convert it to gray
	//src = imread("source/pair_4/block_1.png", CV_LOAD_IMAGE_COLOR);
	src = cv::imread(src_image_filename.toUtf8().constData(), CV_LOAD_IMAGE_COLOR);

	cv::Scalar lowerb = cv::Scalar(255, 0, 0);
	cv::Scalar upperb = cv::Scalar(255, 0, 0);
	cv::inRange(src, lowerb, upperb, src_gray);

	cv::Mat threshold_output;
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy;

	/// Detect edges using Threshold
	threshold(src_gray, threshold_output, thresh, 255, cv::THRESH_BINARY);
	/// Find contours
	findContours(threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
	//
	float building_area = 0.0f;
	int building_num = 0;
	/// Draw polygonal contour + bonding rects + circles
	for (int i = 0; i< contours.size(); i++)
	{
		building_area += cv::contourArea(contours.at(i));
		if (cv::contourArea(contours.at(i)) > 100)
			building_num++;
	}
	return (1.2 * building_area) / building_num;
}

float UrbanGeometry::compute_min_dimension_bld(const QString& src_image_filename){
	int thresh = 100;
	int max_thresh = 255;
	cv::RNG rng(12345);
	cv::Mat src;
	cv::Mat src_gray;
	/// Load source image and convert it to gray
	//src = imread("source/pair_4/block_1.png", CV_LOAD_IMAGE_COLOR);
	src = cv::imread(src_image_filename.toUtf8().constData(), CV_LOAD_IMAGE_COLOR);

	cv::Scalar lowerb = cv::Scalar(255, 0, 0);
	cv::Scalar upperb = cv::Scalar(255, 0, 0);
	cv::inRange(src, lowerb, upperb, src_gray);

	cv::Mat threshold_output;
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy;

	/// Detect edges using Threshold
	threshold(src_gray, threshold_output, thresh, 255, cv::THRESH_BINARY);
	/// Find contours
	findContours(threshold_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
	//
	float building_area = 0.0f;
	int building_num = 0;
	/// Draw polygonal contour + bonding rects + circles
	for (int i = 0; i< contours.size(); i++)
	{
		building_area += cv::contourArea(contours.at(i));
		if (cv::contourArea(contours.at(i)) > 100)
			building_num++;
	}
	return 0.8 * sqrt(building_area / building_num);
}

float UrbanGeometry::getBuildingTotalArea(){
	int number_buildings = 0;
	glm::vec2 offset;
	if (G::getDouble("center_long") != 0 && G::getDouble("center_lat") != 0){
		QVector2D result = Util::projLatLonToMeter(G::getDouble("center_long"), G::getDouble("center_lat"));
		offset = glm::vec2(result.x(), result.y());
	}
	else{
		offset = (maxBound + minBound) * 0.5f;
	}
	gs::Shape shape(wkbPolygon);
	for (int i = 0; i < blocks.blocks.size(); ++i) {
		if (blocks[i].isPark) continue;

		for (int j = 0; j < blocks[i].parcels.size(); ++j) {
			if (blocks[i].parcels[j].isPark) continue;
			if (blocks[i].parcels[j].building.buildingFootprint.size() < 3) continue;
			number_buildings++;

			gs::ShapeObject shapeObject;
			shapeObject.parts.resize(1);

			// set height in the attribute field
			shapeObject.attributes["NbreEtages"] = std::to_string(blocks[i].parcels[j].building.numStories);

			// set elevation in the attribute field
			float min_elev = std::numeric_limits<float>::max();
			for (int k = 0; k < blocks[i].parcels[j].building.buildingFootprint.size(); ++k) {
				float z = mainWin->glWidget->vboRenderManager.getTerrainHeight(blocks[i].parcels[j].building.buildingFootprint[k].x(), blocks[i].parcels[j].building.buildingFootprint[k].y());
				min_elev = std::min(min_elev, z);
			}
			shapeObject.attributes["BaseElev"] = std::to_string(min_elev);

			// make a closed clockwise polygon
			Loop3D contour = blocks[i].parcels[j].building.buildingFootprint.contour;
			if (!contour.isClockwise()) {
				std::reverse(contour.begin(), contour.end());

			}
			contour.push_back(contour.front());

			for (int k = 0; k < contour.size(); ++k) {
				float z = mainWin->glWidget->vboRenderManager.getTerrainHeight(contour[k].x(), contour[k].y());
				shapeObject.parts[0].points.push_back(glm::vec3(contour[k].x() + offset.x, contour[k].y() + offset.y, z));
			}

			shape.shapeObjects.push_back(shapeObject);
		}
	}
	std::cout << "building number is " << number_buildings << std::endl;
	std::cout << "building avg area is " << shape.getTotalArea() / number_buildings << std::endl;
	return 	shape.getTotalArea() / number_buildings;
}

void UrbanGeometry::generateToolImageOBB(const float parcel_area, const float image_width, const float image_height, const QString& des_dir){
	if (!QDir(des_dir).exists()) {
		QDir().mkpath(des_dir);
	}
	// set the parameter values
	G::global()["blockWidth"] = image_width;
	G::global()["blockHeight"] = image_height;
	G::global()["parksRatio"] = 0.0f;
	G::global()["parcel_area_mean"] = parcel_area;
	G::global()["parcel_area_deviation"] = 0;
	G::global()["parcel_setback_front"] = Util::genRand(2, 2);
	G::global()["parcel_setback_rear"] = Util::genRand(2, 2);
	G::global()["parcel_setback_sides"] = Util::genRand(2, 2);
	G::global()["building_stories_min"] = 2;
	G::global()["building_stories_max"] = 8;
	G::global()["building_min_dimension"] = Util::genRand(2, 2);
	QString filename(des_dir + "/predict.png");

	clear();

	// 2016/11/10
	// We decided to remove randomness.
	//srand(0);

	// warm up the random numbers
	for (int i = 0; i < 100; ++i) rand();

	//
	int blockWidth = G::getFloat("blockWidth");
	int blockHeight = G::getFloat("blockHeight");
	float x_min = -blockWidth / 2;
	float x_min_third = -blockWidth / 6;
	float x_max = blockWidth / 2;
	float x_max_third = blockWidth / 6;
	float y_min = -blockHeight / 2;
	float y_min_third = -blockHeight / 6;
	float y_max = blockHeight / 2;
	float y_max_third = -blockHeight / 6;
	//std::cout << "x_min is " << x_min << std::endl;
	//std::cout << "y_min is " << y_min << std::endl;

	std::vector<Block> blocks;
	Block block;
	std::vector<Polygon3D> blockContours;
	Polygon3D loop;
	{
		QVector3D p1(x_min, y_min, 0.0f);
		QVector3D p2(x_min_third, y_min, 0.0f);
		QVector3D p3(x_max_third, y_min, 0.0f);
		QVector3D p4(x_max, y_min, 0.0f);

		QVector3D p5(x_max, y_min_third, 0.0f);
		QVector3D p6(x_max, y_max_third, 0.0f);

		QVector3D p7(x_max, y_max, 0.0f);
		QVector3D p8(x_max_third, y_max, 0.0f);
		QVector3D p9(x_min_third, y_max, 0.0f);
		QVector3D p10(x_min, y_max, 0.0f);

		QVector3D p11(x_min, y_max_third, 0.0f);
		QVector3D p12(x_min, y_min_third, 0.0f);

		loop.push_back(p1);
		loop.push_back(p2);
		loop.push_back(p3);
		loop.push_back(p4);
		loop.push_back(p5);
		loop.push_back(p6);
		loop.push_back(p7);
		loop.push_back(p8);
		loop.push_back(p9);
		loop.push_back(p10);
		loop.push_back(p11);
		loop.push_back(p12);
	}
	{
		blockContours.push_back(loop);
		block.blockContours = blockContours;
		block.isPark = false;
		blocks.push_back(block);
	}

	PmParcels::generateParcels(mainWin->glWidget->vboRenderManager, blocks);
	PmBuildings::generateBuildings(mainWin->glWidget->vboRenderManager, blocks);
	std::vector<cv::Point> points;

	//save to an image
	{
		cv::Mat img(blockHeight, blockWidth, CV_8UC3, cv::Scalar(0, 255, 0));
		//std::cout << "height is " << img.size().height << std::endl;
		float offset_x = blockWidth * 0.5;
		float offset_y = blockHeight * 0.5;
		// draw parcels
		for (int bn = 0; bn < blocks.size(); bn++){
			for (int i = 0; i < blocks[bn].parcels.size(); i++){
				if (blocks[bn].parcels.at(i).isPark)
					continue;

				for (int j = 0; j < blocks[bn].parcels.at(i).building.buildingFootprint.size(); j++) {
					//std::cout << block.parcels.at(i).building.buildingFootprint.size() << std::endl;
					int next = (j + 1) % blocks[bn].parcels.at(i).building.buildingFootprint.size();
					int x1 = blocks[bn].parcels.at(i).building.buildingFootprint[j].x();
					int y1 = blocks[bn].parcels.at(i).building.buildingFootprint[j].y();
					int x2 = blocks[bn].parcels.at(i).building.buildingFootprint[next].x();
					int y2 = blocks[bn].parcels.at(i).building.buildingFootprint[next].y();
					//cv::line(img, cv::Point((x1 + offset_x) * scale_x, (y1 + offset_y) * scale_y), cv::Point((x2 + offset_x) * scale_x, (y2 + offset_y) * scale_y), cv::Scalar(255, 0, 0), 1);
					points.push_back(cv::Point((x1 + offset_x), img.rows - (y1 + offset_y)));
				}
				cv::fillConvexPoly(img,               //Image to be drawn on
					points,                 //C-Style array of points
					cv::Scalar(255, 0, 0),  //Color , BGR form
					8,             // connectedness, 4 or 8
					0);
				points.clear();
			}

		}
		cv::imwrite(filename.toUtf8().constData(), img);
	}
}

/**
 * Update all the geometry
 *
 * This function may take time, so don't call this function so often.
 * It is recommnded to call this function only when the geometry is changed, added, or the 2d/3d mode is changed.
 */
void UrbanGeometry::update(VBORenderManager& vboRenderManager) {
	// Remove all the geometry
	vboRenderManager.removeStaticGeometry("3d_blocks");
	vboRenderManager.removeStaticGeometry("3d_parks");
	vboRenderManager.removeStaticGeometry("3d_parcels");
	vboRenderManager.removeStaticGeometry("3d_roads");
	vboRenderManager.removeStaticGeometry("3d_building");
	vboRenderManager.removeStaticGeometry("tree");
	vboRenderManager.removeStaticGeometry("streetLamp");

	if (G::getBool("shader2D")) {
		RoadMeshGenerator::generate2DRoadMesh(vboRenderManager, roads);
		BlockMeshGenerator::generate2DParcelMesh(vboRenderManager, blocks);
	}
	else {
		RoadMeshGenerator::generateRoadMesh(vboRenderManager, roads);
		BlockMeshGenerator::generateBlockMesh(vboRenderManager, blocks);
		BlockMeshGenerator::generateParcelMesh(vboRenderManager, blocks);
		Pm::generateBuildings(mainWin->glWidget->vboRenderManager, blocks);
		//PmVegetation::generateVegetation(mainWin->glWidget->vboRenderManager, blocks.blocks);
	}
}

void UrbanGeometry::loadZone(const std::string& filename) {
	zone.clear();

	gs::Shape shape;
	shape.load(filename);

	glm::vec2 offset = (glm::vec2(shape.maxBound) + glm::vec2(shape.minBound)) * 0.5f;
	minBound = glm::vec2(shape.minBound);
	maxBound = glm::vec2(shape.maxBound);
	std::cout << "minBound (" << minBound.x << ", " << minBound.y << ")" << std::endl;
	std::cout << "maxBound (" << maxBound.x << ", " << maxBound.y << ")" << std::endl;
	//std::cout << shape.shapeObjects.size() << std::endl;
	for (int i = 0; i < shape.shapeObjects.size(); ++i) {
		//std::cout << shape.shapeObjects.size() << std::endl;
		//for (int j = 0; j < shape.shapeObjects[i].parts.size(); ++j) {
		for (int k = shape.shapeObjects[i].parts[0].points.size() - 1; k >= 1; --k) {
			QVector2D pt;
			pt.setX(shape.shapeObjects[i].parts[0].points[k].x - offset.x);
			pt.setY(shape.shapeObjects[i].parts[0].points[k].y - offset.y);
			//std::cout << "pt " << k << " (" << shape.shapeObjects[i].parts[0].points[k].x - offset.x << ", ";
			//std::cout << shape.shapeObjects[i].parts[0].points[k].y - offset.y << ")" << std::endl;
			zone.push_back(pt);
		}
	}
	//manully
	//{
	//	QVector2D pt1;
	//	pt1.setX(-800);
	//	pt1.setY(800);
	//	QVector2D pt2;
	//	pt2.setX(800);
	//	pt2.setY(800);
	//	QVector2D pt3;
	//	pt3.setX(800);
	//	pt3.setY(-800);
	//	QVector2D pt4;
	//	pt4.setX(-800);
	//	pt4.setY(-800);
	//	zone.push_back(pt1);
	//	zone.push_back(pt4);
	//	zone.push_back(pt3);
	//	zone.push_back(pt2);
	//}
}

void UrbanGeometry::loadTerrain(const std::string& filename) {
	gs::DEM dem;
	dem.load(filename);

	mainWin->glWidget->vboRenderManager.changeTerrainDimensions(glm::vec2(dem.width, dem.height));
	if (zone.size() == 0) {
		glm::vec2 offset = dem.origin + glm::vec2(dem.width, dem.height) * 0.5f;
		minBound = dem.origin;
		maxBound = dem.origin + glm::vec2(dem.width, dem.height);

		zone.push_back(QVector2D(minBound.x - offset.x, minBound.y - offset.y));
		zone.push_back(QVector2D(maxBound.x - offset.x, minBound.y - offset.y));
		zone.push_back(QVector2D(maxBound.x - offset.x, maxBound.y - offset.y));
		zone.push_back(QVector2D(minBound.x - offset.x, maxBound.y - offset.y));
	}

	cv::Mat layerData = cv::Mat(dem.height, dem.width, CV_32FC1, dem.data.data()).clone();
	cv::flip(layerData, layerData, 0);

	// update texture
	mainWin->glWidget->vboRenderManager.vboTerrain.setTerrain(layerData);
}

void UrbanGeometry::loadRoads(const std::string& filename) {
	roads.clear();

	gs::Shape shape;
	shape.load(filename);

	if (zone.size() == 0) {
		glm::vec2 offset = (glm::vec2(shape.maxBound) + glm::vec2(shape.minBound)) * 0.5f;
		minBound = glm::vec2(shape.minBound);
		maxBound = glm::vec2(shape.maxBound);

		zone.push_back(QVector2D(minBound.x - offset.x, minBound.y - offset.y));
		zone.push_back(QVector2D(maxBound.x - offset.x, minBound.y - offset.y));
		zone.push_back(QVector2D(maxBound.x - offset.x, maxBound.y - offset.y));
		zone.push_back(QVector2D(minBound.x - offset.x, maxBound.y - offset.y));
	}

	glm::vec2 offset = (maxBound + minBound) * 0.5f;

	for (int i = 0; i < shape.shapeObjects.size(); ++i) {
		for (int j = 0; j < shape.shapeObjects[i].parts.size(); ++j) {
			QVector2D pt1;
			RoadVertexDesc desc1;
			pt1.setX(shape.shapeObjects[i].parts[j].points.front().x - offset.x);
			pt1.setY(shape.shapeObjects[i].parts[j].points.front().y - offset.y);

			if (!GraphUtil::getVertex(roads, pt1, 0.1f, desc1)) {
				RoadVertexPtr v(new RoadVertex(pt1));
				desc1 = GraphUtil::addVertex(roads, v);
			}

			QVector2D pt2;
			RoadVertexDesc desc2;
			pt2.setX(shape.shapeObjects[i].parts[j].points.back().x - offset.x);
			pt2.setY(shape.shapeObjects[i].parts[j].points.back().y - offset.y);

			if (!GraphUtil::getVertex(roads, pt2, 0.1f, desc2)) {
				RoadVertexPtr v(new RoadVertex(pt2));
				desc2 = GraphUtil::addVertex(roads, v);
			}

			RoadEdgePtr edge(new RoadEdge(RoadEdge::TYPE_STREET, 1, false, false, false));
			for (int k = 0; k < shape.shapeObjects[i].parts[j].points.size(); ++k) {
				QVector2D pt;
				pt.setX(shape.shapeObjects[i].parts[j].points[k].x - offset.x);
				pt.setY(shape.shapeObjects[i].parts[j].points[k].y - offset.y);
				edge->addPoint(pt);
			}

			if (GraphUtil::hasEdge(roads, desc1, desc2)) {
				// duplicate edge, so ignore this edge
			}
			else {
				GraphUtil::addEdge(roads, desc1, desc2, edge);
			}

			// we use only the first part
			break;
		}
	}

	update(mainWin->glWidget->vboRenderManager);
}

void UrbanGeometry::loadOSMRoads(const QString& filename) {
	OSMRoadsParser parser(&roads);

	// read OSM file
	QXmlSimpleReader reader;
	reader.setContentHandler(&parser);
	QFile file(filename);
	QXmlInputSource source(&file);
	reader.parse(source);

	// make the vertex with degree of 2 just a point on an edge
	GraphUtil::reduce(roads);
	//GraphUtil::clean(roads);
	//GraphUtil::planarify(roads);
	//GraphUtil::clean(roads);
	{
		GraphUtil::normalizeLoop(roads);

		RoadGraph * roadGraphPtr = &roads;
		BBox bbox = GraphUtil::getAABoundingBox(*roadGraphPtr, true);
		std::cout << bbox.dy() << std::endl;
		std::cout << bbox.dx() << std::endl;
		std::cout << bbox.minPt.x() << std::endl;
		std::cout << bbox.minPt.y() << std::endl;
		std::cout << bbox.maxPt.x() << std::endl;
		std::cout << bbox.maxPt.y() << std::endl;
	}
	update(mainWin->glWidget->vboRenderManager);
}

void UrbanGeometry::saveRoads(const std::string &filename) {
	std::cout << "minBound is " << minBound.x << ", " << minBound.y << std::endl;
	std::cout << "maxBound is " << maxBound.x << ", " << maxBound.y << std::endl;
	glm::vec2 offset;
	if (G::getDouble("center_long") != 0 && G::getDouble("center_lat") != 0){
		QVector2D result = Util::projLatLonToMeter(G::getDouble("center_long"), G::getDouble("center_lat"));
		offset = glm::vec2(result.x(), result.y());
	}
	else{
		offset = (maxBound + minBound) * 0.5f;
	}

	gs::Shape shape(wkbLineString);
	RoadEdgeIter ei, eend;
	for (boost::tie(ei, eend) = boost::edges(roads.graph); ei != eend; ++ei) {
		if (!roads.graph[*ei]->valid) continue;

		gs::ShapeObject shapeObject;
		shapeObject.parts.resize(1);
		for (int k = 0; k < roads.graph[*ei]->polyline.size(); ++k) {
			const QVector2D& pt = roads.graph[*ei]->polyline[k];
			float z = mainWin->glWidget->vboRenderManager.getTerrainHeight(pt.x(), pt.y());
			shapeObject.parts[0].points.push_back(glm::vec3(pt.x() + offset.x, pt.y() + offset.y, z));
		}

		shape.shapeObjects.push_back(shapeObject);
	}

	shape.save(filename);
}

void  UrbanGeometry::getCoordsForSvf(std::vector<std::vector<glm::vec3>>& points_set){
	RoadEdgeIter ei, eend;
	for (boost::tie(ei, eend) = boost::edges(roads.graph); ei != eend; ++ei) {
		if (!roads.graph[*ei]->valid) continue;
		std::vector<glm::vec3> points;
		for (int k = 0; k < roads.graph[*ei]->polyline.size(); ++k) {
			const QVector2D& pt = roads.graph[*ei]->polyline[k];
			float z = mainWin->glWidget->vboRenderManager.getTerrainHeight(pt.x(), pt.y());
			points.push_back(glm::vec3(pt.x(), pt.y(), z));
		}
		points_set.push_back(points);
	}
}

void UrbanGeometry::loadParcels(const std::string& filename) {
	blocks.clear();

	gs::Shape shape;
	shape.load(filename);
	if (zone.size() == 0) {
		glm::vec2 offset = (glm::vec2(shape.maxBound) + glm::vec2(shape.minBound)) * 0.5f;
		minBound = glm::vec2(shape.minBound);
		maxBound = glm::vec2(shape.maxBound);

		zone.push_back(QVector2D(minBound.x - offset.x, minBound.y - offset.y));
		zone.push_back(QVector2D(maxBound.x - offset.x, minBound.y - offset.y));
		zone.push_back(QVector2D(maxBound.x - offset.x, maxBound.y - offset.y));
		zone.push_back(QVector2D(minBound.x - offset.x, maxBound.y - offset.y));
	}

	glm::vec2 offset = (maxBound + minBound) * 0.5f;

	for (int i = 0; i < shape.shapeObjects.size(); ++i) {
		for (int j = 0; j < shape.shapeObjects[i].parts.size(); ++j) {
			Block block;
			block.blockContours.resize(1);
			for (int k = shape.shapeObjects[i].parts[j].points.size() - 1; k >= 1; --k) {
				QVector3D pt;
				pt.setX(shape.shapeObjects[i].parts[j].points[k].x - offset.x);
				pt.setY(shape.shapeObjects[i].parts[j].points[k].y - offset.y);
				pt.setZ(shape.shapeObjects[i].parts[j].points[k].z);
				block.blockContours[0].push_back(pt);
			}
			
			Parcel parcel;
			parcel.parcelContour = block.blockContours[0];
			block.parcels.push_back(parcel);

			blocks.blocks.push_back(block);

			// we use only the first part
			break;
		}
	}

	update(mainWin->glWidget->vboRenderManager);
}

void UrbanGeometry::saveParcels(const std::string& filename) {
	glm::vec2 offset;
	if (G::getDouble("center_long") != 0 && G::getDouble("center_lat") != 0){
		QVector2D result = Util::projLatLonToMeter(G::getDouble("center_long"), G::getDouble("center_lat"));
		offset = glm::vec2(result.x(), result.y());
	}
	else{
		offset = (maxBound + minBound) * 0.5f;
	}
	gs::Shape shape(wkbPolygon);
	for (int i = 0; i < blocks.blocks.size(); ++i) {
		for (int pN = 0; pN < blocks.blocks[i].parcels.size(); ++pN) {
			// make a closed clockwise polygon
			Loop3D contour = blocks[i].parcels[pN].parcelContour.contour;
			if (contour.size() < 3) continue;
			if (!contour.isClockwise()) {
				std::reverse(contour.begin(), contour.end());

			}
			contour.push_back(contour.front());

			gs::ShapeObject shapeObject;
			shapeObject.parts.resize(1);
			for (int k = 0; k < contour.size(); ++k) {
				float z = mainWin->glWidget->vboRenderManager.getTerrainHeight(contour[k].x(), contour[k].y());
				shapeObject.parts[0].points.push_back(glm::vec3(contour[k].x() + offset.x, contour[k].y() + offset.y, z));
			}

			shape.shapeObjects.push_back(shapeObject);
		}
	}

	shape.save(filename);
}

void UrbanGeometry::loadBuildings(const std::string& filename) {
	std::vector<Building> buildings;

	gs::Shape shape;
	shape.load(filename);
	if (zone.size() == 0) {
		glm::vec2 offset = (glm::vec2(shape.maxBound) + glm::vec2(shape.minBound)) * 0.5f;
		minBound = glm::vec2(shape.minBound);
		maxBound = glm::vec2(shape.maxBound);

		zone.push_back(QVector2D(minBound.x - offset.x, minBound.y - offset.y));
		zone.push_back(QVector2D(maxBound.x - offset.x, minBound.y - offset.y));
		zone.push_back(QVector2D(maxBound.x - offset.x, maxBound.y - offset.y));
		zone.push_back(QVector2D(minBound.x - offset.x, maxBound.y - offset.y));
	}

	glm::vec2 offset = (maxBound + minBound) * 0.5f;

	for (int i = 0; i < shape.shapeObjects.size(); ++i) {
		for (int j = 0; j < shape.shapeObjects[i].parts.size(); ++j) {
			Building building;

			if (shape.shapeObjects[i].attributes.find("NbreEtages") != shape.shapeObjects[i].attributes.end()) {
				building.numStories = shape.shapeObjects[i].attributes["NbreEtages"].intValue();
			}
			if (building.numStories <= 0) {
				building.numStories = 2;
			}

			building.color = QColor(rand() % 256, rand() % 256, 255);

			// For now, only one type of building is implemented.
			if (building.numStories == 1) {	// Low building with flat roof
				building.bldType = 1;
			}
			else if (building.numStories > 6) {	// High tower with flat roof
				building.bldType = 1;
			}
			else {	// residential house with gable roof
				building.bldType = 1;
			}

			for (int k = shape.shapeObjects[i].parts[j].points.size() - 1; k >= 1; --k) {
				QVector3D pt;
				pt.setX(shape.shapeObjects[i].parts[j].points[k].x - offset.x);
				pt.setY(shape.shapeObjects[i].parts[j].points[k].y - offset.y);
				pt.setZ(shape.shapeObjects[i].parts[j].points[k].z);

				building.buildingFootprint.push_back(pt);
			}
			
			buildings.push_back(building);
			
			// we use only the first part
			break;
		}
	}

	// remove the building that is within the other buildings
	for (int i = 0; i < buildings.size(); ) {
		bool inside = false;
		for (int k = 0; k < buildings[i].buildingFootprint.size() && !inside; ++k) {
			for (int j = 0; j < buildings.size(); ++j) {
				if (i == j) continue;

				if (buildings[j].buildingFootprint.contains(buildings[i].buildingFootprint[k])) {
					inside = true;
					break;
				}
			}
		}

		if (inside) {
			buildings.erase(buildings.begin() + i);
		}
		else {
			i++;
		}
	}

	// find a parcel that contains this building
	for (int i = 0; i < buildings.size(); ++i) {
		std::vector<Loop3D> offsetFootprints;
		buildings[i].buildingFootprint.offsetInside(0.01, offsetFootprints);

		Loop3D offsetFootprint;
		bool parcelFound = false;
		if (offsetFootprints.size() > 0) {
			for (int k = 0; k < offsetFootprints[0].size(); ++k) {
				int next = (k + 1) % offsetFootprints[0].size();
				offsetFootprint.push_back(offsetFootprints[0][k]);
				offsetFootprint.push_back((offsetFootprints[0][k] + offsetFootprints[0][next]) * 0.5);
			}

			for (int bN = 0; bN < blocks.size() && !parcelFound; ++bN) {
				if (blocks[bN].isPark) continue;

				for (int pN = 0; pN < blocks[bN].parcels.size() && !parcelFound; ++pN) {
					if (blocks[bN].parcels[pN].isPark) continue;

					for (int k = 0; k < offsetFootprint.size(); ++k) {
						if (blocks[bN].parcels[pN].parcelContour.contains(offsetFootprint[k])) {
							blocks[bN].parcels[pN].building = buildings[i];
							parcelFound = true;
							break;
						}
					}
				}
			}
		}
	}

	update(mainWin->glWidget->vboRenderManager);
}

void UrbanGeometry::saveBuildings(const std::string& filename) {
	glm::vec2 offset;
	if (G::getDouble("center_long") != 0 && G::getDouble("center_lat") != 0){
		QVector2D result = Util::projLatLonToMeter(G::getDouble("center_long"), G::getDouble("center_lat"));
		offset = glm::vec2(result.x(), result.y());
	}
	else{
		offset = (maxBound + minBound) * 0.5f;
	}
	gs::Shape shape(wkbPolygon);
	for (int i = 0; i < blocks.blocks.size(); ++i) {
		if (blocks[i].isPark) continue;

		for (int j = 0; j < blocks[i].parcels.size(); ++j) {
			if (blocks[i].parcels[j].isPark) continue;
			if (blocks[i].parcels[j].building.buildingFootprint.size() < 3) continue;

			gs::ShapeObject shapeObject;
			shapeObject.parts.resize(1);

			// set height in the attribute field
			shapeObject.attributes["Net_Height"] = std::to_string(blocks[i].parcels[j].building.numStories * 3);

			// set elevation in the attribute field
			float min_elev = std::numeric_limits<float>::max();
			for (int k = 0; k < blocks[i].parcels[j].building.buildingFootprint.size(); ++k) {
				float z = mainWin->glWidget->vboRenderManager.getTerrainHeight(blocks[i].parcels[j].building.buildingFootprint[k].x(), blocks[i].parcels[j].building.buildingFootprint[k].y());
				min_elev = std::min(min_elev, z);
			}
			shapeObject.attributes["BaseElev"] = std::to_string(min_elev);
			
			// make a closed clockwise polygon
			Loop3D contour = blocks[i].parcels[j].building.buildingFootprint.contour;
			if (!contour.isClockwise()) {
				std::reverse(contour.begin(), contour.end());

			}
			contour.push_back(contour.front());

			for (int k = 0; k < contour.size(); ++k) {
				float z = mainWin->glWidget->vboRenderManager.getTerrainHeight(contour[k].x(), contour[k].y());
				shapeObject.parts[0].points.push_back(glm::vec3(contour[k].x() + offset.x, contour[k].y() + offset.y, z));
			}

			shape.shapeObjects.push_back(shapeObject);
		}
	}

	shape.save(filename);
}

void UrbanGeometry::getCoordsForHeight(std::vector<float>& blds_height, std::vector<std::vector<glm::vec3>>& blds_contour){
	for (int i = 0; i < blocks.blocks.size(); ++i) {
		if (blocks[i].isPark) continue;

		for (int j = 0; j < blocks[i].parcels.size(); ++j) {
			if (blocks[i].parcels[j].isPark) continue;
			if (blocks[i].parcels[j].building.buildingFootprint.size() < 3) continue;

			// set height in the attribute field
			blds_height.push_back(blocks[i].parcels[j].building.numStories * 3);

			// make a closed clockwise polygon
			Loop3D contour = blocks[i].parcels[j].building.buildingFootprint.contour;
			if (!contour.isClockwise()) {
				std::reverse(contour.begin(), contour.end());

			}
			contour.push_back(contour.front());

			std::vector<glm::vec3> contour_tmp;
			for (int k = 0; k < contour.size(); ++k) {
				float z = mainWin->glWidget->vboRenderManager.getTerrainHeight(contour[k].x(), contour[k].y());
				contour_tmp.push_back(glm::vec3(contour[k].x(), contour[k].y(), z));
			}

			blds_contour.push_back(contour_tmp);
		}
	}
}

void UrbanGeometry::clear() {
	roads.clear();
	blocks.clear();
	update(mainWin->glWidget->vboRenderManager);
}


