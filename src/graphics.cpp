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
void drawCircle(SDL_Renderer* renderer, int x, int y, int radius) {
    int limit = radius * radius;

    for (int i = -radius; i< radius; i++){
        for (int j =-radius; j<radius; j++){
            if (( i*i) + (j*j) <limit){
                SDL_RenderDrawPoint(renderer, x+i, y+j);
            }
        }
    }
    // int x = 0;
    // int y = radius;
    // int decision = 1 - radius; // Initial decision parameter
    
    // while (x <= y) {
    //     // Draw the 8 symmetrical points
    //     SDL_RenderDrawPoint(renderer, centerX + x, centerY + y); // Octant 1
    //     SDL_RenderDrawPoint(renderer, centerX - x, centerY + y); // Octant 2
    //     SDL_RenderDrawPoint(renderer, centerX + x, centerY - y); // Octant 3
    //     SDL_RenderDrawPoint(renderer, centerX - x, centerY - y); // Octant 4
    //     SDL_RenderDrawPoint(renderer, centerX + y, centerY + x); // Octant 5
    //     SDL_RenderDrawPoint(renderer, centerX - y, centerY + x); // Octant 6
    //     SDL_RenderDrawPoint(renderer, centerX + y, centerY - x); // Octant 7
    //     SDL_RenderDrawPoint(renderer, centerX - y, centerY - x); // Octant 8

    //     // Update decision parameter and coordinates
    //     if (decision < 0) {
    //         decision += 2 * x + 3;
    //     } else {
    //         decision += 2 * (x - y) + 5;
    //         y--;
    //     }
    //     x++;
    // }
}
void drawTriangle(SDL_Renderer* renderer, int objSize, int defCX, int defCY, double angle, int length, bool right){

    // int defBLX = defCX - objSize/3;
    // int defBLY = defCY + objSize/3;
    // int defTX = defCX; //top x
    // int defTY = defCY - objSize/length; //top y
    // int defBRX = defCX + objSize/3;
    // int defBRY = defCY + objSize/3;
    //TODO here are preset points - make it an argument
    int defBLX;
    int defBLY;
    int defTX;
    int defTY;
    int defBRX;
    int defBRY; //top y
    if(right == true){
        defBLX = defCX;
        defBLY = defCY - objSize/length; //top y
        defTX = defCX;
        defTY = defCY;
        defBRX = defCX + objSize/3;
        defBRY = defCY + objSize/3;
    }else{
        defBLX = defCX;
        defBLY = defCY - objSize/length; //top y
        defTX = defCX;
        defTY = defCY;
        defBRX = defCX - objSize/3;
        defBRY = defCY + objSize/3;
    }
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


    
    float startingY = (float)y1;
    float endingY = (float)y1;

    //set slope to int( so that each certain itteration there will be a pixel)
    int startingYRounded = y1;
    int endingYRounded = y1;

    float startingSlope = m13;
    float endingSlope = m12;

    if(m12 != inf){
        for(int i = x1; i<x2; i++){
            startingY+= m12;
            endingY+= m13;
            startingYRounded = (int)(startingY);
            endingYRounded = (int)(endingY);
            drawVerticalLine(renderer, startingYRounded, endingYRounded, i);
        }
    }else{
        startingY = y2;
        endingY = y1;
    }
    //second loop:

    if(m23 != inf){
        for(int i = x2; i<x3; i++){
            startingY+= m23;
            endingY+= m13;
            startingYRounded = (int)(startingY);
            endingYRounded = (int)(endingY);
            drawVerticalLine(renderer, startingYRounded, endingYRounded, i);
        }
    }
    // for (int xCoordinate = x1; xCoordinate < x3; xCoordinate++) {
    //     // if(m12 == inf){
    //     //     xCoordinate = x2;// that will skip first loop
            
    //     // }
    //     if(xCoordinate == x2){
    //         endingSlope = m23;
    //         startingY = 
    //     }
    //     startingY+= startingSlope;
    //     endingY+= endingSlope;
    //     startingYRounded = std::round(startingY);
    //     endingYRounded = std::round(endingY);
    //     drawVerticalLine(renderer, startingYRounded, endingYRounded, xCoordinate);
    // }
}
// void drawWallHorizontal(){

// }
// void drawWallVertical(){

// }