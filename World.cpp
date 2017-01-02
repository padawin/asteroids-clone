#include "World.hpp"

void World::setNbMaxEntities(unsigned int nbMaxEntities) {
	m_iNbMaxEntities = nbMaxEntities;
}

void World::addEntity(Entity* entity) {
	m_vEntities.push_back(std::make_pair(entity, false));
}

bool World::addCappedEntity(Entity* entity) {
	if (m_iNbCappedEntities == m_iNbMaxEntities) {
		return false;
	}

	m_vEntities.push_back(std::make_pair(entity, true));
	++m_iNbCappedEntities;
	return true;
}

void World::_update(Vector3D playerPosition, std::vector<std::pair<Entity*, bool>>* entities) {
	std::vector<Entity*>::size_type i = 0;
	while (i < entities->size()) {
		if (!entities->at(i).first->update(*this, playerPosition)) {
			// this is a capped entity
			if (entities->at(i).second) {
				--m_iNbCappedEntities;
			}
			free(entities->at(i).first);
			entities->at(i) = entities->back();
			entities->pop_back();
		}
		else {
			m_renderables.addEntity(entities->at(i).first);
			++i;
		}
	}
}

void World::update(Vector3D playerPosition) {
	m_renderables.flush();
	_update(playerPosition, &m_vEntities);
}

void World::render(GLuint shaderProgram, ShapeCollection shapes) {
	m_renderables.render(shaderProgram, shapes);
}

void World::clean() {
	for (std::vector<Entity*>::size_type i = 0; i < m_vEntities.size(); ++i) {
		free(m_vEntities[i].first);
	}
	m_iNbCappedEntities = 0;
}
