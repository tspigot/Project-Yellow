#include "MovementType.h"
#include "Tile.h"

bool GroundMovementType::passable(Tile *t) {
	if(t->t.type == TileType::TILE_BLOCKING) {
		return false;
	}
	return true;
}

MovementType& GroundMovementType::get() {
	static GroundMovementType gmt;
	return gmt;
}