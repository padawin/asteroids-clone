#include "RenderableCollection.hpp"

void RenderableCollection::addEntity(Entity *entity) {
	ShapeType type = entity->getShapeType();
	if (m_mEntities.find(type) == m_mEntities.end()) {
		m_mEntities[type] = std::vector<Entity*>();
	}

	m_mEntities[type].push_back(entity);
}

void RenderableCollection::flush() {
	m_mEntities.clear();
}

void RenderableCollection::update(World& world, Vector3D position) {
	for (auto& it : m_mEntities) {
		for (auto &itEntity : it.second) {
			itEntity->update(world, position);
		}
	}
}

void RenderableCollection::render(
	GLuint shaderProgram,
	ShapeCollection shapes,
	std::map<std::string, GLuint> textures
) {
	for (auto& it : m_mEntities) {
		shapes.bind(it.first, textures);
		for (auto &itEntity : it.second) {
			glm::mat4 trans = itEntity->getTransformationMatrix();
			GLint uniTrans = glGetUniformLocation(shaderProgram, "trans");
			glUniformMatrix4fv(uniTrans, 1, GL_FALSE, glm::value_ptr(trans));
			shapes.render(it.first);
		}
	}
}
