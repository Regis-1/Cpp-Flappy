#pragma once
#include <math.h>

#include "Entity.h"

struct PsychAttrs {
	int v0, a;
};

class Player : public Entity {
private:
	int mSize;
	PsychAttrs mPsychAttrs;

public:
	Player() = delete;
	Player(const Player& other) = delete;
	Player(int x, int y, int size);
	
	void Move(uint32_t dt) override;

	int GetSize() { return mSize; }
	void SetV0(const int newV0) { mPsychAttrs.v0 = newV0; }
};