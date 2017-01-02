#include "Bullet.hpp"
#include "config.h"

bool Bullet::update(World& world, Vector3D referencePosition) {
	Vector3D distance = getPosition() - referencePosition;
	if (distance.getLength() > MAX_DISTANCE_FROM_PLAYER) {
		return false;
	}
	else {
		return Entity::update(world, referencePosition);
	}
}

ShapeType GunBullet::getShapeType() {
	return GUN_BULLET;
}

float GunBullet::getSpeed() {
	return 0.2f;
}

ShapeType Missile::getShapeType() {
	return MISSILE;
}

float Missile::getSpeed() {
	return 0.3f;
}
