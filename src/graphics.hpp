#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SDL.h>
#include <iostream>
#include <cmath> // For sqrt

void swap(int * var1, int * var2);

bool isPointOnLine(int x1, int y1, int x2, int y2, int x, int y);

void drawVerticalLine(SDL_Renderer * renderer, int y1, int y2, int x);
// Function declarations
void drawCircle(SDL_Renderer* renderer, int objSize, int defCX, int defCY);
void drawTriangle(SDL_Renderer* renderer, int objSize, int x, int y, double angle, int length, bool right);
// void drawWallHorizontal(SDL_Renderer* renderer, int x, int y, int length);
// void drawWallVertical(SDL_Renderer* renderer, int x, int y, int length);

#endif // GRAPHICS_HPP
