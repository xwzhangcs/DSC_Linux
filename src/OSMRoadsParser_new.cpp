#include <vector>
#include <iostream>
#include "Util.h"
#include "GraphUtil.h"
#include "RoadVertex.h"
#include "RoadEdge.h"
#include "BBox.h"
#include "OSMRoadsParser.h"
#include "global.h"

OSMRoadsParser::OSMRoadsParser(RoadGraph *roads) {
	this->roads = roads;

	way.parentNodeName = "osm";
}

bool OSMRoadsParser::startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts) {
	if (localName == "bounds") {
		handleBounds(atts);
	}
	else if (localName == "node") {
		handleNode(atts);
	}
	else if (localName == "way") {
		way.parentNodeName = "way";
		handleWay(atts);
	}
	else if (localName == "nd") {
		if (way.parentNodeName == "way") {
			handleNd(atts);
		}
	}
	else if (localName == "tag") {
		if (way.parentNodeName == "way") {
			handleTag(atts);
		}
	}

	return true;
}

bool OSMRoadsParser::characters(const QString &ch_in) {
	return true;
}

bool OSMRoadsParser::endElement(const QString& namespaceURI, const QString& localName, const QString& qName) {
	if (localName == "way") {
		way.parentNodeName = "osm";

		createRoadEdge();
	}

	return true;
}

void OSMRoadsParser::handleBounds(const QXmlAttributes &atts) {
	float minlat = atts.value("minlat").toFloat();
	float maxlat = atts.value("maxlat").toFloat();
	float minlon = atts.value("minlon").toFloat();
	float maxlon = atts.value("maxlon").toFloat();
	centerLonLat = QVector2D((minlon + maxlon) * 0.5, (minlat + maxlat) * 0.5);
	G::global()["center_long"] = centerLonLat.x();
	G::global()["center_lat"] = centerLonLat.y();
	std::cout << "center_long is " << G::getDouble("center_long")<< std::endl;
	std::cout << "center_lat is " << G::getDouble("center_lat")<< std::endl;
}

void OSMRoadsParser::handleNode(const QXmlAttributes &atts) {
	unsigned long long id = atts.value("id").toULongLong();
	QVector2D pos = Util::projLatLonToMeter(atts.value("lon").toDouble(), atts.value("lat").toDouble(), centerLonLat);
	//if (pos.x() > 159.0 && pos.x() < 160.0 && pos.y() > 700){
	//	std::cout << "long/lat v1 is ( " << atts.value("lon").toDouble() << ", " << atts.value("lat").toDouble() << ")" << std::endl;
	//	std::cout << "pos is ( " << pos.x() << ", " << pos.y() << ")" << std::endl;
	//	QVector2D test = Util::projMeterToLatLon(pos.x(), pos.y(), centerLonLat);	
	//	std::cout << "long/lat v2 is ( " << test.x() << ", " << test.y() << ")" << std::endl;
	//}
	idToActualId.insert(id, id);

	// add a vertex
	vertices.insert(id, RoadVertex(pos));
}

void OSMRoadsParser::handleWay(const QXmlAttributes &atts) {
	way.way_id = atts.value("id").toULongLong();

	way.isStreet = false;
	way.oneWay = false;
	way.link = false;
	way.roundabout = false;
	way.bridge = false;
	way.lanes = 1;
	way.type = RoadEdge::TYPE_STREET;
	way.nds.clear();
}

void OSMRoadsParser::handleNd(const QXmlAttributes &atts) {
	QString hoge = atts.value("ref");
	unsigned long long ref = atts.value("ref").toULongLong();
	way.nds.push_back(ref);
}

