#ifndef __ASTEROID__
#define __ASTEROID__

#include "Entity.hpp"

class Asteroid : public Entity {
	protected:
	float m_fDistanceRecycle;
	int m_iHP;

	public:
	Asteroid(float distanceRecycle);
	ShapeType getShapeType();
	bool update(World& world, Vector3D thresholdPosition);
	S_Circle getHitZone();
	E_EntityType getType();
};

#endif
