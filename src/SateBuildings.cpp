#include "SateBuildings.h"
#include "global.h"
#include "Util.h"
#include <QFileDialog>
#include "gdal_priv.h"

bool SateBuildings::generateBuildings(VBORenderManager& rendManager, std::vector<Block>& blocks, float correction) {
	std::cout << "correction " << correction << std::endl;
	bool bHeight_Info = false;
	bool bBuilding_Type = false;
	if (G::getString("height_tif") != NULL &&QFile(G::getString("height_tif")).exists()) {
		std::cout << " height info file exists." << std::endl;
		bHeight_Info = true;
	}
	if (G::getString("building_type_tif") != NULL && QFile(G::getString("building_type_tif")).exists()) {
		std::cout << " building type file exists." << std::endl;
		bBuilding_Type = true;
	}
	std::vector<std::vector<int>> height_info;
	std::vector<double> result;
	if (bHeight_Info){
		height_info = get_height_info(G::getString("height_tif"));
		result = Util::getGeoInfo(G::getString("height_tif").toUtf8().data());
	}

	std::vector<std::vector<int>> building_type_info;
	std::vector<double> result_blds;
	if (bBuilding_Type){
		building_type_info = get_blds_type_info(G::getString("building_type_tif"));
		result_blds = Util::getGeoInfo(G::getString("building_type_tif").toUtf8().data());
	}

	int stories = 0;
	int avg_height = 0;
	int building_type = 1;
	cv::Point center;
	QVector2D center_geo;
	cv::Rect bb_tmp;
	srand(0);
	for (int i = 0; i < blocks.size(); ++i) {
		//
		{
			for (int j = 0; j < blocks[i].parcels.size();)
				if (blocks[i].parcels[j].isPark){
					blocks[i].parcels.erase(blocks[i].parcels.begin() + j);
				}
				else
					j++;
		}
		for (int j = 0; j < blocks[i].parcels.size(); ++j) {
			// warm up the random numbers
			// set random seed
			/*srand((unsigned)time(NULL) + i * j);
			for (int i = 0; i < 100; ++i) rand();*/
			// compute the height for that parcel
			if (bHeight_Info || bBuilding_Type)
			{
				std::vector<cv::Point> contour_tmp;
				avg_height = 0;
				Polygon3D contour = blocks[i].parcels[j].parcelContour;
				contour.simplify(0.5);
				if (contour.size() == 0){
					blocks[i].parcels[j].isPark = true;
					continue;
				}
				for (int l = 0; l < contour.size(); l++){
					float x = contour.contour[l].x();
					float y = contour.contour[l].y();
					contour_tmp.push_back(cv::Point(x, y));
				}
				bb_tmp = cv::boundingRect(cv::Mat(contour_tmp));
				center.x = bb_tmp.x + 0.5 * bb_tmp.width;
				center.y = bb_tmp.y + 0.5 * bb_tmp.height;
				// find the long/lat coord for the center of the parcel
				center_geo = Util::getLongLatCoord(center.x, center.y);
			}
			if (bHeight_Info){
				QVector2D center_xy = Util::getXYCoord(center_geo.x(), center_geo.y(), result);
				int height_y = center_xy.y();
				int width_x = center_xy.x();
				//std::cout << "height center_xy is " << center_xy.x() << ", " << center_xy.y() <<std::endl;
				if (center_xy.y() >= height_info.size())
				{
					height_y = height_info.size() - 1;
				}
				if (center_xy.x() >= height_info.at(0).size())
				{
					width_x = height_info.at(0).size() - 1;
				}

				avg_height = height_info.at(height_y).at(width_x);
				//if (avg_height >= 500){
				//	stories = 10;
				//}
				//else
				stories = avg_height / 3 + 1;
				//stories = Util::genRand(5, 50);
				//if (stories > 10)
				//	stories -= 2;
				//std::cout << "center_geo is " << center_geo.x() << ", " << center_geo.y() << std::endl;
				//std::cout << "height center_xy is " << center_xy.x() << ", " << center_xy.y() <<std::endl;
				//std::cout << "stories " << stories << std::endl;
				/*if (stories <= 5)
					stories = 5;*/
				//if (stories <= 40 && stories >= 20)
				//	stories = stories - 15;
				//std::cout << "stories " << stories << std::endl;
			}
			else{
				stories = Util::genRand(5, 8 + 1);
			}
			if (bBuilding_Type){
				// set up setbacks
				float sd_setback_front = 0;
				float sd_setback_side = 0;
				float parcel_front_side = (bb_tmp.width > bb_tmp.height) ? bb_tmp.height : bb_tmp.width;
				float parcel_side_side = (bb_tmp.width > bb_tmp.height) ? bb_tmp.height : bb_tmp.width;
				QVector2D center_xy = Util::getXYCoord(center_geo.x(), center_geo.y(), result_blds);
				int height_y = center_xy.y();
				int width_x = center_xy.x();
				//std::cout << "height center_xy is " << center_xy.x() << ", " << center_xy.y() <<std::endl;
				if (center_xy.y() >= height_info.size())
				{
					height_y = height_info.size() - 1;
				}
				if (center_xy.x() >= height_info.at(0).size())
				{
					width_x = height_info.at(0).size() - 1;
				}
				building_type = building_type_info.at(height_y).at(width_x);
				//std::cout << "blds type center_xy is " << center_xy.x() << ", " << center_xy.y() << std::endl;
				//std::cout << "building_type " << building_type << std::endl;
				float scale_factor = 1.0;
				float scale_factor_v2 = 1.0;
				float correction_factor = correction;
				// record height for different building type
				//if (building_type == 2)
				//{
				//	QFile file_params = QString("source/block_type_2.txt");
				//	if (!file_params.open(QIODevice::WriteOnly | QIODevice::Append)) {
				//		std::cerr << "Cannot open file for writing: " << file_params.fileName().toUtf8().constData() << std::endl;
				//		return true;
				//	}
				//	QTextStream out_params(&file_params);
				//	out_params << avg_height << "\n";
				//	out_params.flush();
				//	file_params.close();
				//}
				//if (building_type == 3)
				//{
				//	QFile file_params = QString("source/block_type_3.txt");
				//	if (!file_params.open(QIODevice::WriteOnly | QIODevice::Append)) {
				//		std::cerr << "Cannot open file for writing: " << file_params.fileName().toUtf8().constData() << std::endl;
				//		return true;
				//	}
				//	QTextStream out_params(&file_params);
				//	out_params << avg_height << "\n";
				//	out_params.flush();
				//	file_params.close();
				//}
				//if (building_type == 4)
				//{
				//	QFile file_params = QString("source/block_type_4.txt");
				//	if (!file_params.open(QIODevice::WriteOnly | QIODevice::Append)) {
				//		std::cerr << "Cannot open file for writing: " << file_params.fileName().toUtf8().constData() << std::endl;
				//		return true;
				//	}
				//	QTextStream out_params(&file_params);
				//	out_params << avg_height << "\n";
				//	out_params.flush();
				//	file_params.close();
				//}
				//if (building_type == 5)
				//{
				//	QFile file_params = QString("source/block_type_5.txt");
				//	if (!file_params.open(QIODevice::WriteOnly | QIODevice::Append)) {
				//		std::cerr << "Cannot open file for writing: " << file_params.fileName().toUtf8().constData() << std::endl;
				//		return true;
				//	}
				//	QTextStream out_params(&file_params);
				//	out_params << avg_height << "\n";
				//	out_params.flush();
				//	file_params.close();
				//}
				//if (building_type == 6)
				//{
				//	QFile file_params = QString("source/block_type_6.txt");
				//	if (!file_params.open(QIODevice::WriteOnly | QIODevice::Append)) {
				//		std::cerr << "Cannot open file for writing: " << file_params.fileName().toUtf8().constData() << std::endl;
				//		return true;
				//	}
				//	QTextStream out_params(&file_params);
				//	out_params << avg_height << "\n";
				//	out_params.flush();
				//	file_params.close();
				//}

				// for content generation
				//if (building_type == 6)
				//{
				//	stories = (133.0 + Util::genRand(-54, 54)) / 3 + 1;
				//}
				//else if (building_type == 2){
				//	building_type = 3;
				//	stories = (35.0 + Util::genRand(-6.7, 6.7)) / 3 + 1;
				//}

				switch (building_type) {
				case 1:
					sd_setback_front = 0.136;
					sd_setback_side = 0.113;
					G::global()["parcel_setback_front"] = correction_factor * std::max(0.0f, Util::genRand(parcel_front_side * (0.25 - scale_factor * sd_setback_front), parcel_front_side * (0.25 + scale_factor_v2 * sd_setback_front)));
					G::global()["parcel_setback_rear"] = correction_factor * std::max(0.0f, Util::genRand(parcel_front_side * (0.25 - scale_factor * sd_setback_front), parcel_front_side * (0.25 + scale_factor_v2 * sd_setback_front)));
					G::global()["parcel_setback_sides"] = correction_factor /** 0.5 */* std::max(0.0f, Util::genRand(parcel_side_side * (0.194 - scale_factor * sd_setback_side), parcel_side_side * (0.194 + scale_factor_v2 * sd_setback_side)));
					break;
				case 2:
					sd_setback_front = 0.138;
					sd_setback_side = 0.117;
					G::global()["parcel_setback_front"] = correction_factor * std::max(0.0f, Util::genRand(parcel_front_side * (0.234 - scale_factor * sd_setback_front), parcel_front_side * (0.234 + scale_factor_v2 * sd_setback_front)));
					G::global()["parcel_setback_rear"] = correction_factor * std::max(0.0f, Util::genRand(parcel_front_side * (0.234 - scale_factor * sd_setback_front), parcel_front_side * (0.234 + scale_factor_v2 * sd_setback_front)));
					G::global()["parcel_setback_sides"] = correction_factor/** 0.5 */ * std::max(0.0f, Util::genRand(parcel_side_side * (0.189 - scale_factor * sd_setback_side), parcel_side_side * (0.189 + scale_factor_v2 * sd_setback_side)));
					break;
				case 3:
					sd_setback_front = 0.11;
					sd_setback_side = 0.14;
					G::global()["parcel_setback_front"] = correction_factor * std::max(0.0f, Util::genRand(parcel_front_side * (0.12 - scale_factor * sd_setback_front), parcel_front_side * (0.12 + scale_factor_v2 * sd_setback_front)));
					G::global()["parcel_setback_rear"] = correction_factor * std::max(0.0f, Util::genRand(parcel_front_side * (0.12 - scale_factor * sd_setback_front), parcel_front_side * (0.12 + scale_factor_v2 * sd_setback_front)));
					G::global()["parcel_setback_sides"] = correction_factor/** 0.5*/  * std::max(0.0f, Util::genRand(parcel_side_side * (0.159 - scale_factor * sd_setback_side), parcel_side_side * (0.159 + scale_factor_v2 * sd_setback_side)));
					break;
				case 4:
					sd_setback_front = 0.122;
					sd_setback_side = 0.118;
					G::global()["parcel_setback_front"] = correction_factor * std::max(0.0f, Util::genRand(parcel_front_side * (0.121 - scale_factor * sd_setback_front), parcel_front_side * (0.121 + scale_factor_v2 * sd_setback_front)));
					G::global()["parcel_setback_rear"] = correction_factor * std::max(0.0f, Util::genRand(parcel_front_side * (0.121 - scale_factor * sd_setback_front), parcel_front_side * (0.121 + scale_factor_v2 * sd_setback_front)));
					G::global()["parcel_setback_sides"] = correction_factor/** 0.5*/  * std::max(0.0f, Util::genRand(parcel_side_side * (0.134 - scale_factor * sd_setback_side), parcel_side_side * (0.134 + scale_factor_v2 * sd_setback_side)));
					break;
				case 5:
					sd_setback_front = 0.143;
					sd_setback_side = 0.139;
					G::global()["parcel_setback_front"] = correction_factor * std::max(0.0f, Util::genRand(parcel_front_side * (0.144 - scale_factor * sd_setback_front), parcel_front_side * (0.144 + scale_factor_v2 * sd_setback_front)));
					G::global()["parcel_setback_rear"] = correction_factor * std::max(0.0f, Util::genRand(parcel_front_side * (0.144 - scale_factor * sd_setback_front), parcel_front_side * (0.144 + scale_factor_v2 * sd_setback_front)));
					G::global()["parcel_setback_sides"] = correction_factor/** 0.5*/  * std::max(0.0f, Util::genRand(parcel_side_side * (0.141 - scale_factor * sd_setback_side), parcel_side_side * (0.141 + scale_factor_v2 * sd_setback_side)));
					break;
				case 6:
					sd_setback_front = 0.09;
					sd_setback_side = 0.103;
					G::global()["parcel_setback_front"] = correction_factor * std::max(0.0f, Util::genRand(parcel_front_side * (0.08 - scale_factor * sd_setback_front), parcel_front_side * (0.08 + scale_factor_v2 * sd_setback_front)));
					G::global()["parcel_setback_rear"] = correction_factor * std::max(0.0f, Util::genRand(parcel_front_side * (0.08 - scale_factor * sd_setback_front), parcel_front_side * (0.08 + scale_factor_v2 * sd_setback_front)));
					G::global()["parcel_setback_sides"] = correction_factor/** 0.5*/  * std::max(0.0f, Util::genRand(parcel_side_side * (0.1 - scale_factor * sd_setback_side), parcel_side_side * (0.1 + scale_factor_v2 * sd_setback_side)));
					break;
				default:
					G::global()["parcel_setback_front"] = correction_factor * Util::genRand(1, 3);
					G::global()["parcel_setback_rear"] = correction_factor * Util::genRand(1, 3);
					G::global()["parcel_setback_sides"] = correction_factor /** 0.5*/ * Util::genRand(1, 3);
				}
				//std::cout << "parcel_front_side is " << parcel_front_side << std::endl;
				//std::cout << "parcel_side_side is " << parcel_side_side << std::endl;
				//std::cout << "parcel_setback_front is " << G::getFloat("parcel_setback_front") << std::endl;
				//std::cout << "parcel_setback_side is " << G::getFloat("parcel_setback_sides") << std::endl;
			}
			else{
				G::global()["parcel_setback_front"] =  Util::genRand(1, 3);
				G::global()["parcel_setback_rear"] = Util::genRand(1, 3);
				G::global()["parcel_setback_sides"] =  Util::genRand(1, 3);
			}
			if (!generateBuilding(rendManager, blocks[i], blocks[i].parcels[j], stories)) {
				blocks[i].parcels[j].isPark = true;
			}
			/*if (j != 0)
				blocks[i].parcels[j].isPark = true;*/
		}
		{
			saveBldsImage(blocks[i], i);
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
bool SateBuildings::generateBuilding(VBORenderManager& rendManager, Block& block, Parcel& parcel, int stories) {
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
	parcel.building.numStories = stories;
	//std::cout << "stories is " << stories << std::endl;
	float c = rand() % 192;
	parcel.building.color = QColor(c, c, c);
	parcel.building.bldType = 0;
	QString filename = "source/base_level.txt";
	if (!filename.isEmpty()){
		QFile file(filename);
		if (!file.open(QIODevice::ReadOnly)) {
			parcel.building.baseLevel = -1;
			return true;
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
		parcel.building.baseLevel = tmp.at(0);
		//std::cout << "baseLevel is " << parcel.building.baseLevel << std::endl;
	}
	else
	{
		parcel.building.baseLevel = -1;
	}

	return true;
}

void SateBuildings::saveBldsImage(Block& block, int index){
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

void SateBuildings::findCorrespondedBlock(const Block & block, QString filename, int index){
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

std::vector<std::vector<int>> SateBuildings::get_height_info(QString height_tiff){
	// height info
	GDALDataset  *poDataset_height;
	std::vector<std::vector<int>> height_info;
	GDALAllRegister();
	poDataset_height = (GDALDataset *)GDALOpen(height_tiff.toUtf8().data(), GA_ReadOnly);
	if (poDataset_height == NULL)
	{
		std::cout << " Null data" << std::endl;
	}
	else{
		// Getting Dataset Information
		double        adfGeoTransform[6];
		printf("Driver: %s/%s\n",
			poDataset_height->GetDriver()->GetDescription(),
			poDataset_height->GetDriver()->GetMetadataItem(GDAL_DMD_LONGNAME));
		printf("Size is %dx%dx%d\n",
			poDataset_height->GetRasterXSize(), poDataset_height->GetRasterYSize(),
			poDataset_height->GetRasterCount());
		if (poDataset_height->GetProjectionRef() != NULL)
			printf("Projection is `%s'\n", poDataset_height->GetProjectionRef());
		if (poDataset_height->GetGeoTransform(adfGeoTransform) == CE_None)
		{
			printf("Origin = (%.6f,%.6f)\n",
				adfGeoTransform[0], adfGeoTransform[3]);
			printf("Pixel Size = (%.6f,%.6f)\n",
				adfGeoTransform[1], adfGeoTransform[5]);
		}

		//Fetching a Raster Band
		GDALRasterBand  *poBand;
		int             nBlockXSize, nBlockYSize;
		int             bGotMin, bGotMax;
		double          adfMinMax[2];
		poBand = poDataset_height->GetRasterBand(1);
		poBand->GetBlockSize(&nBlockXSize, &nBlockYSize);
		adfMinMax[0] = poBand->GetMinimum(&bGotMin);
		adfMinMax[1] = poBand->GetMaximum(&bGotMax);
		if (!(bGotMin && bGotMax))
			GDALComputeRasterMinMax((GDALRasterBandH)poBand, TRUE, adfMinMax);
		printf("Min=%.3fd, Max=%.3f\n", adfMinMax[0], adfMinMax[1]);
		if (poBand->GetOverviewCount() > 0)
			printf("Band has %d overviews.\n", poBand->GetOverviewCount());
		if (poBand->GetColorTable() != NULL)
			printf("Band has a color table with %d entries.\n",
			poBand->GetColorTable()->GetColorEntryCount());
		//Reading Raster Data
		int nXSize = poBand->GetXSize();
		int nYSize = poBand->GetYSize();
		int *pafScanline = new int[nXSize*nYSize];
		printf("Band nXSize is %d.\n", nXSize);
		printf("Band nYSize is %d.\n", nYSize);
		pafScanline = (int *)CPLMalloc(sizeof(int)*nXSize*nYSize);
		poBand->RasterIO(GF_Read, 0, 0, nXSize, nYSize,
			pafScanline, nXSize, nYSize, GDT_Int32,
			0, 0);

		// save to a matrix
		std::vector<int> tmp;
		for (int i = 0; i < nYSize; i++){
			for (int j = 0; j < nXSize; j++){
				tmp.push_back(pafScanline[j + nXSize*i]);
			}
			height_info.push_back(tmp);
			tmp.clear();
		}
	}
	return height_info;
}

std::vector<std::vector<int>> SateBuildings::get_blds_type_info(QString blds_type_tiff){
	// population info
	std::vector<std::vector<int>> blds_type_info;
	GDALDataset *poDataset_population = (GDALDataset *)GDALOpen(blds_type_tiff.toUtf8().data(), GA_ReadOnly);
	GDALAllRegister();
	if (poDataset_population == NULL)
	{
		std::cout << " Null data" << std::endl;
	}
	else{
		// Getting Dataset Information
		double        adfGeoTransform[6];
		printf("Driver: %s/%s\n",
			poDataset_population->GetDriver()->GetDescription(),
			poDataset_population->GetDriver()->GetMetadataItem(GDAL_DMD_LONGNAME));
		printf("Size is %dx%dx%d\n",
			poDataset_population->GetRasterXSize(), poDataset_population->GetRasterYSize(),
			poDataset_population->GetRasterCount());
		if (poDataset_population->GetProjectionRef() != NULL)
			printf("Projection is `%s'\n", poDataset_population->GetProjectionRef());
		if (poDataset_population->GetGeoTransform(adfGeoTransform) == CE_None)
		{
			printf("Origin = (%.6f,%.6f)\n",
				adfGeoTransform[0], adfGeoTransform[3]);
			printf("Pixel Size = (%.6f,%.6f)\n",
				adfGeoTransform[1], adfGeoTransform[5]);
		}

		//Fetching a Raster Band
		GDALRasterBand  *poBand;
		int             nBlockXSize, nBlockYSize;
		int             bGotMin, bGotMax;
		double          adfMinMax[2];
		poBand = poDataset_population->GetRasterBand(1);
		poBand->GetBlockSize(&nBlockXSize, &nBlockYSize);
		printf("Block=%dx%d Type=%s, ColorInterp=%s\n",
			nBlockXSize, nBlockYSize,
			GDALGetDataTypeName(poBand->GetRasterDataType()),
			GDALGetColorInterpretationName(
			poBand->GetColorInterpretation()));
		adfMinMax[0] = poBand->GetMinimum(&bGotMin);
		adfMinMax[1] = poBand->GetMaximum(&bGotMax);
		if (!(bGotMin && bGotMax))
			GDALComputeRasterMinMax((GDALRasterBandH)poBand, TRUE, adfMinMax);
		printf("Min=%.3fd, Max=%.3f\n", adfMinMax[0], adfMinMax[1]);
		if (poBand->GetOverviewCount() > 0)
			printf("Band has %d overviews.\n", poBand->GetOverviewCount());
		if (poBand->GetColorTable() != NULL)
			printf("Band has a color table with %d entries.\n",
			poBand->GetColorTable()->GetColorEntryCount());
		//Reading Raster Data
		int nXSize = poBand->GetXSize();
		int nYSize = poBand->GetYSize();
		int *pafScanline = new int[nXSize*nYSize];
		printf("Band nXSize is %d.\n", nXSize);
		printf("Band nYSize is %d.\n", nYSize);
		pafScanline = (int *)CPLMalloc(sizeof(int)*nXSize*nYSize);
		poBand->RasterIO(GF_Read, 0, 0, nXSize, nYSize,
			pafScanline, nXSize, nYSize, GDT_Int32,
			0, 0);

		// save to a matrix
		std::vector<int> tmp;
		for (int i = 0; i < nYSize; i++){
			for (int j = 0; j < nXSize; j++){
				tmp.push_back(pafScanline[j + nXSize*i]);
			}
			blds_type_info.push_back(tmp);
			tmp.clear();
		}
	}
	return blds_type_info;
}