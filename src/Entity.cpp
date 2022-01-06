#include "../include/Entity.h"

Entity::Entity(int x, int y) : mX(x), mY(y) {}

Position Entity::GetPos() {
	return { mX, mY };
}

void Entity::SetPos(const Position pos) {
	mX = pos.x;
	mY = pos.y;
}