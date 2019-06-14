#include "SateParcels.h"
#include "qmatrix4x4.h"
#include "global.h"
#include "Util.h"
#include <QFileDialog>

bool SateParcels::generateParcels(VBORenderManager& rendManager, std::vector<Block>& blocks, float boundary_v1, float boundary_v2, int testbN, bool bTest) {
	if (QDir("output").exists()) {
		//std::cout << "Removing existing files in the output directory...";
		QDir("output").removeRecursively();
		std::cout << " done." << std::endl;
	}
	if (!QDir("output").exists()){
		QDir().mkpath("output");
	}
	CaffeWrapper *caffe_parcel_type = new CaffeWrapper("models/parcel_type/deploy.prototxt", "models/parcel_type/parcel_type.caffemodel",
		"models/parcel_type/mean.binaryproto");
	Regression * parcel_small = new Regression("models/parcel_small/deploy.prototxt", "models/parcel_small/parcel.caffemodel");
	Regression * parcel_median = new Regression("models/parcel_median/deploy.prototxt", "models/parcel_median/parcel.caffemodel");
	Regression * parcel_big = new Regression("models/parcel_big/deploy.prototxt", "models/parcel_big/parcel.caffemodel");
	cv::Mat src = cv::imread(G::getString("segmented_image").toUtf8().data(), CV_LOAD_IMAGE_COLOR);
	cv::Mat parcel_src, gt_src, gt_whole_src;
	if (bTest){
		parcel_src = cv::imread(G::getString("parcel_image").toUtf8().data(), CV_LOAD_IMAGE_COLOR);
		gt_src = cv::imread(G::getString("ground_truth_image").toUtf8().data(), CV_LOAD_IMAGE_COLOR);
		gt_whole_src = cv::imread(G::getString("gt_whole_image").toUtf8().data(), CV_LOAD_IMAGE_COLOR);
	}
	int image_width = 227;
	int image_height = 227;
	int count = 0;
	int thresh = 100;
	int max_thresh = 255;
	cv::RNG rng(12345);
	std::cout << "Block size is " << blocks.size() << std::endl;
	for (int bN = 0; bN < 200/*blocks.size()*/; ++bN) {
		if (bN != testbN && testbN > 0)
			continue;
		if (blocks[bN].isPark) {
			std::cout << "bN is " << bN << std::endl;
			continue;
		}
		for (int cN = 0; cN < blocks[bN].blockContours.size(); ++cN) {
			//
			//QString blockFilename = QString("output/block_" + QString::number(bN) + ".png");
			//if (!QFile(blockFilename).exists())
			//	continue;
			// Find the segmentd block path
			QString blockFilename = getBlockPath(blocks[bN], src, parcel_src, gt_src, gt_whole_src, bN, bTest);
			if (QString::compare(blockFilename, "empty", Qt::CaseInsensitive) == 0){
				//std::cout << "bN is empty " << bN << std::endl;
				blocks[bN].isPark = true;
				continue;
			}
			// only one buidling in this block, simply use opencv
			cv::Mat src_gray;
			cv::Mat src;
			src = cv::imread(blockFilename.toUtf8().data(), CV_LOAD_IMAGE_COLOR);
			if (src.size().width * src.size().height < 20)
			{
				blocks[bN].isPark = true;
				continue;
			}
			remove_roads(src);
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
			if (contours.size() <= 3 && contours.size() >= 1)
			{
				float total_area = 0.0f;
				for (int i = 0; i < contours.size(); i++)
					total_area += contourArea(contours.at(i));
				if (total_area < 5.0f) // total_area is almost 0
				{
					blocks[bN].isPark = true;
					continue;
				}
				set_parcel_paras(total_area / contours.size());
			}
			else{
				float ori_size = 0.0f;
				float later_size = 0.0f;
				// Train to get paras
				ori_size = src.size().width * src.size().height;
				//resize the image
				remove_roads(src);
				QString tmp_path = "tmp/without_roads_" + QString::number(bN) + ".png";
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
				tmp_path = "tmp/resize_width_" + QString::number(bN) + ".png";
				cv::imwrite(tmp_path.toUtf8().data(), img);
				// if the height is beyond 227, then resize the height agaon. (This won't happen. But just in case)
				if (src.size().height > 227){
					cv::resize(img, img, cv::Size(image_width, image_height), 0, 0, cv::INTER_NEAREST);
					tmp_path = "tmp/resize_height_" + QString::number(bN) + ".png";
					cv::imwrite(tmp_path.toUtf8().data(), img);
				}
				// resize to 227 * 227
				cv::Mat output(cv::Size(image_width, image_height), CV_8UC3, cv::Scalar(0, 255, 0));
				img.copyTo(output(cv::Rect(0, 227 - img.size().height, img.size().width, img.size().height)));

				tmp_path = "tmp/output_" + QString::number(bN) + ".png";
				cv::imwrite(tmp_path.toUtf8().data(), output);

				cv::Mat tmp[3];
				cv::split(output, tmp);
				//transfer img
				cv::equalizeHist(tmp[0], tmp[0]);
				cv::equalizeHist(tmp[1], tmp[1]);
				cv::equalizeHist(tmp[2], tmp[2]);
				cv::merge(tmp, 3, output);
				// predict the parcel type
				int parcel_type = 0;
				std::vector<float> weights;
				std::vector<float> pred = caffe_parcel_type->get_pred(output);
				{
					int index = 0;
					float max_tmp = 0.0f;
					for (int iter = 0; iter < 3; iter++){
						weights.push_back(pred[iter]);
						//std::cout << "weigth is " << pred[iter] << std::endl;
						if (pred[iter] > max_tmp){
							max_tmp = pred[iter];
							index = iter;
						}
					}
					parcel_type = index;
				}
				//if (weights.at(0) > 0.85){
				//	std::cout << "type0 is "<<bN<< std::endl;
				//}
				// go to appropriate parcel regression model
				std::pair<float, float> parcelMeanArea;
				std::vector<float> pred_parcel;
				std::vector<float> predic_values;
				if (true){
					pred_parcel.clear();
					// output
					parcelMeanArea = std::make_pair(80.0f, boundary_v1);
					pred_parcel = parcel_small->get_pred(output);
					// Set paras
					if (pred_parcel[1] < 0){
						//std::cout << "pred[1]" << pred_parcel[1] << std::endl;
						pred_parcel[1] = 0.0;
						count++;
					}
					//std::cout << "pred_parcel[1] is " << pred_parcel[1] << std::endl;
					predic_values.push_back((pred_parcel[1] * (parcelMeanArea.second - parcelMeanArea.first) + parcelMeanArea.first));
					// resize back
					//set_parcel_paras((pred_parcel[1] * (parcelMeanArea.second - parcelMeanArea.first) + parcelMeanArea.first) / (resize_factor * resize_factor));
				}
				if (true){
					pred_parcel.clear();
					// output
					parcelMeanArea = std::make_pair(boundary_v1, boundary_v2);
					pred_parcel = parcel_median->get_pred(output);
					// Set paras
					if (pred_parcel[1] < 0){
						//std::cout << "pred[1]" << pred_parcel[1] << std::endl;
						pred_parcel[1] = 0.0;
						count++;
					}
					//std::cout << "pred_parcel[1] is " << pred_parcel[1] << std::endl;
					predic_values.push_back((pred_parcel[1] * (parcelMeanArea.second - parcelMeanArea.first) + parcelMeanArea.first));
					// resize back
					//set_parcel_paras((pred_parcel[1] * (parcelMeanArea.second - parcelMeanArea.first) + parcelMeanArea.first) / (resize_factor * resize_factor));
				}
				if (true){
					pred_parcel.clear();
					// output
					parcelMeanArea = std::make_pair(boundary_v2, 10000.0f);
					pred_parcel = parcel_big->get_pred(output);
					// Set paras
					if (pred_parcel[1] < 0){
						//std::cout << "pred[1]" << pred_parcel[1] << std::endl;
						pred_parcel[1] = 0.0;
						count++;
					}
					//std::cout << "pred_parcel[1] is " << pred_parcel[1] << std::endl;
					predic_values.push_back((pred_parcel[1] * (parcelMeanArea.second - parcelMeanArea.first) + parcelMeanArea.first));
					// resize back
					//set_parcel_paras((pred_parcel[1] * (parcelMeanArea.second - parcelMeanArea.first) + parcelMeanArea.first) / (resize_factor * resize_factor));
				}
				//compute the parcel size using weights

				float final_parcel_size = predic_values.at(0) * weights.at(0) + predic_values.at(1) * weights.at(1) + predic_values.at(2) * weights.at(2);
				//float final_parcel_size = predic_values.at(0);
				//std::cout << "final_parcel_size is " << final_parcel_size << std::endl;
				//std::cout << "resize_factor is " << resize_factor << std::endl;

				set_parcel_paras(final_parcel_size / (resize_factor * resize_factor));
			}
			std::cout << "---Processing block " << bN << std::endl;
			std::vector<Parcel> parcels;
			subdivideBlockIntoParcels(blocks[bN], blocks[bN].blockContours[cN], parcels);

			blocks[bN].parcels.insert(blocks[bN].parcels.end(), parcels.begin(), parcels.end());

			{
				//saveParcelImage(blocks[bN].blockContours[cN], blocks[bN].parcels, bN);
			}
		}

	}
	std::cout << "count is " << count << std::endl;
	return true;
}

