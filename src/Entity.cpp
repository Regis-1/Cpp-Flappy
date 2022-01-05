#include "../include/Entity.h"

Entity::Entity(int x, int y, float speed) : mX(x), mY(y), mSpeed(speed) {}

Position Entity::GetPos() {
	return { mX, mY };
}

void Entity::SetPos(const Position pos) {
	mX = pos.x;
	mY = pos.y;
}