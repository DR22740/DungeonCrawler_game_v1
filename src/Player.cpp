/* Player.cpp */
#include "Player.hpp"

Player::Player(int x, int y) : Entity(x, y, 50, 50, 0, 255, 0, 255) {}

void Player::draw(SDL_Renderer* renderer, double angle) const {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, a);
    SDL_RenderDrawPoint(renderer, getXPos(), getYPos());
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    drawTriangle(renderer, 30, getXPos(), getYPos(), angle, 1, false);
    drawTriangle(renderer, 30, getXPos(), getYPos(), angle, 1, true);
}