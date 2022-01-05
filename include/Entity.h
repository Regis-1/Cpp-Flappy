#pragma once
#include <cstdint>

struct Position {
	int x, y;
};

class Entity {
protected:
	int mX, mY;
	float mSpeed;
public:
	Entity() = delete;
	Entity(int x, int y, float speed);

	virtual void Move(uint32_t dt) {};
	Position GetPos();
	void SetPos(const Position pos);
	float GetSpeed() { return mSpeed; }
	void SetSpeed(float speed) { mSpeed = speed; }
};