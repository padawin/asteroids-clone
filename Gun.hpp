#ifndef __GUN__
#define __GUN__

#include "Weapon.hpp"
#include "Bullet.hpp"

class Gun : public Weapon {
	protected:
	unsigned int _getReloadSpeed() {return 100;}
	Bullet* _createBullet();
};

#endif
