#pragma once
#include <iostream>

#include "../include/Logger.h"
#include "../include/Block.h"

class Obstacle {
public:
	Block* mObstacles[2];
	int mPassage;

	Obstacle() = delete;
	Obstacle(int x, int passage, int width, int speed, int scrWidth, int scrHeight, int grndHeight);
	~Obstacle();

	void Move();
	Block* GetBlock(int idx) { return mObstacles[idx]; }
	int GetPassage() { return mPassage; }

	bool IsRemovable();
};