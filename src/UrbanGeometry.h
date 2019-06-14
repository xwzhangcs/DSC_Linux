#pragma once

#include "glew.h"

#include "VBORenderManager.h"
#include "RoadGraph.h"
#include "BlockSet.h"
#include <glm/glm.hpp>
#include "Building.h"
#include "Util.h"

class MainWindow;

class UrbanGeometry {
public:
	static int width;
	static int depth;
	static MainWindow* mainWin;
	static RoadGraph roads;
	static BlockSet blocks;
	static glm::vec2 minBound;
	static glm::vec2 maxBound;
	static Polygon2D zone;
	static std::vector<Block> myBlocks;
	static VBORenderManager myRenderManager;

	static float minBuildingError;
	static ShapefileStats truthStats;

public:
	UrbanGeometry(MainWindow* mainWin);

	void generateRoads();
	void generateBlocks();
	void generateParcels();
	void sateGetBlocks();
	void sateGetParcels(float boundary_v1, float boundary_v2, int testbN, bool bTest);
	void sateGetParcelsAndBuildings();
	void sateGetBuildings(float correction);
	void generateBuildings();
	void generateVegetation();
	float generateAll(bool updateGeometry);
	bool generateScenarios(int numScenarios, const QString& output_dir, bool useSimulator, const QString& flood_simulator_dir, const std::pair<float, float>& avenueSegmentLengthRange, const std::pair<float, float>& roadBaseOrientationRange, const std::pair<float, float>& roadCurvatureRange, const std::pair<float, float>& majorRoadWidthRange, const std::pair<float, float>& minorRoadWidthRange, const std::pair<float, float>& parkRatioRange, const std::pair<float, float>& parcelAreaRange, float parcelAreaDev, const std::pair<float, float>& setbackFrontRange, const std::pair<float, float>& setbackRearRange, const std::pair<float, float>& setbackSideRange, const std::pair<int, int>& numStoriesRange, const std::pair<int, int>& minBuildingDimRange, bool useBuildingCoverage, const std::pair<float, float>& buildingCoverageRange, bool generate_building_footprints_image, int building_footprints_image_size);

	bool generateToolBlocks(int numScenarios, const QString& output_dir, const QString& batch_num, const std::pair<float, float>& blockWidthRange, const std::pair<float, float>& blockHeightRange, const std::pair<float, float>& parkRatioRange, const std::pair<float, float>& parcelAreaRange, float parcelAreaDev, const std::pair<float, float>& setbackFrontRange, const std::pair<float, float>& setbackRearRange, const std::pair<float, float>& setbackSideRange, const std::pair<int, int>& numStoriesRange, const std::pair<int, int>& minBuildingDimRange, int building_footprints_image_size);

	void generateToolImageOBB(const float parcel_area, const float image_width, const float image_height, const QString& des_dir);

	void generateToolAll(const QString & filename, int image_size);

	void update(VBORenderManager& vboRenderManager);

	void loadZone(const std::string& filename);
	void loadTerrain(const std::string& filename);
	void loadRoads(const std::string& filename);
	void loadOSMRoads(const QString& filename);
	void saveRoads(const std::string &filename);
	void loadParcels(const std::string& filename);
	void saveParcels(const std::string& filename);
	void loadBuildings(const std::string& filename);
	void saveBuildings(const std::string& filename);

	void clear();

	float compute_mean_parcel_area(const QString& src_image_filename);
	float compute_min_dimension_bld(const QString& src_image_filename);

	static float getBuildingTotalArea();
	// SVF computation
	void getCoordsForSvf(std::vector<std::vector<glm::vec3>>& points_set);
	void getCoordsForHeight(std::vector<float>& blds_height, std::vector<std::vector<glm::vec3>>& blds_contour);
};
