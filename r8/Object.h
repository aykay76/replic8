#pragma once

// TODO: object should not have windows specific stuff
#include <vector>

#include "r8_base.h"

// TODO: These will be removed!!
class CDC;
class CRect;
class Pen;
class Graphics;
class Brush;
class Rect;

namespace r8 {

class Vector;
class Polygon;
class Camera;

class Object
{
public:
	Object(void);
	Object(const Vector& position, int nVertices);
	~Object(void);

public:
	std::vector<Polygon>& polygons() { return m_polygons; }
	void setVertex(int n, const Vector& v) { if (m_vertices) m_vertices[n] = v; }
	Vector* getVertices() { return m_vertices; }
	Vector* getTransformedVertices() { return m_tvertices; }

	void addTriangle(int v1, int v2, int v3);
//	void addQuad(int v1, int v2, int v3, int v4);
	void addPolygon(const Polygon& polygon);

	Vector& getPosition() { return m_position; }

	virtual void toWorld();
	virtual void removeBackfaces(Camera* pCamera);
	virtual void toView(Camera* pCamera);
	virtual void calcBounds();
	virtual bool checkBounds(Camera* pCamera);
	virtual void render(Renderer& renderer, Rect& rc, Camera* pCamera);

protected:
	Vector* m_vertices;
	int m_nVertices;
	Vector* m_tvertices;
	int m_nTVertices;
	std::vector<Polygon> m_polygons;
	Vector m_position;

public:
	double m_yaw;
	double m_roll;
	double m_pitch;

	float m_minx;
	float m_miny;
	float m_minz;
	float m_maxx;
	float m_maxy;
	float m_maxz;
};

}