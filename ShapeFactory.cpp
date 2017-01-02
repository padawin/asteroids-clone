#include "ShapeFactory.hpp"
#include <stdio.h>

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
		case ASTEROID:
			_getAsteroidShape(shape);
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

void ShapeFactory::_getAsteroidShape(Shape *asteroid) {
	GLfloat vertices[] = {
		0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f
	};
	GLuint elements[] = {
		// back
		0, 2, 1,
		0, 3, 2,
		// front
		4, 5, 6,
		4, 6, 7,
		// top
		7, 6, 2,
		7, 2, 3,
		// bottom
		4, 1, 5,
		4, 0, 1,
		// left
		4, 3, 0,
		4, 7, 3,
		// right
		5, 1, 2,
		5, 2, 6
	};

	asteroid->setVertices(vertices, sizeof(vertices));
	asteroid->setElements(elements, sizeof(elements));
}
