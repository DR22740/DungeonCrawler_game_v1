#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP
#include <array>
#include <SDL.h>
#include <iostream>
#include <cmath> // For sqrt

void swap(int * var1, int * var2);

bool isPointOnLine(int x1, int y1, int x2, int y2, int x, int y);

void drawVerticalLine(SDL_Renderer * renderer, int y1, int y2, int x);
// Function declarations
void drawSquare(SDL_Renderer* renderer, int objSize, int x1, int y1);
void drawCircle(SDL_Renderer* renderer, int objSize, int defCX, int defCY);
void drawLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2);
void drawTriangleWithThreePoints(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, int x3, int y3);
void drawVisionTriangle(SDL_Renderer* renderer, int objSize, int defCX, int defCY, double angle, int length);
void drawTriangle(SDL_Renderer* renderer, int objSize, int x, int y, double angle, int length, bool right);
// void drawWallHorizontal(SDL_Renderer* renderer, int x, int y, int length);
// void drawWallVertical(SDL_Renderer* renderer, int x, int y, int length);

#endif // GRAPHICS_HPP
