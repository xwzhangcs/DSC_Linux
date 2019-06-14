#include "PMRoadGenerator.h"
#include <QTest>
#include <boost/graph/planar_face_traversal.hpp>
#include <boost/graph/boyer_myrvold_planar_test.hpp>
#include "global.h"
#include "Util.h"
#include "GraphUtil.h"
#include <assert.h>
#include "Util.h"

void PMRoadGenerator::generateRoadNetwork() {
	std::list<RoadVertexDesc> seeds;
	std::vector<std::pair<QVector2D, float>> regular_elements;

	float segment_length = G::getFloat("avenueAvgSegmentLength");
	float base_orientation = G::getFloat("road_base_orientation") / 180.0 * M_PI;
	float curvature = G::getFloat("road_curvature");
	bool use_elevation = G::getBool("use_elevation_for_road_generation");

	// generate a central road that does not contain any crossing
	while (true) {
		bool crossed = false;
		roads.clear();
		seeds.clear();

		// make roads along the boundary of the area
		generateRoadsAtBoundary();

		// generate a central road
		RoadVertexPtr v0 = RoadVertexPtr(new RoadVertex(QVector2D(0, 0)));
		RoadVertexDesc v0_desc = GraphUtil::addVertex(roads, v0);
		roads.graph[v0_desc]->eigenType = RoadVertex::EIGEN_TYPE_MAJOR;
		seeds.push_back(v0_desc);

		if (!growRoads(base_orientation, v0_desc, curvature, segment_length, RoadVertex::EIGEN_TYPE_MAJOR, regular_elements, seeds)) {
			crossed = true;
		}
		if (!growRoads(base_orientation, v0_desc, curvature, -segment_length, RoadVertex::EIGEN_TYPE_MAJOR, regular_elements, seeds)) {
			crossed = true;
		}
		if (!crossed) break;
	}

	// clear teh flag
	RoadEdgeIter ei, eend;
	for (boost::tie(ei, eend) = boost::edges(roads.graph); ei != eend; ++ei) {
		roads.graph[*ei]->new_edge = false;
	}
	saveRoadImage(roads, "initial_roads.png");

	// setup the tensor field
	cv::Mat tensor;
	setupTensor(targetArea, regular_elements, tensor, use_elevation);
	saveTensorImage(tensor, "tensor.png");

	// generate roads
	generateRoadsByTensor(tensor, segment_length, segment_length * 0.7, seeds);

	// remove dangling edges
	removeDanglingEdges();
}

void PMRoadGenerator::generateRoadsAtBoundary() {
	RoadVertexDesc first_desc;
	RoadVertexDesc cur_desc;
	for (int i = 0; i < targetArea.size(); ++i) {
		int next = (i + 1) % targetArea.size();

		// create an intersection
		if (i == 0) {
			RoadVertexPtr v = RoadVertexPtr(new RoadVertex(targetArea[i]));
			cur_desc = GraphUtil::addVertex(roads, v);
			first_desc = cur_desc;
		}

		RoadVertexDesc next_desc;
		if (next == 0) {
			next_desc = first_desc;
		}
		else {
			RoadVertexPtr v = RoadVertexPtr(new RoadVertex(targetArea[next]));
			next_desc = GraphUtil::addVertex(roads, v);
		}

		// add edge
		RoadEdgePtr e = RoadEdgePtr(new RoadEdge(RoadEdge::TYPE_STREET, 1));
		e->polyline.push_back(roads.graph[cur_desc]->pt);
		e->polyline.push_back(roads.graph[next_desc]->pt);
		GraphUtil::addEdge(roads, cur_desc, next_desc, e);

		cur_desc = next_desc;
	}
}

