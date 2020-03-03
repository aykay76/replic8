#include "quaternion.h"

namespace r8 {

Quaternion::Quaternion()
	: m_x(0)
	, m_y(0)
	, m_z(0)
	, m_s(0)
{
}

Quaternion::Quaternion(double x, double y, double z, double s)
	: m_x(x)
	, m_y(y)
	, m_z(z)
	, m_s(s)
{
}

double Quaternion::magnitude()
{
	return vector().magnitude();
}

Vector Quaternion::vector()
{
	return Vector(m_x, m_y, m_z);
}

double Quaternion::scalar()
{
	return m_s;
}

}