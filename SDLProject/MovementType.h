#pragma once

struct Tile;

class MovementType {
public:
	virtual bool passable(Tile *t)=0;
};

class GroundMovementType : public MovementType {
private:
	GroundMovementType() {}
public:
	bool passable(Tile *t);
	static MovementType& get();
};