/**
* Generate a road segment starting from a specified point with specified angle
*
* @param angle						angle [rad]
* @param pt						starting point
* @param curvature					curvature
* @param segment_length			segment length
* @param regular_elements [OUT]	control elements for tensor field
* @param seeds [OUT]				seed list
* @return							true if no crossing, false otherwise
*/
bool PMRoadGenerator::growRoads(float angle, RoadVertexDesc srcDesc, float curvature, float segment_length, int type, std::vector<std::pair<QVector2D, float>>& regular_elements, std::list<RoadVertexDesc>& seeds) {
	int num_steps = 5;

	QVector2D pt = roads.graph[srcDesc]->pt;

	bool loop = true;
	while (loop) {
		// randomly distribute the curvature
		std::vector<float> rotates;
		float total = 0.0f;
		for (int i = 0; i < num_steps; ++i) {
			float r = rand() % 100;
			rotates.push_back(r);
			total += r;
		}
		for (int i = 0; i < num_steps; ++i) {
			rotates[i] = rotates[i] / total * curvature * num_steps;
		}

		// decide the orientation of the road
		int rotate_dir = rand() % 2 == 0 ? 1 : -1;

		// generate 5 steps of road segments
		for (int i = 0; i < num_steps; ++i) {
			// if it is ouside the target area, stop  growing
			if (!targetArea.contains(pt)) return true;

			angle += rotates[i] * rotate_dir;
			QVector2D pt2 = pt + QVector2D(cosf(angle), sinf(angle)) * (segment_length + Util::genRand(-1.0, 1.0));

			RoadEdgeDesc closestEdge;
			QVector2D intPt;
			if (GraphUtil::isIntersect(roads, pt, pt2, closestEdge, intPt)) {
				// if the road crosses the edge that is currently being generated, cancel the generation
				if (roads.graph[closestEdge]->new_edge) return false;

				// connect to the existing edge
				RoadVertexDesc tgtDesc = GraphUtil::splitEdge(roads, closestEdge, intPt);
				roads.graph[tgtDesc]->eigenType |= type;

				// generate an edge
				RoadEdgePtr new_edge = RoadEdgePtr(new RoadEdge(RoadEdge::TYPE_AVENUE, 1));
				new_edge->addPoint(pt);
				new_edge->addPoint(intPt);
				new_edge->eigenType = type;
				new_edge->new_edge = true;
				GraphUtil::addEdge(roads, srcDesc, tgtDesc, new_edge);

				return true;
			}

			// add a vertex
			RoadVertexPtr v = RoadVertexPtr(new RoadVertex(pt2));
			RoadVertexDesc tgtDesc = GraphUtil::addVertex(roads, v);
			roads.graph[tgtDesc]->eigenType = type;

			// add this vertex to the seeds
			seeds.push_back(tgtDesc);

			// add an edge
			RoadEdgePtr new_edge = RoadEdgePtr(new RoadEdge(RoadEdge::TYPE_AVENUE, 1));
			new_edge->addPoint(pt);
			new_edge->addPoint(pt2);
			new_edge->new_edge = true;
			GraphUtil::addEdge(roads, srcDesc, tgtDesc, new_edge);

			regular_elements.push_back(std::make_pair(pt2, angle));

			pt = pt2;
			srcDesc = tgtDesc;
		}
	}

	return true;
}

