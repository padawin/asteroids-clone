#include "Asteroid.hpp"
#include "ShapeFactory.hpp"

Asteroid::Asteroid(float distanceRecycle) : m_fDistanceRecycle(distanceRecycle) {
	setCenter(Vector3D(0.5f, 0.5f, 0.5f));
}

ShapeType Asteroid::getShapeType() {
	return ASTEROID;
}
