#pragma once

const float tol = 0.000001f;
const float pi = 3.141592653f;

#include <math.h>

namespace r8 {
// general mathematical classes
class Vector;
class Matrix;
class Quaternion;
class Vertex;

// some useful classes
class Particle;
class Object;
class Polygon;
class Colour;

// 3D projection stuff
class Point;
class Camera;
class Scene;
class Rect;

/*class Renderer;
class RendererCDC;
class RendererGraphics;*/
class Renderer;

};

#include "rect.h"
#include "colour.h"
#include "vector.h"
#include "matrix.h"
#include "quaternion.h"
#include "point.h"
#include "vertex.h"
#include "object.h"
#include "particle.h"
#include "camera.h"
#include "scene.h"
#include "polygon.h"
#include "renderer.h"