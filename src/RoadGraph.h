#pragma once

#include "glew.h"
#include "common.h"
#include <stdio.h>
#include "RoadVertex.h"
#include "RoadEdge.h"
#include "VBORenderManager.h"

using namespace boost;

typedef adjacency_list<vecS, vecS, undirectedS, RoadVertexPtr, RoadEdgePtr> BGLGraph;
typedef graph_traits<BGLGraph>::vertex_descriptor RoadVertexDesc;
typedef graph_traits<BGLGraph>::edge_descriptor RoadEdgeDesc;
typedef graph_traits<BGLGraph>::vertex_iterator RoadVertexIter;
typedef graph_traits<BGLGraph>::edge_iterator RoadEdgeIter;
typedef graph_traits<BGLGraph>::out_edge_iterator RoadOutEdgeIter;
typedef graph_traits<BGLGraph>::in_edge_iterator RoadInEdgeIter;

class RoadGraph {
public:
	BGLGraph graph;

public:
	RoadGraph();

	void clear();
	float getBridgeElevationFromClosestNeighbors(RoadVertexDesc srcDesc, VBORenderManager &renderManager, float seaLevel);
	float getBridgeElevationFromClosestNeighbors(RoadEdgeDesc edge_desc, const Polyline2D &polyline, int index, VBORenderManager &renderManager, float seaLevel);
};

typedef boost::shared_ptr<RoadGraph> RoadGraphPtr;
