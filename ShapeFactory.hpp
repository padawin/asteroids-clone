#ifndef __SHAPE_FACTORY__
#define __SHAPE_FACTORY__

#include "Shape.hpp"

enum ShapeType {GUN_BULLET, MISSILE, SHIP, ASTEROID_LARGE, ASTEROID_MEDIUM, ASTEROID_SMALL};

class ShapeFactory {
	private:
	static void _getGunBulletShape(Shape *ship);
	static void _getMissileShape(Shape *ship);
	static void _getShipShape(Shape *ship);
	static void _getAsteroidLargeShape(Shape *asteroid);
	static void _getAsteroidMediumShape(Shape *asteroid);
	static void _getAsteroidSmallShape(Shape *asteroid);

	public:
	static void getShape(ShapeType type, Shape *shape);
};

#endif
