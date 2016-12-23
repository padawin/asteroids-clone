#ifndef __PLAYER__
#define __PLAYER__

#include "Entity.hpp"
#include "Bullet.hpp"
#include <vector>

class Player : public Entity {
	private:
	void _steer(float angle);
	void _updateDirection();
	void _fire();

	WeaponType m_selectedWeapon = TYPE_GUN;
	float m_fSteerAngle = 0.0f;
	bool m_bIsFiring = false;
	std::vector<Bullet*> m_vBullets;

	public:
	ShapeType getShapeType();
	void thrust(bool activate);
	void reverseThrust(bool activate);
	void steerLeft(bool activate);
	void steerRight(bool activate);
	void update();
	void openFire();
	void ceaseFire();
	std::vector<Bullet*> getBullets();
	void clean();
};

#endif
