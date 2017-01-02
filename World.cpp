#include "World.hpp"

void World::addEntity(Entity* entity) {
	m_vEntities.push_back(entity);
}

void World::update(Vector3D playerPosition) {
	for (std::vector<Entity*>::size_type i = 0; i < m_vEntities.size(); ++i) {
		m_vEntities[i]->update();
	}
}

void World::render(ShapeCollection shapes) {

}
