#include "Asteroid.hpp"
#include "Bullet.hpp"
#include "ShapeFactory.hpp"

Asteroid::Asteroid(float distanceRecycle) : m_fDistanceRecycle(distanceRecycle), m_iHP(100) {
	setCenter(Vector3D(0.0f, 0.0f, 0.0f));
}

ShapeType Asteroid::getShapeType() {
	return ASTEROID;
}

bool Asteroid::update(World& world, Vector3D thresholdPosition) {
	if (m_iHP < 0) {
		m_iHP = 0;
	}
	Vector3D distance = getPosition() - thresholdPosition;
	if (m_iHP == 0 || distance.getLength() > m_fDistanceRecycle) {
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
		.radius = 0.5f
	};

	return hz;
}

E_EntityType Asteroid::getType() {
	return ENTITY_ASTEROID;
}

void Asteroid::handleCollision(Entity* entity) {
	switch (entity->getType()) {
		case ENTITY_BULLET:
			// destroyed
			m_iHP -= dynamic_cast<Bullet*>(entity)->getDamages();
			break;
		default:
			break;
	}
}
