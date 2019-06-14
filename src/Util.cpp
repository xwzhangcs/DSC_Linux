#include "Util.h"
#include <random>
#include "gdal_priv.h"
#include "cpl_conv.h" // for CPLMalloc()
#include "global.h"
//const float M_PI = 3.1415926535;

const double Util::MTC_FLOAT_TOL = 1e-10;

/**
 * Return the distance from segment ab to point c.
 * If the 
 */
float Util::pointSegmentDistanceXY(const QVector3D &a, const QVector3D &b, const QVector3D &c, bool segmentOnly) {
	float r_numerator = (c.x()-a.x())*(b.x()-a.x()) + (c.y()-a.y())*(b.y()-a.y());
	float r_denomenator = (b.x()-a.x())*(b.x()-a.x()) + (b.y()-a.y())*(b.y()-a.y());

	if (r_denomenator <= 0.0f) {
		return (a - c).length();
	}

	float r = r_numerator / r_denomenator;

	if (segmentOnly && (r < 0 || r > 1)) {
		float dist1 = SQR(c.x() - a.x()) + SQR(c.y() - a.y());
		float dist2 = SQR(c.x() - b.x()) + SQR(c.y() - b.y());
		if (dist1 < dist2) {	
			return sqrt(dist1);
		} else {
			return sqrt(dist2);
		}
	} else {
		return abs((a.y()-c.y())*(b.x()-a.x())-(a.x()-c.x())*(b.y()-a.y())) / sqrt(r_denomenator);
	}
}

QVector2D Util::projLatLonToMeter(double longitude, double latitude, const QVector2D &centerLatLon) {
	QVector2D result;

	// comment our old projection
	//double y = latitude / 180 * M_PI;
	//double dx = (longitude - centerLatLon.x()) / 180 * M_PI;
	//double dy = (latitude - centerLatLon.y()) / 180 * M_PI;

	//double radius = 6378137;

	//result.setX(radius * cos(y) * dx);
	//result.setY(radius * dy);

	// new projection EPSG: 3857 by xwzhang
	double constant = 2 * M_PI * 6378137 / 2.0;
	double mx = longitude * constant / 180.0;
	double my = log(tan((90 + latitude) * M_PI / 360.0)) / (M_PI / 180.0);
	my = my * constant / 180.0;

	// center
	double center_mx = centerLatLon.x() * constant / 180.0;
	double center_my = log(tan((90 + centerLatLon.y()) * M_PI / 360.0)) / (M_PI / 180.0);
	center_my = center_my * constant / 180.0;

	result.setX(mx - center_mx);
	result.setY(my - center_my);
	return  result; 
}

QVector2D Util::projLatLonToMeter(double longitude, double latitude) {
	QVector2D result;
	// new projection EPSG: 3857 by xwzhang
	double constant = 2 * M_PI * 6378137 / 2.0;
	double mx = longitude * constant / 180.0;
	double my = log(tan((90 + latitude) * M_PI / 360.0)) / (M_PI / 180.0);
	my = my * constant / 180.0;

	result.setX(mx);
	result.setY(my);
	return  result;
}

QVector2D Util::projMeterToLatLon(double x, double y, const QVector2D &centerLatLon) {
	QVector2D result;
	//double radius = 6378137;
	//double latitude = 0.0;
	//double longitude = 0.0;
	//double dx = 0.0;
	//double dy = 0.0;
	//dy = y / radius;
	//latitude = (dy * 180) / M_PI + centerLatLon.y();
	//double tmp_y = latitude / 180 * M_PI;
	//dx = x / (radius * cos(tmp_y));
	//longitude = (dx * 180) / M_PI + centerLatLon.x();

	//result.setX(longitude);
	//result.setY(latitude);
	double constant = 2 * M_PI * 6378137 / 2.0;
	//get center x and y
	// center
	double center_mx = centerLatLon.x() * constant / 180.0;
	double center_my = log(tan((90 + centerLatLon.y()) * M_PI / 360.0)) / (M_PI / 180.0);
	center_my = center_my * constant / 180.0;
	double mx = x + center_mx;
	double my = y + center_my;
	double lon = (mx / constant) * 180.0;
	double lat = (my / constant) * 180.0;

	lat = 180 / M_PI * (2 * atan(exp(lat * M_PI / 180.0)) - M_PI / 2.0);

	result.setX(lon);
	result.setY(lat);
	return  result;
}