void SateParcels::subdivideBlockIntoParcels(const Block & block, const Polygon3D& contour, std::vector<Parcel>& parcels) {
	// set the initial parcel be the block itself
	Parcel parcel;
	parcel.parcelContour = contour;
	//std::cout <<"parcel area is " <<G::getFloat("parcel_area_mean") << std::endl;
	//std::cout << "parcel contour area  is " << parcel.parcelContour.area() << std::endl;
	subdivideParcel(block, parcel, G::getFloat("parcel_area_mean"), G::getFloat("parcel_area_deviation"), G::getFloat("parcel_split_deviation"), parcels);

	// set some parcels as park
	// ........................................................................................
	// 11/8/2016: We decided not to make any parcel be an open space explicitly
	//            in order to make as many closed area as possible.
	//            Some blocks can be an open space according to the specified parameter value.
	// ........................................................................................
	/*
	for (int i = 0; i < parcels.size(); ++i) {
	if (parcels[i].parcelContour.isClockwise()) {
	std::reverse(parcels[i].parcelContour.contour.begin(), parcels[i].parcelContour.contour.end());
	}

	if (Util::genRand() < G::getFloat("parksRatio")) {
	parcels[i].isPark = true;
	}
	}
	*/

	// Check if the parcel is facing to a street
	// If not, set it as an open space
	for (int pN = 0; pN < parcels.size(); ++pN) {
		if (parcels[pN].isPark) {
			continue;
		}

		bool facing = false;
		for (int i = 0; i < parcels[pN].parcelContour.size(); ++i) {
			for (int j = 0; j < contour.size(); ++j) {
				int next = (j + 1) % contour.size();
				float dist = Util::pointSegmentDistanceXY(contour[j], contour[next], parcels[pN].parcelContour[i]);
				if (dist < 2) {
					facing = true;
					break;
				}
			}
		}

		if (!facing) {
			parcels[pN].isPark = true;
		}
	}
}

