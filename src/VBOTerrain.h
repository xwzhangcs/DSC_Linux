#pragma once

#include "GL/glew.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <glm/glm.hpp>
#include <QString>

class VBORenderManager;

class VBOTerrain {
private:
	VBORenderManager* rendManager;
	GLuint texId;

	GLuint elementbuffer;
	GLuint vbo;
	GLuint indicesCount;
	GLuint grassText;

	bool initialized;			// flag to check if initialization is done
	glm::vec2 size;

public:
	cv::Mat layerData;			// the grid that stores the terrain elevation data

public:
	VBOTerrain();

	void init(VBORenderManager* rendManager, const glm::vec2& size);

	void render();
	void updateGaussian(float u, float v, float height, float rad_ratio);
	void excavate(float u, float v, float height, float rad_ratio);
	void smoothTerrain();
	float getTerrainHeight(float u, float v);
	void loadTerrain(const QString& fileName);
	void setTerrain(const cv::Mat& mat);
	void saveTerrain(const QString& fileName);

private:
	void updateTexture();
};
