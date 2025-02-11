/* main.cpp */
#define SDL_MAIN_HANDLED
#include "Player.hpp"
#include "Mob.hpp"
#include "Wall.hpp"
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <cmath>
#include <iostream>
#include <array>
// Screen dimensions
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;

//create an instance of an entity: 
// Entity entity(10, 10);  // Create an instance
double calculateAngle(int xc, int yc, int xm, int ym){
    // atan2(dy, dx) * (180.0 / M_PI);
    // Calculate the angle in radians using atan2
    double angleRadians = std::atan2(ym - yc, xm - xc);

    // Convert radians to degrees
    // double angleDegrees = angleRadians * (180.0 / M_PI);

    // // Ensure the angle is in the range [0, 360)
    // if (angleDegrees < 0) {
    //     angleDegrees += 360.0;
    // }

    return angleRadians + 0.5*M_PI;
}

int main() {
    // entity.displayMessage();  
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    // Initialize SDL_ttf
    if (TTF_Init() == -1) {
        std::cerr << "TTF Error: " << TTF_GetError() << std::endl;
        SDL_Quit();
        return 1;
    }

    // Create SDL window
    SDL_Window* window = SDL_CreateWindow(
        "Bruh game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN
    );
    if (!window) {
        std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Create SDL renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    // Load font
    TTF_Font* font = TTF_OpenFont("Assets/font/arial.ttf", 24); // Ensure you have "arial.ttf" or a valid font file
    if (!font) {
        std::cerr << "Font loading failed: " << TTF_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }


    // Get the text to display
    std::string displayedTextPos = "Okbro";
    // Set the text color
    SDL_Color textColor = {255, 255, 255, 255}; // White color
    // Create a surface with the text
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, displayedTextPos.c_str(), textColor);
    if (!textSurface) {
        std::cerr << "Text rendering failed: " << TTF_GetError() << std::endl;
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    // Create a texture from the surface
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    if (!textTexture) {
        std::cerr << "Text texture creation failed: " << SDL_GetError() << std::endl;
        TTF_CloseFont(font);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    // Get text dimensions
    int textWidth, textHeight;
    SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);
    // Position the text
    SDL_Rect textRect = {20, 20, textWidth, textHeight}; // Top-left corner at (20, 20)


    // Main loop
    bool isRunning = true;
    SDL_Event event;
    //player and mob starting positions and initializers
    Player player(500, 500, 20);
    Mob mob1(200, 150, 10);
    Wall wall1(300, 200, 10);

    bool wKeyPressed = false;
    bool sKeyPressed = false;
    bool aKeyPressed = false;
    bool dKeyPressed = false;

    float normalSpeed = 3.0f;
    float diagonalSpeed = normalSpeed * 0.70711f;

    while (isRunning) { // main loop
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) isRunning = false;
            
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_w: wKeyPressed = true; break;
                    case SDLK_a: aKeyPressed = true; break;
                    case SDLK_s: sKeyPressed = true; break;
                    case SDLK_d: dKeyPressed = true; break;
                }
            }
            if (event.type == SDL_KEYUP) {
                switch (event.key.keysym.sym) {
                    case SDLK_w: wKeyPressed = false; break;
                    case SDLK_a: aKeyPressed = false; break;
                    case SDLK_s: sKeyPressed = false; break;
                    case SDLK_d: dKeyPressed = false; break;
                }
            }
        }
        
        float moveSpeed = (wKeyPressed || sKeyPressed) && (aKeyPressed || dKeyPressed) ? diagonalSpeed : normalSpeed;
        
        if (wKeyPressed) player.setPosition(player.getXPos(), player.getYPos() - (int)std::round(moveSpeed));
        if (aKeyPressed) player.setPosition(player.getXPos() - (int)std::round(moveSpeed), player.getYPos());
        if (sKeyPressed) player.setPosition(player.getXPos(), player.getYPos() + (int)std::round(moveSpeed));
        if (dKeyPressed) player.setPosition(player.getXPos() + (int)std::round(moveSpeed), player.getYPos());

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);

        // Render the text
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        
        // Get mouse position
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);


        // std::cout << "Angle: (" << angle << ", Mouse position( x and y ) "<< mouseX << ", " << mouseY << ")" << std::endl;
        // Draw mouse position on the screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
        SDL_RenderDrawPoint(renderer, mouseX, mouseY);
            
        // get the angle for drawing
        double angle = calculateAngle(player.getXPos(), player.getYPos(), mouseX, mouseY);



        //rendering all the mobs (should be a function later! TODO)
        player.draw(renderer, angle);
        mob1.draw(renderer);
        wall1.draw(renderer);
        // wall1.draw(renderer, angle);

// REMOVE-------------------------------------
        // Draw a single pixel
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
        SDL_RenderDrawPoint(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2); // Pixel at center of screen
// REMOVE-------------------------------------

        // Present the updated screen
        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Limit to ~60 FPS
    }

    // Cleanup

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
