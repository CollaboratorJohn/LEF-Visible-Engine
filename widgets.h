#ifndef WIDGETS_H
#define WIDGETS_H

#include <string>
#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <boost/geometry.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/polygon.hpp>
#include <boost/geometry/io/wkt/wkt.hpp>
#include <boost/foreach.hpp>
#include <boost/property_tree/ptree.hpp>

//declear
namespace bg = boost::geometry;
typedef bg::model::d2::point_xy<double> boost_point;
typedef bg::model::polygon<boost_point> boost_polygon;
typedef boost::geometry::model::polygon<boost::geometry::model::d2::point_xy<double> > polygon;
typedef boost::property_tree::ptree node;

class CPin;
class CRectangle;
class CLayer;
class CDesign;
class CCoordinate;
class CCell;
class HashRect;

// CPin
class CPin {
public:
	CPin();
	~CPin();
	void setName(std::string &);
	void setLayerName(const std::string &);
	void setParent(const std::vector<CLayer>::iterator);
	void addPolygon(CRectangle &);
	double area() const;
	double overlapArea();
	polygon getPolygon();
	const std::vector<CRectangle>::iterator getRectIterator();
	void printNames();
	const std::vector<CLayer>::iterator getParent() const;
private:
	std::vector<CLayer>::iterator parent;
	std::string m_layer_name;
	std::string m_pin_name;
	std::vector<CRectangle> m_polygons;
	polygon m_overlap_polygon;
};


// CCoordinate
class CCoordinate {
public:
	CCoordinate();
	~CCoordinate();
	void setX(double);
	void setY(double y);
	double getX()const;
	double getY()const;

private:
	double m_x;
	double m_y;
};

//CRectangle
class CRectangle {
public:
	CRectangle();
	~CRectangle();
	void setName(std::string &);
	void setParent(const std::vector<CPin>::iterator pin);
	void setId(std::string &);
	void setDL(CCoordinate &);
	void setUR(CCoordinate &);
	double area() const;
	void createPolygon();
	polygon getPolygon();
	void printNames();
	const std::vector<CPin>::iterator getParent() const;
private:
	std::vector<CPin>::iterator parent;
	std::string m_layer_name;
	std::string id;
	CCoordinate m_dl;
	CCoordinate m_ur;
	polygon m_poly;
};

// CLAYER
class CLayer{
public:
	CLayer();
	~CLayer();
	void setName(const std::string &);
	void setParent(const std::vector<CCell>::iterator);
	void addPolygons(const CPin &);
	const std::string& getName() const;
	const std::vector<CPin>::iterator getPinIterator();
	double area() const;
	double overlapArea();
	polygon getPolygon();
	void printNames();
	const std::vector<CCell>::iterator getParent() const;
private:
	std::vector<CCell>::iterator parent;
	std::string m_layer_name;
	std::vector<CPin> m_polygons;
	polygon m_overlap_polygon;
};

// CDesign
class CDesign {
public:
	CDesign();
	~CDesign();
	void addCell(CCell &);
	void printNames();
	int findCell(const std::string&) const;
	double getAreaByCellName(const std::string &);
	const std::vector<CCell>::iterator getCellIterator();
protected:
	node root;
	std::vector<CCell> m_design;
};

// CCell
class CCell {
public:
	CCell();
	~CCell();
	void setName(std::string &);
	const std::string& getName() const;
	void addLayer(CLayer & newLayer);
	const std::vector<CLayer>::iterator getLayerIterator(const std::string& layerName);
	void printNames();
	double getCellArea() const;
	double getCellAreaMultiProc() const;
	double getCellOverlapArea();
	double getCellOverlapAreaMultiProc();
private:
	void createProcess(double &, int) const;
	void createProcessWithOverlap(CLayer&);
	std::string m_cell_name;
	std::vector<CLayer> m_layers;
};

// HashRect
class HashRect {
public:
	std::string setRectHash(std::vector<CRectangle>::iterator);
	static HashRect* getInstance();
	void findRectHashInfo(std::string);
private:
	HashRect();
	~HashRect();
	std::string hashStrGenerator();
	std::map<std::string, std::vector<CRectangle>::iterator> hash_rect_map;
	static HashRect* instance;
};

#endif