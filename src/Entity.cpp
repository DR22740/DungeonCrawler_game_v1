/* Entity.cpp - Base Entity Implementation */
#include "Entity.hpp"

Entity::Entity(int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    : x(x), y(y), width(width), height(height), r(r), g(g), b(b), a(a) {}

int Entity::getXPos() const { return x; }
int Entity::getYPos() const { return y; }

void Entity::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}
