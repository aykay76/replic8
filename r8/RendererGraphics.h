#pragma once

#include "r8_base.h"
#include <gdiplus.h>

namespace r8 {

class RendererGraphics : public Renderer
{
public:
	RendererGraphics(Gdiplus::Graphics& graphics);
	~RendererGraphics(void);

public:
	virtual void drawPoint(int x, int y, Colour& colour);
	virtual void drawLine(int x, int y, int x2, int y2, Colour& colour);
	virtual void drawPolygon(Point* pts, int n, Colour& colour);

protected:
	Gdiplus::Graphics& m_graphics;
	Gdiplus::Pen pen;
};

}