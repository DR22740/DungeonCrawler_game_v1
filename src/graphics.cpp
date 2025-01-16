#include <SDL.h>
#include <iostream>
#include <cmath> // For sqrt
#include "graphics.hpp"
#define topPoint 9
#define bottomRight 3
#define bottomLeft 3

int findMax(int a, int b, int c){
    // Find the largest
    int largest = a;
    if (b > largest) largest = b;
    if (c > largest) largest = c;

    return largest;
}

int findMin(int a, int b, int c){
    int smallest = a;
    // Find the smallest
    if (b < smallest) smallest = b;
    if (c < smallest) smallest = c;

    return smallest;
}
bool isPointOnLine(int x1, int y1, int x2, int y2, int x, int y) {
    // Check for vertical line
    if (x1 == x2) {
        return (x == x1); // x must match for vertical line
    }

    // Check for horizontal line
    if (y1 == y2) {
        return (y == y1); // y must match for horizontal line
    }

    // Calculate slope (m)
    double m = static_cast<double>(y2 - y1) / (x2 - x1);

    // Calculate y for the given x
    int expectedY = std::round(y1 + m * (x - x1));

    // Calculate x for the given y
    int expectedX = std::round(x1 + (y - y1) / m);

    // Check if the given point matches the rounded values
    return (y == expectedY && x == expectedX);
}
void drawTriangle(SDL_Renderer* renderer, int objSize, int defCX, int defCY, double angle){

    int defBLX = defCX - objSize/3;
    int defBLY = defCY + objSize/3;
    int defTX = defCX;
    int defTY = defCY - objSize;
    int defBRX = defCX + objSize/3;
    int defBRY = defCY + objSize/3;

    //Angle of rotation (positive counterclockwise)
    
    int newBLX = ((defBLX - defCX)*cos(angle)) - ((defBLY-defCY)*sin(angle)) + defCX; 
    int newBLY = ((defBLX - defCX)*sin(angle)) + ((defBLY-defCY)*cos(angle)) + defCY;
    int newTX = ((defTX - defCX)*cos(angle)) - ((defTY-defCY)*sin(angle)) + defCX;
    int newTY = ((defTX - defCX)*sin(angle)) + ((defTY-defCY)*cos(angle)) + defCY;
    int newBRX = ((defBRX - defCX)*cos(angle)) - ((defBRY-defCY)*sin(angle)) + defCX; 
    int newBRY = ((defBRX - defCX)*sin(angle)) + ((defBRY-defCY)*cos(angle)) + defCY;
    //plot the tree points
    SDL_RenderDrawPoint(renderer, newBLX, newBLY);
    SDL_RenderDrawPoint(renderer, newTX, newTY);
    SDL_RenderDrawPoint(renderer, newBRX, newBRY);


    //find highest and lowest y and x and move up 
    //line 1:
    // rise/run = y2- y1 /  x2 - x1
    //find points on the line
    //we find it for the first line and we have first relation 
    //this is the first set of restrictions
    //line 2: 
    //we make 2nd set of restrictions (which )
    //line 3: 
    //we make 3rd set of restrictions

    //once we have all 
    int smallestX = findMin(newBRX, newBLX, newTX);
    int smallestY = findMin(newBRY, newBLY, newTY);

    int largestX = findMax(newBRX, newBLX, newTX);
    int largestY = findMax(newBRY, newBLY, newTY);

    int Collisions = 0;

    for (int yCoordinate = smallestY-1; yCoordinate<largestY+1; yCoordinate++){
        for (int xCoordinate = smallestX-1; xCoordinate < largestX+1; xCoordinate++) {
            
            if(isPointOnLine(newBRX, newBRY, newBLX, newBLY, xCoordinate, yCoordinate)){
                Collisions = Collisions + 1;
                
            }
            if(isPointOnLine(newBRX, newBRY, newTX, newTY, xCoordinate, yCoordinate)){
                Collisions = Collisions + 1;
               
            }
            if(isPointOnLine(newBLX, newBLY, newTX, newTY, xCoordinate, yCoordinate)){
                Collisions = Collisions + 1;
               
            }
            if(Collisions >= 2){
                break;
            }
            if(Collisions == 1){
                SDL_RenderDrawPoint(renderer, xCoordinate, yCoordinate);
            }
        }
        Collisions = 0;
    }
}
// void drawWallHorizontal(){

// }
// void drawWallVertical(){

// }