/**
* Recursively subdivision of a parcel using OBB technique
* @param parcel			parcel
* @param areaMean			mean parcel area
* @param areaStd			StdDev of parcel area
* @param splitIrregularity	A normalized value 0-1 indicating how far from the middle point the split line should be.
* @param outParcels		the resulting subdivision
**/
bool SateParcels::subdivideParcel(const Block & block, Parcel& parcel, float areaMean, float areaStd, float splitIrregularity, std::vector<Parcel> &outParcels) {
	//float thresholdArea = std::max(0.0f, Util::genRand(areaMean - areaStd, areaMean + areaStd));
	float thresholdArea = areaMean;
	//std::cout <<"areaMean is " <<areaMean << std::endl;
	//std::cout <<"parcel.parcelContour.area() is "<< parcel.parcelContour.area() << std::endl;
	// multiple conditions small parcels, median parcels, big parcels
	if (areaMean < 800){
		if (parcel.parcelContour.area() < thresholdArea * 1.6) {
			outParcels.push_back(parcel);
			return true;
		}
	}
	if (areaMean > 5000){
		if (parcel.parcelContour.area() < thresholdArea * 2.0) {
			outParcels.push_back(parcel);
			return true;
		}
	}
	else{
		if (parcel.parcelContour.area() <= thresholdArea * 1.6) {
			outParcels.push_back(parcel);
			return true;
		}
	}

	// compute OBB
	QVector3D obbSize;
	QMatrix4x4 obbMat;
	parcel.parcelContour.getMyOBB(obbSize, obbMat);

	// compute split line passing through center of OBB TODO (+/- irregularity)
	//		and with direction parallel/perpendicular to OBB main axis
	QVector3D slEndPoint;
	QVector3D dirVectorInit, dirVector, dirVectorOrthogonal;
	QVector3D midPt(0.0f, 0.0f, 0.0f);
	QVector3D auxPt(1.0f, 0.0f, 0.0f);
	QVector3D midPtNoise(0.0f, 0.0f, 0.0f);
	std::vector<QVector3D> splitLine;

	midPt = midPt*obbMat;

	dirVectorInit = (auxPt*obbMat - midPt);
	dirVectorInit.normalize();
	if (obbSize.x() > obbSize.y()) {
		dirVector.setX(-dirVectorInit.y());
		dirVector.setY(dirVectorInit.x());
	}
	else {
		dirVector = dirVectorInit;
	}

	// 11/8/2016: comment out the following lines in order to remove the randomness for subdividing parcels
	midPtNoise.setX(splitIrregularity * Util::genRand(-2, 2));
	midPtNoise.setY(splitIrregularity * Util::genRand(-2, 2));
	midPt = midPt + midPtNoise;

	slEndPoint = midPt + 10000.0f*dirVector;
	splitLine.push_back(slEndPoint);
	slEndPoint = midPt - 10000.0f*dirVector;
	splitLine.push_back(slEndPoint);

	// split parcel with line and obtain two new parcels
	Polygon3D pgon1, pgon2;

	float kDistTol = 0.01f;

	std::vector<Polygon3D> pgons;

	// Use the simple splitting because this is fast
	if (parcel.parcelContour.splitMeWithPolyline(splitLine, pgon1.contour, pgon2.contour)) {

		//check if new contours of pgon1 and pgon2 "touch" the boundary of the block
		if (Polygon3D::distanceXYfromContourAVerticesToContourB(pgon1.contour, block.blockContours[0].contour) > kDistTol
			|| Polygon3D::distanceXYfromContourAVerticesToContourB(pgon2.contour, block.blockContours[0].contour) > kDistTol) {
			splitLine.clear();
			pgon1.clear();
			pgon2.clear();

			//if they don't have street access, rotate split line by 90 degrees and recompute
			dirVectorOrthogonal.setX(-dirVector.y());
			dirVectorOrthogonal.setY(dirVector.x());

			slEndPoint = midPt + 10000.0f * dirVectorOrthogonal;
			splitLine.push_back(slEndPoint);
			slEndPoint = midPt - 10000.0f * dirVectorOrthogonal;
			splitLine.push_back(slEndPoint);
			parcel.parcelContour.splitMeWithPolyline(splitLine, pgon1.contour, pgon2.contour);
		}

		Parcel parcel1;
		Parcel parcel2;

		parcel1.parcelContour = pgon1;
		parcel2.parcelContour = pgon2;

		// call recursive function for both parcels
		subdivideParcel(block, parcel1, areaMean, areaStd, splitIrregularity, outParcels);
		subdivideParcel(block, parcel2, areaMean, areaStd, splitIrregularity, outParcels);
	}
	else {
		//std::cout << "CGAL Version" << std::endl;
		//If the simple splitting fails, try CGAL version which is slow
		if (parcel.parcelContour.split(splitLine, pgons)) {
			for (int i = 0; i < pgons.size(); ++i) {
				Parcel parcel;
				parcel.parcelContour = pgons[i];

				subdivideParcel(block, parcel, areaMean, areaStd, splitIrregularity, outParcels);
			}
		}
		else {
			//parcel.isPark = true;
			outParcels.push_back(parcel);
		}
		return true;
	}

	return true;
}

