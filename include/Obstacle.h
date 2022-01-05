#pragma once

#include "../include/Block.h"

class Obstacle {
public:
	Block* mObstacles[2];

	Obstacle() = delete;
	Obstacle(int x, int y, int passageWidth, int sWidth, int sHeight);
};