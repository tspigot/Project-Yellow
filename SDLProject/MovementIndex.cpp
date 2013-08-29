#include "MovementIndex.h"
#include <queue>

using std::queue;
using std::shared_ptr;

MovementIndex::MovementIndex(Map *m, MovementType &type, TileCoords origin, int radius)
	: type(type)
{
	this->map = m;
	this->origin = origin;
	this->radius = radius;
	this->type = type;
}

template <class T>
inline void hash_combine(std::size_t& seed, const T& v)
{
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

size_t MovementIndex::TileCoordsHash::operator() (TileCoords tc) {
	size_t seed = 0;
	hash_combine(seed, tc.x);
	hash_combine(seed, tc.y);
	return seed;
}

bool MovementIndex::TileCoordsEqual::operator()(TileCoords lhs, TileCoords rhs) {
	return lhs.x == rhs.x && lhs.y == rhs.y;
}

void MovementIndex::construct() {
	typedef shared_ptr<PathNode> Node_ptr;
	queue<Node_ptr> open;
	Node_ptr p = std::make_shared<PathNode>();
	p->depth = 0;
	p->tc = origin;
	p->parent = NULL;
	open.push(p);
	while(!open.empty()) {
		Node_ptr current = open.front();
		open.pop();
		Tile *t = map->get_tile(current->tc);
		if(    !type.passable(t) 
			|| current->depth > this->radius 
			|| (   index.count(current->tc) != 0 
				&& index[current->tc]->depth < current->depth))
		{
			continue;
		}
		index[current->tc] = current;
		std::list<TileCoords> neighbors = map->find_neighbors(current->tc);
		for(TileCoords tc : neighbors) {
			Node_ptr ptr = std::make_shared<PathNode>();
			ptr->depth = current->depth + 1;
			ptr->parent = current;
			ptr->tc = tc;
			open.push(ptr);
		}
	}
}

std::shared_ptr<MovementIndex::PathNode> MovementIndex::get_node(TileCoords tc) {
	if(index.count(tc) == 0) {
		return shared_ptr<PathNode>(NULL);
	} else {
		return index[tc];
	}
}

void MovementIndex::apply_to_tiles(std::function<void(TileCoords)> fn) {
	for(auto p : index) {
		fn(p.first);
	}
}