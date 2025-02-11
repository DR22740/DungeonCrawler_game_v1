/* Player.cpp */
#include "Player.hpp"

Player::Player(int x, int y, int width) : Entity(x, y, width, 0, 255, 0, 255) {}

void Player::draw(SDL_Renderer* renderer) const {
    draw(renderer, 0.0);  // Calls the overloaded version with angle = 0.0 TODO - make sure it is required!!!
}
void Player::draw(SDL_Renderer* renderer, double angle) const {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, a);
    SDL_RenderDrawPoint(renderer, getXPos(), getYPos());
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    drawTriangle(renderer, width, getXPos(), getYPos(), angle, 1, false);
    drawTriangle(renderer, width, getXPos(), getYPos(), angle, 1, true);
}