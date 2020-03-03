#include "matrix.h"
#include "vector.h"
#include "point.h"
#include "particle.h"

namespace r8 {

Particle::Particle(void)
	: m_prevPosition(0.0F, 0.0F)
{
}

Particle::~Particle(void)
{
}
}