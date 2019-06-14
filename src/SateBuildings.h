#pragma once

#include "Block.h"

class SateBuildings {
public:
	static bool generateBuildings(VBORenderManager& rendManager, std::vector<Block>& blocks, float correction);
	static bool generateBuilding(VBORenderManager& rendManager, Block& block, Parcel& parcel, int stories);
	static void  saveBldsImage(Block& block, int index);
	static std::vector<std::vector<int>> get_height_info(QString height_tiff);
	static std::vector<std::vector<int>> get_blds_type_info(QString blds_type_tiff);
	static void findCorrespondedBlock(const Block & block, QString filename, int index);
};