std::vector<double> Util::getGeoInfo(char * filename){
	GDALDataset  *poDataset;
	std::vector<double> result;
	GDALAllRegister();
	poDataset = (GDALDataset *)GDALOpen(filename, GA_ReadOnly);
	if (poDataset == NULL)
	{
		std::cout << " Null data" << std::endl;
	}
	else{
		// Getting Dataset Information
		double adfGeoTransform[6];
		printf("Driver: %s/%s\n",
			poDataset->GetDriver()->GetDescription(),
			poDataset->GetDriver()->GetMetadataItem(GDAL_DMD_LONGNAME));
		printf("Size is %dx%dx%d\n",
			poDataset->GetRasterXSize(), poDataset->GetRasterYSize(),
			poDataset->GetRasterCount());
		if (poDataset->GetProjectionRef() != NULL)
			printf("Projection is `%s'\n", poDataset->GetProjectionRef());
		if (poDataset->GetGeoTransform(adfGeoTransform) == CE_None)
		{
			printf("Origin = (%.6f,%.6f)\n",
				adfGeoTransform[0], adfGeoTransform[3]);
			printf("Pixel Size = (%.6f,%.6f)\n",
				adfGeoTransform[1], adfGeoTransform[5]);
		}
		result.push_back(adfGeoTransform[0]);
		result.push_back(adfGeoTransform[3]);
		result.push_back(adfGeoTransform[1]);
		result.push_back(adfGeoTransform[5]);
	}
	return result;
}

QVector2D Util::getXYCoordSeg(double x, double y){
	// Center long/lat coordinate
	QVector2D centerLonLatOSM(G::getDouble("center_long"), G::getDouble("center_lat"));
	QVector2D originLonLatSeg(G::getDouble("origin_long"), G::getDouble("origin_lat"));
	QVector2D pixelLonLatSeg(G::getDouble("pixel_size_long"), G::getDouble("pixel_size_lat"));
	// Find the long/lat for the x and y
	QVector2D xy_longlat = Util::projMeterToLatLon(x, y, centerLonLatOSM);
	//std::cout << "xy_longlat is (" << xy_longlat.x() << ", " << xy_longlat.y() << ")" << std::endl;
	// Compute the real value in the segmented image
	double diff_long = xy_longlat.x() - originLonLatSeg.x();
	double diff_lat = xy_longlat.y() - originLonLatSeg.y();
	// Compute the pixel position in the segmented image
	double pixel_x = abs(diff_long / pixelLonLatSeg.x());
	double pixel_y = abs(diff_lat / pixelLonLatSeg.y());
	//std::cout << "pixel pos is (" << pixel_x << ", " << pixel_y << ")" << std::endl;
	//
	return QVector2D(pixel_x, pixel_y);
}

QVector2D Util::getLongLatCoord(double x, double y){
	// Center long/lat coordinate
	QVector2D centerLonLatOSM(G::getDouble("center_long"), G::getDouble("center_lat"));
	QVector2D xy_longlat = Util::projMeterToLatLon(x, y, centerLonLatOSM);
	return xy_longlat;
}

QVector2D Util::getXYCoord(double x, double y, const std::vector<double> paras){
	// Compute the real value in the segmented image
	double diff_long = x - paras.at(0);
	double diff_lat = y - paras.at(1);
	// Compute the pixel position in the segmented image
	double pixel_x = diff_long / paras.at(2);
	double pixel_y = diff_lat / paras.at(3);
	//std::cout << "pixel pos is (" << pixel_x << ", " << pixel_y << ")" << std::endl;
	//
	return QVector2D(pixel_x, pixel_y);
}

