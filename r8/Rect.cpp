#include "rect.h"

namespace r8 {

Rect::Rect(void)
	: m_x(0)
	, m_y(0)
	, m_width(0)
	, m_height(0)
{
}

Rect::Rect(float x, float y, float width, float height)
	: m_x(x)
	, m_y(y)
	, m_width(width)
	, m_height(height)
{
}

Rect::~Rect(void)
{
}

}