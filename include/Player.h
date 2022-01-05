#pragma once
#include <math.h>

#include "Entity.h"

struct PsychAttrs {
	float v, g;
};

class Player : public Entity {
private:
	int mSize;
	PsychAttrs mPsychAttrs;
	
	bool CheckCollisionGround();

public:
	Player() = delete;
	Player(const Player& other) = delete;
	Player(int x, int y, int size, float speed = 10.0f);
	
	void Move(uint32_t dt) override;

	int GetSize() { return mSize; }
};