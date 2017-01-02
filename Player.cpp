#include "config.h"
#include "Player.hpp"
#include "ShapeFactory.hpp"
#include "Gun.hpp"
#include "MissileLauncher.hpp"
#include <math.h>

#define ACCELERATION_COEFFICIENT 0.002

Player::Player() : m_selectedWeapon(&m_weapon1) {
	m_weapon1 = new Gun();
	m_weapon2 = new MissileLauncher();
	m_weapon3 = NULL;
	m_weapon4 = NULL;
}

ShapeType Player::getShapeType() {
	return SHIP;
}

void Player::update() {
	Entity::update();

	if (m_fSteerAngle != 0.0f) {
		_updateDirection();
	}

	if (m_bIsFiring) {
		_fire();
	}

	for (std::vector<Entity*>::size_type i = 0; i < m_vBullets.size(); ++i) {
		Vector3D distance = m_vBullets.at(i)->getPosition() - m_VPosition;
		if (distance.getLength() > MAX_DISTANCE_FROM_PLAYER) {
			_removeBullet(i);
		}
	}
}

void Player::_removeBullet(unsigned int bulletIndex) {
	free(m_vBullets[bulletIndex]);
	m_vBullets[bulletIndex] = m_vBullets.back();
	m_vBullets.pop_back();
}

void Player::_updateDirection() {
	Vector3D direction = getDirection();
	float directionAngleZ = atan2(direction.getY(), direction.getX()) * 180 / M_PI;
	float angle = directionAngleZ + m_fSteerAngle;
	if (angle < 0.0f) {
		angle += 360.0f;
	}
	if (angle > 360.0f) {
		angle -= 360.0f;
	}
	angle = angle * M_PI / 180;
	setDirection(Vector3D(cos(angle), sin(angle), 0.0f));
}

void Player::thrust(bool activate) {
	setAcceleration(activate ? getDirection() * ACCELERATION_COEFFICIENT : Vector3D());
}

void Player::reverseThrust(bool activate) {
	setAcceleration(activate ? getDirection() * -ACCELERATION_COEFFICIENT : Vector3D());
}

void Player::_steer(float angle) {
	setAngularSpeed(Vector3D(0.0f, 0.0f, angle));
	m_fSteerAngle = angle;
}

void Player::steerLeft(bool activate) {
	//angle is in degrees
	_steer(activate ? 2.0f : 0.0f);
}

void Player::steerRight(bool activate) {
	_steer(activate ? -2.0f : 0.0f);
}

void Player::_fire() {
	m_vBullets.push_back(
		(*m_selectedWeapon)->fire(m_VPosition, m_VDirection, m_VSpeed)
	);
}

void Player::openFire() {
	m_bIsFiring = true;
}

void Player::ceaseFire() {
	m_bIsFiring = false;
}

std::vector<Bullet*> Player::getBullets() {
	return m_vBullets;
}

void Player::clean() {
	for (auto& bullet : m_vBullets) {
		free(bullet);
	}
}
