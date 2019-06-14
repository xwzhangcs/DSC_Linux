#pragma once

#include "Block.h"

class PmParcels {
public:
	static bool generateParcels(VBORenderManager& rendManager, std::vector<Block>& blocks);

private:
	static void subdivideBlockIntoParcels(const Block & block, const Polygon3D& contour, std::vector<Parcel>& parcels);
	static bool subdivideParcel(const Block & block, Parcel& parcel, float areaMean, float areaVar, float splitIrregularity, std::vector<Parcel>& outParcels);
	static void  saveParcelImage(const Polygon3D& contour, const std::vector<Parcel> parcels);
};
