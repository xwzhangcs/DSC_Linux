#include "Util.h"
#include "RoadEdge.h"

RoadEdge::RoadEdge(unsigned int type, unsigned int lanes, bool oneWay, bool link, bool roundabout) {
	this->type = type;
	this->lanes = lanes;
	this->oneWay = oneWay;
	this->link = link;
	this->roundabout = roundabout;
	this->eigenType = EIGEN_TYPE_NONE;
	this->valid = true;
	this->new_edge = false;
}

RoadEdge::~RoadEdge() {
}

float RoadEdge::getLength() {
	return polyline.length();
}

/**
 * Add a point to the polyline of the road segment.
 *
 * @param pt		new point to be added
 */
void RoadEdge::addPoint(const QVector2D &pt) {
	polyline.push_back(pt);
}

float RoadEdge::getWidth(float widthPerLane) {
	return getHalfWidth(widthPerLane) * 2.0f;
}

float RoadEdge::getHalfWidth(float widthPerLane) {
	return lanes * widthPerLane;
}

/**
 * Check whether the point resides in this road segment.
 * Return true if so, false otherwise.
 *
 * @param pos		the point
 * @return			true if the point is inside the road segment, false otherwise
 */
bool RoadEdge::containsPoint(const QVector2D &pos, float widthPerLane, int& index) {
	for (int i = 0; i < polyline.size() - 1; i++) {
		QVector2D p0(polyline[i].x(), polyline[i].y());
		QVector2D p1(polyline[i + 1].x(), polyline[i + 1].y());

		if (Util::pointSegmentDistanceXY(p0, p1, pos) <= getWidth(widthPerLane)) {
			// find the closest point
			float min_dist = std::numeric_limits<float>::max();
			for (int j = 0; j < polyline.size(); j++) {
				float dist = (polyline[j] - pos).length();
				if (dist < min_dist) {
					min_dist = dist;
					index = j;
				}
			}

			return true;
		}
	}

	return false;
}