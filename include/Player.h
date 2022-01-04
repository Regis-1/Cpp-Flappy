#pragma once

struct PsychAttrs {
	float m, g, F, v, a;
};

class Player {
private:
	float mX, mY;
	int mSize;
	PsychAttrs mPsychAttrs;
	
public:
	Player() = delete;
	Player(const Player& other) = delete;

	Player(float x, float y, int size);
};