/**
 * Project latitude/longitude coordinate to world coordinate.
 * Mercator projection cannot be used for this purpose, becuase
 * it deforms the area especially in the high latitude regions.
 * Hubeny's theorum should be used for this purpose, but not yet implemented yet.
 *
 * @param lat		latitude
 * @param lon		longitude
 * @param centerLat	latitude of the center of the map
 * @param centerLon	longitude of the center of the map
 * @return			the world coordinate (Z coordinate is dummy.)
 */
QVector2D Util::projLatLonToMeter(const QVector2D &latLon, const QVector2D &centerLatLon) {
	QVector2D result;

	double y = latLon.y() / 180 * M_PI;
	double dx = (latLon.x() - centerLatLon.x()) / 180 * M_PI;
	double dy = (latLon.y() - centerLatLon.y()) / 180 * M_PI;

	double radius = 6378137;

	result.setX(radius * cos(y) * dx);
	result.setY(radius * dy);

	return  result; 
}

bool Util::segmentSegmentIntersectXY3D(const QVector3D& a, const QVector3D& b, const QVector3D& c, const QVector3D& d, double *tab, double *tcd, bool segmentOnly, QVector3D& intPoint) {
	QVector2D interPoint;
	bool res=segmentSegmentIntersectXY(QVector2D(a.x(),a.y()),QVector2D(b.x(),b.y()),QVector2D(c.x(),c.y()),QVector2D(d.x(),d.y()),tab,tcd,segmentOnly,interPoint);
	intPoint=interPoint.toVector3D();
	return res;
}//

/**
 * Computes the intersection between two line segments on the XY plane.
 * Segments must intersect within their extents for the intersection to be valid. z coordinate is ignored.
 *
 * @param a one end of the first line
 * @param b another end of the first line
 * @param c one end of the second line
 * @param d another end of the second line
 * @param tab
 * @param tcd
 * @param segmentOnly
 * @param intPoint	the intersection
 * @return true if two lines intersect / false otherwise
 **/
bool Util::segmentSegmentIntersectXY(const QVector2D& a, const QVector2D& b, const QVector2D& c, const QVector2D& d, double *tab, double *tcd, bool segmentOnly, QVector2D& intPoint) {
	QVector2D u = b - a;
	QVector2D v = d - c;

	if (u.lengthSquared() < MTC_FLOAT_TOL || v.lengthSquared() < MTC_FLOAT_TOL) {
		return false;
	}

	double numer = v.x()*(c.y()-a.y()) + v.y()*(a.x()-c.x());
	double denom = u.y()*v.x() - u.x()*v.y();

	if (denom == 0.0)  {
		// they are parallel
		*tab = 0.0;
		*tcd = 0.0;
		return false;
	}

	double t0 = numer / denom;

	QVector2D ipt = a + t0*u;
	QVector2D tmp = ipt - c;
	double t1;
	if (QVector2D::dotProduct(tmp, v) > 0.0){
		t1 = tmp.length() / v.length();
	}
	else {
		t1 = -1.0 * tmp.length() / v.length();
	}

	//Check if intersection is within segments
	//if(segmentOnly && !( (t0 >= MTC_FLOAT_TOL) && (t0 <= 1.0-MTC_FLOAT_TOL) && (t1 >= MTC_FLOAT_TOL) && (t1 <= 1.0-MTC_FLOAT_TOL) ) ){
	if (segmentOnly && !((t0 >= MTC_FLOAT_TOL) && (t0 <= 1.0 - MTC_FLOAT_TOL) && (t1 >= MTC_FLOAT_TOL) && (t1 <= 1.0 - MTC_FLOAT_TOL))){
		return false;
	}

	*tab = t0;
	*tcd = t1;
	QVector2D dirVec = b-a;

	intPoint = a+(*tab)*dirVec;

	return true;
}

/**
 * Compute the distance between the edge A-B and the edge C-D. Store the coordinate of the closest point in closestPtInAB.
 */
