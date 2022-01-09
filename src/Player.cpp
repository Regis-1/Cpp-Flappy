#include "../include/Player.h"

Player::Player(int x, int y, int size) 
	: Entity(x, y), mSize(size) {
	
	mPsychAttrs = { 0, 1 };
}

void Player::Move() {
	mY = mY + mPsychAttrs.v0 + (int)round(0.5f * (float)mPsychAttrs.a);
	mPsychAttrs.v0 = mPsychAttrs.v0 + mPsychAttrs.a;
}