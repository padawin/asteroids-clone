#ifndef __ASTEROID__
#define __ASTEROID__

#include "Entity.hpp"

class Asteroid : public Entity {
	protected:
	float m_fDistanceRecycle;

	public:
	Asteroid(float distanceRecycle);
	ShapeType getShapeType();
};

#endif
