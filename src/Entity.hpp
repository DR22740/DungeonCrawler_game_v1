/* Entity.hpp - Base Entity Class */
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SDL.h>
#include <string>
#include <iostream>
#include "graphics.hpp"
#include <array>
#include <vector>
class Entity {
    protected:
        int x, y; // Position
        int width, height; // Size
        Uint8 r, g, b, a; // Color

    public:
        int hp, dmg;
        std::array<int, 4> hitbox;
        Entity(int x, int y, int hp, int dmg, int width, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        int getXPos() const;
        int getYPos() const;
        virtual void setPosition(int newX, int newY, std::vector<Entity*>& entityList);
        virtual void collisionLogic(Entity* collidedEntity); 
        virtual void draw(SDL_Renderer* renderer) const {}
        virtual std::array<int, 4> calculateHitbox() const;
        virtual ~Entity() {}
};

#endif // ENTITY_HPP