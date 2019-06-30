#pragma once

#include <vector>
#include <QVector2D>
#include <QVector3D>
#include <QHash>
#include <QVariant>
#include <boost/shared_ptr.hpp>

class RoadVertex {

//Liu remove "static" before enum 2019/06/24
public:
	enum { EIGEN_TYPE_NONE = 0, EIGEN_TYPE_MAJOR = 1, EIGEN_TYPE_MINOR = 2, EIGEN_TYPE_BOTH = 3 };

public:
	QVector2D pt;
	QVector3D pt3D;
	bool valid;
	int eigenType;
	bool new_vertex;

public:
	RoadVertex();
	RoadVertex(const QVector2D &pt);

	const QVector2D& getPt() const;
};

typedef boost::shared_ptr<RoadVertex> RoadVertexPtr;
