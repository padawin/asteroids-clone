#ifndef __ASTEROID_GENERATOR__
#define __ASTEROID_GENERATOR__

#include <vector>
#include "Asteroid.hpp"

#define NB_MAX_ASTEROIDS 200

class AsteroidGenerator {
	private:
	std::vector<Asteroid*> m_vAsteroids;

	public:
	Asteroid* addAsteroid(Vector3D position);
	void clean();
};

#endif
