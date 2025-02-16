/* Player.cpp */
#include "Player.hpp"

Player::Player(int x, int y, int width) : Entity(x, y, width, 200, 20, 0, 255, 0, 255) {}

void Player::draw(SDL_Renderer* renderer) const {
    draw(renderer, 0.0);  // Calls the overloaded version with angle = 0.0 TODO - make sure it is required!!!
}

void Player::collisionLogic(Entity* collidedEntity) {
    this->hp = this->hp-collidedEntity->dmg;
    collidedEntity->hp -= this->dmg*99;  // Use melee damage instead of base damage
    std::cout << "Player dealt " << this->dmg*99 << " melee damage! Remaining HP: " << collidedEntity->hp << std::endl;
    std::cout << "Player health: " << this->hp << std::endl;
}
void Player::draw(SDL_Renderer* renderer, double angle) const {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, a);
    SDL_RenderDrawPoint(renderer, getXPos(), getYPos());
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    drawTriangle(renderer, width, getXPos(), getYPos(), angle, 1, false);
    drawTriangle(renderer, width, getXPos(), getYPos(), angle, 1, true);
}