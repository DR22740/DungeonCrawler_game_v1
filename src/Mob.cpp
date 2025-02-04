/* Mob.cpp */
#include "Mob.hpp"

Mob::Mob(int x, int y) : Entity(x, y, 40, 40, 255, 0, 0, 255) {}

void Mob::draw(SDL_Renderer* renderer, double angle) const {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    drawCircle(renderer, getXPos(), getYPos(), 10);
}