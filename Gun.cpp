#include "Gun.hpp"

Bullet* Gun::fire(Vector3D position, Vector3D direction, Vector3D initialSpeed) {
	Bullet* b;
	b = new GunBullet();
	b->setPosition(position);
	b->setDirection(direction);
	Vector3D speed = direction * (initialSpeed.getLength() + b->getSpeed());
	b->setSpeed(speed);
	return b;
}
