#include <afxwin.h>
#include "RendererCDC.h"

namespace r8 {

RendererCDC::RendererCDC(void)
{
}

RendererCDC::~RendererCDC(void)
{
}

void RendererCDC::drawPoint(int x, int y, Colour& colour)
{
	m_pDC->SetPixel(x, y, RGB(colour.m_col.c, 1, 1));
}

void RendererCDC::drawLine(int x, int y, int x2, int y2)
{
}

void RendererCDC::drawPolygon(Point* pts, int n)
{
	if (m_renderMode == Wireframe) {
		m_pDC->MoveTo(pts[0].x(), pts[0].y());
		for (int i = 1; i < n; i++) {
			m_pDC->LineTo(pts[i].x(), pts[i].y());
		}
	}
}

}