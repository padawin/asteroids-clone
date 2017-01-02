#ifndef __RENDERABLE_COLLECTION__
#define __RENDERABLE_COLLECTION__

#include <map>
#include <vector>
#include "ShapeFactory.hpp"
#include "Entity.hpp"
#include "ShapeCollection.hpp"

class RenderableCollection {
	protected:
	std::map<ShapeType, std::vector<Entity*>> m_mEntities;

	public:
	void addEntity(Entity *entity);
	void flush();
	void update();
	void render(GLuint shaderProgram, ShapeCollection shapes);
};

#endif