float Util::pointSegmentDistanceXY(const QVector2D& a, const QVector2D& b, const QVector2D& c, QVector2D& closestPtInAB) {
	float dist;		

	float r_numerator = (c.x()-a.x())*(b.x()-a.x()) + (c.y()-a.y())*(b.y()-a.y());
	float r_denomenator = (b.x()-a.x())*(b.x()-a.x()) + (b.y()-a.y())*(b.y()-a.y());

	// For the case that the denominator is 0.
	if (r_denomenator <= 0.0f) {
		closestPtInAB = a;
		return (a - c).length();
	}

	float r = r_numerator / r_denomenator;

	//
	float px = a.x() + r*(b.x()-a.x());
	float py = a.y() + r*(b.y()-a.y());
	//    
	float s =  ((a.y()-c.y())*(b.x()-a.x())-(a.x()-c.x())*(b.y()-a.y()) ) / r_denomenator;

	float distanceLine = fabs(s)*sqrt(r_denomenator);

	closestPtInAB.setX(px);
	closestPtInAB.setY(py);

	if ((r >= 0) && (r <= 1)) {
		dist = distanceLine;
	} else {
		float dist1 = (c.x()-a.x())*(c.x()-a.x()) + (c.y()-a.y())*(c.y()-a.y());
		float dist2 = (c.x()-b.x())*(c.x()-b.x()) + (c.y()-b.y())*(c.y()-b.y());
		if (dist1 < dist2) {	
			dist = sqrt(dist1);
			closestPtInAB = a;
		} else {
			dist = sqrt(dist2);
			closestPtInAB = b;
		}
	}

	return abs(dist);
}

float Util::deg2rad(float deg) {
	return M_PI * deg / 180.0f;
}

float Util::rad2deg(float rad) {
	return rad * 180.0f / M_PI;
}

/**
 * 角度を正規化し、[-PI , PI]の範囲にする。
 */
float Util::normalizeAngle(float angle) {
	// まずは、正の値に変換する
	if (angle < 0.0f) {
		angle += ((int)(fabs(angle) / M_PI / 2.0f) + 1) * M_PI * 2;
	}

	// 次に、[0, PI * 2]の範囲にする
	angle -= (int)(angle / M_PI / 2.0f) * M_PI * 2;

	// 最後に、[-PI, PI]の範囲にする
	//if (angle > M_PI) angle = M_PI * 2.0f - angle;
	if (angle > M_PI) angle = angle - M_PI * 2.0f;		// fix this bug on 12/17

	return angle;
}

/**
 * Compute the difference in angle that is normalized in the range of [0, PI].
 * absolute == falseの時は、dir1の角度 - dir2の角度を[-PI, PI]で返却する。
 */
float Util::diffAngle(const QVector2D& dir1, const QVector2D& dir2, bool absolute) {
	float ang1 = atan2f(dir1.y(), dir1.x());
	float ang2 = atan2f(dir2.y(), dir2.x());

	if (absolute) {
		return fabs(normalizeAngle(ang1 - ang2));
	} else {
		return normalizeAngle(ang1 - ang2);
	}
}

float Util::diffAngle(const QVector3D& dir1, const QVector3D& dir2, bool absolute) {
	float ang1 = atan2f(dir1.y(), dir1.x());
	float ang2 = atan2f(dir2.y(), dir2.x());

	if (absolute) {
		return fabs(normalizeAngle(ang1 - ang2));
	} else {
		return normalizeAngle(ang1 - ang2);
	}
}

bool Util::withinAngle(float angle, float angle1, float angle2) {
	if (diffAngle(angle1, angle2) > 3.14159f) return true;

	if (diffAngle(angle1, angle2, false) >= 0) {
		if (diffAngle(angle, angle1, false) >= 0) {
			return false;
		} else {
			if (diffAngle(angle, angle1) < diffAngle(angle1, angle2)) return true;
			else return false;
		}
	} else {
		if (diffAngle(angle, angle2, false) >= 0) {
			return false;
		} else {
			if (diffAngle(angle, angle2) < diffAngle(angle1, angle2)) return true;
			else return false;
		}
	}
}

