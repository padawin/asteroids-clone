#ifndef __WORLD__
#define __WORLD__

#include <vector>
#include "Vector3D.hpp"
#include "Entity.hpp"
#include "RenderableCollection.hpp"
#include "ShapeCollection.hpp"

class World {
	private:
	std::vector<Entity*> m_vEntities;
	RenderableCollection m_renderables;

	public:
	void addEntity(Entity* entity);
	void update(Vector3D playerPosition);
	void render(GLuint shaderProgram, ShapeCollection shapes);
};

#endif
