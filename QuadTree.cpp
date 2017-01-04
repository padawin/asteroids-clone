#include "QuadTree.hpp"
#include <stdlib.h>

// Based on
// https://gamedevelopment.tutsplus.com/tutorials/quick-tip-use-quadtrees-to-detect-likely-collisions-in-2d-space--gamedev-374

QuadTree::QuadTree(int level, S_Rectangle bounds) : m_iLevel(level), m_bounds(bounds) {
	m_nodes[0] = NULL;
}

QuadTree::~QuadTree() {
	clear();
}

void QuadTree::split() {
	float subWidth = m_bounds.width / 2;
	float subHeight = m_bounds.height / 2;
	float x = m_bounds.x;
	float y = m_bounds.y;

	S_Rectangle topRight = {x + subWidth, y, subWidth, subHeight};
	S_Rectangle topLeft = {x, y, subWidth, subHeight};
	S_Rectangle bottomLeft = {x, y + subHeight, subWidth, subHeight};
	S_Rectangle bottomRight = {x + subWidth, y + subHeight, subWidth, subHeight};
	m_nodes[0] = new QuadTree(m_iLevel + 1, topRight);
	m_nodes[1] = new QuadTree(m_iLevel + 1, topLeft);
	m_nodes[2] = new QuadTree(m_iLevel + 1, bottomLeft);
	m_nodes[3] = new QuadTree(m_iLevel + 1, bottomRight);
}

void QuadTree::clear() {
	if (m_nodes[0] != NULL) {
		for (int i = 0; i < 4; ++i) {
			m_nodes[i]->clear();
			free(m_nodes[i]);
		}
	}
}

/*
 * Determine which node the object belongs to. -1 means
 * object cannot completely fit within a child node and is part
 * of the parent node
 */
int QuadTree::getIndex(S_Circle zone) {
	int index = -1;
	double verticalMidpoint = m_bounds.x + (m_bounds.width / 2);
	double horizontalMidpoint = m_bounds.y + (m_bounds.height / 2);

	float topZone = zone.y - zone.radius;
	float bottomZone = zone.y + zone.radius;
	float leftZone = zone.x - zone.radius;
	float rightZone = zone.x + zone.radius;
	// Object can completely fit within the top quadrants
	bool topQuadrant = (topZone > m_bounds.y && bottomZone < horizontalMidpoint);
	// Object can completely fit within the bottom quadrants
	bool bottomQuadrant = (topZone > horizontalMidpoint && bottomZone < m_bounds.y + m_bounds.height);

	// Object can completely fit within the left quadrants
	if (leftZone > m_bounds.x && rightZone < verticalMidpoint) {
		if (topQuadrant) {
			index = 1;
		}
		else if (bottomQuadrant) {
			index = 2;
		}
	}
	// Object can completely fit within the right quadrants
	else if (leftZone > verticalMidpoint && rightZone < m_bounds.x + m_bounds.width) {
		if (topQuadrant) {
			index = 0;
		}
		else if (bottomQuadrant) {
			index = 3;
		}
	}

	return index;
}

/*
 * Insert the object into the quadtree. If the node
 * exceeds the capacity, it will split and add all
 * objects to their corresponding nodes.
 */
void QuadTree::insert(Entity* entity) {
	if (m_nodes[0] != NULL) {
		int index = getIndex(entity->getHitZone());

		if (index != -1) {
			m_nodes[index]->insert(entity);
			return;
		}
	}

	m_vObjects.push_back(entity);

	if (m_vObjects.size() > MAX_OBJECTS && m_iLevel < MAX_LEVELS) {
		if (m_nodes[0] == NULL) {
			split();
		}

		std::vector<Entity*>::size_type i = 0;
		while (i < m_vObjects.size()) {
			int index = getIndex(m_vObjects[i]->getHitZone());
			if (index != -1) {
				m_nodes[index]->insert(m_vObjects[i]);
				m_vObjects.erase(m_vObjects.begin() + i, m_vObjects.begin() + i + 1);
			}
			else {
				i++;
			}
		}
	}
}

/*
 * Return all objects that could collide with the given object
 */
std::vector<Entity*> QuadTree::retrieve(Entity* entity) {
	int index = getIndex(entity->getHitZone());
	std::vector<Entity*> returnObjects;
	if (index != -1 && m_nodes[0] != NULL) {
		returnObjects = m_nodes[index]->retrieve(entity);
	}

	returnObjects.insert(returnObjects.end(), m_vObjects.begin(), m_vObjects.end());

	return returnObjects;
}
