#include "colour.h"
#include "vector.h"

#include <math.h>

namespace r8 {

	static double tol = 0.00001;

Vector::Vector()
{
	m_x = 0;
	m_y = 0;
	m_z = 0;
	m_m = -1;
}

Vector::Vector(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
//	m_m = (float)sqrt(m_x * m_x + m_y * m_y + m_z * m_z);
}

Vector::~Vector()
{
}

inline float Vector::magnitude()
{
	m_m = (float)sqrt(m_x * m_x + m_y * m_y + m_z * m_z);

	return m_m;
}

void Vector::normalise()
{
	float m = magnitude();
	if (m <= tol) m = 1.0;

	float im = 1 / m;

	m_x *= im;
	m_y *= im;
	m_z *= im;

	if (fabs(m_x) < tol) m_x = 0.0;
	if (fabs(m_y) < tol) m_y = 0.0;
	if (fabs(m_z) < tol) m_z = 0.0;
}

inline void Vector::reverse()
{
	m_x = -m_x; m_y = -m_y; m_z = -m_z;
}

void Vector::fromLLH(double latitude, double longitude, double height)
{
	m_x = cos(latitude) * sin(longitude) * height;
	m_y = sin(latitude) * height;
	m_z = cos(latitude) * cos(longitude) * height;
}


Vector& Vector::operator+=(const Vector &v)
{
	m_x += v.m_x;
	m_y += v.m_y;
	m_z += v.m_z;
	return *this;
}

Vector& Vector::operator-=(const Vector &v)
{
	m_x -= v.m_x;
	m_y -= v.m_y;
	m_z -= v.m_z;
	return *this;
}

Vector& Vector::operator*=(float s)
{
	m_x *= s;
	m_y *= s;
	m_z *= s;
	return *this;
}

Vector& Vector::operator/=(float s)
{
	float is = 1.0 / s;
	m_x *= is;
	m_y *= is;
	m_z *= is;
	return *this;
}

Vector Vector::operator-()
{
	return Vector(-m_x, -m_y, -m_z);
}

Vector operator+(const Vector& lhs, const Vector& rhs)
{
	return Vector(lhs.m_x + rhs.m_x, lhs.m_y + rhs.m_y, lhs.m_z + rhs.m_z);
}

Vector operator-(const Vector& lhs, const Vector& rhs)
{
	return Vector(lhs.m_x - rhs.m_x, lhs.m_y - rhs.m_y, lhs.m_z - rhs.m_z);
}

// this is the cross product!
Vector operator^(const Vector& lhs, const Vector& rhs)
{
	return Vector(lhs.m_y * rhs.m_z - lhs.m_z * rhs.m_y,
				  lhs.m_z * rhs.m_x - lhs.m_x * rhs.m_z,
				  lhs.m_x * rhs.m_y - lhs.m_y * rhs.m_x);
}

float operator*(const Vector& lhs, const Vector& rhs)
{
	return ((lhs.m_x * rhs.m_x) + (lhs.m_y * rhs.m_y) + (lhs.m_z * rhs.m_z));
}

Vector operator*(float s, const Vector& rhs)
{
	return Vector(rhs.m_x * s, rhs.m_y * s, rhs.m_z * s);
}

Vector operator*(const Vector& lhs, float s)
{
	return Vector(lhs.m_x * s, lhs.m_y * s, lhs.m_z * s);
}

Vector operator/(const Vector& lhs, float s)
{
	return Vector(lhs.m_x / s, lhs.m_y / s, lhs.m_z / s);
}

}