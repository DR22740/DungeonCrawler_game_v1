/* Entity.cpp - Base Entity Implementation */
#include "Entity.hpp"
#include <array>

Entity::Entity(int x, int y, int width, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    : x(x), y(y), width(width), r(r), g(g), b(b), a(a) {}

int Entity::getXPos() const { return x; }
int Entity::getYPos() const { return y; }

void Entity::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}
std::array<int, 4> calculateHitbox(int x, int y, int width) {
    int x1 = x - width / 2;
    int x2 = x + width / 2;
    int y1 = y - width / 2;
    int y2 = y + width / 2;

    return {x1, x2, y1, y2};  // Return as an array
}

// void collisionCheck(std:array hitboxes, ){

// }