#pragma once

#include <vector>
#include "r8_base.h"

// TODO: These will be removed!!
class CDC;
class Pen;
class Graphics;
class Brush;
class Rect;

namespace r8 {

class Camera;
class Object;
class Vector;
class Rect;

class Scene
{
public:
	Scene(void);
	~Scene(void);

public:
	Camera* createCamera(const Vector& position, const Vector& direction, const Vector& up, bool fUse = true);
	void setCamera(const Camera* pCamera);
	Camera* activeCamera() { return m_pCamera; }

	void addObject(Object* pObject) { m_objects.push_back(pObject); }
	void removeObject(Object* pObject);
	Object* createObject(const Vector& position, int nVertices);
	Object* createCube(const Vector& position, float radius);

	void update(double time);
	void render(Renderer& renderer, Rect& rc);

	std::vector<Particle> m_particles;
protected:
	std::vector<Camera *> m_cameras;	// collection of cameras
	Camera *m_pCamera;					// the camera used to view the scene
	Matrix m_worldToView;				// world to view matrix, based on camera position and direction

	std::vector<Object *> m_objects;	// collection of objects in the scene

	// TODO: Add background for scene
	// TODO: Add billboards to scene to set boundaries
};

}