#if 1
void PMRoadGenerator::setupTensor(const Polygon2D& targetArea, const std::vector<std::pair<QVector2D, float>>& regular_elements, cv::Mat& tensor, bool use_elevation) {
	BBox bbox = targetArea.envelope();
	tensor = cv::Mat(bbox.dy() + 1, bbox.dx() + 1, CV_32F);

	cv::Mat slope_mag = cv::Mat(tensor.size(), CV_32F);
	cv::Mat slope_dir = cv::Mat(tensor.size(), CV_32F);
	if (use_elevation) {
		for (int r = 0; r < slope_mag.rows; ++r) {
			for (int c = 0; c < slope_mag.cols; ++c) {
				int r1 = r - 5;
				if (r1 < 0) r1 = 0;
				int r2 = r + 5;
				if (r2 >= vboRenderManager->vboTerrain.layerData.rows) r2 = vboRenderManager->vboTerrain.layerData.rows - 1;

				int c1 = c - 5;
				if (c1 < 0) c1 = 0;
				int c2 = c + 5;
				if (c2 >= vboRenderManager->vboTerrain.layerData.cols) c2 = vboRenderManager->vboTerrain.layerData.cols - 1;

				int rr = r;
				if (rr >= vboRenderManager->vboTerrain.layerData.rows) rr = vboRenderManager->vboTerrain.layerData.rows - 1;
				int cc = c;
				if (cc >= vboRenderManager->vboTerrain.layerData.cols) cc = vboRenderManager->vboTerrain.layerData.cols - 1;

				float slope_x = (vboRenderManager->vboTerrain.layerData.at<float>(rr, c2) - vboRenderManager->vboTerrain.layerData.at<float>(rr, c1)) * 0.5;
				float slope_y = (vboRenderManager->vboTerrain.layerData.at<float>(r2, cc) - vboRenderManager->vboTerrain.layerData.at<float>(r1, cc)) * 0.5;
				float magnitude = sqrtf(slope_x * slope_x + slope_y * slope_y);
				slope_mag.at<float>(r, c) = magnitude;
				if (magnitude > 0) {
					float angle = atan2f(slope_y, slope_x);
					slope_dir.at<float>(r, c) = angle;
				}
				else {
					slope_dir.at<float>(r, c) = 0;
				}
			}
		}

		saveTensorImage(slope_dir, "tensor_elevation.png");
	}

	for (int r = 0; r < tensor.rows; ++r) {
		for (int c = 0; c < tensor.cols; ++c) {
			int x = c + bbox.minPt.x();
			int y = r + bbox.minPt.y();

			double total_angle = 0.0;
			double total_weight = 0.0;
			for (int k = 0; k < regular_elements.size(); ++k) {
				float dist = (QVector2D(x, y) - regular_elements[k].first).length();

				double angle = regular_elements[k].second;
				double weight = exp(-dist / 10);
				total_angle += angle * weight;
				total_weight += weight;
			}

			float avg_angle = total_angle / total_weight;
			tensor.at<float>(r, c) = avg_angle;

			if (use_elevation && slope_mag.at<float>(r, c) > 0.5) {
				float w1 = 1.0f;
				float w2 = slope_mag.at<float>(r, c) * 20;
				float slope_angle = slope_dir.at<float>(r, c);
				slope_angle = normalize_angle(slope_angle, tensor.at<float>(r, c));

				tensor.at<float>(r, c) = (tensor.at<float>(r, c) * w1 + slope_angle * w2) / (w1 + w2);
			}
		}
	}
}
#endif

#if 0
void PMRoadGenerator::setupTensor(const Polygon2D& targetArea, const std::vector<std::pair<QVector2D, float>>& regular_elements, cv::Mat& tensor) {
	BBox bbox = targetArea.envelope();
	tensor = cv::Mat(bbox.dy() + 1, bbox.dx() + 1, CV_32F);

	for (int r = 0; r < tensor.rows; ++r) {
		for (int c = 0; c < tensor.cols; ++c) {
			int x = c + bbox.minPt.x();
			int y = r + bbox.minPt.y();

			double min_dist = std::numeric_limits<double>::max();
			double angle;
			for (int k = 0; k < regular_elements.size(); ++k) {
				double dist = (QVector2D(x, y) - regular_elements[k].first).length();
				if (dist < min_dist) {
					min_dist = dist;
					angle = regular_elements[k].second;
				}
			}

			tensor.at<float>(r, c) = angle;
		}
	}
}
#endif

