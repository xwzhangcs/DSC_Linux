#pragma once

#include <vector>
#include <Qvector2D>
#include <QHash>
#include <QVariant>
#include <QColor>
#include <boost/shared_ptr.hpp>
#include "Polyline3D.h"
#include "Polyline2D.h"

class RoadEdge {
public:
	static enum { TYPE_OTHERS = 0, TYPE_STREET = 1, TYPE_AVENUE = 2, TYPE_SECONDARY = 3, TYPE_MOTOR = 4 };
	static enum { EIGEN_TYPE_NONE = 0, EIGEN_TYPE_MAJOR = 1, EIGEN_TYPE_MINOR = 2, EIGEN_TYPE_BOTH = 3 };


public:
	int type;
	int lanes;
	bool oneWay;
	bool link;
	bool roundabout;
	Polyline2D polyline;
	Polyline3D polyline3D;

	bool valid;			// if this edge is valid
	int eigenType;
	bool new_edge;

public:
	RoadEdge(unsigned int type, unsigned int lanes, bool oneWay = false, bool link = false, bool roundabout = false);
	~RoadEdge();
	
	float getLength();

	void addPoint(const QVector2D &pt);
	float getWidth(float widthPerLane);
	float getHalfWidth(float widthPerLane);

	bool containsPoint(const QVector2D &pos, float widthPerLane, int& index);
};

typedef boost::shared_ptr<RoadEdge> RoadEdgePtr;