void OSMRoadsParser::handleTag(const QXmlAttributes &atts) {
	QString key = atts.value("k");
	if (key == "highway") {
		QString value = atts.value("v");
		way.isStreet = true;
		if (value == "motorway" || value == "motorway_link" || value == "trunk") {
			way.type = RoadEdge::TYPE_MOTOR;
		}
		else if (value == "trunk_link") {
			way.type = RoadEdge::TYPE_AVENUE;
			way.link = true;
		}
		else if (value == "primary") {
			way.type = RoadEdge::TYPE_AVENUE;
		}
		else if (value == "primary_link") {
			way.type = RoadEdge::TYPE_AVENUE;
			way.link = true;
		}
		else if (value == "secondary") {
			way.type = RoadEdge::TYPE_SECONDARY;
		}
		else if (value == "secondary_link") {
			way.type = RoadEdge::TYPE_SECONDARY;
			way.link = true;
		}
		else if (value == "tertiary") {
			way.type = RoadEdge::TYPE_STREET;
		}
		else if (value == "tertiary_link") {
			way.type = RoadEdge::TYPE_STREET;
			way.link = true;
		}
		else if (value == "residential" || value == "living_street" || value == "unclassified") {
			way.type = RoadEdge::TYPE_STREET;
		}
		else if (value == "pedestrian") {
			way.type = RoadEdge::TYPE_STREET;
		}
		else if (value == "service") {
			way.type = RoadEdge::TYPE_STREET;
		}
		else if (value == "footway") {
			way.type = RoadEdge::TYPE_STREET;
		}
		else {
			way.type = RoadEdge::TYPE_OTHERS;
		}
		return;
	}
	else if (key == "sidewalk") {
	}
	else if (key == "junction") {
		QString value = atts.value("v");
		if (value == "roundabout") {
			way.roundabout = true;
		}
	}
	else if (key == "bridge") {
	}
	else if (key == "bridge_number") {
	}
	else if (key == "oneway") {
		QString value = atts.value("v");
		if (value == "yes") {
			way.oneWay = true;
		}
	}
	else if (key == "lanes") {
		//if (way.type == RoadEdge::TYPE_MOTOR)
		//	way.lanes = atts.value("v").toUInt();
		//else{
		//	way.lanes = 1; // atts.value("v").toUInt();
		//}
		way.lanes = 1; // atts.value("v").toUInt();
	}
	else if (key == "name") {
	}
	else if (key == "maxspeed") {
	}
	else if (key == "layer") {
	}
	else {
	}
}

void OSMRoadsParser::createRoadEdge() {
	if (!way.isStreet || way.type == 0) return;

	if (way.nds.size() == 0) return;
	for (int k = 0; k < way.nds.size() - 1; k++) {
		unsigned long long id = way.nds[k];
		unsigned long long next = way.nds[k + 1];

		// check if both end points are already registered
		if (!idToActualId.contains(id)) continue;
		if (!idToActualId.contains(next)) continue;

		RoadVertexDesc sourceDesc;
		if (idToDesc.contains(id)) {		// obtain the vertex desc
			sourceDesc = idToDesc[id];
		}
		else {							// add a vertex
			RoadVertexPtr v = RoadVertexPtr(new RoadVertex(vertices[id].getPt()));
			sourceDesc = GraphUtil::addVertex(*roads, v);
			idToDesc.insert(id, sourceDesc);
		}

		RoadVertexDesc destDesc;
		if (idToDesc.contains(next)) {		// obtain the vertex desc
			destDesc = idToDesc[next];
		}
		else {							// add a vertex
			RoadVertexPtr v = RoadVertexPtr(new RoadVertex(vertices[next].getPt()));
			destDesc = GraphUtil::addVertex(*roads, v);
			idToDesc.insert(next, destDesc);
		}

		// check the duplication of the edge
		bool duplicated = false;
		RoadOutEdgeIter ei, eend;
		for (boost::tie(ei, eend) = boost::out_edges(sourceDesc, roads->graph); ei != eend; ++ei) {
			RoadVertexDesc tgt = boost::target(*ei, roads->graph);
			if (tgt == destDesc) duplicated = true;
		}

		// add a road segment
		if (!duplicated) {
			GraphUtil::addEdge(*roads, sourceDesc, destDesc, way.type, way.lanes, way.oneWay, way.link, way.roundabout);
		}
	}
}