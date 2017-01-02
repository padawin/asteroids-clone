#ifndef __BULLET__
#define __BULLET__

#include "Entity.hpp"

typedef enum {TYPE_GUN, TYPE_MISSILE} BulletType;

class Bullet : public Entity {
	public:
	virtual float getSpeed() = 0;
	bool update(World& world, Vector3D referencePosition);
};

class GunBullet : public Bullet {
	public:
	float getSpeed();
	ShapeType getShapeType();
};

class Missile : public Bullet {
	public:
	float getSpeed();
	ShapeType getShapeType();
};

#endif
