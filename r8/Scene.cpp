#include "point.h"
#include "matrix.h"
#include "vector.h"
#include "camera.h"
#include "object.h"
#include "scene.h"

#include <algorithm>

namespace r8 {

Scene::Scene(void)
	: m_pCamera(NULL)
{
}

Scene::~Scene(void)
{
	std::vector<Camera *>::iterator it = m_cameras.begin();
	std::vector<Camera *>::iterator end = m_cameras.end();
	while (it != end) {
		delete *it;
		++it;
	}
	m_cameras.clear();

	std::vector<Object *>::iterator oit = m_objects.begin();
	std::vector<Object *>::iterator oend = m_objects.end();
	while (oit != oend) {
		delete *oit;
		++oit;
	}
	m_objects.clear();
}


Camera* Scene::createCamera(const Vector& position, const Vector& direction, const Vector& up, bool fUse)
{
	Camera *pCamera = new Camera(position, direction, up);
	m_cameras.push_back(pCamera);

	if (fUse) {
		m_pCamera = pCamera;
	}

	return pCamera;
}

inline void Scene::setCamera(const Camera* pCamera)
{
	std::vector<Camera *>::iterator it = std::find(m_cameras.begin(), m_cameras.end(), pCamera);
	if (it != m_cameras.end()) {
		m_pCamera = *it;
	}
}

Object* Scene::createObject(const Vector& position, int nVertices)
{
	Object *pObject = new Object(position, nVertices);

	m_objects.push_back(pObject);

	return pObject;
}

void Scene::render(Renderer& renderer, Rect& rc)
{
	if (rc.width() > rc.height()) {
		m_pCamera->setFocalLength(rc.width());
	} else {
		m_pCamera->setFocalLength(rc.height());
	}

	std::vector<Object *>::iterator it = m_objects.begin();
	std::vector<Object *>::iterator end = m_objects.end();
	while (it != end) {
		Object *pObject = *it;

		// transform the object from its own space into world space
		pObject->toWorld();

		pObject->removeBackfaces(m_pCamera);

		// TODO: Perform lighting here in world space

		pObject->toView(m_pCamera);

		// update the bounding coordinates of the object
		pObject->calcBounds();

		// see if the object should be displayed before attempting to draw it
		if (pObject->checkBounds(m_pCamera)) {
			pObject->render(renderer, rc, m_pCamera);
		}

		++it;
	}

	// render any particle systems
	std::vector<Particle>::iterator pit = m_particles.begin();
	while (pit != m_particles.end())
	{
		Point pt;

		// particles are already in world coordinates so we simply move into view space.
		Vector v = pit->position();
		m_pCamera->toView(v);
		m_pCamera->project(v, pt, rc);

		Colour colour;
		colour.m_col.c = 0x00000000;
		unsigned char intensity = 128 + (unsigned char)((5.0 - v.z()) * 255.0F);
//		colour.m_col.c |= (intensity << 16);
		colour.m_col.c |= (intensity << 8);
		colour.m_col.c |= (intensity << 0);

//		if (pit->prevPosition().x() != 0.0 && pit->prevPosition().y() != 0.0)
//		{
//			renderer.drawLine(pit->prevPosition().x(), pit->prevPosition().y(), pt.x(), pt.y(), colour);
//		}
//		pit->prevPosition(pt);
		renderer.drawPoint(pt.x(), pt.y(), colour);

		++pit;
	}
}
	
Object* Scene::createCube(const Vector& position, float radius)
{
	Object *pObject = new Object(position, 8);

	pObject->setVertex(0, Vector(radius, radius, radius));
	pObject->setVertex(1, Vector(radius, radius, -radius));
	pObject->setVertex(2, Vector(-radius, radius, -radius));
	pObject->setVertex(3, Vector(-radius, radius, radius));
	pObject->setVertex(4, Vector(radius, -radius, radius));
	pObject->setVertex(5, Vector(radius, -radius, -radius));
	pObject->setVertex(6, Vector(-radius, -radius, -radius));
	pObject->setVertex(7, Vector(-radius, -radius, radius));

	pObject->polygons().reserve(12);
	pObject->addTriangle(0, 1, 2);
	pObject->addTriangle(0, 2, 3);
	pObject->addTriangle(0, 3, 4);
	pObject->addTriangle(3, 7, 4);
	pObject->addTriangle(0, 5, 1);
	pObject->addTriangle(0, 4, 5);
	pObject->addTriangle(5, 2, 1);
	pObject->addTriangle(2, 5, 6);
	pObject->addTriangle(6, 5, 7);
	pObject->addTriangle(5, 4, 7);
	pObject->addTriangle(3, 2, 6);
	pObject->addTriangle(3, 6, 7);

/*	pObject->addQuad(0, 1, 2, 3);
	pObject->addQuad(1, 4, 7, 2);
	pObject->addQuad(4, 5, 6, 7);
	pObject->addQuad(0, 5, 4, 1);
	pObject->addQuad(5, 0, 3, 6);
	pObject->addQuad(3, 2, 7, 6);
*/

	m_objects.push_back(pObject);

	return pObject;
}

void Scene::removeObject(Object* pObject)
{
	std::vector<Object *>::iterator it = std::find(m_objects.begin(), m_objects.end(), pObject);

	if (it != m_objects.end()) {
		m_objects.erase(it);
	}
}

void updateParticle(Particle& particle, double time)
{
	Vector v = particle.position();
	Vector deceleration = (particle.acceleration() * time);

	particle.velocity(particle.velocity() + (particle.acceleration() * time));
	particle.position(particle.position() + (particle.velocity() * time));

	int a = 0;
}

void Scene::update(double time)
{
	// spin all objects by 1 dgree
	std::vector<Object *>::iterator it = m_objects.begin();

	while (it != m_objects.end()) {
		(*it)->m_yaw += 2.0 * 3.141592653 / 180.0;
		++it;
	}
	

	/* NOTE: Keep this for now - it's a very nice fountain particle system
	std::vector<Particle>::iterator it = m_particles.begin();
	while (it != m_particles.end())
	{
		updateParticle(*it, time);

		if (it->position().y() < 0.0) {
			Vector pp(0.0, (float)rand() / ((float)RAND_MAX * 2.0F), 10.0F);
			it->position(pp);
			it->velocity(Vector(
				((float)rand() - ((float)RAND_MAX / 2.0F)) / (float)RAND_MAX, 
				5.0F, 
				((float)rand() - ((float)RAND_MAX / 2.0F)) / (float)RAND_MAX));
			it->acceleration(Vector(0.0, -9.8F, 0));
		}

		if (it != m_particles.end()) ++it;
	}

	if (m_particles.size() < 100000)
	{
		for (int i = 0; i < 5; i++) 
		{
			Vector pp(0.0, (float)rand() / ((float)RAND_MAX * 2.0F), 10.0F);
			Particle particle;
			particle.position(pp);
			particle.velocity(Vector(
				((float)rand() - ((float)RAND_MAX / 2.0F)) / (float)RAND_MAX, 
				5.0F, 
				((float)rand() - ((float)RAND_MAX / 2.0F)) / (float)RAND_MAX));
			particle.acceleration(Vector(0.0, -9.8F, 0));
			m_particles.push_back(particle);
		}
	}
	*/
}

}
