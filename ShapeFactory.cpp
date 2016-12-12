#include "ShapeFactory.hpp"
#include <stdio.h>

void ShapeFactory::getShape(ShapeType type, Shape *shape) {
	switch (type) {
		case SHIP:
			_getShipShape(shape);
			break;
		case ASTEROID:
			_getAsteroidShape(shape);
	}
}

void ShapeFactory::_getShipShape(Shape *ship) {
	GLfloat vertices[] = {
		1.006243f, 0.018257f, 1.000726f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		-0.993757f, 0.018257f, 1.000726f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.006244f, 0.069619f, -1.927195f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
		0.000000f, 0.750000f, 0.500000f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
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
