#include "Asteroid.hpp"
#include "ShapeFactory.hpp"

Asteroid::Asteroid(float distanceRecycle) : m_fDistanceRecycle(distanceRecycle) {
	setCenter(Vector3D(0.5f, 0.5f, 0.5f));
}

ShapeType Asteroid::getShapeType() {
	return ASTEROID;
}

bool Asteroid::update(World& world, Vector3D thresholdPosition) {
	Vector3D distance = getPosition() - thresholdPosition;
	if (distance.getLength() > m_fDistanceRecycle) {
		return false;
	}
	else {
		return Entity::update(world, thresholdPosition);
	}
}

S_Circle Asteroid::getHitZone() {
	S_Circle hz = {
		.x = getPosition().getX(),
		.y = getPosition().getY(),
		.radius = 1.0f
	};

	return hz;
}
