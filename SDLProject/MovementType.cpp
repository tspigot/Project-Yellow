#include "MovementType.h"
#include "Tile.h"

bool GroundMovementType::passable(Tile *t) {
	if(t->type == Tile::Type::TILE_BLOCKING) {
		return false;
	}
	return true;
}

MovementType& GroundMovementType::get() {
	static GroundMovementType gmt;
	return gmt;
}