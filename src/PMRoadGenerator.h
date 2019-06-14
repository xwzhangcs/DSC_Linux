#pragma once

#include "Polygon2D.h"
#include "RoadGraph.h"
#include "MainWindow.h"
#include "VBORenderManager.h"

class PMRoadGenerator {
private:
	MainWindow *mainWin;
	RoadGraph &roads;
	VBORenderManager *vboRenderManager;
	Polygon2D targetArea;

public:
	PMRoadGenerator(MainWindow *mainWin, RoadGraph &roads, VBORenderManager *vboRenderManager, const Polygon2D& targetArea) : mainWin(mainWin), roads(roads), vboRenderManager(vboRenderManager), targetArea(targetArea) {}
	~PMRoadGenerator() {}

	void generateRoadNetwork();

private:
	void generateRoadsAtBoundary();
	bool growRoads(float angle, RoadVertexDesc srcDesc, float curvature, float segment_length, int type, std::vector<std::pair<QVector2D, float>>& regular_elements, std::list<RoadVertexDesc>& seeds);
	void setupTensor(const Polygon2D& targetArea, const std::vector<std::pair<QVector2D, float>>& regular_elements, cv::Mat& tensor, bool use_elevation);
	void generateRoadsByTensor(const cv::Mat& tensor, float segment_length, float near_threshold, std::list<RoadVertexDesc>& seeds);
	void generateRoadByTensor(const cv::Mat& tensor, float segment_length, float near_threshold, RoadVertexDesc srcDesc, int road_type, int eigen_type, std::list<RoadVertexDesc>& seeds);
	int generateRoadSegmentByTensor(const cv::Mat& tensor, float segment_length, float near_threshold, RoadVertexDesc srcDesc, RoadVertexDesc& tgtDesc, int road_type, int eigen_type);
	void removeDanglingEdges();
	void saveTensorImage(const cv::Mat& tensor, const std::string& filename);
	void saveRoadImage(RoadGraph& roads, const std::string& filename);
	float normalize_angle(float orig_angle, float ref_angle);
	float normalize_angle(float orig_angle);
	float diff_angle(float angle1, float angle2);
};

