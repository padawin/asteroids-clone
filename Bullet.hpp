#ifndef __BULLET__
#define __BULLET__

#include "Entity.hpp"

typedef enum {TYPE_GUN, TYPE_MISSILE} WeaponType;

class Bullet : public Entity {
	public:
	virtual float getSpeed() = 0;
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
