#ifndef __BULLET__
#define __BULLET__

#include "Entity.hpp"

typedef enum {TYPE_GUN, TYPE_MISSILE} WeaponType;

class Bullet : public Entity {
};

class GunBullet : public Bullet {
	ShapeType getShapeType();
};

class Missile : public Bullet {
	ShapeType getShapeType();
};

#endif