/**
* Recursively subdivision of a parcel using OBB technique
* @param parcel			parcel
* @param areaMean			mean parcel area
* @param areaStd			StdDev of parcel area
* @param splitIrregularity	A normalized value 0-1 indicating how far from the middle point the split line should be.
* @param outParcels		the resulting subdivision
**/
//bool SateParcels::subdivideParcel(const Block & block, Parcel& parcel, float areaMean, float areaStd, float splitIrregularity, std::vector<Parcel> &outParcels) {
//	if (areaMean < 0.01){
//		return true;
//	}
//	float thresholdArea = areaMean;
//	//std::cout <<"areaMean is " <<areaMean << std::endl;
//	//std::cout <<"parcel.parcelContour.area() is "<< parcel.parcelContour.area() << std::endl;
//	// multiple conditions small parcels, median parcels, big parcels
//	//if (areaMean < 1000){
//	//	if (parcel.parcelContour.area() < thresholdArea * 1.6) {
//	//		outParcels.push_back(parcel);
//	//		return true;
//	//	}
//	//}
//	//else{
//	//	if (parcel.parcelContour.area() <= thresholdArea * 1.6) {
//	//		outParcels.push_back(parcel);
//	//		return true;
//	//	}
//	//}
//
//	if (areaMean < 500){
//				if (parcel.parcelContour.area() < thresholdArea * 1.8) {
//					outParcels.push_back(parcel);
//					return true;
//				}
//	}
//	if (areaMean > 3000){
//		if (parcel.parcelContour.area() < thresholdArea * 2.0) {
//			outParcels.push_back(parcel);
//			return true;
//		}
//	}
//	else{
//		if (parcel.parcelContour.area() <= thresholdArea * 1.5) {
//			outParcels.push_back(parcel);
//			return true;
//		}
//	}
//
//	// compute OBB
//	QVector3D obbSize;
//	QMatrix4x4 obbMat;
//	parcel.parcelContour.getMyOBB(obbSize, obbMat);
//
//	// compute split line passing through center of OBB TODO (+/- irregularity)
//	//		and with direction parallel/perpendicular to OBB main axis
//	QVector3D slEndPoint;
//	QVector3D dirVectorInit, dirVector, dirVectorOrthogonal;
//	QVector3D midPt(0.0f, 0.0f, 0.0f);
//	QVector3D auxPt(1.0f, 0.0f, 0.0f);
//	QVector3D midPtNoise(0.0f, 0.0f, 0.0f);
//	std::vector<QVector3D> splitLine;
//
//	midPt = midPt*obbMat;
//
//	dirVectorInit = (auxPt*obbMat - midPt);
//	dirVectorInit.normalize();
//	if (obbSize.x() > obbSize.y()) {
//		dirVector.setX(-dirVectorInit.y());
//		dirVector.setY(dirVectorInit.x());
//	}
//	else {
//		dirVector = dirVectorInit;
//	}
//
//	// 11/8/2016: comment out the following lines in order to remove the randomness for subdividing parcels
//	//midPtNoise.setX(splitIrregularity * Util::genRand(-2, 2));
//	//midPtNoise.setY(splitIrregularity * Util::genRand(-2, 2));
//	//midPt = midPt + midPtNoise;
//
//	slEndPoint = midPt + 10000.0f*dirVector;
//	splitLine.push_back(slEndPoint);
//	slEndPoint = midPt - 10000.0f*dirVector;
//	splitLine.push_back(slEndPoint);
//
//	// split parcel with line and obtain two new parcels
//	Polygon3D pgon1, pgon2;
//
//	float kDistTol = 0.01f;
//
//	std::vector<Polygon3D> pgons;
//
//	// Use the simple splitting because this is fast
//	if (parcel.parcelContour.splitMeWithPolyline(splitLine, pgon1.contour, pgon2.contour)) {
//		Parcel parcel1;
//		Parcel parcel2;
//
//		parcel1.parcelContour = pgon1;
//		parcel2.parcelContour = pgon2;
//
//		// call recursive function for both parcels
//		subdivideParcel(block, parcel1, areaMean, areaStd, splitIrregularity, outParcels);
//		subdivideParcel(block, parcel2, areaMean, areaStd, splitIrregularity, outParcels);
//	} else {
//		//std::cout << "split point 1";
//		//std::cout << "( " << splitLine.at(0).x() << ",";
//		//std::cout << splitLine.at(0).y() << ")" << std::endl;
//		//std::cout << "split point 2";
//		//std::cout << "( " << splitLine.at(1).x() << ",";
//		//std::cout << splitLine.at(1).y() << ")" << std::endl;
//		// If the simple splitting fails, try CGAL version which is slow
//		if (parcel.parcelContour.split(splitLine, pgons)) {
//			for (int i = 0; i < pgons.size(); ++i) {
//				Parcel parcel;
//				parcel.parcelContour = pgons[i];
//
//				subdivideParcel(block, parcel, areaMean, areaStd, splitIrregularity, outParcels);
//			}
//		} else {
//			//parcel.isPark = true;
//			outParcels.push_back(parcel);
//		}
//		return true;
//	}
//	return true;
//}

