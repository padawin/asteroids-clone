#ifndef __BULLET__
#define __BULLET__

#include "Entity.hpp"

typedef enum {TYPE_GUN, TYPE_MISSILE} BulletType;

class Bullet : public Entity {
	protected:
	bool m_bDestroyed = false;

	public:
	virtual float getSpeed() = 0;
	bool update(World& world, Vector3D referencePosition);
	S_Circle getHitZone();
	E_EntityType getType();
	virtual int getDamages() = 0;
	void handleCollision(Entity* entity);
};

class GunBullet : public Bullet {
	public:
	float getSpeed();
	ShapeType getShapeType();
	int getDamages();
};

class Missile : public Bullet {
	public:
	float getSpeed();
	ShapeType getShapeType();
	int getDamages();
};

#endif
