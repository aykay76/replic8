#pragma once

class Vector;
class Matrix;

#include "vector.h"

namespace r8 {

class Quaternion
{
public:
	Quaternion();
	Quaternion(double x, double y, double z, double s);
	~Quaternion();

public:
	double magnitude();
	Vector vector();
	double scalar();

protected:
	double m_x;
	double m_y;
	double m_z;
	double m_s;
};


}