void SateParcels::saveParcelImage(const Polygon3D& contour, const std::vector<Parcel> parcels, int index){
	std::vector<cv::Point2f>contour_cv;
	for (int i = 0; i < contour.size(); i++){
		contour_cv.push_back(cv::Point2f(contour.contour[i].x(), contour.contour[i].y()));
		//std::cout << "point ( " << contour.contour[i].x() << "," << contour.contour[i].y() <<")"<< std::endl;
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
	//	cv::line(img, cv::Point(x1, img.rows - y1), cv::Point(x2, img.rows - y2), cv::Scalar(0, 0, 0), 3);
	//}
	// draw parcels
	for (int i = 0; i < parcels.size(); i++){
		//std::cout << parcels.at(i).parcelContour.size() << std::endl;
		for (int j = 0; j < parcels.at(i).parcelContour.size(); j++) {
			if (parcels.at(i).isPark)
				continue;
			int next = (j + 1) % parcels.at(i).parcelContour.size();
			int x1 = parcels.at(i).parcelContour[j].x() - boundRect.x;
			int y1 = parcels.at(i).parcelContour[j].y() - boundRect.y;
			int x2 = parcels.at(i).parcelContour[next].x() - boundRect.x;
			int y2 = parcels.at(i).parcelContour[next].y() - boundRect.y;
			cv::line(img, cv::Point(x1, img.rows - y1), cv::Point(x2, img.rows - y2), cv::Scalar(0, 0, 0), 3);
		}
	}
	cv::imwrite(QString("output/qt_parcel_" + QString::number(index) + ".png").toUtf8().data(), img);
}

bool SateParcels::valid_block(cv::Mat &src){
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

QString SateParcels::getBlockPath(const Block & block, const cv::Mat& src, const cv::Mat& parcel_src, const cv::Mat& gt_src, const cv::Mat& gt_whole_src, int index, bool bTest){
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
	QFile file_params = QString("output/block_parameter.txt");
	if (!file_params.open(QIODevice::WriteOnly | QIODevice::Append)) {
		std::cerr << "Cannot open file for writing: " << file_params.fileName().toUtf8().constData() << std::endl;
		return QString("empty");
	}
	cv::Rect2f boundRect_ori = cv::boundingRect(cv::Mat(contour_ori));

	float center_x = boundRect_ori.x + 0.5 * boundRect_ori.width;
	float center_y = boundRect_ori.y + 0.5 * boundRect_ori.height;
	QVector2D center_longlat = Util::getLongLatCoord(center_x, center_y);

	QTextStream out_params(&file_params);
	out_params << index << "," << boundRect.x << "," << boundRect.y << "," << boundRect.width << "," << boundRect.height << "," << center_longlat.x() << "," << center_longlat.y() << "\n";
	out_params.flush();
	file_params.close();

	QString filename_out("output/block_" + QString::number(index) + ".png");
	cv::resize(tmp, tmp, cv::Size(boundRect_ori.width, boundRect_ori.height), 0, 0, cv::INTER_NEAREST);
	cv::imwrite(filename_out.toUtf8().data(), tmp);
	// at the same time generating the ground truth block
	if (false){
		cv::Mat gt_src_block = gt_src(boundRect);
		cv::Mat gt_tmp(gt_src_block.size(), CV_8UC3, cv::Scalar(0, 255, 0));
		gt_src_block.copyTo(gt_tmp, mask);
		QString gt_filename_out("output/gt_" + QString::number(index) + ".png");
		cv::resize(gt_tmp, gt_tmp, cv::Size(boundRect_ori.width, boundRect_ori.height), 0, 0, cv::INTER_NEAREST);
		cv::imwrite(gt_filename_out.toUtf8().data(), gt_tmp);
	}
	if (bTest){
		cv::Mat parcel_src_block = parcel_src(boundRect);
		cv::Mat parcel_tmp(parcel_src_block.size(), CV_8UC3, cv::Scalar(0, 255, 0));
		parcel_src_block.copyTo(parcel_tmp, mask);
		QString parcel_filename_out("output/parcel_" + QString::number(index) + ".png");
		cv::imwrite(parcel_filename_out.toUtf8().data(), parcel_tmp);
	}
	if (bTest){
		cv::Mat whole_src_block = gt_whole_src(boundRect);
		cv::Mat whole_tmp(whole_src_block.size(), CV_8UC3, cv::Scalar(0, 255, 0));
		whole_src_block.copyTo(whole_tmp, mask);
		QString whole_filename_out("output/whole_" + QString::number(index) + ".png");
		cv::imwrite(whole_filename_out.toUtf8().data(), whole_tmp);
	}
	return filename_out;
}

void SateParcels::set_parcel_paras(float parcel_mean_area){
	// testing for San Francisco
	//if (parcel_mean_area < 300)
	//	parcel_mean_area = 1.2 * parcel_mean_area;

	G::global()["parcel_area_mean"] = parcel_mean_area;
	G::global()["parcel_area_deviation"] = 0;
	G::global()["parcel_setback_front"] = Util::genRand(2, 2);
	G::global()["parcel_setback_rear"] = Util::genRand(2, 2);
	G::global()["parcel_setback_sides"] = Util::genRand(2, 2);
	G::global()["building_stories_min"] = 2;
	G::global()["building_stories_max"] = 8;
	G::global()["building_min_dimension"] = Util::genRand(1, 1);
}

void SateParcels::remove_roads(cv::Mat &img){
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

float SateParcels::compute_parcel_area(const cv::Mat & src){
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