/**
* Generate roads baased on the tensor field
*
* @param tensor			tensor field
* @param segment_length	segment length
* @param near_threshold	near threshold
* @param vertices [OUT]	interesections
* @param edges	[OUT]	road edges
*/
void PMRoadGenerator::generateRoadsByTensor(const cv::Mat& tensor, float segment_length, float near_threshold, std::list<RoadVertexDesc>& seeds) {
	int count = 0;
	while (!seeds.empty()) {
		RoadVertexDesc desc = seeds.front();
		seeds.pop_front();

		if (roads.graph[desc]->eigenType == RoadVertex::EIGEN_TYPE_NONE) {
			std::cout << "ERROR: eigenType is unknown!!!" << std::endl;
		}

		// skip this seed if it is outside the target area
		if (!targetArea.contains(roads.graph[desc]->pt)) continue;

		// select the type of the eigen vector
		int eigen_type;
		if (roads.graph[desc]->eigenType == RoadVertex::EIGEN_TYPE_MAJOR) {
			eigen_type = RoadVertex::EIGEN_TYPE_MINOR;
		}
		else if (roads.graph[desc]->eigenType == RoadVertex::EIGEN_TYPE_MINOR) {
			eigen_type = RoadVertex::EIGEN_TYPE_MAJOR;
		}
		else {
			// do not generate a road if there are already road segments of major and minor eigen vectors
			continue;
		}

		// check if there is any intersection around here
		bool foundNearVertex = false;
		RoadVertexIter vi, vend;
		for (boost::tie(vi, vend) = boost::vertices(roads.graph); vi != vend; ++vi) {
			// skip if it is itself
			if (*vi == desc) continue;

			// skip of the type of eigen vector is different
			if (!(roads.graph[*vi]->eigenType & eigen_type)) continue;

			float dist = (roads.graph[*vi]->pt - roads.graph[desc]->pt).length();
			if (dist < near_threshold) {
				foundNearVertex = true;
				break;
			}
		}

		//std::cout << count << ": (" << roads.graph[desc]->pt.x() << ", " << roads.graph[desc]->pt.y() << ") " << type << (foundNearVertex ? " canceled" : "") << std::endl;

		if (!foundNearVertex) {
			generateRoadByTensor(tensor, segment_length, near_threshold, desc, (count == 0 ? RoadEdge::TYPE_AVENUE : RoadEdge::TYPE_STREET), eigen_type, seeds);
			generateRoadByTensor(tensor, -segment_length, near_threshold, desc, (count == 0 ? RoadEdge::TYPE_AVENUE : RoadEdge::TYPE_STREET), eigen_type, seeds);
		}

		/*
		QString name = QString("road_images/road_%1.png").arg(count);
		saveRoadImage(roads, name.toUtf8().constData());
		*/

		count++;
		if (count > 1000) break;
	}
}

/**
* Generate a road segment from the specified point based on the tensor field
*
* @param tensor			tensor field
* @param segment_length	segment length
* @param near_threshold	near threshold
* @param pt				starting point
* @param road_type		Major or minor road
* @param eigen_type		1 -- major eigen vector / 2 -- minor eigen vector
* @param seeds [OUT]	seed list
*/
void PMRoadGenerator::generateRoadByTensor(const cv::Mat& tensor, float segment_length, float near_threshold, RoadVertexDesc srcDesc, int road_type, int eigen_type, std::list<RoadVertexDesc>& seeds) {
	QVector2D pt = roads.graph[srcDesc]->pt;

	RoadVertexDesc tgtDesc;

	while (true) {
		int result = generateRoadSegmentByTensor(tensor, segment_length, near_threshold, srcDesc, tgtDesc, road_type, eigen_type);
		if (result == 1) {	// outside the target area
			break;
		}
		else if (result == 2) {	// corssed the existing edge
			break;
		}
		else {
			// check if there is any intersection around here
			bool foundNearVertex = false;
			RoadVertexIter vi, vend;
			for (boost::tie(vi, vend) = boost::vertices(roads.graph); vi != vend; ++vi) {
				if (*vi == tgtDesc) continue;

				// skip the intersections that are currently being generated
				if (roads.graph[*vi]->new_vertex) continue;

				// skip if the type of eigen vector is different
				if (!(roads.graph[*vi]->eigenType & eigen_type)) continue;

				float dist = (roads.graph[*vi]->pt - roads.graph[tgtDesc]->pt).length();
				if (dist < near_threshold) {
					foundNearVertex = true;
					break;
				}
			}

			if (foundNearVertex) break;
		}

		seeds.push_back(tgtDesc);

		srcDesc = tgtDesc;
	}

	// clear the flag
	RoadVertexIter vi, vend;
	for (boost::tie(vi, vend) = boost::vertices(roads.graph); vi != vend; ++vi) {
		roads.graph[*vi]->new_vertex = false;
	}
}

