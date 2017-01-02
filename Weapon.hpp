#ifndef __WEAPON__
#define __WEAPON__

#include "Bullet.hpp"

class Weapon {
	protected:
	BulletType m_bulletType;

	public:
	virtual Bullet* fire(Vector3D position, Vector3D direction, Vector3D initialSpeed, Vector3D angle) = 0;
};

#endif
