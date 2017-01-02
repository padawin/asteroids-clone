#include "Bullet.hpp"

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
