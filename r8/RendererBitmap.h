#pragma once

#include "r8_base.h"

namespace r8 {

class RendererBitmap : public Renderer
{
public:
	RendererBitmap(void);
	RendererBitmap(DWORD* pBitmap, int width, int height)
		: m_bitmap(pBitmap)
		, m_width(width)
		, m_height(height)
		, m_pitch(width) { }

	~RendererBitmap(void);

public:
	virtual void drawPoint(int x, int y, Colour& colour);
	virtual void drawLine(int x, int y, int x2, int y2, Colour& colour);
	virtual void drawPolygon(Point* pts, int n, Colour& colour);

protected:
	DWORD* m_bitmap;
	int m_width;
	int m_height;
	int m_pitch;
};

}