/* Entity.hpp - Base Entity Class */
#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SDL.h>
#include <string>
#include <iostream>
#include "graphics.hpp"

class Entity {
protected:
    int x, y; // Position
    int width, height; // Size
    Uint8 r, g, b, a; // Color

public:
    Entity(int x, int y, int width, Uint8 r, Uint8 g, Uint8 b, Uint8 a);
    int getXPos() const;
    int getYPos() const;
    void setPosition(int newX, int newY);
    virtual void draw(SDL_Renderer* renderer) const = 0;
    virtual ~Entity() {}
};

#endif // ENTITY_HPP