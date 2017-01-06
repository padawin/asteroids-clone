#ifndef __ASTEROID__
#define __ASTEROID__

#include "Entity.hpp"

class Asteroid : public Entity {
	protected:
	float m_fDistanceRecycle;
	int m_iHP;

	public:
	Asteroid(float distanceRecycle);
	bool update(World& world, Vector3D thresholdPosition);
	E_EntityType getType();
	void handleCollision(Entity* entity);
};

class AsteroidLarge : public Asteroid {
	public:
	AsteroidLarge(float distanceRecycle);
	bool update(World& world, Vector3D thresholdPosition);
	S_Circle getHitZone();
	ShapeType getShapeType();
};

class AsteroidMedium : public Asteroid {
	public:
	AsteroidMedium(float distanceRecycle);
	bool update(World& world, Vector3D thresholdPosition);
	S_Circle getHitZone();
	ShapeType getShapeType();
};

class AsteroidSmall : public Asteroid {
	public:
	AsteroidSmall(float distanceRecycle);
	S_Circle getHitZone();
	ShapeType getShapeType();
};

#endif
