#include "World.hpp"

void World::setNbMaxEntities(unsigned int nbMaxEntities) {
	m_iNbMaxEntities = nbMaxEntities;
}

void World::addEntity(Entity* entity) {
	m_vEntities.push_back(entity);
}

bool World::addCappedEntity(Entity* entity) {
	if (m_vCappedEntities.size() == m_iNbMaxEntities) {
		return false;
	}

	m_vCappedEntities.push_back(entity);
	return true;
}

void World::_update(Vector3D playerPosition, std::vector<Entity*>* entities) {
	std::vector<Entity*>::size_type i = 0;
	while (i < entities->size()) {
		if (!entities->at(i)->update(*this, playerPosition)) {
			free(entities->at(i));
			entities->at(i) = entities->back();
			entities->pop_back();
		}
		else {
			m_renderables.addEntity(entities->at(i));
			++i;
		}
	}
}

void World::update(Vector3D playerPosition) {
	m_renderables.flush();
	_update(playerPosition, &m_vEntities);
	_update(playerPosition, &m_vCappedEntities);
}

void World::render(GLuint shaderProgram, ShapeCollection shapes) {
	m_renderables.render(shaderProgram, shapes);
}