/**
 * Compute the difference in angle that is normalized in the range of [0, PI].
 */
float Util::diffAngle(float angle1, float angle2, bool absolute) {
	if (absolute) {
		return fabs(normalizeAngle(angle1 - angle2));
	} else {
		return normalizeAngle(angle1 - angle2);
	}
}

/**
 * Angle between 3 points A-B-C
 **/
float Util::angleThreePoints(const QVector3D& pa, const QVector3D& pb, const QVector3D& pc) {
	float a = (pb - pc).length();
	float b = (pa - pc).length();
	float c = (pa - pb).length();
	return acos(0.999f * (a*a + c*c - b*b) / (2.0f*a*c));
}

double Util::angleBetweenVectors(const QVector2D& vec1, const QVector2D& vec2) {
	return acos(0.999*(QVector2D::dotProduct(vec1, vec2)) / (vec1.length() * vec2.length()));
}

double Util::angleBetweenVectors(const QVector3D& vec1, const QVector3D& vec2) {
	return acos( 0.999*(QVector3D::dotProduct(vec1, vec2)) / ( vec1.length() * vec2.length() ) );
}

/**
 * 指定された点を、反時計回りにrad回転させた位置を返却する。
 */
QVector2D Util::rotate(const QVector2D &pt, float rad) {
	QVector2D ret;

	ret.setX(cosf(rad) * pt.x() - sinf(rad) * pt.y());
	ret.setY(sinf(rad) * pt.x() + cosf(rad) * pt.y());

	return ret;
}

/**
 * 指定された点を、反時計回りにrad回転させた位置を返却する。
 */
QVector2D Util::rotate(const QVector2D &pt, float rad, const QVector2D &orig) {
	return rotate(pt - orig, rad) + orig;
}

/**
 * カーテシアン座標系から、極座標系へ変換する。
 */
void Util::cartesian2polar(const QVector2D &pt, float &radius, float &theta) {
	radius = pt.length();
	theta = atan2f(pt.y(), pt.x());
}

/**
 * 指定されたptを、座標変換する。
 * 座標変換は、sourcePtで指定された点がtargetPtへ移り、且つ、rad[radian]回転するような変換だ。
 */
QVector2D Util::transform(const QVector2D &pt, const QVector2D &sourcePt, float rad, const QVector2D &targetPt) {
	return rotate(pt - sourcePt, rad) + targetPt;
}

/**
 * 曲率を計算する
 * 各セグメント間で曲率を計算し、その加重平均を返す。
 */
float Util::curvature(const Polyline2D &polyline) {
	float curvature = 0.0f;
	float length = 0.0f;

	for (int i = 0; i < polyline.size() - 2; ++i) {
		QVector2D vec1 = (polyline[i + 1] - polyline[i]).normalized();
		QVector2D vec2 = (polyline[i + 2] - polyline[i + 1]).normalized();

		float l = (polyline[i + 1] - polyline[i]).length();
		curvature += (vec1 - vec2).length() * l;
		length += l;
	}

	if (length == 0.0f) return 0.0f;
	else return curvature / length;
}

/**
 * Uniform乱数[0, 1)を生成する
 */
float Util::genRand() {
	return rand() / (float(RAND_MAX) + 1);
}

/**
 * 指定された範囲[a, b)のUniform乱数を生成する
 */
float Util::genRand(float a, float b) {
	return genRand() * (b - a) + a;
}

int Util::sampleFromCdf(std::vector<float> &cdf) {
	float rnd = genRand(0, cdf.back());

	for (int i = 0; i < cdf.size(); ++i) {
		if (rnd <= cdf[i]) return i;
	}

	return cdf.size() - 1;
}