/**
* Generate a road segment from the specified point based on the tensor field.
*
* @param tensor				tensor field
* @param segment_length		segment length
* @param near_threshold		near threshold
* @param srcDesc			src vertex desc
* @param tgtDesc [OUT]		tgt vertex desc
* @param eigen_type			1 -- major eigen vector / 2 -- minor eigen vector
* @return					0 -- done without any problem / 1 -- outside the target area / 2 -- crossed the existing edge
*/
int PMRoadGenerator::generateRoadSegmentByTensor(const cv::Mat& tensor, float segment_length, float near_threshold, RoadVertexDesc srcDesc, RoadVertexDesc& tgtDesc, int road_type, int eigen_type) {
	int num_step = 5;
	float step_length = (segment_length + Util::genRand(-1.0, 1.0)) / num_step;

	BBox bbox = targetArea.envelope();

	QVector2D pt = roads.graph[srcDesc]->pt;
	RoadEdgePtr new_edge = RoadEdgePtr(new RoadEdge(road_type, 1));
	new_edge->addPoint(pt);

	for (int i = 0; i < num_step; ++i) {
		// stop if it is outside the targert area
		if (!targetArea.contains(pt)) {
			return 1;
		}

		/////////////////////////////////////////////////////////////////////
		// use Runge-Kutta 4 to obtain the next angle
		int c = pt.x() - bbox.minPt.x();
		int r = pt.y() - bbox.minPt.y();
		float angle1 = tensor.at<float>(r, c);
		if (eigen_type == 2) angle1 += M_PI / 2;	// minor eigen vector

		// angle2
		QVector2D pt2 = pt + QVector2D(cosf(angle1), sinf(angle1)) * (step_length * 0.5);
		int c2 = pt2.x() - bbox.minPt.x();
		int r2 = pt2.y() - bbox.minPt.y();
		float angle2 = angle1;
		if (c2 >= 0 && c2 < tensor.cols && r2 >= 0 && r2 < tensor.rows) {
			angle2 = tensor.at<float>(r2, c2);
			if (eigen_type == 2) angle2 += M_PI / 2;	// minor eigen vector
		}

		// angle3
		QVector2D pt3 = pt + QVector2D(cosf(angle2), sinf(angle2)) * (step_length * 0.5);
		int c3 = pt3.x() - bbox.minPt.x();
		int r3 = pt3.y() - bbox.minPt.y();
		float angle3 = angle2;
		if (c3 >= 0 && c3 < tensor.cols && r3 >= 0 && r3 < tensor.rows) {
			angle3 = tensor.at<float>(r3, c3);
			if (eigen_type == 2) angle3 += M_PI / 2;	// minor eigen vector
		}

		// angle4
		QVector2D pt4 = pt + QVector2D(cosf(angle3), sinf(angle3)) * step_length;
		int c4 = pt4.x() - bbox.minPt.x();
		int r4 = pt4.y() - bbox.minPt.y();
		float angle4 = angle3;
		if (c4 >= 0 && c4 < tensor.cols && r4 >= 0 && r4 < tensor.rows) {
			angle4 = tensor.at<float>(r4, c4);
			if (eigen_type == 2) angle4 += M_PI / 2;	// minor eigen vector
		}

		// compute the angle by RK4
		float angle = angle1 / 6.0 + angle2 / 3.0 + angle3 / 3.0 + angle4 / 6.0;

		// next point
		QVector2D next_pt = pt + QVector2D(cosf(angle), sinf(angle)) * step_length;

		// compute the intersection
		RoadEdgeDesc nearestEdgeDesc;
		QVector2D intPt;
		if (GraphUtil::isIntersect(roads, pt, next_pt, nearestEdgeDesc, intPt)) {
			int edgeEigenType = roads.graph[nearestEdgeDesc]->eigenType;

			// connect the existing edge
			tgtDesc = GraphUtil::splitEdge(roads, nearestEdgeDesc, intPt);
			intPt = roads.graph[tgtDesc]->pt;
			roads.graph[tgtDesc]->eigenType |= eigen_type;
			roads.graph[tgtDesc]->eigenType |= edgeEigenType;
			roads.graph[tgtDesc]->new_vertex = true;

			new_edge->addPoint(intPt);

			// create an edge
			new_edge->eigenType = eigen_type;
			GraphUtil::addEdge(roads, srcDesc, tgtDesc, new_edge);

			// restart the edge from the intersection
			srcDesc = tgtDesc;
			pt = intPt;
			new_edge = RoadEdgePtr(new RoadEdge(road_type, 1));
			new_edge->addPoint(pt);

			// check if there is any intersection around here
			bool foundNearVertex = false;
			RoadVertexIter vi, vend;
			for (boost::tie(vi, vend) = boost::vertices(roads.graph); vi != vend; ++vi) {
				// skip if the intersection is currently being generated
				if (roads.graph[*vi]->new_vertex) continue;

				// skip if the type of the eigen vector is different
				if (!(roads.graph[*vi]->eigenType & eigen_type)) continue;

				float dist = (roads.graph[*vi]->pt - intPt).length();
				if (dist < near_threshold) {
					foundNearVertex = true;
					break;
				}
			}

			if (foundNearVertex) {
				// crossed the existing road segment
				return 2;
			}
		}

		// outside the target area
		if (!targetArea.contains(next_pt)) {
			return 1;
		}

		new_edge->addPoint(next_pt);

		pt = next_pt;
	}

	if (new_edge->getLength() >= 1.0f) {
		RoadVertexPtr v = RoadVertexPtr(new RoadVertex(pt));
		tgtDesc = GraphUtil::addVertex(roads, v);
		roads.graph[tgtDesc]->eigenType = eigen_type;
		roads.graph[tgtDesc]->new_vertex = true;

		// add edge
		new_edge->eigenType = eigen_type;
		GraphUtil::addEdge(roads, srcDesc, tgtDesc, new_edge);
	}
	else {
		tgtDesc = srcDesc;
	}

	return 0;
}

