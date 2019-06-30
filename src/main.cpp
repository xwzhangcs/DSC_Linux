#include "MainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[]) {
	std::cout << "main function start" << std::endl;
	G::global()["MAX_Z"] = 1000.0f;
	G::global()["shader2D"] = true;
	G::global()["2DroadsStroke"] = 1.5f;
	G::global()["sidewalk_width"] = 2.0f;
	G::global()["tree_setback"] = 1.3f;
	G::global()["sea_level"] = 74.5f;
	G::global()["road_min_level"] = 61.0f;
	G::global()["show_water"] = false;

	// parameters
	G::global()["roadAngleTolerance"] = 0.52f;
	G::global()["slopeTolerance"] = 0.3f;
	G::global()["acrossRiverTolerance"] = 200.0f;
	G::global()["avenueAvgSegmentLength"] = 100.0f;
	G::global()["road_base_orientation"] = 0.0f;
	G::global()["use_elevation_for_road_generation"] = true;
	G::global()["road_curvature"] = 0.2f;
	//normal
	G::global()["major_road_width"] = 20.0f;
	G::global()["second_road_width"] = 14.0f;
	G::global()["minor_road_width"] = 7.0f;
	// chicago
	//G::global()["major_road_width"] = 25.0f;
	//G::global()["second_road_width"] = 18.0f;
	//G::global()["minor_road_width"] = 7.0f;
	G::global()["rog"] = 20.0f;
	G::global()["parksRatio"] = 0.1f;
	G::global()["parcel_area_mean"] = 1000.0f;
	G::global()["parcel_area_deviation"] = 200.0f;
	G::global()["parcel_split_deviation"] = 0.2f;
	G::global()["parcel_setback_front"] = 5.0f;
	G::global()["parcel_setback_rear"] = 5.0f;
	G::global()["parcel_setback_sides"] = 5.0f;
	G::global()["building_stories_min"] = 2.0f;
	G::global()["building_stories_max"] = 8.0f;
	G::global()["building_min_dimension"] = 10.0f;
	QCoreApplication::addLibraryPath(".");
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
	//return 0;
}
