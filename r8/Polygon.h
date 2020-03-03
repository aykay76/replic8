#pragma once

#include <vector>

#include "r8_base.h"

namespace r8 {

class Object;
class Camera;
class Point;

class Polygon
{
public:
	Polygon(void);
	Polygon(Object* pObject, int v1, int v2, int v3);
	~Polygon(void);

public:
	Vector& calcNormal();
	void setObject(Object* pObject) { m_pObject = pObject; }
	void render(Renderer& renderer, Rect& rc, Camera* pCamera, Colour& colour);
	r8::Vector& normal() { return m_normal; }
	int* vertices() { return m_vertices; }
	bool backface() { return m_backface; }
	void backface(bool f) { m_backface = f; }

protected:
	int m_nVertices;
	Object *m_pObject;
	int m_vertices[3];
	bool m_backface;			// flag to indicate whether this polygon is a backface or not

	r8::Vector m_normal;
};

}