void PMRoadGenerator::removeDanglingEdges() {
	while (true) {
		bool updated = false;

		RoadVertexIter vi, vend;
		for (boost::tie(vi, vend) = boost::vertices(roads.graph); vi != vend; ++vi) {
			int count = 0;
			RoadOutEdgeIter ei, eend;
			for (boost::tie(ei, eend) = boost::out_edges(*vi, roads.graph); ei != eend; ++ei) {
				if (roads.graph[*ei]->valid) count++;
			}

			if (count == 1) {
				roads.graph[*vi]->valid = false;
				RoadOutEdgeIter ei, eend;
				for (boost::tie(ei, eend) = boost::out_edges(*vi, roads.graph); ei != eend; ++ei) {
					roads.graph[*ei]->valid = false;
				}
				updated = true;
			}
		}

		if (!updated) break;
	}
}

void PMRoadGenerator::saveTensorImage(const cv::Mat& tensor, const std::string& filename) {
	cv::Mat result(tensor.size(), CV_8U, cv::Scalar(255));
	for (int r = 0; r < tensor.rows; r += 25) {
		for (int c = 0; c < tensor.cols; c += 25) {
			float angle = tensor.at<float>(r, c);
			int x1 = c - cosf(angle) * 10;
			int y1 = r - sinf(angle) * 10;
			int x2 = x1 + cosf(angle) * 20;
			int y2 = y1 + sinf(angle) * 20;
			cv::line(result, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0), 1, cv::LINE_AA);
		}
	}

	cv::flip(result, result, 0);
	cv::imwrite(filename.c_str(), result);
}

