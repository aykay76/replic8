#pragma once

namespace r8 {

class Point
{
public:
	Point(void);
	Point(float x, float y);
	~Point(void);

public:
	float x() { return m_x; }
	float y() { return m_y; }
	void x(float x) { m_x = x; }
	void y(float y) { m_y = y; }

protected:
	float m_x;
	float m_y;
};

}