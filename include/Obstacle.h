#pragma once

#include "../include/Block.h"

class Obstacle {
public:
	Block* mObstacles[2];

	Obstacle() = delete;
	Obstacle(int x, int passage, int width, float speed, int scrWidth, int scrHeight, int grndHeight);
	~Obstacle();

	void Move(uint32_t dt);
	Block* GetBlock(int idx) { return mObstacles[idx]; }
};