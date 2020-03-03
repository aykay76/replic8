#pragma once

namespace r8 {

class Vector;
class Point;
class Colour;

class Vertex
{
public:
	Vertex(void);
	Vertex(const Vector& position);
	~Vertex(void);

public:
	Vector& position() { return m_position; }
	void position(Vector& position) { m_position = position; }

protected:
	Vector m_position;				// position of vertex
	Vector m_normal;				// normal to vertex
	Point m_texture;				// texture start pos
	Colour m_colour;				// colour of this vertex
};

}