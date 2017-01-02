#ifndef __PLAYER__
#define __PLAYER__

#include "Entity.hpp"
#include "Bullet.hpp"
#include "Weapon.hpp"
#include <vector>

#define NB_MAX_WEAPONS 4

class Player : public Entity {
	private:
	void _steer(float angle);
	void _updateDirection();
	void _fire();
	void _removeBullet(unsigned int bulletIndex);
	void _setWeapon(int weaponIndex);

	Weapon* m_weapons[NB_MAX_WEAPONS];
	int m_selectedWeapon;
	float m_fSteerAngle = 0.0f;
	bool m_bIsFiring = false;
	std::vector<Bullet*> m_vBullets;

	public:
	Player();
	ShapeType getShapeType();
	void thrust(bool activate);
	void reverseThrust(bool activate);
	void steerLeft(bool activate);
	void steerRight(bool activate);
	void update();
	void openFire();
	void ceaseFire();
	void setWeapon1();
	void setWeapon2();
	void setWeapon3();
	void setWeapon4();
	std::vector<Bullet*> getBullets();
	void clean();
};

#endif
