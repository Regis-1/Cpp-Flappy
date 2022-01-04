#include "../include/Player.h"

Player::Player(float x, float y, int size) : mX(x), mY(y), mSize(size) {
	mPsychAttrs = { 10.0f, 9.81f, 0.0f, 0.0f, 0.0f };
}