#ifndef __WORLD__
#define __WORLD__

#include <vector>
#include "Vector3D.hpp"
#include "Entity.hpp"
#include "RenderableCollection.hpp"
#include "ShapeCollection.hpp"

class World {
	private:
	unsigned int m_iNbMaxEntities;
	unsigned int m_iNbCappedEntities = 0;
	std::vector<std::pair<Entity*, bool>> m_vEntities;
	RenderableCollection m_renderables;
	void _update(Vector3D playerPosition, std::vector<std::pair<Entity*, bool>>* entities);
	void _handleCollision(Entity* entity1, Entity* entity2);

	public:
	void setNbMaxEntities(unsigned int nbMaxEntities);
	void addEntity(Entity* entity);
	bool addCappedEntity(Entity* entity);
	void update(Vector3D playerPosition);
	void render(GLuint shaderProgram, ShapeCollection shapes);
	void clean();
};

#endif
