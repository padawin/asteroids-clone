#ifndef __MISSILE_LAUNCHER__
#define __MISSILE_LAUNCHER__

#include "Weapon.hpp"
#include "Bullet.hpp"

class MissileLauncher : public Weapon {
	public:
	MissileLauncher() {m_bulletType = TYPE_MISSILE;}
	Bullet* fire(Vector3D Position, Vector3D direction, Vector3D initialSpeed, Vector3D angle);
};

#endif
