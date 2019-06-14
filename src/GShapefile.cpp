#include "GShapefile.h"

namespace gs {

	Variant::Variant(int value) : _intValue(value), type(OFTInteger) {
		_doubleValue = value;
		_stringValue = std::to_string(value);
	}

	Variant::Variant(double value) : _doubleValue(value), type(OFTReal) {
		_intValue = value;
		_stringValue = std::to_string(value);
	}

	Variant::Variant(const std::string& value) : _stringValue(value), type(OFTString) {
		char* pEnd;
		_doubleValue = std::strtod(value.c_str(), &pEnd);
		if (*pEnd == 0) {
			try {
				_intValue = std::stoi(value);
				_doubleValue = std::stod(value);
			}
			catch (std::invalid_argument ex) {
				_intValue = 0;
				_doubleValue = 0;
			}
			catch (std::out_of_range ex) {
				_intValue = 0;
				_doubleValue = 0;
			}
		}
		else {
			_intValue = 0;
			_doubleValue = 0;
		}
	}

	std::ostream& operator<<(std::ostream& os, const Variant& v) {
		if (v.type == OFTInteger) {
			os << v._intValue;
		}
		else if (v.type == OFTReal) {
			os << v._doubleValue;
		}
		else if (v.type == OFTString) {
			os << v._stringValue;
		}
		return os;
	}

	bool Shape::load(const std::string& filename) {
		GDALAllRegister();

		GDALDataset* poDS;
		poDS = (GDALDataset*)GDALOpenEx(filename.c_str(), GDAL_OF_VECTOR, NULL, NULL, NULL);
		if (poDS == NULL) return false;

		// 初期化
		shapeObjects.clear();
		minBound.x = std::numeric_limits<float>::max();
		minBound.y = std::numeric_limits<float>::max();
		minBound.z = std::numeric_limits<float>::max();
		maxBound.x = -std::numeric_limits<float>::max();
		maxBound.y = -std::numeric_limits<float>::max();
		maxBound.z = -std::numeric_limits<float>::max();

		int nLayers = poDS->GetLayerCount();
		int i = 0;
		for (int n = 0; n < nLayers; ++n) {
			OGRLayer* poLayer = poDS->GetLayer(n);
			shapeType = poLayer->GetGeomType();
			shapeObjects.resize(shapeObjects.size() + poLayer->GetFeatureCount());
			
			OGRFeature* poFeature;
			poLayer->ResetReading();
			while ((poFeature = poLayer->GetNextFeature()) != NULL) {
				// 属性の名前を読み込む
				std::vector<std::string> fieldNames;
				for (int j = 0; j < poFeature->GetFieldCount(); ++j) {
					OGRFieldDefn* poFieldDefn = poFeature->GetFieldDefnRef(j);
					fieldNames.push_back(poFieldDefn->GetNameRef());
				}

				// 属性の値を読み込む
				OGRFeatureDefn *poFDefn = poLayer->GetLayerDefn();
				for (int j = 0; j < poFDefn->GetFieldCount(); ++j) {
					OGRFieldDefn* poFieldDefn = poFDefn->GetFieldDefn(j);
					if (poFieldDefn->GetType() == OFTInteger) {
						shapeObjects[i].attributes[fieldNames[j]] = Variant(poFeature->GetFieldAsInteger(j));
					}
					else if (poFieldDefn->GetType() == OFTInteger64) {
						shapeObjects[i].attributes[fieldNames[j]] = Variant(poFeature->GetFieldAsInteger(j));
					}
					else if (poFieldDefn->GetType() == OFTReal) {
						shapeObjects[i].attributes[fieldNames[j]] = Variant(poFeature->GetFieldAsDouble(j));
					}
					else if (poFieldDefn->GetType() == OFTString) {
						shapeObjects[i].attributes[fieldNames[j]] = Variant(poFeature->GetFieldAsString(j));
					}
					else {
						shapeObjects[i].attributes[fieldNames[j]] = Variant(poFeature->GetFieldAsString(j));
					}
				}

				// このshapeのベクトルデータを読み込む
				OGRGeometry* poGeometry = poFeature->GetGeometryRef();
				if (poGeometry != NULL) {
					if (wkbFlatten(poGeometry->getGeometryType()) == wkbPoint) {
						shapeObjects[i].parts.resize(1);
						shapeObjects[i].parts[0].points.resize(1);

						OGRPoint* poPoint = (OGRPoint*)poGeometry;
						shapeObjects[i].parts[0].points[0].x = poPoint->getX();
						shapeObjects[i].parts[0].points[0].y = poPoint->getY();

						updateBounds(poPoint);
					}
					else if (wkbFlatten(poGeometry->getGeometryType()) == wkbLineString) {						OGRLineString* poLineString = (OGRLineString*)poGeometry;						readLineString(poLineString, shapeObjects[i]);					}
					else if (wkbFlatten(poGeometry->getGeometryType()) == wkbPolygon) {
						OGRPolygon* poPolygon = (OGRPolygon*)poGeometry;
						readPolygon(poPolygon, shapeObjects[i]);
					}
					else if (wkbFlatten(poGeometry->getGeometryType()) == wkbMultiPolygon) {
						OGRMultiPolygon* poMultiPolygon = (OGRMultiPolygon*)poGeometry;
						readMultiPolygon(poMultiPolygon, shapeObjects[i]);
					}
					else {
						// not supported
					}
				}

				// shapeObjectsのインデックスをインクリメント
				i++;

				// OGRが取得したメモリを開放
				OGRFeature::DestroyFeature(poFeature);
			}
		}

		GDALClose(poDS);

		return true;
	}

