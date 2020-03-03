#include "vector.h"
#include "matrix.h"
#include "point.h"
#include "camera.h"

#include <math.h>

namespace r8 {

Camera::Camera(void)
	: m_focal(100.0)
{
}

Camera::Camera(const Vector& position, const Vector& lookAt, const Vector& up)
	: m_position(position)
	, m_lookAt(lookAt)
	, m_focal(100.0)
{
	m_v = up;
	rePoint();
}

Camera::~Camera(void)
{
}

void Camera::pointAt(const Vector& pointAt)
{
	// step 1 - calculate the n vector
	m_n = pointAt - m_position;

	// step 2 - v points straight up for the time being (allows us to calculate the right vector)
	// BUG: if the camera is pointing straight down and we assume up is straight up our vectors get screwed
	m_v = Vector(0.0, 1.0, 0.0);

	// step 3 - calculate the right hand vector as a cross product of the direction and up vectors
	m_u = m_v^m_n;

	// step 4 - now calculate the real up vector as a cross product of the direction and right vectors
	m_v = m_n^m_u;

	// step 5 - normalise all those vectors
	m_u.normalise();
	m_v.normalise();
	m_n.normalise();

	// step 6 - create the world to camera transformation matrix
	m_ctow.FromUVN(m_u, m_v, m_n);
	m_wtoc = m_ctow.inverse();
}

void Camera::toView(Vector& v)
{
	// simply transform into view space
	v = (v - m_position) * m_wtoc;
}

bool Camera::project(const Vector& v, Point& p, Rect& rc)
{
	// the vector coming in should be in view space already by previously calling toView.
	double invz = 0.0;
	if (v.m_z) {
		invz = 1.0 / v.m_z;
	}

	p.x(rc.midx() + (m_focal * v.m_x) * invz);
	p.y(rc.midy() - (m_focal * v.m_y) * invz);

	return true;
}

bool Camera::unProject(Point& p, Vector& v)
{
	Vector tv(p.x() / m_focal, 
			  p.y() / m_focal,
			  1);

	v = (tv * m_ctow);

	return true;
}

void Camera::yaw(float angle)
{
	// create a rotation matrix
	r8::Matrix mat;
	mat.FromEulerAngles(0.0, 0.0, angle);

	// rotate the look and right (n and u) vectors
	m_u = m_u * mat;
	m_u.normalise();
	m_n = m_n * mat;
	m_n.normalise();

	// recreate the world to camera matrix
	m_ctow.FromUVN(m_u, m_v, m_n);
	m_wtoc = m_ctow.inverse();
}

void Camera::pitch(float angle)
{
	// create a rotation matrix
	r8::Matrix mat;
	mat.FromEulerAngles(0.0, angle, 0.0);

	// rotate the look and up (n and v) vectors
	m_n = m_n * mat;
	m_n.normalise();
	m_v = m_v * mat;
	m_v.normalise();

	// recreate the world to camera matrix
	m_ctow.FromUVN(m_u, m_v, m_n);
	m_wtoc = m_ctow.inverse();
}

void Camera::roll(float angle)
{
	// create a rotation matrix
	r8::Matrix mat;
	mat.FromEulerAngles(angle, 0.0, 0.0);

	// rotate the up and right (v and u) vectors
	m_u = m_u * mat;
	m_u.normalise();
	m_v = m_v * mat;
	m_v.normalise();

	// recreate the world to camera matrix
	m_ctow.FromUVN(m_u, m_v, m_n);
	m_wtoc = m_ctow.inverse();
}

void Camera::moveForward(float distance)
{
	m_position += m_n * distance;
}

void Camera::moveBackward(float distance)
{
	m_position -= m_n * distance;
}

void Camera::moveUp(float distance)
{
	m_position += m_v * distance;
}

void Camera::moveDown(float distance)
{
	m_position -= m_v * distance;
}

void Camera::moveLeft(float distance)
{
	m_position -= m_u * distance;
}

void Camera::moveRight(float distance)
{
	m_position += m_u * distance;
}

}
