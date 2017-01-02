#include "AsteroidGenerator.hpp"
#include <math.h>

void AsteroidGenerator::setDistanceRecycle(float distance) {
	m_fDistanceRecycle = distance;
}

void AsteroidGenerator::setRangeDistanceAppear(unsigned int minDistance, unsigned int maxDistance) {
	m_iMinDistanceAppear = minDistance;
	// multiplication because rand returns an int, so the returned value will
	// then be divided by 1000.0f
	m_iMaxDistanceAppear = maxDistance * 1000;
}

void AsteroidGenerator::addAsteroid(World& world, Vector3D position) {
	Asteroid *asteroid = new Asteroid(m_fDistanceRecycle);
	asteroid->setPosition(position);
	// angle is between -2.0f and 2.0f degrees
	float angularSpeedX = rand() % 4 - 2.0f,
		  angularSpeedY = rand() % 4 - 2.0f,
		  angularSpeedZ = rand() % 4 - 2.0f;

	float speed = (rand() % 1000) / 10000.0f;
	float angle = (rand() % 360) * M_PI / 180;
	asteroid->setAngularSpeed(
		Vector3D(angularSpeedX, angularSpeedY, angularSpeedZ)
	);
	asteroid->setSpeed(Vector3D(
		speed * cos(angle),
		speed * sin(angle),
		0.0f
	));
	if (!world.addCappedEntity(asteroid)) {
		free(asteroid);
	}
}

void AsteroidGenerator::update(World& world, Vector3D thresholdPosition) {
	int nbNewAsteroids = rand() % NB_MAX_ASTEROIDS;
	while (nbNewAsteroids--) {
		float distance, angle, x, y;
		distance = m_iMinDistanceAppear + (rand() % m_iMaxDistanceAppear) / 1000.0f;
		angle = (rand() % 360) * M_PI / 180;
		x = thresholdPosition.getX() + distance * cos(angle);
		y = thresholdPosition.getY() + distance * sin(angle);
		addAsteroid(world, Vector3D(x, y, 0.0f));
	}
}
