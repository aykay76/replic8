#pragma once

class Vector;
class Matrix;

namespace r8 {

class Vector
{
	friend class Camera;
	friend class Projector;
public:
	Vector();
	Vector(float x, float y, float z);
	~Vector();

public:
	float x() const { return m_x; }
	float y() const { return m_y; }
	float z() const { return m_z; }

	float magnitude();
	void normalise();
	void reverse();
	void fromLLH(double latitude, double longitude, double height);

	Vector& operator+=(const Vector& v);
	Vector& operator-=(const Vector& v);
	Vector& operator*=(float s);
	Vector& operator/=(float s);
	Vector  operator- ();

	friend Vector operator+(const Vector& lhs, const Vector& rhs);
	friend Vector operator-(const Vector& lhs, const Vector& rhs);
	friend Vector operator^(const Vector& lhs, const Vector& rhs);
	friend float operator*(const Vector& lhs, const Vector& rhs);
	friend Vector operator*(float s, const Vector& rhs);
	friend Vector operator*(const Vector& lhs, float s);
	friend Vector operator/(const Vector& lhs, float s);
	friend Vector operator*(const Matrix& lhs, const Vector& rhs);
	friend Vector operator*(const Vector& lhs, const Matrix& rhs);

protected:
	float m_x;
	float m_y;
	float m_z;
	float m_m;
};

}