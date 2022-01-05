#include "../include/Block.h"

Block::Block(int x, int y, int w, int h, float speed)
	: Entity(x, y, speed), mWidth(w), mHeight(h) {

}

void Block::Move(uint32_t dt) {
	mX = mX - mSpeed;
}