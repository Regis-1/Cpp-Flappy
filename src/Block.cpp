#include "../include/Block.h"

Block::Block(int x, int y, int w, int h, int speed)
	: Entity(x, y), mWidth(w), mHeight(h), mSpeed(speed) {

}

void Block::Move() {
	mX = mX - mSpeed;
}