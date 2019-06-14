#include "SateParcelsAndBuildings.h"
#include "qmatrix4x4.h"
#include "global.h"
#include "Util.h"
#include <QFileDialog>
#include "gdal_priv.h"

bool SateParcelsAndBuildings::generateParcelsAndBuildings(VBORenderManager& rendManager, std::vector<Block>& blocks) {
	if (QDir("output").exists()) {
		//std::cout << "Removing existing files in the output directory...";
		QDir("output").removeRecursively();
		std::cout << " done." << std::endl;
	}
	if (!QDir("output").exists()){
		QDir().mkpath("output");
	}
	cv::Mat src = cv::imread(G::getString("segmented_image").toUtf8().data(), CV_LOAD_IMAGE_COLOR);
	cv::Mat parcel_src, gt_src, gt_whole_src;

	bool bHeight_Info = false;
	if (G::getString("height_tif") != NULL &&QFile(G::getString("height_tif")).exists()) {
		std::cout << " height info file exists." << std::endl;
		bHeight_Info = true;
	}
	std::vector<std::vector<int>> height_info;
	std::vector<double> result;
	if (bHeight_Info){
		height_info = get_height_info(G::getString("height_tif"));
		result = Util::getGeoInfo(G::getString("height_tif").toUtf8().data());
	}

	int thresh = 100;
	int max_thresh = 255;
	cv::RNG rng(12345);
	std::cout << "block size is " << blocks.size() << std::endl;
	for (int bN = 0; bN < blocks.size(); ++bN) {
		//std::cout << "bN is " << bN << std::endl;
		// chicago
		/*if (bN == 2982 || bN == 3747 || bN == 3804 || bN == 3848)
			continue;*/
		if (blocks[bN].isPark) {
			std::cout << "bN is " << bN << std::endl;
			continue;
		}
		for (int cN = 0; cN < blocks[bN].blockContours.size(); ++cN) {
			//
			// Find the segmentd block path
			QString blockFilename = getBlockPath(blocks[bN], src, parcel_src, gt_src, gt_whole_src, bN, false);
			if (QString::compare(blockFilename, "empty", Qt::CaseInsensitive) == 0){
				//std::cout << "bN is empty " << bN << std::endl;
				blocks[bN].isPark = true;
				continue;
			}
			// only one buidling in this block, simply use opencv
			cv::Mat src_gray;
			cv::Mat src_block;
			src_block = cv::imread(blockFilename.toUtf8().constData(), CV_LOAD_IMAGE_COLOR);
			if (src_block.size().width * src_block.size().height < 20)
			{
				blocks[bN].isPark = true;
				continue;
			}
			remove_roads(src_block);
			cv::Scalar lowerb = cv::Scalar(255, 0, 0);
			cv::Scalar upperb = cv::Scalar(255, 0, 0);
			cv::inRange(src_block, lowerb, upperb, src_gray);
			cv::Mat threshold_output;
			std::vector<std::vector<cv::Point> > contours_ori;
			std::vector<cv::Vec4i> hierarchy;

			/// Detect edges using Threshold
			threshold(src_gray, threshold_output, thresh, 255, cv::THRESH_BINARY);
			/// Find contours
			findContours(threshold_output, contours_ori, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, cv::Point(0, 0));
			
			// check the topology
			std::vector<std::vector<cv::Point> > contours;
			for (int i = 0; i < contours_ori.size(); i++){
				if (hierarchy[i][3] == -1)
					contours.push_back(contours_ori[i]);
			}
			//
			// find the origin 
			Polygon3D contour = blocks[bN].blockContours.at(0);
			std::vector<cv::Point>contour_ori;
			for (int i = 0; i < blocks[bN].blockContours[0].size(); i++){
				float x = contour.contour[i].x();
				float y = contour.contour[i].y();
				contour_ori.push_back(cv::Point(x, y));
			}
			cv::Rect2f boundRect_ori = cv::boundingRect(cv::Mat(contour_ori));

			blocks[bN].parcels.resize(contours.size());
			for (int j = 0; j < blocks[bN].parcels.size(); j++){
				std::vector<cv::Point> building_contour;
				//float epsilon = 0.5f;
				// simplify contour
				//cv::approxPolyDP(contours[j], building_contour, epsilon, true);
				/*while (!isSimple(building_contour) && epsilon < 3.0f){
					epsilon += 0.5;
					building_contour.clear();
					cv::approxPolyDP(contours[j], building_contour, epsilon, true);
				}*/

				float epsilon = 1.0f;
				cv::approxPolyDP(contours[j], building_contour, epsilon, true);
				while (!isSimple(building_contour) && epsilon < 4.0f){
				epsilon += 0.5;
				building_contour.clear();
				cv::approxPolyDP(contours[j], building_contour, epsilon, true);
				}

				if (!isSimple(building_contour)){
					blocks[bN].parcels[j].isPark = true;
					continue;
				}
				if (building_contour.size() == 0){
					blocks[bN].parcels[j].isPark = true;
					continue;
				}
				cv::RotatedRect boundRect_test = cv::minAreaRect(cv::Mat(building_contour));
				//std::cout << "boundRect_test size is " << boundRect_test.size << std::endl;
				/*if (boundRect_test.size.width < 15 || boundRect_test.size.height < 15){
					blocks[bN].parcels[j].isPark = true;
					continue;
				}*/
				Loop3D pgon;
				for (int k = 0; k < building_contour.size(); k++){
					pgon.push_back(QVector3D(boundRect_ori.x + building_contour[k].x, boundRect_ori.y + src_block.rows - building_contour[k].y, 0.0f));
					//std::cout << "(" << boundRect_ori.x + building_contour[k].x << ", " << boundRect_ori.y + src_block.rows - building_contour[k].y << std::endl;
				}
				//std::cout << "----" << std::endl;
				blocks[bN].parcels[j].building.buildingFootprint.contour = pgon;
				float avg_height = 0;
				// get the height for this building
				{
					std::vector<cv::Point> contour_tmp;
					cv::Point center;
					QVector2D center_geo;
					cv::Rect bb_tmp;
					Polygon3D contour = blocks[bN].parcels[j].building.buildingFootprint;
					if (contour.size() == 0){
						blocks[bN].parcels[j].isPark = true;
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
				}
				blocks[bN].parcels[j].building.numStories = avg_height / 3 + 1;
				float c = rand() % 192;
				blocks[bN].parcels[j].building.color = QColor(c, c, c);
				blocks[bN].parcels[j].building.bldType = 0;
				blocks[bN].parcels[j].isPark = false;
				QString filename = "source/base_level.txt";
				if (!filename.isEmpty()){
					QFile file(filename);
					if (!file.open(QIODevice::ReadOnly)) {
						blocks[bN].parcels[j].building.baseLevel = -1;
						continue;
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
					blocks[bN].parcels[j].building.baseLevel = tmp.at(0);
					//std::cout << "baseLevel is " << parcel.building.baseLevel << std::endl;
				}
				else
				{
					blocks[bN].parcels[j].building.baseLevel = -1;
				}
			}
		}

	}
	return true;
}

QString SateParcelsAndBuildings::getBlockPath(const Block & block, const cv::Mat& src, const cv::Mat& parcel_src, const cv::Mat& gt_src, const cv::Mat& gt_whole_src, int index, bool bTest){
	Polygon3D contour = block.blockContours.at(0);
	std::vector<cv::Point>contour_ori;
	std::vector<cv::Point>contour_cv;
	for (int i = 0; i < block.blockContours[0].size(); i++){
		float x = contour.contour[i].x();
		float y = contour.contour[i].y();
		contour_ori.push_back(cv::Point(x, y));
		QVector2D point_tmp = Util::getXYCoordSeg(x, y);
		contour_cv.push_back(cv::Point(point_tmp.x(), point_tmp.y()));
	}
	//std::cout << "index size " << index << std::endl;
	//std::cout << "contour size " << block.blockContours[0].size() << std::endl;
	cv::Rect2f boundRect = cv::boundingRect(cv::Mat(contour_cv));
	if (boundRect.x < -1000000 || boundRect.y < -1000000){
		std::cout << "invalide negative!" << std::endl;
		return QString("empty");
	}
	//cv::Mat src = cv::imread(filename.toUtf8().data(), CV_LOAD_IMAGE_COLOR);
	if (boundRect.x + boundRect.width >= src.size().width || boundRect.y + boundRect.height >= src.size().height){
		return QString("empty");
	}
	std::vector<cv::Point>contour_block;
	for (int i = 0; i < block.blockContours[0].size(); i++){
		contour_block.push_back(cv::Point(contour_cv.at(i).x - boundRect.x, contour_cv.at(i).y - boundRect.y));
	}
	cv::Mat src_block = src(boundRect);
	cv::Mat mask = cv::Mat::zeros(src_block.size(), CV_8UC1);
	std::vector<std::vector<cv::Point> > contours;
	contours.push_back(contour_block);
	drawContours(mask, contours, -1, cv::Scalar(255), CV_FILLED);
	cv::Mat tmp(src_block.size(), CV_8UC3, cv::Scalar(0, 255, 0));
	src_block.copyTo(tmp, mask);
	if (!valid_block(tmp)){
		return QString("empty");
	}
	cv::Rect2f boundRect_ori = cv::boundingRect(cv::Mat(contour_ori));

	QString filename_out("output/block_" + QString::number(index) + ".png");
	cv::resize(tmp, tmp, cv::Size(boundRect_ori.width, boundRect_ori.height), 0, 0, cv::INTER_NEAREST);
	cv::imwrite(filename_out.toUtf8().data(), tmp);
	return filename_out;
}

bool SateParcelsAndBuildings::valid_block(cv::Mat &src){
	float block_area = src.size().width * src.size().height;
	float block_parcel_area = compute_parcel_area(src);
	if (block_parcel_area / block_area < 0.05)
		return false;
	// condition 1
	if (block_area < 100)
		return false;
	return true;
	if (src.size().height < 20)
		return false;
	return true;
}

void SateParcelsAndBuildings::remove_roads(cv::Mat &img){
	for (int i = 0; i < img.size().height; i++){
		for (int j = 0; j < img.size().width; j++){
			//noise
			if (img.at<cv::Vec3b>(i, j)[2] == 255){
				img.at<cv::Vec3b>(i, j)[0] = 0;
				img.at<cv::Vec3b>(i, j)[1] = 255;
				img.at<cv::Vec3b>(i, j)[2] = 0;
			}
		}
	}
}

float SateParcelsAndBuildings::compute_parcel_area(const cv::Mat & src){
	int thresh = 100;
	int max_thresh = 255;
	cv::RNG rng(12345);

	cv::Mat src_gray;

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
	/// Draw polygonal contour + bonding rects + circles
	for (int i = 0; i< contours.size(); i++)
	{
		building_area += cv::contourArea(contours.at(i));
	}
	return building_area;
}

std::vector<std::vector<int>> SateParcelsAndBuildings::get_height_info(QString height_tiff){
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

bool SateParcelsAndBuildings::isSimple(const std::vector<cv::Point>& points) {
	CDT cdt;
	CGAL::Partition_traits_2<Kernel>::Polygon_2 polygon;
	for (int i = 0; i < points.size(); i++) {
		polygon.push_back(CDT::Point(points[i].x, points[i].y));
	}
	return polygon.is_simple();
}