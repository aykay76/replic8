#pragma once

namespace r8 {

class Rect
{
public:
	Rect(void);
	Rect(float x, float y, float width, float height);
	~Rect(void);

public:
	float x() { return m_x; }
	float y() { return m_y; }
	float width() { return m_width; }
	float height() { return m_height; }
	void x(float x) { m_x = x; }
	void y(float y) { m_y = y; }
	float midx() { return (m_x + m_width / 2.0); }
	float midy() { return (m_y + m_height / 2.0); }

protected:
	float m_x;
	float m_y;
	float m_width;
	float m_height;
};

}