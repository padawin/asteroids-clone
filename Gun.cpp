#include "Gun.hpp"

Bullet* Gun::_createBullet() {
	return new GunBullet();
}
