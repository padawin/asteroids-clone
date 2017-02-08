#include "Asteroid.hpp"
#include "Bullet.hpp"
#include "ShapeFactory.hpp"
#include "World.hpp"

Asteroid::Asteroid(float distanceRecycle) : m_fDistanceRecycle(distanceRecycle) {
	setCenter(Vector3D(0.0f, 0.0f, 0.0f));
	// angle is between -2.0f and 2.0f degrees
	float angularSpeedX = rand() % 4 - 2.0f,
		  angularSpeedY = rand() % 4 - 2.0f,
		  angularSpeedZ = rand() % 4 - 2.0f;

	float speed = (rand() % 1000) / 10000.0f;
	float angle = (rand() % 360) * M_PI / 180;
	setAngularSpeed(
		Vector3D(angularSpeedX, angularSpeedY, angularSpeedZ)
	);
	setSpeed(Vector3D(
		speed * cos(angle),
		speed * sin(angle),
		0.0f
	));
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

E_EntityType Asteroid::getType() {
	return ENTITY_ASTEROID;
}

void Asteroid::handleCollision(Entity* entity) {
	switch (entity->getType()) {
		case ENTITY_BULLET:
			// destroyed
			m_iHP -= dynamic_cast<Bullet*>(entity)->getDamages();
			break;
		case ENTITY_SHIP:
		case ENTITY_ASTEROID:
			// destroyed
			setSpeed(getSpeed() * -1);
			break;
		default:
			break;
	}
}

AsteroidLarge::AsteroidLarge(float distanceRecycle) : Asteroid(distanceRecycle) {
	m_iHP = 150;
}

bool AsteroidLarge::update(World& world, Vector3D thresholdPosition) {
	bool updated = Asteroid::update(world, thresholdPosition);
	if (m_iHP == 0) {
		AsteroidMedium *med1 = new AsteroidMedium(m_fDistanceRecycle),
			*med2 = new AsteroidMedium(m_fDistanceRecycle);
		med1->setPosition(getPosition());
		med2->setPosition(getPosition());
		world.addEntity(med1);
		world.addEntity(med2);
	}

	return updated;
}

S_Circle AsteroidLarge::getHitZone() {
	S_Circle hz = {
		.x = getPosition().getX(),
		.y = getPosition().getY(),
		.radius = 0.6f
	};

	return hz;
}

ShapeType AsteroidLarge::getShapeType() {
	return ASTEROID_LARGE;
}

float AsteroidLarge::getDamages() {
	return 200.0f;
}

AsteroidMedium::AsteroidMedium(float distanceRecycle) : Asteroid(distanceRecycle) {
	m_iHP = 75;
}

bool AsteroidMedium::update(World& world, Vector3D thresholdPosition) {
	bool updated = Asteroid::update(world, thresholdPosition);
	if (m_iHP == 0) {
		AsteroidSmall *small1 = new AsteroidSmall(m_fDistanceRecycle),
			*small2 = new AsteroidSmall(m_fDistanceRecycle);
		small1->setPosition(getPosition());
		small2->setPosition(getPosition());
		world.addEntity(small1);
		world.addEntity(small2);
	}

	return updated;
}

S_Circle AsteroidMedium::getHitZone() {
	S_Circle hz = {
		.x = getPosition().getX(),
		.y = getPosition().getY(),
		.radius = 0.1f
	};

	return hz;
}

ShapeType AsteroidMedium::getShapeType() {
	return ASTEROID_MEDIUM;
}

float AsteroidMedium::getDamages() {
	return 50.0f;
}

AsteroidSmall::AsteroidSmall(float distanceRecycle) : Asteroid(distanceRecycle) {
	m_iHP = 25;
}

S_Circle AsteroidSmall::getHitZone() {
	S_Circle hz = {
		.x = getPosition().getX(),
		.y = getPosition().getY(),
		.radius = 0.1f
	};

	return hz;
}

ShapeType AsteroidSmall::getShapeType() {
	return ASTEROID_SMALL;
}

float AsteroidSmall::getDamages() {
	return 10.0f;
}
