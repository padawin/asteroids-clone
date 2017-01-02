#include "Weapon.hpp"

Bullet* Weapon::fire(Vector3D position, Vector3D direction, Vector3D initialSpeed, Vector3D angle) {
	if (m_iReloadedPercent < 100) {
		return NULL;
	}

	Bullet* b = _createBullet();
	b->setPosition(position);
	b->setDirection(direction);
	Vector3D speed = direction * (initialSpeed.getLength() + b->getSpeed());
	b->setSpeed(speed);
	b->setAngle(angle);
	m_iReloadedPercent = 0;
	return b;
}

void Weapon::update(World& world, Vector3D referencePosition) {
	if (m_iReloadedPercent > 100) {
		m_iReloadedPercent = 100;
	}
	else if (m_iReloadedPercent < 100) {
		m_iReloadedPercent += _getReloadSpeed();
	}
}
