#pragma once
#include "coords.h"
#include <unordered_map>
#include "Map.h"
#include <memory>
#include <functional>
#include "MovementType.h"

class MovementIndex
{
private:
	struct PathNode {
		TileCoords tc;
		std::shared_ptr<PathNode> parent;
		int depth;
	};
	class TileCoordsHash { public: size_t operator()(TileCoords); };
	class TileCoordsEqual { public: bool operator()(TileCoords, TileCoords); };
	std::unordered_map<TileCoords, std::shared_ptr<PathNode>, TileCoordsHash, TileCoordsEqual> index;
	Map *map;
	TileCoords origin;
	int radius;
	MovementType &type;
public:
	MovementIndex(Map *m, MovementType &mt, TileCoords origin, int radius);
	void construct();
	std::shared_ptr<PathNode> get_node(TileCoords tc);
	void apply_to_tiles(std::function<void(TileCoords)> fn);
};

