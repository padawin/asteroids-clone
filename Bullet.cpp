#include "Bullet.hpp"
#include "config.h"

bool Bullet::update(World& world, Vector3D referencePosition) {
	Vector3D distance = getPosition() - referencePosition;
	if (m_bDestroyed || distance.getLength() > MAX_DISTANCE_FROM_PLAYER) {
		return false;
	}
	else {
		return Entity::update(world, referencePosition);
	}
}

S_Circle Bullet::getHitZone() {
	S_Circle hz = {
		.x = getPosition().getX(),
		.y = getPosition().getY(),
		.radius = 1.0f
	};

	return hz;
}

E_EntityType Bullet::getType() {
	return ENTITY_BULLET;
}

void Bullet::handleCollision(Entity* entity) {
	if (entity->getType() != ENTITY_BULLET) {
		m_bDestroyed = true;
	}
}

ShapeType GunBullet::getShapeType() {
	return GUN_BULLET;
}

float GunBullet::getSpeed() {
	return 0.2f;
}

int GunBullet::getDamages() {
	return 10;
}

ShapeType Missile::getShapeType() {
	return MISSILE;
}

float Missile::getSpeed() {
	return 0.3f;
}

int Missile::getDamages() {
	return 100;
}
