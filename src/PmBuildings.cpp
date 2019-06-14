#include "PmBuildings.h"
#include "global.h"
#include "Util.h"
#include <QFileDialog>
#include "gdal_priv.h"

bool PmBuildings::generateBuildings(VBORenderManager& rendManager, std::vector<Block>& blocks) {

	for (int i = 0; i < blocks.size(); ++i) {
		for (int j = 0; j < blocks[i].parcels.size(); ++j) {
			if (!generateBuilding(rendManager, blocks[i], blocks[i].parcels[j])) {
				blocks[i].parcels[j].isPark = true;
			}
		}
		{
			//saveBldsImage(blocks[i], i);
		}
	}

	return true;
}

/**
 * Generate a building in a parcel.
 * If the parcel is too small, return false.
 *
 * @param rendManager	render manager
 * @param block			block
 * @param parcel		parcel
 * @return				true if the building is generated, false otherwise
 */
bool PmBuildings::generateBuilding(VBORenderManager& rendManager, Block& block, Parcel& parcel) {
	Loop3D pContourCpy;
	
	if (parcel.isPark) return false;

	// Compute parcel frontage
	std::vector<int> frontEdges;
	std::vector<int> rearEdges;
	std::vector<int> sideEdges;

	// simplify the contour in order to obtain a simple building footprint
	Polygon3D contour = parcel.parcelContour;
	contour.simplify(0.5);

	block.findParcelFrontAndBackEdges(contour, frontEdges, rearEdges, sideEdges);
	//{
	//	std::cout <<"frontEdges " << frontEdges.size() << std::endl;
	//	std::cout <<"rearEdges " <<rearEdges.size() << std::endl;
	//	std::cout <<"sideEdges "<<sideEdges.size() << std::endl;
	//}
	// Compute building footprint
	Loop3D footprint;
	Parcel::computeBuildingFootprint(contour, G::getFloat("parcel_setback_front"), G::getFloat("parcel_setback_rear"), G::getFloat("parcel_setback_sides"), frontEdges, rearEdges, sideEdges, footprint);
	if (footprint.size() == 0) return false;
	if (footprint.isSelfIntersecting()) {
		return false;
	}

	parcel.building.buildingFootprint.contour = footprint;

	// Cancel the building if the dimension is too small
	QVector3D obbSize;
	QMatrix4x4 obbMat;
	parcel.building.buildingFootprint.getMyOBB(obbSize, obbMat);
	if (obbSize.x() < G::getFloat("building_min_dimension") || obbSize.y() < G::getFloat("building_min_dimension")) return false;

	// set the elevation
	for (int i = 0; i < parcel.building.buildingFootprint.size(); ++i) {
		parcel.building.buildingFootprint[i].setZ(0.0f);
	}

	// Set building attributes
	// compute the height of building by xwzhang
	parcel.building.numStories = Util::genRand(G::getInt("building_stories_min"), G::getInt("building_stories_max") + 1);
	float c = rand() % 192;
	parcel.building.color = QColor(c, c, c);
	parcel.building.bldType = 1;

	return true;
}

