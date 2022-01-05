#include "../include/Player.h"

Player::Player(int x, int y, int size, float speed) 
	: Entity(x, y, speed), mSize(size) {
	
	mPsychAttrs = { 0.0f, 9.81f };
}

void Player::Move(uint32_t dt) {
	mX = mX + (int)floor((dt / 100.0f) * mSpeed);
}