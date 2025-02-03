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
#define topPoint 9
#define bottomRight 3
#define bottomLeft 3
void Entity::draw(SDL_Renderer* renderer, double angle, bool player, bool mob, bool wall) const {

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, a); // Color

    //make center 
    SDL_RenderDrawPoint(renderer, this->getXPos(), this->getYPos());

    SDL_SetRenderDrawColor(renderer, r, g, b, a); // Color
    //TODO MAKE THEM ARGUMENT:
    int objSize = 30;
    int length = 1;
    // double angle = 0.0;
    // bool player = true;
    //Angle of rotation (positive counterclockwise)
    // Set the render color for the entity
    
    //default values: 
    
    if(player){
        // drawCircle(renderer, this->getXPos(), this->getYPos(), objSize/2);
        drawTriangle(renderer, objSize, this->getXPos(), this->getYPos(), angle, length, false);
        
        // length = 3;
        drawTriangle(renderer, objSize, this->getXPos(), this->getYPos(), angle, length, true);
    }else{//TODO make a distinguishable function for walls and mobs
        drawCircle(renderer, this->getYPos(), this->getXPos(), 10);
    }
     
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
