#include "RoadGraph.h"
#include <QGLWidget>
#include "GraphUtil.h"
#include "Util.h"
#include "global.h"

RoadGraph::RoadGraph() {
}

void RoadGraph::clear() {
	graph.clear();
}

float RoadGraph::getBridgeElevationFromClosestNeighbors(RoadVertexDesc srcDesc, VBORenderManager &renderManager, float seaLevel) {
	QList<RoadVertexDesc> queue;
	queue.push_back(srcDesc);

	QMap<RoadVertexDesc, bool> visited;

	while (!queue.empty()) {
		RoadVertexDesc desc = queue.front();
		queue.pop_front();

		if (visited[desc]) continue;
		visited[desc] = true;

		float z = renderManager.getTerrainHeight(graph[desc]->pt.x(), graph[desc]->pt.y());
		if (z >= seaLevel) {
			return z;
		}

		RoadOutEdgeIter ei, eend;
		for (boost::tie(ei, eend) = boost::out_edges(srcDesc, graph); ei != eend; ++ei) {
			if (!graph[*ei]->valid) continue;

			RoadVertexDesc tgt = boost::target(*ei, graph);
			if (visited[tgt]) continue;
			queue.push_back(tgt);
		}
	}

	return seaLevel;
}

float RoadGraph::getBridgeElevationFromClosestNeighbors(RoadEdgeDesc edge_desc, const Polyline2D &polyline, int index, VBORenderManager &renderManager, float seaLevel) {
	RoadVertexDesc src = boost::source(edge_desc, graph);
	RoadVertexDesc tgt = boost::target(edge_desc, graph);

	/*
	float z = renderManager.getTerrainHeight(polyline[index].x(), polyline[index].y(), true);
	if (z >= seaLevel) {
		return z;
	}
	*/

	// find the one height
	float elevation1 = getBridgeElevationFromClosestNeighbors(src, renderManager, seaLevel);
	float dist1;
	{
		if ((graph[src]->pt - polyline[0]).lengthSquared() < (graph[tgt]->pt - polyline[0]).lengthSquared()) {
			dist1 = polyline.length(index);
		} else {
			dist1 = polyline.length() - polyline.length(index);
		}
	}

	// find another height
	float elevation2 = getBridgeElevationFromClosestNeighbors(tgt, renderManager, seaLevel);
	float dist2;
	{
		if ((graph[src]->pt - polyline[0]).lengthSquared() < (graph[tgt]->pt - polyline[0]).lengthSquared()) {
			dist2 = polyline.length() - polyline.length(index);
		} else {
			dist2 = polyline.length(index);
		}
	}

	return (elevation1 * dist2 + elevation2 * dist1) / (dist1 + dist2);
}
