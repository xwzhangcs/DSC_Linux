#pragma once

#include "Block.h"

class PmBuildings {
public:
	static bool generateBuildings(VBORenderManager& rendManager, std::vector<Block>& blocks);
	static bool generateBuilding(VBORenderManager& rendManager, Block& block, Parcel& parcel);
	static void  saveBldsImage(Block& block, int index);
	static void findCorrespondedBlock(const Block & block, QString filename, int index);
};