int Util::sampleFromPdf(std::vector<float> &pdf) {
	if (pdf.size() == 0) return 0;

	std::vector<float> cdf(pdf.size(), 0.0f);
	cdf[0] = pdf[0];
	for (int i = 1; i < pdf.size(); ++i) {
		if (pdf[i] >= 0) {
			cdf[i] = cdf[i - 1] + pdf[i];
		} else {
			cdf[i] = cdf[i - 1];
		}
	}

	return sampleFromCdf(cdf);
}

/**
 * p0, p1, p2の値(Z座標)を使い、指定された点pの値(Z座標)をBarycentric interpolationにより計算する。
 */
float Util::barycentricInterpolation(const QVector3D& p0, const QVector3D& p1, const QVector3D& p2, const QVector2D& p) {
	QVector3D vec1 = p1 - p0;
	QVector3D vec2 = p2 - p0;
	QVector2D vec = p - QVector2D(p0.x(), p0.y());

	float s, t;
	float den = vec1.x() * vec2.y() - vec2.x() * vec1.y();

	if (den >= MTC_FLOAT_TOL) {
		s = (vec.x() * vec2.y() - vec2.x() * vec.y()) / den;
		t = (vec1.x() * vec.y() - vec.x() * vec1.y()) / den;
		return p0.z() + vec1.z() * s + vec2.z() * t;
	}

	return 0.0f;
}

/**
* Given three non colinear points p0, p1, p2, this function computes
* the intersection between the lines A and B. Line A is the line parallel to the segment p0-p1
* and at a distance d01 from that segment. Line B is the line parallel to the segment
* p1-p2 at a distance d12 from that segment.
* Returns true if point is successfully computed
**/
bool Util::getIrregularBisector(const QVector3D& p0, const QVector3D& p1, const QVector3D& p2, float d01, float d12, QVector3D& intPt) {
	double alpha;
	double theta;
	double L;

	QVector3D p1_p0;
	QVector3D p1_p2;
	QVector3D p1_p2_perp;
	QVector3D crossP;

	p1_p0 = p0 - p1;
	p1_p0.setZ(0.0f);

	p1_p2 = p2 - p1;
	p1_p2.setZ(0.0f);

	p1_p2_perp.setX( -p1_p2.y() );
	p1_p2_perp.setY(  p1_p2.x() );
	p1_p2_perp.setZ( 0.0f );

	alpha = diffAngle(p1_p0, p1_p2);				

	if (!(alpha == alpha)) {
		return false;
	}				

	theta = atan2( sin(alpha), (d01 / d12) + cos(alpha) );				
	L = d12 / sin(theta);

	//This is done to handle convex vs. concave angles in polygon
	crossP = QVector3D::crossProduct(p1_p2, p1_p0);

	if (crossP.z() > 0) {
		intPt = p1 + (p1_p2.normalized())*L*cos(theta) + (p1_p2_perp.normalized())*d12;
	} else {
		intPt = p1 - (p1_p2.normalized()) * L * cos(theta) + (p1_p2_perp.normalized()) * d12;
	}
	return true;
}

bool Util::getIrregularBisector(const QVector2D& p0, const QVector2D& p1, const QVector2D& p2, float d01, float d12, QVector2D& intPt) {
	double alpha;
	double theta;
	double L;

	QVector2D p1_p0 = p0 - p1;
	QVector2D p1_p2 = p2 - p1;

	QVector2D p1_p2_perp(-p1_p2.y(), p1_p2.x());

	alpha = diffAngle(p1_p0, p1_p2);				

	theta = atan2( sin(alpha), (d01 / d12) + cos(alpha) );				
	L = d12 / sin(theta);

	//This is done to handle convex vs. concave angles in polygon
	float crossP = p1_p2.x() * p1_p0.y() - p1_p2.y() * p1_p0.x();//QVector2D:crossProduct(p1_p2, p1_p0);

	if (crossP > 0) {
		intPt = p1 + (p1_p2.normalized())*L*cos(theta) + (p1_p2_perp.normalized())*d12;
	} else {
		intPt = p1 - (p1_p2.normalized()) * L * cos(theta) + (p1_p2_perp.normalized()) * d12;
	}
	return true;
}
