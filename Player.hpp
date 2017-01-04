#ifndef __PLAYER__
#define __PLAYER__

#include "World.hpp"
#include "Entity.hpp"
#include "Bullet.hpp"
#include "Weapon.hpp"
#include <vector>

#define NB_MAX_WEAPONS 4

class Player : public Entity {
	private:
	void _steer(float angle);
	void _updateDirection();
	void _fire(World& world);
	void _removeBullet(unsigned int bulletIndex);
	void _setWeapon(int weaponIndex);

	Weapon* m_weapons[NB_MAX_WEAPONS];
	int m_selectedWeapon;
	float m_fSteerAngle = 0.0f;
	bool m_bIsFiring = false;

	public:
	Player();
	ShapeType getShapeType();
	void thrust(bool activate);
	void reverseThrust(bool activate);
	void steerLeft(bool activate);
	void steerRight(bool activate);
	bool update(World& world, Vector3D position);
	void openFire();
	void ceaseFire();
	void setWeapon1();
	void setWeapon2();
	void setWeapon3();
	void setWeapon4();
	void clean();
	S_Circle getHitZone();
	E_EntityType getType();
};

#endif
