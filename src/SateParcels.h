#pragma once

#include "Block.h"
#include "caffe_wrapper.h"
#include "Regression.h"

class SateParcels {

public:
	static bool generateParcels(VBORenderManager& rendManager, std::vector<Block>& blocks, float boundary_v1, float boundary_v2, int testbN, bool bTest);
	static QString getBlockPath(const Block & block, const cv::Mat& src, const cv::Mat& parcel_src, const cv::Mat& gt_src, const cv::Mat& gt_whole_src, int index, bool bTest);
	static void set_parcel_paras(float parcel_mean_area);
	static void remove_roads(cv::Mat &img);
	static bool valid_block(cv::Mat &src);
	static float compute_parcel_area(const cv::Mat & src);

private:
	static void subdivideBlockIntoParcels(const Block & block, const Polygon3D& contour, std::vector<Parcel>& parcels);
	static bool subdivideParcel(const Block & block, Parcel& parcel, float areaMean, float areaVar, float splitIrregularity, std::vector<Parcel>& outParcels);
	static void  saveParcelImage(const Polygon3D& contour, const std::vector<Parcel> parcels, int index);
};
