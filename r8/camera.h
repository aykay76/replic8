#pragma once

#include "r8_base.h"

namespace r8 {

class Camera
{
public:
	Camera(void);
	Camera(const Vector& position, const Vector& lookAt, const Vector& up);
	~Camera(void);

public:
	Vector& lookAt() { return m_lookAt; }
	void setFocalLength(float focal) { m_focal = focal; }
	float getFocalLength() { return m_focal; }
	void toView(Vector& v);
	bool project(const Vector& v, r8::Point& p, Rect& rc);
	bool unProject(Point& p, Vector& v);
	Vector& position() { return m_position; }
	void position(const Vector& v) { m_position = v; }
	void pointAt(const Vector& pointAt);
	// call this when the camera moves but you want it to point where it was before
	void rePoint() { pointAt(m_lookAt); }

	void yaw(float angle);
	void pitch(float angle);
	void roll(float angle);

	void moveForward(float distance);
	void moveBackward(float distance);
	void moveUp(float distance);
	void moveDown(float distance);
	void moveLeft(float distance);
	void moveRight(float distance);

protected:
	Vector m_position;		// position
	Vector m_lookAt;		// what we are looking at
	Vector m_u;				// u is the new x - the right vector
	Vector m_v;				// v is the new y - the up vector
	Vector m_n;				// n is the new z - the direction we are looking

	float m_focal;			// focal length of camera

	// TODO: These may be temporary
public:
	Matrix m_wtoc;			// world to camera transformation matrix
	Matrix m_ctow;			// camera to world transformation matrix
};

}