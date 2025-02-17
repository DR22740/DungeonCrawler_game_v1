/* Projectile.cpp */
#include "Projectile.hpp"

                                                        //x, y, width, hp, dmg, colors RGBA
Projectile::Projectile(int x, int y, int width, bool aggroed, int dx, int dy) : Entity(x, y, width, 60, 30, 255, 0, 0, 255), aggroed(aggroed), dx(dx), dy(dy) {}

void Projectile::draw(SDL_Renderer* renderer) const {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
    drawCircle(renderer, getXPos(), getYPos(), width);
}
void Projectile::setPosition(int newX, int newY, std::vector<Entity*>& entityList){
    setPosition(newX, newY, entityList, 0);  // Calls the overloaded version with angle = 0.0 TODO - make sure it is required!!!
}
void Projectile::setPosition(int newX, int newY, std::vector<Entity*>& entityList, int mobIndex) {
    this->hp = this->hp - 1;
    for (int i = 0; i < entityList.size(); i++) {
        if (entityList[i] == NULL) continue;
        if (i == mobIndex) continue; // Ignore checking the mob that spawned a projectile

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
void Projectile::collisionLogic(Entity* collidedEntity) {
    collidedEntity->hp -= this->dmg;  // Use melee damage instead of base damage
    std::cout << "Projectile colided " << std::endl;
    this->hp = this->hp - 60;
}
std::array<int, 4> Projectile::calculateHitbox() const {

    return {0, 0, 0, 0};//no hitbox

}