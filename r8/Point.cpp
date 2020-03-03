#include "point.h"

namespace r8 {

Point::Point(void)
	: m_x(0)
	, m_y(0)
{
}

Point::Point(float x, float y)
	: m_x(x)
	, m_y(y)
{
}

Point::~Point(void)
{
}

}