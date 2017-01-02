#ifndef __MISSILE_LAUNCHER__
#define __MISSILE_LAUNCHER__

#include "Weapon.hpp"
#include "Bullet.hpp"

class MissileLauncher : public Weapon {
	protected:
	unsigned int _getReloadSpeed() {return 5;}
	Bullet* _createBullet();
};

#endif
