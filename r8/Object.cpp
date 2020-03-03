#include "matrix.h"
#include "vector.h"
#include "polygon.h"
#include "object.h"

#include <float.h>

namespace r8 {

Object::Object(void)
	: m_roll(0.0)
	, m_pitch(0.0)
	, m_yaw(0.0)
	, m_vertices(NULL)
	, m_nVertices(0)
{
}

Object::Object(const Vector& position, int nVertices)
	: m_position(position)
	, m_roll(0.0)
	, m_pitch(0.0)
	, m_yaw(0.0)
{
	m_nVertices = nVertices;
	m_vertices = new Vector[nVertices];
	m_tvertices = new Vector[nVertices];
}

Object::~Object(void)
{
	if (m_vertices != NULL) {
		delete [] m_vertices;
	}
	if (m_tvertices != NULL) {
		delete [] m_tvertices;
	}
}

void Object::addTriangle(int v1, int v2, int v3)
{
	m_polygons.push_back(Polygon(this, v1, v2, v3));
}
/*
void Object::addQuad(int v1, int v2, int v3, int v4)
{
	Polygon polygon(this, 5);
	polygon.addVertex(v1);
	polygon.addVertex(v2);
	polygon.addVertex(v3);
	polygon.addVertex(v4);
	polygon.setObject(this);
	polygon.calcNormal();

	m_polygons.push_back(polygon);
}
*/
void Object::toWorld()
{
	Matrix mobject;
	mobject.FromEulerAngles(m_roll, m_pitch, m_yaw);

	m_minx = FLT_MAX;
	m_maxx = FLT_MIN;
	m_miny = FLT_MAX;
	m_maxy = FLT_MIN;
	m_minz = FLT_MAX;
	m_maxz = FLT_MIN;

	for (int i = 0; i < m_nVertices; i++) {
		// the vertices in the object are in object space (ie. their position is relative
		// to the object's position) this means that rotations can be transformed as though
		// they are at the origin because of course they are.
		m_tvertices[i] = (m_vertices[i] * mobject) + m_position;

		if (m_tvertices[i].x() < m_minx) m_minx = m_tvertices[i].x();
		if (m_tvertices[i].x() > m_maxx) m_maxx = m_tvertices[i].x();
		if (m_tvertices[i].y() < m_miny) m_miny = m_tvertices[i].y();
		if (m_tvertices[i].y() > m_maxy) m_maxy = m_tvertices[i].y();
		if (m_tvertices[i].z() < m_minz) m_minz = m_tvertices[i].z();
		if (m_tvertices[i].z() > m_maxz) m_maxz = m_tvertices[i].z();
	}

	// The object is now in 'world' space.  :D
}

void Object::toView(Camera* pCamera)
{
	for (int i = 0; i < m_nVertices; i++) {
		pCamera->toView(m_tvertices[i]);
	}
}

bool Object::checkBounds(Camera* pCamera)
{
	if ((m_maxz < m_minx) || (m_maxz < m_miny) ||
		(m_maxz < -m_maxx) || (m_maxz < -m_maxy) || 
		(m_maxz <= 1.0))
		return false;
	
	return true;
}

void Object::removeBackfaces(Camera* pCamera)
{
	std::vector<Polygon>::iterator pit = m_polygons.begin();
	std::vector<Polygon>::iterator pend = m_polygons.end();

	while (pit != pend) {
		// each polygon will be checked to see if its normal faces into the camera
//		Vector &normal = pit->normal();
		Vector u = m_tvertices[pit->vertices()[1]] - m_tvertices[pit->vertices()[0]];
		Vector v = m_tvertices[pit->vertices()[2]] - m_tvertices[pit->vertices()[0]];
		Vector n = u^v;
		
		Vector view = pCamera->position() - m_tvertices[pit->vertices()[0]];
		float angle = view * n;

		if (angle <= 0.0)
		{
			pit->backface(true);
		}
		else
		{
			pit->backface(false);
		}

		++pit;
	}
}

void Object::render(Renderer& renderer, Rect& rc, Camera* pCamera)
{
	std::vector<Polygon>::iterator pit = m_polygons.begin();
	std::vector<Polygon>::iterator pend = m_polygons.end();
	while (pit != pend) {
		// we don't do backfaces
		if (pit->backface() == false)
		{
			Colour col;
			col.m_col.c = 0xffffffff;
			pit->render(renderer, rc, pCamera, col);
		}

		++pit;
	}
}

void Object::calcBounds()
{
	m_minx = FLT_MAX, m_maxx = -FLT_MAX, m_miny = FLT_MAX, m_maxy = -FLT_MAX, m_minz = FLT_MAX, m_maxz = -FLT_MAX;
	for (int i = 0; i < m_nVertices; i++) {
		if (m_tvertices[i].x() < m_minx) m_minx = m_tvertices[i].x();
		if (m_tvertices[i].x() > m_maxx) m_maxx = m_tvertices[i].x();
		if (m_tvertices[i].y() < m_miny) m_miny = m_tvertices[i].y();
		if (m_tvertices[i].y() > m_maxy) m_maxy = m_tvertices[i].y();
		if (m_tvertices[i].z() < m_minz) m_minz = m_tvertices[i].z();
		if (m_tvertices[i].z() > m_maxz) m_maxz = m_tvertices[i].z();
	}
}

}