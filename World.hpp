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
	std::vector<Entity*> m_vEntities;
	std::vector<Entity*> m_vCappedEntities;
	RenderableCollection m_renderables;
	void _update(Vector3D playerPosition, std::vector<Entity*>* entities);

	public:
	void setNbMaxEntities(unsigned int nbMaxEntities);
	void addEntity(Entity* entity);
	bool addCappedEntity(Entity* entity);
	void update(Vector3D playerPosition);
	void render(GLuint shaderProgram, ShapeCollection shapes);
};

#endif
