#pragma once

#include "Block.h"
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Partition_traits_2.h>
#include <CGAL/partition_2.h>
#include <CGAL/point_generators_2.h>
#include <CGAL/random_polygon_2.h>
#include <CGAL/Polygon_2.h>
#include <CGAL/create_offset_polygons_2.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/random_polygon_2.h>
#include <CGAL/Boolean_set_operations_2.h>

class SateParcelsAndBuildings {

public:
	static bool generateParcelsAndBuildings(VBORenderManager& rendManager, std::vector<Block>& blocks);
	static QString getBlockPath(const Block & block, const cv::Mat& src, const cv::Mat& parcel_src, const cv::Mat& gt_src, const cv::Mat& gt_whole_src, int index, bool bTest);
	static void remove_roads(cv::Mat &img);
	static bool valid_block(cv::Mat &src);
	static float compute_parcel_area(const cv::Mat & src);
	static std::vector<std::vector<int>> get_height_info(QString height_tiff);
	static bool isSimple(const std::vector<cv::Point>& points);

public:
	// The following definitions are for triangulation only.
	struct FaceInfo {
		FaceInfo() {}
		int nesting_level;
		bool in_domain(){
			return nesting_level % 2 == 1;
		}
	};
	typedef CGAL::Exact_predicates_exact_constructions_kernel       Kernel;
	typedef CGAL::Triangulation_vertex_base_2<Kernel>                      Vb;
	typedef CGAL::Triangulation_face_base_with_info_2<FaceInfo, Kernel>    Fbb;
	typedef CGAL::Constrained_triangulation_face_base_2<Kernel, Fbb>        Fb;
	typedef CGAL::Triangulation_data_structure_2<Vb, Fb>               TDS;
	typedef CGAL::Exact_predicates_tag                                Itag;
	typedef CGAL::Constrained_Delaunay_triangulation_2<Kernel, TDS, Itag>  CDT;

};
