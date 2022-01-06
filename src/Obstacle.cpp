#include "../include/Obstacle.h"

#include <math.h>
#include <stdlib.h>
#include <time.h>

Obstacle::Obstacle(int x, int passage, int width, int speed, int scrWidth, int scrHeight, int grndHeight) {
	int x1 = x - (int)round(0.5f * width);
	int y1 = 0;
	int h1 = rand() % 200 + 100;
	int w1 = width;
	mObstacles[0] = new Block(x1, y1, w1, h1, speed);

	int x2 = x - (int)round(0.5f * width);
	int y2 = passage + h1;
	int h2 = scrHeight - passage - h1 - grndHeight;
	int w2 = w1;
	mObstacles[1] = new Block(x2, y2, w2, h2, speed);

	Logger::Info("Created Obstacle.");
}

Obstacle::~Obstacle() {
	delete mObstacles[0];
	delete mObstacles[1];
	Logger::Info("Obstacle removed.");
}

void Obstacle::Move(uint32_t dt) {
	mObstacles[0]->Move(dt);
	mObstacles[1]->Move(dt);
}

bool Obstacle::IsRemovable() {
	Position pos = mObstacles[0]->GetPos();
	Dimension dims = mObstacles[0]->GetDimensions();
	if (pos.x <= -dims.w)
		return true;
	else
		return false;
}