	bool Shape::save(const std::string& filename) {
		if (shapeType == -1) {
			std::cout << "Shape type is not set." << std::endl;
			return false;
		}

		if (shapeObjects.size() == 0) {
			std::cout << "No shape exists." << std::endl;
			return false;
		}

		const char *pszDriverName = "ESRI Shapefile";
		GDALDriver *poDriver;
		GDALAllRegister();

		poDriver = GetGDALDriverManager()->GetDriverByName(pszDriverName);
		if (poDriver == NULL) {
			printf("%s driver not available.\n", pszDriverName);
			return false;
		}

		GDALDataset *poDS;
		poDS = poDriver->Create(filename.c_str(), 0, 0, 0, GDT_Unknown, NULL);
		if (poDS == NULL) {
			printf("Creation of output file failed.\n");
			return false;
		}

		OGRLayer *poLayer;
		if (shapeType == wkbPoint) {
			poLayer = poDS->CreateLayer("point_out", NULL, wkbPoint, NULL);
		}
		else if (shapeType == wkbLineString) {
			poLayer = poDS->CreateLayer("point_out", NULL, wkbLineString, NULL);
		}
		else if (shapeType == wkbPolygon) {
			poLayer = poDS->CreateLayer("point_out", NULL, wkbPolygon, NULL);
		}
		if (poLayer == NULL) {
			printf("Layer creation failed.\n");
			return false;
		}

		for (auto it = shapeObjects[0].attributes.begin(); it != shapeObjects[0].attributes.end(); ++it) {
			OGRFieldDefn oField(it->first.c_str(), static_cast<OGRFieldType>(it->second.type));
			if (it->second.type == OFTString) {
				oField.SetWidth(it->second.stringValue().size());
			}
			if (poLayer->CreateField(&oField) != OGRERR_NONE) {
				printf("Creating Name field failed.\n");
				return false;
			}
		}

		for (int i = 0; i < shapeObjects.size(); ++i) {
			if (shapeObjects[i].parts.size() == 0) continue;

			OGRFeature *poFeature;
			poFeature = OGRFeature::CreateFeature(poLayer->GetLayerDefn());

			// 属性をセット
			for (auto it = shapeObjects[i].attributes.begin(); it != shapeObjects[i].attributes.end(); ++it) {
				poFeature->SetField(it->first.c_str(), it->second.stringValue().c_str());
			}

			// ジオメトリ情報をセット
			if (shapeType == wkbPoint) {
				OGRPoint point;
				point.setX(shapeObjects[i].parts[0].points[0].x);
				point.setY(shapeObjects[i].parts[0].points[0].y);
				point.setZ(shapeObjects[i].parts[0].points[0].z);
				poFeature->SetGeometry(&point);
			}
			else if (shapeType == wkbLineString) {
				OGRLineString lineString;
				for (int k = 0; k < shapeObjects[i].parts[0].points.size(); ++k) {
					lineString.addPoint(shapeObjects[i].parts[0].points[k].x, shapeObjects[i].parts[0].points[k].y, shapeObjects[i].parts[0].points[k].z);
				}
				poFeature->SetGeometry(&lineString);
			}
			else if (shapeType == wkbPolygon) {
				OGRPolygon polygon;
				
				for (int j = 0; j < shapeObjects[i].parts.size(); ++j) {
					OGRLinearRing linearRing;
					for (int k = 0; k < shapeObjects[i].parts[j].points.size(); ++k) {
						linearRing.addPoint(shapeObjects[i].parts[j].points[k].x, shapeObjects[i].parts[j].points[k].y, shapeObjects[i].parts[j].points[k].z);
					}
					polygon.addRing(&linearRing);
				}
				poFeature->SetGeometry(&polygon);
			}

			if (poLayer->CreateFeature(poFeature) != OGRERR_NONE) {
				printf("Failed to create feature in shapefile.\n");
				return false;
			}
			OGRFeature::DestroyFeature(poFeature);
		}

		GDALClose(poDS);

		return true;
	}


