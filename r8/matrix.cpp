#include "matrix.h"
#include "vector.h"
#include <math.h>

namespace r8 {

Matrix::Matrix(void)
{
	m_r1c1 = 1; m_r1c2 = 0; m_r1c3 = 0;
	m_r2c1 = 0; m_r2c2 = 1; m_r2c3 = 0;
	m_r3c1 = 0; m_r3c2 = 0; m_r3c3 = 1;
}

Matrix::Matrix(float r1c1, float r1c2, float r1c3,
			   float r2c1, float r2c2, float r2c3,
			   float r3c1, float r3c2, float r3c3)
{
	m_r1c1 = r1c1; m_r1c2 = r1c2; m_r1c3 = r1c3;
	m_r2c1 = r2c1; m_r2c2 = r2c2; m_r2c3 = r2c3;
	m_r3c1 = r3c1; m_r3c2 = r3c2; m_r3c3 = r3c3;
}

Matrix::~Matrix(void)
{
}

void Matrix::identity()
{
	m_r1c1 = 1.0; m_r1c2 = 0.0; m_r1c3 = 0.0;
	m_r2c1 = 0.0; m_r2c2 = 1.0; m_r2c3 = 0.0;
	m_r3c1 = 0.0; m_r3c2 = 0.0; m_r3c3 = 1.0;
}

// The reverse flag specified whether this is a reversed matrix - world/view matrices
// are reversed
void Matrix::FromEulerAngles(float roll, float pitch, float yaw, bool reverse)
{
	float cosroll = (float)cos(roll);
	float sinroll = (float)sin(roll);
	float cospitch = (float)cos(pitch);
	float sinpitch = (float)sin(pitch);
	float cosyaw = (float)cos(yaw);
	float sinyaw = (float)sin(yaw);

	if (reverse) {
		m_r1c1 = (cosroll * cosyaw) - (sinroll * sinpitch*sinyaw);
		m_r2c1 = (sinroll * cosyaw) + (cosroll * (sinpitch*sinyaw));
		m_r3c1 = (cospitch * sinyaw);

		m_r1c2 = -(sinroll * cospitch);
		m_r2c2 = (cosroll * cospitch);
		m_r3c2 = -sinpitch;

		m_r1c3 = -(cosroll * sinyaw) - (sinroll * (sinpitch * cosyaw));
		m_r2c3 =(cosroll * (sinpitch * cosyaw)) - (sinroll * sinyaw);
		m_r3c3 =(cospitch * cosyaw);              /* calculating the matrix */
	} else {
		m_r1c1 = sinyaw * sinpitch * sinroll + cosyaw * cosroll;
		m_r2c1 = cospitch * sinroll;
		m_r3c1 = sinyaw * cosroll - cosyaw * sinpitch * sinroll;
		m_r1c2 = sinyaw * sinpitch * cosroll - cosyaw * sinroll;
		m_r2c2 = cospitch * cosroll;
		m_r3c2 = -cosyaw * sinpitch * cosroll - sinyaw * sinroll;
		m_r1c3 = -sinyaw * cospitch;
		m_r2c3 = sinpitch;
		m_r3c3 = cosyaw * cospitch;
	}
/*
	m_r1c1 = cosroll * cospitch;
	m_r1c2 = sinyaw * sinpitch * cosroll - cosyaw * sinroll;
	m_r1c3 = cosyaw * sinpitch * cosroll + sinyaw * sinroll;
	m_r2c1 = cospitch * sinroll;
	m_r2c2 = sinyaw * sinpitch * sinroll + cosyaw * cosroll;
	m_r2c3 = sinroll * sinpitch * cosyaw - cosroll * sinyaw;
	m_r3c1 = -sinpitch;
	m_r3c2 = cospitch * sinyaw;
	m_r3c3 = cospitch * cosyaw;*/
}

float Matrix::det()
{
	return m_r1c1 * m_r2c2 * m_r3c3 - 
		   m_r1c1 * m_r3c2 * m_r2c3 + 
		   m_r2c1 * m_r3c2 * m_r1c3 -
		   m_r2c1 * m_r1c2 * m_r3c3 + 
		   m_r3c1 * m_r1c2 * m_r2c3 - 
		   m_r3c1 * m_r2c2 * m_r1c3;
}

Matrix Matrix::transpose()
{
	return Matrix(m_r1c2, m_r2c1, m_r3c1,
				  m_r1c2, m_r2c2, m_r3c2,
				  m_r1c3, m_r2c3, m_r3c3);
}

Matrix Matrix::inverse()
{
	float d = det();

	if (d == 0.0) d = 1.0;

	return Matrix((m_r2c2 * m_r3c3 - m_r2c3 * m_r3c2) / d,
				 -(m_r1c2 * m_r3c3 - m_r1c3 * m_r3c2) / d,
				  (m_r1c2 * m_r2c3 - m_r1c3 * m_r2c2) / d,
			     -(m_r2c1 * m_r3c3 - m_r2c3 * m_r3c1) / d,
				  (m_r1c1 * m_r3c3 - m_r1c3 * m_r3c1) / d,
			     -(m_r1c1 * m_r2c3 - m_r1c3 * m_r2c1) / d,
				  (m_r2c1 * m_r3c2 - m_r2c2 * m_r3c1) / d,
			     -(m_r1c1 * m_r3c2 - m_r1c2 * m_r3c1) / d,
				  (m_r1c1 * m_r2c2 - m_r1c2 * m_r2c1) / d);
}

Matrix& Matrix::operator+=(const Matrix& rhs)
{
	m_r1c1 += rhs.m_r1c1; m_r1c2 += rhs.m_r1c2; m_r1c3 += rhs.m_r1c3;
	m_r2c1 += rhs.m_r2c1; m_r2c2 += rhs.m_r2c2; m_r2c3 += rhs.m_r2c3;
	m_r3c1 += rhs.m_r3c1; m_r3c2 += rhs.m_r3c2; m_r3c3 += rhs.m_r3c3;
	return *this;
}

Matrix& Matrix::operator-=(const Matrix& rhs)
{
	m_r1c1 -= rhs.m_r1c1; m_r1c2 -= rhs.m_r1c2; m_r1c3 -= rhs.m_r1c3;
	m_r2c1 -= rhs.m_r2c1; m_r2c2 -= rhs.m_r2c2; m_r2c3 -= rhs.m_r2c3;
	m_r3c1 -= rhs.m_r3c1; m_r3c2 -= rhs.m_r3c2; m_r3c3 -= rhs.m_r3c3;
	return *this;
}

Matrix& Matrix::operator*=(float s)
{
	m_r1c1 *= s; m_r1c2 *= s; m_r1c3 *= s;
	m_r2c1 *= s; m_r2c2 *= s; m_r2c3 *= s;
	m_r3c1 *= s; m_r3c2 *= s; m_r3c3 *= s;
	return *this;
}

Matrix& Matrix::operator/=(float s)
{
	m_r1c1 /= s; m_r1c2 /= s; m_r1c3 /= s;
	m_r2c1 /= s; m_r2c2 /= s; m_r2c3 /= s;
	m_r3c1 /= s; m_r3c2 /= s; m_r3c3 /= s;
	return *this;
}

Matrix operator+(const Matrix& lhs, const Matrix& rhs)
{
	return Matrix(
		lhs.m_r1c1 + rhs.m_r1c1, lhs.m_r1c2 + rhs.m_r1c2, lhs.m_r1c3 + rhs.m_r1c3,
		lhs.m_r2c1 + rhs.m_r2c1, lhs.m_r2c2 + rhs.m_r2c2, lhs.m_r2c3 + rhs.m_r2c3,
		lhs.m_r3c1 + rhs.m_r3c1, lhs.m_r3c2 + rhs.m_r3c2, lhs.m_r3c3 + rhs.m_r3c3
		);
}

Matrix operator-(const Matrix& lhs, const Matrix& rhs)
{
	return Matrix(
		lhs.m_r1c1 - rhs.m_r1c1, lhs.m_r1c2 - rhs.m_r1c2, lhs.m_r1c3 - rhs.m_r1c3,
		lhs.m_r2c1 - rhs.m_r2c1, lhs.m_r2c2 - rhs.m_r2c2, lhs.m_r2c3 - rhs.m_r2c3,
		lhs.m_r3c1 - rhs.m_r3c1, lhs.m_r3c2 - rhs.m_r3c2, lhs.m_r3c3 - rhs.m_r3c3
		);
}

Matrix operator/(const Matrix& lhs, float s)
{
	return Matrix(
		lhs.m_r1c1 / s, lhs.m_r1c2 / s, lhs.m_r1c3 / s,
		lhs.m_r2c1 / s, lhs.m_r2c2 / s, lhs.m_r2c3 / s,
		lhs.m_r3c1 / s, lhs.m_r3c2 / s, lhs.m_r3c3 / s
		);
}

Matrix operator*(const Matrix& lhs, float s)
{
	return Matrix(
		lhs.m_r1c1 * s, lhs.m_r1c2 * s, lhs.m_r1c3 * s,
		lhs.m_r2c1 * s, lhs.m_r2c2 * s, lhs.m_r2c3 * s,
		lhs.m_r3c1 * s, lhs.m_r3c2 * s, lhs.m_r3c3 * s
		);
}

Matrix operator*(float s, const Matrix& lhs)
{
	return Matrix(
		lhs.m_r1c1 * s, lhs.m_r1c2 * s, lhs.m_r1c3 * s,
		lhs.m_r2c1 * s, lhs.m_r2c2 * s, lhs.m_r2c3 * s,
		lhs.m_r3c1 * s, lhs.m_r3c2 * s, lhs.m_r3c3 * s
		);
}

Matrix operator*(const Matrix& lhs, const Matrix& rhs)
{
	return Matrix(
		lhs.m_r1c1 * rhs.m_r1c1 + lhs.m_r1c2 * rhs.m_r2c1 + lhs.m_r1c3 * rhs.m_r3c1,
		lhs.m_r1c1 * rhs.m_r1c2 + lhs.m_r1c2 * rhs.m_r2c2 + lhs.m_r1c3 * rhs.m_r3c2,
		lhs.m_r1c1 * rhs.m_r1c3 + lhs.m_r1c2 * rhs.m_r2c3 + lhs.m_r1c3 * rhs.m_r3c3,
		lhs.m_r2c1 * rhs.m_r1c1 + lhs.m_r2c2 * rhs.m_r2c1 + lhs.m_r2c3 * rhs.m_r3c1,
		lhs.m_r2c1 * rhs.m_r1c2 + lhs.m_r2c2 * rhs.m_r2c2 + lhs.m_r2c3 * rhs.m_r3c2,
		lhs.m_r2c1 * rhs.m_r1c3 + lhs.m_r2c2 * rhs.m_r2c3 + lhs.m_r2c3 * rhs.m_r3c3,
		lhs.m_r3c1 * rhs.m_r1c1 + lhs.m_r3c2 * rhs.m_r2c1 + lhs.m_r3c3 * rhs.m_r3c1,
		lhs.m_r3c1 * rhs.m_r1c2 + lhs.m_r3c2 * rhs.m_r2c2 + lhs.m_r3c3 * rhs.m_r3c2,
		lhs.m_r3c1 * rhs.m_r1c3 + lhs.m_r3c2 * rhs.m_r2c3 + lhs.m_r3c3 * rhs.m_r3c3
		);
}

Vector operator*(const Matrix& lhs, const Vector& rhs)
{
	return Vector(
		lhs.m_r1c1 * rhs.m_x + lhs.m_r1c2 * rhs.m_y + lhs.m_r1c3 * rhs.m_z,
		lhs.m_r2c1 * rhs.m_x + lhs.m_r2c2 * rhs.m_y + lhs.m_r2c3 * rhs.m_z,
		lhs.m_r3c1 * rhs.m_x + lhs.m_r3c2 * rhs.m_y + lhs.m_r3c3 * rhs.m_z
		);
}

Vector operator*(const Vector& lhs, const Matrix& rhs)
{
	return Vector(
		rhs.m_r1c1 * lhs.m_x + rhs.m_r1c2 * lhs.m_y + rhs.m_r1c3 * lhs.m_z,
		rhs.m_r2c1 * lhs.m_x + rhs.m_r2c2 * lhs.m_y + rhs.m_r2c3 * lhs.m_z,
		rhs.m_r3c1 * lhs.m_x + rhs.m_r3c2 * lhs.m_y + rhs.m_r3c3 * lhs.m_z
		);
}

void Matrix::FromUVN(const r8::Vector& u, const r8::Vector& v, const r8::Vector& n)
{
	m_r1c1 = u.x();
	m_r2c1 = u.y();
	m_r3c1 = u.z();

	m_r1c2 = v.x();
	m_r2c2 = v.y();
	m_r3c2 = v.z();

	m_r1c3 = n.x();
	m_r2c3 = n.y();
	m_r3c3 = n.z();
}


}