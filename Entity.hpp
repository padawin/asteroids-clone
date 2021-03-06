#ifndef __ENTITY__
#define __ENTITY__

// for math transformations
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class World;

#include "EntityManager.hpp"
#include "Geometry.hpp"
#include "Vector3D.hpp"
#include "ShapeFactory.hpp"

class Entity {
	protected:
	Vector3D m_VAcceleration, m_VSpeed, m_VPosition, m_VDirection;
	Vector3D m_VAngularAcceleration, m_VAngularSpeed, m_VAngle;
	Vector3D m_VCenter;

	public:
	void setCenter(Vector3D center);
	void setAcceleration(Vector3D acceleration);
	void setSpeed(Vector3D speed);
	void setPosition(Vector3D position);
	void setDirection(Vector3D direction);
	void setAngularAcceleration(Vector3D acceleration);
	void setAngularSpeed(Vector3D speed);
	void setAngle(Vector3D angle);
	Vector3D getCenter();
	Vector3D getAcceleration();
	Vector3D getSpeed();
	Vector3D getPosition();
	Vector3D getDirection();
	Vector3D getAngularAcceleration();
	Vector3D getAngularSpeed();
	Vector3D getAngle();
	virtual bool update(World& world, Vector3D position);
	glm::mat4 getTransformationMatrix();
	virtual ShapeType getShapeType() = 0;
	virtual S_Circle getHitZone() = 0;
	virtual E_EntityType getType() = 0;
	bool collidesWith(Entity* entity);
	virtual void handleCollision(Entity* entity) = 0;
};

#endif
