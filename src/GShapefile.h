#pragma once

#include <string>
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include <ogrsf_frmts.h>
#include <iostream>

namespace gs {

	class Variant {
	private:
		int _intValue;
		double _doubleValue;
		std::string _stringValue;

	public:
		int type;

	public:
		Variant() : type(-1) {}
		Variant(int value);
		Variant(double value);
		Variant(const std::string& value);

		int intValue() { return _intValue; }
		double doubleValue() { return _doubleValue; }
		std::string stringValue() { return _stringValue; }

		friend std::ostream& operator<<(std::ostream& os, const Variant& v);
	};

	std::ostream& operator<<(std::ostream& os, const Variant& v);

	class ShapePart {
	public:
		bool selected;
		std::vector<glm::vec3> points;

	public:
		ShapePart() : selected(false) {}
	};

	class ShapeObject {
	public:
		bool selected;
		std::vector<ShapePart> parts;
		std::map<std::string, Variant> attributes;

	public:
		ShapeObject() : selected(false) {}
	};

	class Shape {
	public:
		int shapeType;
		glm::vec3 minBound;
		glm::vec3 maxBound;
		std::vector<ShapeObject> shapeObjects;

	public:
		Shape() : shapeType(-1) {}
		Shape(int shapeType) : shapeType(shapeType) {}

		bool load(const std::string& filename);
		bool save(const std::string& filename);

		double getTotalArea();

	private:
		void updateBounds(OGRPoint* poPoint);
		void readMultiPolygon(OGRMultiPolygon* poMultiPolygon, ShapeObject& shapeObject);
		void readPolygon(OGRPolygon* poPolygon, ShapeObject& shapeObject);
		void readLineString(OGRLineString* lineString, ShapeObject& shapeObject);
		void readRing(OGRLinearRing* ring, ShapePart& shapePart);
	};

	class DEM {
	public:
		glm::vec2 origin;
		glm::vec2 pixelSize;
		int width;
		int height;
		std::vector<float> data;
		float min_val;
		float max_val;

	public:
		DEM() {}

		bool load(const std::string& filename);

	};

}
