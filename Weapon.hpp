#ifndef __WEAPON__
#define __WEAPON__

#include "Bullet.hpp"

class Weapon {
	protected:
	virtual Bullet* _createBullet() = 0;

	int m_iReloadedPercent = 100;
	virtual unsigned int _getReloadSpeed() = 0;

	public:
	virtual Bullet* fire(Vector3D position, Vector3D direction, Vector3D initialSpeed, Vector3D angle);
	void update();
};

#endif
