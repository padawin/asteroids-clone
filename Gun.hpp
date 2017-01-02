#ifndef __GUN__
#define __GUN__

#include "Weapon.hpp"
#include "Bullet.hpp"

class Gun : public Weapon {
	protected:
	Bullet* _createBullet();
};

#endif
