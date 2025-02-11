/* Mob.cpp */
#include "Mob.hpp"


Mob::Mob(int x, int y, int width) : Entity(x, y, width, 255, 0, 0, 255) {}

void Mob::draw(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    drawCircle(renderer, getXPos(), getYPos(), width);
}