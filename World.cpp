#include "World.hpp"

void World::addEntity(Entity* entity) {
	m_vEntities.push_back(entity);
}

void World::update(Vector3D playerPosition) {
	m_renderables.flush();
	for (std::vector<Entity*>::size_type i = 0; i < m_vEntities.size(); ++i) {
		if (!m_vEntities[i]->update(*this, playerPosition)) {
			free(m_vEntities[i]);
			m_vEntities[i] = m_vEntities.back();
			m_vEntities.pop_back();

		}
		else {
			m_renderables.addEntity(m_vEntities.at(i));
		}
	}
}

void World::render(GLuint shaderProgram, ShapeCollection shapes) {
	m_renderables.render(shaderProgram, shapes);
}
