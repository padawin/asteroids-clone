#include "ShapeFactory.hpp"
#include "ObjParser.hpp"

void ShapeFactory::getShape(ShapeType type, Shape *shape) {
	switch (type) {
		case GUN_BULLET:
			_getGunBulletShape(shape);
			break;
		case MISSILE:
			_getMissileShape(shape);
			break;
		case SHIP:
			_getShipShape(shape);
			break;
		case ASTEROID_LARGE:
			_getAsteroidLargeShape(shape);
			break;
		case ASTEROID_MEDIUM:
			_getAsteroidMediumShape(shape);
			break;
		case ASTEROID_SMALL:
			_getAsteroidSmallShape(shape);
			break;
	}
}

void ShapeFactory::_getShipShape(Shape *ship) {
	GLfloat vertices[] = {
		0.0f, 2.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.75f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
	};
	GLuint elements[] = {
		3, 2, 1,
		2, 3, 0,
		3, 1, 0,
		1, 2, 0
	};

	ship->setVertices(vertices, sizeof(vertices));
	ship->setElements(elements, sizeof(elements));
}

void ShapeFactory::_getGunBulletShape(Shape *gunBullet) {
	GLfloat vertices[] = {
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.1f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.1f, 0.1f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.1f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f
	};
	GLuint elements[] = {
		0, 2, 1,
		3, 1, 0
	};

	gunBullet->setVertices(vertices, sizeof(vertices));
	gunBullet->setElements(elements, sizeof(elements));
}

void ShapeFactory::_getMissileShape(Shape *missile) {
	GLfloat vertices[] = {
		0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.1f, 0.3f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
		0.1f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f
	};
	GLuint elements[] = {
		0, 2, 1,
		3, 1, 0
	};

	missile->setVertices(vertices, sizeof(vertices));
	missile->setElements(elements, sizeof(elements));
}

void ShapeFactory::_getAsteroidLargeShape(Shape *asteroid) {
	ObjParser parser;
	parser.parse("./objects/LargeAsteroid.obj", asteroid);
}

void ShapeFactory::_getAsteroidMediumShape(Shape *asteroid) {
	ObjParser parser;
	parser.parse("./objects/MediumAsteroid.obj", asteroid);
}

void ShapeFactory::_getAsteroidSmallShape(Shape *asteroid) {
	ObjParser parser;
	parser.parse("./objects/SmallAsteroid.obj", asteroid);
}
