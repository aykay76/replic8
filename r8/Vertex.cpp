#include "point.h"
#include "colour.h"
#include "vector.h"
#include "vertex.h"

namespace r8 {

Vertex::Vertex(void)
{
}

Vertex::Vertex(const Vector& position)
	: m_position(position)
{
}

Vertex::~Vertex(void)
{
}

}