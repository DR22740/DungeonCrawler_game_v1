/* Projectile.hpp */
#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "Entity.hpp"

class Projectile : public Entity {
public:
    Projectile(int x, int y, int width, bool aggroed, int dx, int dy);
    int dx, dy;
    bool aggroed;
    void draw(SDL_Renderer* renderer) const override;
    void setPosition(int newX, int newY, std::vector<Entity*>& entityList, int mobIndex);  // Overloaded version
private:
    void collisionLogic(Entity* collidedEntity) override; // Override collision logic
    void setPosition(int newX, int newY, std::vector<Entity*>& entityList) override; //gets overriden
    std::array<int, 4> calculateHitbox() const override;
};

#endif // MOB_HPP