#pragma once

#include "r8_base.h"

namespace r8 {

class RendererCDC : public Renderer
{
public:
	RendererCDC(void);
	RendererCDC(CDC* pDC) : m_pDC(pDC) { }
	~RendererCDC(void);

public:
	void setDC(CDC* pDC) { m_pDC = pDC; }
	virtual void drawPoint(int x, int y, Colour& colour);
	virtual void drawLine(int x, int y, int x2, int y2);
	virtual void drawPolygon(Point* pts, int n);

protected:
	CDC* m_pDC;
};

}