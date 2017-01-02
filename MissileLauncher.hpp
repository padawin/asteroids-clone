#ifndef __MISSILE_LAUNCHER__
#define __MISSILE_LAUNCHER__

#include "Weapon.hpp"
#include "Bullet.hpp"

class MissileLauncher : public Weapon {
	protected:
	Bullet* _createBullet();
};

#endif