void PMRoadGenerator::saveRoadImage(RoadGraph& roads, const std::string& filename) {
	BBox bbox;
	RoadVertexIter vi, vend;
	for (boost::tie(vi, vend) = boost::vertices(roads.graph); vi != vend; ++vi) {
		if (!roads.graph[*vi]->valid) continue;

		bbox.addPoint(roads.graph[*vi]->pt);
	}

	cv::Mat result((int)(bbox.dy() + 1), (int)(bbox.dx() + 1), CV_8UC3, cv::Scalar(255, 255, 255));

	RoadEdgeIter ei, eend;
	for (boost::tie(ei, eend) = boost::edges(roads.graph); ei != eend; ++ei) {
		if (!roads.graph[*ei]->valid) continue;

		for (int k = 0; k < roads.graph[*ei]->polyline.size() - 1; ++k) {
			int x1 = roads.graph[*ei]->polyline[k].x() - bbox.minPt.x();
			int y1 = roads.graph[*ei]->polyline[k].y() - bbox.minPt.y();
			int x2 = roads.graph[*ei]->polyline[k + 1].x() - bbox.minPt.x();
			int y2 = roads.graph[*ei]->polyline[k + 1].y() - bbox.minPt.y();

			cv::line(result, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 0, 0), 1, cv::LINE_AA);
		}
	}

	for (boost::tie(vi, vend) = boost::vertices(roads.graph); vi != vend; ++vi) {
		if (!roads.graph[*vi]->valid) continue;

		int count = 0;
		RoadOutEdgeIter oi, oend;
		for (boost::tie(oi, oend) = boost::out_edges(*vi, roads.graph); oi != oend; ++oi) {
			if (roads.graph[*oi]->valid) count++;
		}

		if (count == 2) continue;

		int x = roads.graph[*vi]->pt.x() - bbox.minPt.x();
		int y = roads.graph[*vi]->pt.y() - bbox.minPt.x();
		cv::circle(result, cv::Point(x, y), 5, cv::Scalar(255, 0, 0), 1, cv::LINE_AA);

		QString text = QString::number(count);
		cv::putText(result, text.toUtf8().constData(), cv::Point(x, y), cv::FONT_HERSHEY_PLAIN, 2, cv::Scalar(0, 0, 0), 1, cv::LINE_AA);
	}

	cv::flip(result, result, 0);
	cv::imwrite(filename.c_str(), result);
}

/**
 * Reprent the angle such that it is close to the reference angle.
 * For this, we check the original angle, original angle +/- 90 degree, and original angle + 180 degree.
 */
float PMRoadGenerator::normalize_angle(float orig_angle, float ref_angle) {
	float angle1 = normalize_angle(orig_angle);
	float diff1 = diff_angle(angle1, ref_angle);
	float angle2 = normalize_angle(orig_angle + M_PI * 0.5f);
	float diff2 = diff_angle(angle2, ref_angle);
	float angle3 = normalize_angle(orig_angle + M_PI);
	float diff3 = diff_angle(angle3, ref_angle);
	float angle4 = normalize_angle(orig_angle + M_PI * 1.5f);
	float diff4 = diff_angle(angle4, ref_angle);

	if (diff1 < diff2 && diff1 < diff3 && diff1 < diff4) return angle1;
	if (diff2 < diff3 && diff2 < diff4) return angle2;
	if (diff3 < diff4) return angle3;
	return angle4;
}

/**
 * Normalize the angle such that the result is within -90 deg and +90 deg.
 */
float PMRoadGenerator::normalize_angle(float orig_angle) {
	float angle = orig_angle;
	if (angle < 0) {
		int k = 1 - angle / 2.0 / M_PI;
		angle += M_PI * 2 * k;
	}
	int k = angle / 2.0 / M_PI;
	angle = angle - M_PI * 2 * k;
	if (angle > M_PI * 1.5) angle -= M_PI * 2;
	else if (angle > M_PI) angle -= M_PI;
	else if (angle > M_PI * 0.5) angle -= M_PI;

	return angle;
}

/**
 * Find the smallest difference between two angles.
 */
float PMRoadGenerator::diff_angle(float angle1, float angle2) {
	angle1 = normalize_angle(angle1);
	angle2 = normalize_angle(angle2);
	if (angle1 - angle2 >= M_PI * 0.5) {
		return angle2 + M_PI - angle1;
	}
	else if (angle2 - angle1 >= M_PI * 0.5) {
		return angle1 + M_PI - angle2;
	}
	else {
		return fabs(angle1 - angle2);
	}
}