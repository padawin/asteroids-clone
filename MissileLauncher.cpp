#include "MissileLauncher.hpp"

Bullet* MissileLauncher::_createBullet() {
	return new Missile();
}
