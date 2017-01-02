#ifndef __ASTEROID_GENERATOR__
#define __ASTEROID_GENERATOR__

#include <vector>
#include "Asteroid.hpp"
#include "World.hpp"

#define NB_MAX_ASTEROIDS 10

class AsteroidGenerator {
	private:
	float m_fDistanceRecycle;
	unsigned int m_iMinDistanceAppear;
	unsigned int m_iMaxDistanceAppear;

	public:
	void setDistanceRecycle(float distance);
	void setRangeDistanceAppear(unsigned int minDistance, unsigned int maxDistance);
	void addAsteroid(World& world, Vector3D position);
	void update(World& world, Vector3D thresholdPosition);
};

#endif
