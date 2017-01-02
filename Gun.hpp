#ifndef __GUN__
#define __GUN__

#include "Weapon.hpp"
#include "Bullet.hpp"

class Gun : public Weapon {
	public:
	Gun() {m_bulletType = TYPE_GUN;}
	Bullet* fire(Vector3D position, Vector3D direction, Vector3D initialSpeed, Vector3D angle);
};

#endif
