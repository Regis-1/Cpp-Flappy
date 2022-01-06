#pragma once
#include "../include/Entity.h"

struct Dimension {
	int w, h;
};

class Block : public Entity {
private:
	int mWidth, mHeight;
	int mSpeed;
public:
	Block() = delete;
	Block(int x, int y, int w, int h, int speed);

	void Move(uint32_t dt);
	Dimension GetDimensions() { return { mWidth, mHeight }; }
};