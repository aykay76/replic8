#include "point.h"
#include "matrix.h"
#include "vector.h"
#include "camera.h"
#include "object.h"
#include "polygon.h"

namespace r8 {

Polygon::Polygon(void)
//	: m_pPoints(NULL)
{
}

Polygon::Polygon(Object* pObject, int v1, int v2, int v3)
	: m_pObject(pObject)
	, m_backface(false)
{
	m_vertices[0] = v1;
	m_vertices[1] = v2;
	m_vertices[2] = v3;
}

Polygon::~Polygon(void)
{
}

// Project the vertices, handle the 2D clipping, then if visible etc. pass to renderer to render
// the actual polygon on the screen
void Polygon::render(Renderer& renderer, Rect& rc, Camera* pCamera, Colour& colour)
{
	int i = 0;

	Point* pts = new Point[3];

	for (int i = 0; i < 3; i++)
	{
		pCamera->project(m_pObject->getTransformedVertices()[m_vertices[i]], pts[i], rc);
	}

	renderer.drawPolygon(pts, 3, colour);

	delete [] pts;
}

Vector& Polygon::calcNormal()
{
	// v1 = 2 - 1
	// v2 = 0 - 1
	// normal = v1 (dot) v2
	r8::Vector v1 = m_pObject->getVertices()[m_vertices[1]] - m_pObject->getVertices()[m_vertices[0]];
	r8::Vector v2 = m_pObject->getVertices()[m_vertices[2]] - m_pObject->getVertices()[m_vertices[0]];

	m_normal = v1^v2;
	m_normal.normalise();

	return m_normal;
}


}
