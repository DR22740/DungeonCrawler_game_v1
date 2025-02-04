/* Wall.cpp */
#include "Wall.hpp"

Wall::Wall(int x, int y) : Entity(x, y, 30, 30, 0, 0, 255, 255) {}

void Wall::draw(SDL_Renderer* renderer, double angle) const {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    SDL_Rect rect = { getXPos() - width / 2, getYPos() - height / 2, width, height };
    SDL_RenderFillRect(renderer, &rect);
}