#include "Entity.hpp"

// Constructor
Entity::Entity(int x, int y, int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
    : x(x), y(y), width(width), height(height), r(r), g(g), b(b), a(a) {}

// Function to display "Hello, World!"
void Entity::displayMessage() const {
    std::cout << "Hello, World!" << std::endl;
}

// Getter for number
int Entity::getXPos() const {
    return x;
}

int Entity::getYPos() const {
    return y;
}

// Setter for number
void Entity::setPosition(int newX, int newY) {
    x = newX;
    y = newY;
}
void Entity::draw(SDL_Renderer* renderer) const {
    // Set the render color for the entity
    SDL_SetRenderDrawColor(renderer, r, g, b, a);

    // Create a rectangle representing the entity
    SDL_Rect rect = { x, y, width, height };

    // Draw the rectangle
    SDL_RenderFillRect(renderer, &rect);
}
// Getter for text
std::string Entity::getPosText() const {
    int yPosText = this->getYPos();
    int xPosText = this->getXPos();
    std::string strY = std::to_string(yPosText);
    std::string strX = std::to_string(xPosText);
    std::string text = "y: " + strY + "x: " + strX ;  
    return text;
}

// Setter for text
// void Entity::setText(const std::string& str) {
//     text = str;
// }
