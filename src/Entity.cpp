/* Entity.cpp - Base Entity Implementation */
#include "Entity.hpp"
#include <array>
#include <vector>
Entity::Entity(int x, int y, int width, int hp, int dmg, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    : x(x), y(y), hp(hp), dmg(dmg), width(width), r(r), g(g), b(b), a(a), hitbox(calculateHitbox()) {}

int Entity::getXPos() const { return x; }
int Entity::getYPos() const { return y; }
#include <array>
#include <iostream>

// Function to check if the position collides with any hitbox
void Entity::setPosition(int newX, int newY, std::vector<Entity*>& entityList) {
    for (int i = 0; i < entityList.size(); i++) {
        if (entityList[i] == NULL) continue;
        if (entityList[i] == this) continue; // Ignore checking itself

        int x1 = entityList[i]->hitbox[0];
        int y1 = entityList[i]->hitbox[1];
        int x2 = entityList[i]->hitbox[2];
        int y2 = entityList[i]->hitbox[3];

        // Check if newX, newY is inside the hitbox
        if (newX >= x1 && newX <= x2 && newY >= y1 && newY <= y2) {
            std::cout << "Collision detected at (" << newX << ", " << newY << ") within hitbox: [" << x1 << ", " << y1 << ", " << x2 << ", " << y2 << "]" << std::endl;

            // Get the objects involved in the collision
            Entity* currentEntity = this;  // The moving entity
            Entity* collided = entityList[i];            // The entity it collided with

            collisionLogic(collided);

            // Log the damage
            std::cout << "Entity at index " << i << " took " << currentEntity->dmg 
            << " damage! Remaining HP: " << collided->hp << std::endl;

            return; // Exit early if collision detected
        }
    }

    // No collision, update position
    this->x = newX;
    this->y = newY;

    // Call calculateHitbox() to update hitbox
    this->hitbox = calculateHitbox();
}

void Entity::collisionLogic(Entity* collidedEntity) {
    collidedEntity->hp -= dmg;
    std::cout << "Entity took " << dmg << " damage! Remaining HP: " << collidedEntity->hp << std::endl;
}

std::array<int, 4> Entity::calculateHitbox() const {

    return {x - width, y - width, x + width, y + width};

}

// void collisionCheck(std:array hitboxes, ){

// }