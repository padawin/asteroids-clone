#ifndef __QUADTREE__
#define __QUADTREE__

#include "Geometry.hpp"
#include "Entity.hpp"
#include <vector>

class QuadTree {
	private:
	static const int MAX_OBJECTS = 10;
	static const int MAX_LEVELS = 5;

	int m_iLevel;
	std::vector<Entity*> m_vObjects;
	S_Rectangle m_bounds;
	QuadTree* m_nodes[4];

	public:
	QuadTree(int level, S_Rectangle bounds);
	~QuadTree();
	void clear();
	void split();
	int getIndex(S_Circle zone);
	void insert(Entity* entity);
	std::vector<Entity*> retrieve(Entity* entity);
};

#endif
