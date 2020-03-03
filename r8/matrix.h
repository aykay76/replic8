#pragma once

/////////////////////////////////////////////////////////////////////
//
//	class Matrix
//	============
//
//	A general matrix class used in any mathematical matrix operations
//	(mostly rotation in 3D) but also in other situations
//


namespace r8 {
class Matrix;
class Vector;

class Matrix
{
public:
	Matrix(void);
	Matrix(float r1c1, float r1c2, float r1c3,
		   float r2c1, float r2c2, float r2c3,
		   float r3c1, float r3c2, float r3c3);
	~Matrix(void);

public:
	void FromUVN(const r8::Vector& u, const r8::Vector& v, const r8::Vector& n);
	void FromEulerAngles(float roll, float pitch, float yaw, bool reverse = false);
	float det();
	Matrix transpose();
	Matrix inverse();
	void identity();

	Matrix& operator+=(const Matrix& rhs);
	Matrix& operator-=(const Matrix& rhs);
	Matrix& operator*=(float s);
	Matrix& operator/=(float s);

	friend Matrix operator+(const Matrix& lhs, const Matrix& rhs);
	friend Matrix operator-(const Matrix& lhs, const Matrix& rhs);
	friend Matrix operator/(const Matrix& lhs, float s);
	friend Matrix operator*(const Matrix& lhs, float s);
	friend Matrix operator*(float s, const Matrix& lhs);
	friend Matrix operator*(const Matrix& lhs, const Matrix& rhs);
	friend Vector operator*(const Matrix& lhs, const Vector& rhs);
	friend Vector operator*(const Vector& lhs, const Matrix& rhs);

public:
	float m_r1c1, m_r1c2, m_r1c3;
	float m_r2c1, m_r2c2, m_r2c3;
	float m_r3c1, m_r3c2, m_r3c3;
};

}