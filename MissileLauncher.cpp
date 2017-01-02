#include "MissileLauncher.hpp"

Bullet* MissileLauncher::fire(Vector3D position, Vector3D direction, Vector3D initialSpeed, Vector3D angle) {
	Bullet* b;
	b = new Missile();
	b->setPosition(position);
	b->setDirection(direction);
	Vector3D speed = direction * (initialSpeed.getLength() + b->getSpeed());
	b->setSpeed(speed);
	b->setAngle(angle);
	return b;
}
