/* Wall.cpp */
#include "Wall.hpp"

Wall::Wall(int x, int y, int width) : Entity(x, y, 30, 0, 0, 255, 255) {}

void Wall::draw(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    //TODO implement a square drawing method bro
    drawSquare(renderer, width, x, y);

}