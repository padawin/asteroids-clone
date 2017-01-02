#include "Weapon.hpp"

Bullet* Weapon::fire(Vector3D position, Vector3D direction, Vector3D initialSpeed, Vector3D angle) {
	Bullet* b = _createBullet();
	b->setPosition(position);
	b->setDirection(direction);
	Vector3D speed = direction * (initialSpeed.getLength() + b->getSpeed());
	b->setSpeed(speed);
	b->setAngle(angle);
	return b;
}
