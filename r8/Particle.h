#pragma once

namespace r8 {

class Vector;
class Point;

class Particle
{
public:
	Particle(void);
	~Particle(void);

public:
	Vector& position() { return m_position; }
	void position(Vector& v) { m_position = v; }
	Vector& velocity() { return m_velocity; }
	void velocity(Vector& v) { m_velocity = v; }
	Vector& acceleration() { return m_acceleration; }
	void acceleration(Vector& v) { m_acceleration = v; }
	double mass() { return m_mass; }
	void mass(double d) { m_mass = d; }

	Point prevPosition() { return m_prevPosition; }
	void prevPosition(Point p) { m_prevPosition = p; }

protected:
	Vector m_position;
	Vector m_velocity;
	Vector m_acceleration;
	double m_mass;
	Point m_prevPosition;
};

}