	double Shape::getTotalArea(){
		int count = 0;
		float totalArea = 0;
		if (shapeType == -1) {
			std::cout << "Shape type is not set." << std::endl;
			return 0;
		}

		if (shapeObjects.size() == 0) {
			std::cout << "No shape exists." << std::endl;
			return 0;
		}

		for (int i = 0; i < shapeObjects.size(); ++i) {
			if (shapeObjects[i].parts.size() == 0) continue;
			else if (shapeType == wkbPolygon) {
				OGRPolygon polygon;

				for (int j = 0; j < shapeObjects[i].parts.size(); ++j) {
					OGRLinearRing linearRing;
					for (int k = 0; k < shapeObjects[i].parts[j].points.size(); ++k) {
						linearRing.addPoint(shapeObjects[i].parts[j].points[k].x, shapeObjects[i].parts[j].points[k].y, shapeObjects[i].parts[j].points[k].z);
					}
					polygon.addRing(&linearRing);
				}
				/*if (polygon.get_Area() > 2000){
					continue;
				}*/
				count++;
				totalArea += polygon.get_Area();
			}
		}
		//std::cout << "The total buildings are " << count << std::endl;
		//std::cout << "The avg area  is " << totalArea / count << std::endl;
	return totalArea;
}
	void Shape::updateBounds(OGRPoint* poPoint) {
		// bounding boxを更新
		if (poPoint->getX() < minBound.x) minBound.x = poPoint->getX();
		if (poPoint->getX() > maxBound.x) maxBound.x = poPoint->getX();
		if (poPoint->getY() < minBound.y) minBound.y = poPoint->getY();
		if (poPoint->getY() > maxBound.y) maxBound.y = poPoint->getY();
		if (poPoint->getZ() < minBound.z) minBound.z = poPoint->getZ();
		if (poPoint->getZ() > maxBound.z) maxBound.z = poPoint->getZ();
	}

	void Shape::readMultiPolygon(OGRMultiPolygon* poMultiPolygon, ShapeObject& shapeObject) {
		int numGeometries = poMultiPolygon->getNumGeometries();
		int partsIndex = 0;
		for (int i = 0; i < numGeometries; ++i) {
			OGRGeometry* geo = poMultiPolygon->getGeometryRef(i);
			if (wkbFlatten(geo->getGeometryType()) == wkbPolygon) {
				OGRPolygon* poPolygon = (OGRPolygon*)geo;

				int nInteriorRings = poPolygon->getNumInteriorRings();
				shapeObject.parts.resize(shapeObject.parts.size() + nInteriorRings + 1);

				OGRLinearRing* ring = poPolygon->getExteriorRing();
				readRing(ring, shapeObject.parts[partsIndex++]);

				for (int j = 0; j < nInteriorRings; ++j) {
					OGRLinearRing* ring = poPolygon->getInteriorRing(j);
					readRing(ring, shapeObject.parts[partsIndex++]);
				}
			}
		}
	}

	void Shape::readPolygon(OGRPolygon* poPolygon, ShapeObject& shapeObject) {
		int nInteriorRings = poPolygon->getNumInteriorRings();
		shapeObject.parts.resize(nInteriorRings + 1);

		OGRLinearRing* ring = poPolygon->getExteriorRing();
		readRing(ring, shapeObject.parts[0]);

		for (int j = 0; j < nInteriorRings; ++j) {
			OGRLinearRing* ring = poPolygon->getInteriorRing(j);
			readRing(ring, shapeObject.parts[j + 1]);
		}
	}

	void Shape::readLineString(OGRLineString* lineString, ShapeObject& shapeObject) {
		shapeObject.parts.resize(1);
		shapeObject.parts[0].points.resize(lineString->getNumPoints());

		for (int i = 0; i < lineString->getNumPoints(); ++i) {			OGRPoint point;			lineString->getPoint(i, &point);			shapeObject.parts[0].points[i].x = point.getX();			shapeObject.parts[0].points[i].y = point.getY();			updateBounds(&point);		}	}

