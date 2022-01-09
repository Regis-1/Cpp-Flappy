#pragma once
#include <cstdint>

struct Position {
	int x, y;
};

class Entity {
protected:
	int mX, mY;
public:
	Entity() = delete;
	Entity(int x, int y);

	virtual void Move() {};
	Position GetPos();
	void SetPos(const Position pos);
};