/* Mob.cpp */
#include "Mob.hpp"


Mob::Mob(int x, int y, int width) : Entity(x, y, width, 100, 20, 255, 0, 0, 255) {}

void Mob::draw(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    drawCircle(renderer, getXPos(), getYPos(), width);
}
std::array<int, 4> Mob::calculateHitbox() const {

    return {x - width*2, y - width*2, x + width*2, y + width*2};

}