	void Shape::readRing(OGRLinearRing* ring, ShapePart& shapePart) {
		shapePart.points.resize(ring->getNumPoints());
		for (int j = 0; j < ring->getNumPoints(); ++j) {
			OGRPoint point;
			ring->getPoint(j, &point);

			shapePart.points[j].x = point.getX();
			shapePart.points[j].y = point.getY();
			updateBounds(&point);
		}
	}

	bool DEM::load(const std::string& filename) {
		GDALAllRegister();

		GDALDataset* poDS;
		poDS = (GDALDataset*)GDALOpenEx(filename.c_str(), GDAL_OF_RASTER, NULL, NULL, NULL);
		if (poDS == NULL) return false;

		double adfGeoTransform[6];
		if (poDS->GetGeoTransform(adfGeoTransform) == CE_None) {
			origin.x = adfGeoTransform[0];
			origin.y = adfGeoTransform[3];

			pixelSize.x = adfGeoTransform[1];
			pixelSize.y = abs(adfGeoTransform[5]);
		}

		width = poDS->GetRasterXSize() * pixelSize.x;
		height = poDS->GetRasterYSize() * pixelSize.y;
		data.resize(width * height);
		min_val = std::numeric_limits<float>::max();
		max_val = -std::numeric_limits<float>::max();

		// bandが存在しない場合は、エラー
		if (poDS->GetRasterCount() == 0) return false;

		// 最初のbandのみを読み込む。複数bandは未対応
		GDALRasterBand* poBand = poDS->GetRasterBand(1);

		int nBlockXSize, nBlockYSize;
		poBand->GetBlockSize(&nBlockXSize, &nBlockYSize);
		//printf("Block=%dx%d Type=%s, ColorInterp=%s\n", nBlockXSize, nBlockYSize, GDALGetDataTypeName(poBand->GetRasterDataType()), GDALGetColorInterpretationName(poBand->GetColorInterpretation()));

		// 最低、最高の値を取得
		int bGotMin, bGotMax;
		double adfMinMax[2];
		adfMinMax[0] = poBand->GetMinimum(&bGotMin);
		adfMinMax[1] = poBand->GetMaximum(&bGotMax);
		if (!(bGotMin && bGotMax)) GDALComputeRasterMinMax((GDALRasterBandH)poBand, TRUE, adfMinMax);
		//printf("Min=%.3fd, Max=%.3f\n", adfMinMax[0], adfMinMax[1]);
		min_val = adfMinMax[0];
		max_val = adfMinMax[1];
			
		//int nXSize = poBand->GetXSize();
		//int nYSize = poBand->GetYSize();

		int nXBlocks = (poBand->GetXSize() + nBlockXSize - 1) / nBlockXSize;
		int nYBlocks = (poBand->GetYSize() + nBlockYSize - 1) / nBlockYSize;
		float *pData = (float *)CPLMalloc(sizeof(float*) * nBlockXSize * nBlockYSize);
		for (int iYBlock = 0; iYBlock < nYBlocks; iYBlock++) {
			for (int iXBlock = 0; iXBlock < nXBlocks; iXBlock++) {
				int nXValid, nYValid;

				poBand->ReadBlock(iXBlock, iYBlock, pData);

				// Compute the portion of the block that is valid
				// for partial edge blocks.
				if ((iXBlock + 1) * nBlockXSize > poBand->GetXSize())
					nXValid = poBand->GetXSize() - iXBlock * nBlockXSize;
				else
					nXValid = nBlockXSize;
				if ((iYBlock + 1) * nBlockYSize > poBand->GetYSize())
					nYValid = poBand->GetYSize() - iYBlock * nBlockYSize;
				else
					nYValid = nBlockYSize;

				for (int iY = 0; iY < nYValid; iY++) {
					for (int iX = 0; iX < nXValid; iX++) {
						float val;
						if (pData[iY * nBlockXSize + iX] > max_val) {
							val = max_val;
						}
						else if (pData[iY * nBlockXSize + iX] < min_val) {
							val = min_val;
						}
						else {
							val = pData[iY * nBlockXSize + iX];
						}

						for (int y = 0; y < pixelSize.y; ++y) {
							for (int x = 0; x < pixelSize.x; ++x) {
								data[((iYBlock * nBlockYSize + iY) * pixelSize.y + y) * width + (iXBlock * nBlockXSize + iX) * pixelSize.x + x] = val;
							}
						}
						
					}
				}
			}
		}

		GDALClose(poDS);

		return true;
	}
}