#define SDL_MAIN_HANDLED
#include <Entity.hpp>
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <iostream>

// Screen dimensions
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//create an instance of an entity: 
// Entity entity(10, 10);  // Create an instance


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
        "Text Rendering", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
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
    Entity player(100, 100, 50, 50, 0, 255, 0, 255); // Green player
    Entity mob1(200, 150, 40, 40, 255, 0, 0, 255);  // Red mob
    Entity mob2(300, 200, 30, 30, 0, 0, 255, 255);  // Blue mob
    while (isRunning) {
        // Handle events
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isRunning = false;
            }
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);

        // Render the text
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);

        //rendering all the mobs (should be a function later! TODO)
        player.draw(renderer);
        mob1.draw(renderer);
        mob2.draw(renderer);
        
        // Draw a single pixel
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
        SDL_RenderDrawPoint(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2); // Pixel at center of screen
        
        // Present the updated screen
        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Limit to ~60 FPS
    }

    // Cleanup
    SDL_DestroyTexture(textTexture);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
