#pragma once

namespace r8 {

class Point;

class Renderer
{
public:
	Renderer();
	~Renderer();

	enum RenderMode {
		Spot = 0, Wireframe, Flat, Gourad, Texture
	};

public:
	virtual void drawPoint(int x, int y, Colour& colour) = 0;
	virtual void drawLine(int x, int y, int x2, int y2, Colour& colour) = 0;
	virtual void drawPolygon(Point* pts, int n, Colour& colour) = 0;

protected:
	RenderMode m_renderMode;
};

}