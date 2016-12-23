#ifndef __PLAYER__
#define __PLAYER__

#include "Entity.hpp"
#include "Bullet.hpp"
#include <vector>

class Player : public Entity {
	private:
	void _steer(float angle);
	void _updateDirection();
	float m_fSteerAngle = 0.0f;
	std::vector<Bullet*> m_vBullets;

	public:
	ShapeType getShapeType();
	void thrust(bool activate);
	void reverseThrust(bool activate);
	void steerLeft(bool activate);
	void steerRight(bool activate);
	void update();
	std::vector<Bullet*> getBullets();
	void clean();
};

#endif
