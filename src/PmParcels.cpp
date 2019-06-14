#include "PmParcels.h"
#include "qmatrix4x4.h"
#include "global.h"
#include "Util.h"

bool PmParcels::generateParcels(VBORenderManager& rendManager, std::vector<Block>& blocks) {
	// output block size
	//std::cout << blocks.size() << std::endl;
	for (int bN = 0; bN < blocks.size(); ++bN) {
		if (blocks[bN].isPark) continue;

		for (int cN = 0; cN < blocks[bN].blockContours.size(); ++cN) {
			//output the points of the block
			{
				//for (int j = 0; j < blocks[bN].blockContours.at(0).size(); j++){
				//	std::cout << "block point " << j;
				//	std::cout << "( " << blocks[bN].blockContours.at(0)[j].x() << ",";
				//	std::cout << blocks[bN].blockContours.at(0)[j].y() << ",";
				//	std::cout << blocks[bN].blockContours.at(0)[j].z() << ")" << std::endl;
				//}
			}
			//
			std::vector<Parcel> parcels;
			subdivideBlockIntoParcels(blocks[bN], blocks[bN].blockContours[cN], parcels);
			
			blocks[bN].parcels.insert(blocks[bN].parcels.end(), parcels.begin(), parcels.end());

			{
				//std::cout << "pacels size is "<< blocks[bN].parcels.size() << std::endl;
				//saveParcelImage(blocks[bN].blockContours[cN], blocks[bN].parcels);
			}
		}
	}

	return true;
}

void PmParcels::subdivideBlockIntoParcels(const Block & block, const Polygon3D& contour, std::vector<Parcel>& parcels) {
	// set the initial parcel be the block itself
	Parcel parcel;
	parcel.parcelContour = contour;
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
bool PmParcels::subdivideParcel(const Block & block, Parcel& parcel, float areaMean, float areaStd, float splitIrregularity, std::vector<Parcel> &outParcels) {
	float thresholdArea = std::max(0.0f, Util::genRand(areaMean - areaStd, areaMean + areaStd));

	if (parcel.parcelContour.area() <= thresholdArea * 1.2f) {
		outParcels.push_back(parcel);
		return true;
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
	} else {
		dirVector = dirVectorInit;
	}

	// 11/8/2016: comment out the following lines in order to remove the randomness for subdividing parcels
	//midPtNoise.setX(splitIrregularity * Util::genRand(-2, 2));
	//midPtNoise.setY(splitIrregularity * Util::genRand(-2, 2));
	//midPt = midPt + midPtNoise;

	slEndPoint = midPt + 10000.0f*dirVector;
	splitLine.push_back(slEndPoint);
	slEndPoint = midPt - 10000.0f*dirVector;
	splitLine.push_back(slEndPoint);

	// split parcel with line and obtain two new parcels
	Polygon3D pgon1, pgon2;

	float kDistTol = 0.01f;

	std::vector<Polygon3D> pgons;

	//// Use the simple splitting because this is fast
	//if (parcel.parcelContour.splitMeWithPolyline(splitLine, pgon1.contour, pgon2.contour)) {
	//	Parcel parcel1;
	//	Parcel parcel2;

	//	parcel1.parcelContour = pgon1;
	//	parcel2.parcelContour = pgon2;

	//	// call recursive function for both parcels
	//	subdivideParcel(parcel1, areaMean, areaStd, splitIrregularity, outParcels);
	//	subdivideParcel(parcel2, areaMean, areaStd, splitIrregularity, outParcels);
	//} else {
	//	//std::cout << "split point 1";
	//	//std::cout << "( " << splitLine.at(0).x() << ",";
	//	//std::cout << splitLine.at(0).y() << ")" << std::endl;
	//	//std::cout << "split point 2";
	//	//std::cout << "( " << splitLine.at(1).x() << ",";
	//	//std::cout << splitLine.at(1).y() << ")" << std::endl;
	//	// If the simple splitting fails, try CGAL version which is slow
	//	if (parcel.parcelContour.split(splitLine, pgons)) {
	//		for (int i = 0; i < pgons.size(); ++i) {
	//			Parcel parcel;
	//			parcel.parcelContour = pgons[i];

	//			subdivideParcel(parcel, areaMean, areaStd, splitIrregularity, outParcels);
	//		}
	//	} else {
	//		parcel.isPark = true;
	//		outParcels.push_back(parcel);
	//	}
	//}
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
		std::cout << "CGAL Version" << std::endl;
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

void PmParcels::saveParcelImage(const Polygon3D& contour, const std::vector<Parcel> parcels){

	cv::Mat img(120, 120, CV_8UC3, cv::Scalar(255, 255, 255));
	// draw block
	for (int i = 0; i < contour.size(); ++i) {
		int next = (i + 1) % contour.size();
		int x1 = contour.contour[i].x() + 60;
		int y1 = contour.contour[i].y() + 60;
		int x2 = contour.contour[next].x() + 60;
		int y2 = contour.contour[next].y() + 60;
		//if (i == 0){
		//	cv::circle(img, cv::Point(x1, img.rows - y1), 5, cv::Scalar(255, 255, 0));
		//}
		//if (i == 1){
		//	cv::circle(img, cv::Point(x1, img.rows - y1), 5, cv::Scalar(0, 0, 255));
		//}
		//if (i == 6){
		//	cv::circle(img, cv::Point(x1, img.rows - y1), 5, cv::Scalar(0, 255, 0));
		//}
		cv::line(img, cv::Point(x1, img.rows - y1), cv::Point(x2, img.rows - y2), cv::Scalar(0, 0, 0), 3);
	}
	// draw parcels
	for (int i = 0; i < parcels.size(); i++){
		//std::cout << parcels.at(i).parcelContour.size() << std::endl;
		for (int j = 0; j < parcels.at(i).parcelContour.size(); j++) {
			if (parcels.at(i).isPark)
				continue;
			int next = (j + 1) % parcels.at(i).parcelContour.size();
			int x1 = parcels.at(i).parcelContour[j].x() + 60;
			int y1 = parcels.at(i).parcelContour[j].y() + 60;
			int x2 = parcels.at(i).parcelContour[next].x() + 60;
			int y2 = parcels.at(i).parcelContour[next].y() + 60;
			cv::line(img, cv::Point(x1, img.rows - y1), cv::Point(x2, img.rows - y2), cv::Scalar(255, 0, 0), 3);
		}
	}
	cv::imwrite("output/parcel.png", img);
}

