#include "config.h"
#include "Player.hpp"
#include "ShapeFactory.hpp"
#include "Gun.hpp"
#include "MissileLauncher.hpp"
#include <math.h>

#define ACCELERATION_COEFFICIENT 0.002

Player::Player() : m_selectedWeapon(0) {
	m_weapons[0] = new Gun();
	m_weapons[1] = new MissileLauncher();
	m_weapons[2] = NULL;
	m_weapons[3] = NULL;
}

ShapeType Player::getShapeType() {
	return SHIP;
}

bool Player::update(World& world, Vector3D position) {
	Entity::update(world, position);

	if (m_fSteerAngle != 0.0f) {
		_updateDirection();
	}

	if (m_bIsFiring) {
		_fire(world);
	}

	for (int w = 0; w < NB_MAX_WEAPONS; ++w) {
		if (m_weapons[w] != NULL) {
			m_weapons[w]->update(world, position);
		}
	}

	return true;
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

void Player::_fire(World& world) {
	Bullet* b = m_weapons[m_selectedWeapon]->fire(
		m_VPosition + m_VDirection * 2.0f,
		m_VDirection,
		m_VSpeed,
		m_VAngle
	);

	if (b != NULL) {
		world.addEntity(b);
	}
}

void Player::openFire() {
	m_bIsFiring = true;
}

void Player::ceaseFire() {
	m_bIsFiring = false;
}

void Player::_setWeapon(int weaponIndex) {
	if (weaponIndex >= NB_MAX_WEAPONS || m_weapons[weaponIndex] == NULL) {
		return;
	}

	m_selectedWeapon = weaponIndex;
}

void Player::setWeapon1() {
	_setWeapon(0);
}

void Player::setWeapon2() {
	_setWeapon(1);
}

void Player::setWeapon3() {
	_setWeapon(2);
}

void Player::setWeapon4() {
	_setWeapon(3);
}

S_Circle Player::getHitZone() {
	S_Circle hz = {
		.x = getPosition().getX(),
		.y = getPosition().getY(),
		.radius = 1.0f
	};

	return hz;
}

E_EntityType Player::getType() {
	return ENTITY_SHIP;
}

void Player::handleCollision(Entity* entity) {
}
