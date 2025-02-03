#ifndef Entity_HPP
#define Entity_HPP
#include <SDL.h>
#include <string>
#include <iostream>
#include "graphics.hpp"

class Entity {
private:
    int x, y; // Position of the entity
    int width, height; // Size of the entity
    Uint8 r, g, b, a; // Color of the entity       // Example variable
    
public:
    // Constructor
    Entity(int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

    // Function to display "Hello, World!"
    void displayMessage() const;
  
    // Getter for number
    int getXPos() const;

    int getYPos() const;
    // Setter for number
    void setPosition(int newX, int newY);

    void draw(SDL_Renderer* renderer, double angle, bool player, bool mob, bool wall) const;
    // Getter for text
    std::string getPosText() const; 
    // Setter for text
    // void setText(const std::string& str);
};

#endif // Entity_HPP