void PmBuildings::saveBldsImage(Block& block, int index){
	// find the corrsponded the image
	if (!QFile(QString("output/block_" + QString::number(index) + ".png")).exists()) {
		std::cout << "segmented block doesn't exist...";
		std::cout << " done." << std::endl;
		return;
	}

	Polygon3D contour = block.blockContours.at(0);
	std::vector<cv::Point2f>contour_cv;
	for (int i = 0; i < block.blockContours[0].size(); i++){
		contour_cv.push_back(cv::Point2f(contour.contour[i].x(), contour.contour[i].y()));
		//std::cout << "point ( " << contour.contour[i].x() << "," << contour.contour[i].y() << ")" << std::endl;
	}
	cv::Rect2f boundRect = cv::boundingRect(cv::Mat(contour_cv));
	float block_width = boundRect.width;
	float block_height = boundRect.height;
	//std::cout << "block_width " << block_width << std::endl;
	//std::cout << "block_height " << block_height << std::endl;
	//std::cout << "block x " << boundRect.x << std::endl;
	//std::cout << "block y " << boundRect.y << std::endl;

	cv::Mat img(cv::Size(block_width, block_height), CV_8UC3, cv::Scalar(0, 255, 0));
	// draw block
	//for (int i = 0; i < contour.size(); ++i) {
	//	int next = (i + 1) % contour.size();
	//	int x1 = contour.contour[i].x() - boundRect.x;
	//	int y1 = contour.contour[i].y() - boundRect.y;
	//	int x2 = contour.contour[next].x() - boundRect.x;
	//	int y2 = contour.contour[next].y() - boundRect.y;
	//	cv::line(img, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 0, 0), 1);
	//}
	// draw parcels
	//std::vector<Parcel> parcels = block.parcels;
	//std::vector<std::vector<cv::Point>> multi_points;
	//std::vector<cv::Point> tmp;
	//for (int i = 0; i < parcels.size(); i++){
	//	//std::cout << parcels.at(i).parcelContour.size() << std::endl;
	//	for (int j = 0; j < parcels.at(i).parcelContour.size(); j++) {
	//		if (parcels.at(i).isPark)
	//			continue;
	//		//int next = (j + 1) % parcels.at(i).parcelContour.size();
	//		int x1 = parcels.at(i).parcelContour[j].x() - boundRect.x;
	//		int y1 = parcels.at(i).parcelContour[j].y() - boundRect.y;
	//		//int x2 = parcels.at(i).parcelContour[next].x() - boundRect.x;
	//		//int y2 = parcels.at(i).parcelContour[next].y() - boundRect.y;
	//		//cv::line(img, cv::Point(x1, img.rows - y1), cv::Point(x2, img.rows - y2), cv::Scalar(0, 0, 0), 1);
	//		tmp.push_back(cv::Point(x1, img.rows - y1));
	//	}
	//	multi_points.push_back(tmp);
	//	tmp.clear();
	//}
	//cv::polylines(img, multi_points,true, cv::Scalar(0, 0, 0), 3, 8, 0);
	// draw buildings
	//for (int i = 0; i < block.parcels.size(); i++){
	//	for (int j = 0; j < block.parcels.at(i).building.buildingFootprint.size(); j++) {
	//		if (block.parcels.at(i).isPark)
	//			continue;
	//		//std::cout << block.parcels.at(i).building.buildingFootprint.size() << std::endl;
	//		int next = (j + 1) % block.parcels.at(i).building.buildingFootprint.size();
	//		int x1 = block.parcels.at(i).building.buildingFootprint[j].x() - boundRect.x;
	//		int y1 = block.parcels.at(i).building.buildingFootprint[j].y() - boundRect.y;
	//		int x2 = block.parcels.at(i).building.buildingFootprint[next].x() - boundRect.x;
	//		int y2 = block.parcels.at(i).building.buildingFootprint[next].y() - boundRect.y;
	//		cv::line(img, cv::Point(x1, img.rows - y1), cv::Point(x2, img.rows - y2), cv::Scalar(255, 0, 0), 1);
	//	}
	//}
	std::vector<cv::Point> points;
	for (int i = 0; i < block.parcels.size(); i++){
		if (block.parcels.at(i).isPark)
			continue;
		for (int j = 0; j < block.parcels.at(i).building.buildingFootprint.size(); j++) {
			int x1 = block.parcels.at(i).building.buildingFootprint[j].x() - boundRect.x;
			int y1 = block.parcels.at(i).building.buildingFootprint[j].y() - boundRect.y;
			points.push_back(cv::Point(x1, img.rows - y1));
			//std::cout << "points ( " << x1 << ", " << y1 << ")"<< std::endl;
		}
		cv::fillConvexPoly(img,               //Image to be drawn on
			points,                 //C-Style array of points
			cv::Scalar(255, 0, 0),  //Color , BGR form
			8,             // connectedness, 4 or 8
			0);
		points.clear();
	}
	cv::imwrite(QString("output/pre_" + QString::number(index) + ".png").toUtf8().data(), img);
	// find the corrsponded the image
	if (false){
		QString filename_out("output/label_" + QString::number(index) + ".png");
		cv::Mat seg_out = cv::imread(QString("output/label_" + QString::number(index) + ".png").toUtf8().data(), CV_LOAD_IMAGE_COLOR);
		cv::imwrite(filename_out.toUtf8().data(), seg_out);
		// find the corrsponded the image
		QString gt_filename_out("output/gt_" + QString::number(index) + ".png");
		cv::Mat gt_out = cv::imread(QString("output/gt_" + QString::number(index) + ".png").toUtf8().data(), CV_LOAD_IMAGE_COLOR);
		cv::imwrite(gt_filename_out.toUtf8().data(), gt_out);
	}
}

void PmBuildings::findCorrespondedBlock(const Block & block, QString filename, int index){
	Polygon3D contour = block.blockContours.at(0);
	std::vector<cv::Point2f>contour_cv;
	for (int i = 0; i < block.blockContours[0].size(); i++){
		float x = contour.contour[i].x();
		float y = contour.contour[i].y();
		QVector2D point_tmp = Util::getXYCoordSeg(x, y);
		contour_cv.push_back(cv::Point2f(point_tmp.x(), point_tmp.y()));
	}
	cv::Rect2f boundRect = cv::boundingRect(cv::Mat(contour_cv));
	cv::Mat src = cv::imread(filename.toUtf8().data(), CV_LOAD_IMAGE_COLOR);
	cv::Mat crop = src(boundRect);
	QString filename_out("output/gt_" + QString::number(index) + ".png");
	cv::imwrite(filename_out.toUtf8().data(), crop);
}