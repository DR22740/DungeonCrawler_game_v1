#include <SDL.h>
#include <iostream>
#include <cmath> // For sqrt
#include "graphics.hpp"
#define topPoint 9
#define bottomRight 3
#define bottomLeft 3


void swap(int * var1, int * var2){
    int temp = *var1;
    *var1 = *var2;
    *var2 = temp;
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

void drawVerticalLine(SDL_Renderer * renderer, int y1, int y2, int x){
        if(y1 > y2){
            swap(&y1, &y2);
        }
        for (int i = y1; i <= y2; i++){
            SDL_RenderDrawPoint(renderer, x, i);

        }
}
void drawTriangle(SDL_Renderer* renderer, int objSize, int defCX, int defCY, double angle){

    int defBLX = defCX - objSize/3;
    int defBLY = defCY + objSize/3;
    int defTX = defCX;
    int defTY = defCY - objSize;
    int defBRX = defCX + objSize/3;
    int defBRY = defCY + objSize/3;

    //Angle of rotation (positive counterclockwise)
    
    int x1 = ((defBLX - defCX)*cos(angle)) - ((defBLY-defCY)*sin(angle)) + defCX; 
    int y1 = ((defBLX - defCX)*sin(angle)) + ((defBLY-defCY)*cos(angle)) + defCY;
    int x2 = ((defTX - defCX)*cos(angle)) - ((defTY-defCY)*sin(angle)) + defCX;
    int y2 = ((defTX - defCX)*sin(angle)) + ((defTY-defCY)*cos(angle)) + defCY;
    int x3 = ((defBRX - defCX)*cos(angle)) - ((defBRY-defCY)*sin(angle)) + defCX; 
    int y3 = ((defBRX - defCX)*sin(angle)) + ((defBRY-defCY)*cos(angle)) + defCY;
    //plot the tree points
    SDL_RenderDrawPoint(renderer, x1, y1);
    SDL_RenderDrawPoint(renderer, x2, y2);
    SDL_RenderDrawPoint(renderer, x3, y3);


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

    //TODO - set a function to decide on which side of the LINE (inside or outside the triangle)
    //TODO - make sure you check if it is inside the triangle (its ok if it does not draw)
    //the key is bresenhams algorithm
    if(x1 > x2){
        swap(&x1, &x2);
        swap(&y1, &y2);
    }
    if(x1 > x3){
        swap(&x1, &x3);
        swap(&y1, &y3);
    }
    if(x2 > x3){
        swap(&x2, &x3);
        swap(&y2, &y3);
    }
    //TODO if x1 = x2 
    //freakyyyy
    float m12;
    float m13;
    float m23;

    #define inf 1e10

    if(x2==x1){
        m12 = inf;
    }else{
        m12 = (float)(y2-y1)/(x2-x1);
    }
    if(x3==x1){
        m13 = inf;
    }else{
        m13 = (float)(y3-y1)/(x3-x1);
    }
    if(x3==x2){
        m23 = inf;
    }else{
        m23 = (float)(y3-y2)/(x3-x2);
    }

    // std::cout << "Slope m12: " << m12 << std::endl;
    // std::cout << "Slope m13: " << m13 << std::endl;
    // std::cout << "Slope m23: " << m23 << std::endl;
    
    float startingY = (float)y1;
    float endingY = (float)y1;

    //set slope to int( so that each certain itteration there will be a pixel)
    int startingYRounded = y1;
    int endingYRounded = y1;
    // if(m12 != inf){
    //     for(int i = x1; i<x2; i++){
    //         startingY+= m12;
    //         endingY+= m13;
    //         startingYRounded = (int)(startingY);
    //         endingYRounded = (int)(endingY);
    //         drawVerticalLine(renderer, startingYRounded, endingYRounded, i);
    //     }
    // }
    float startingSlope = m13;
    float endingSlope = m12;

    for (int xCoordinate = x1; xCoordinate < x3; xCoordinate++) {
        if(xCoordinate == x2){
            endingSlope = m23;
        }
        startingY+= startingSlope;
        endingY+= endingSlope;
        startingYRounded = std::round(startingY);
        endingYRounded = std::round(endingY);
        drawVerticalLine(renderer, startingYRounded, endingYRounded, xCoordinate);
    }
}
// void drawWallHorizontal(){

// }
// void drawWallVertical(){

// }