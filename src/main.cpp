/* main.cpp */
#define SDL_MAIN_HANDLED
#include "Player.hpp"
#include "Mob.hpp"
#include "Projectile.hpp"
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
void getPointInDirection(int playerX, int playerY, int mouseX, int mouseY, int distance, int& targetX, int& targetY) {
    // Calculate the angle toward the mouse
    double angle = atan2(mouseY - playerY, mouseX - playerX);

    // Find new point that is `distance` units away
    targetX = playerX + distance * cos(angle);
    targetY = playerY + distance * sin(angle);
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
        "Dungeon Crawler game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
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

    int frameCount = 0;
    float fps = 0.0f;
    Uint32 lastTime = SDL_GetTicks(); //fps
    
    // Main loop
    bool isRunning = true;
    SDL_Event event;
    //==============================================================================================
    //---------------------------SPAWNING ALL THE STUFF HERE-----------------------------------------
    //==============================================================================================
    //player and mob starting positions and initializers
    Player* player = new Player(500, 500, 20);
    Mob* mob1 = new Mob(200, 150, 10);
    Wall* wall1 = new Wall(300, 200, 30);
    Wall* wall2 = new Wall(40, 40, 30);
    Wall* wall3 = new Wall(40, 80, 30);
    Wall* wall4 = new Wall(40, 120, 30);
    Wall* wall5 = new Wall(40, 160, 30);
    Wall* wall6 = new Wall(40, 200, 30);
    Wall* wall7 = new Wall(40, 240, 30);
    Wall* wall8 = new Wall(40, 280, 30);
    Wall* wall9 = new Wall(40, 320, 30);
    Wall* wall10 = new Wall(40, 360, 30);
    Wall* wall11 = new Wall(40, 400, 30);
    Projectile* projectile1 = nullptr;
    // std::vector<std::array<int, 4>> hitboxes(4); // Hardcoded for 3 entities
    std::vector<Entity*> entityList(13); // Second list with object pointers
    // Spawn Entities
    // Player player(500, 500, 20);
    // Mob mob1(200, 150, 10);
    // Wall wall1(300, 200, 10);
    
    // Populate the hitbox (placeholder) for each entity

    // Associate entities with hitboxes using pointers (hacky way yet to be changed but it is what it is)
    entityList[0] = player;
    entityList[1] = mob1;
    //we dont input the projectile1 since it has no hitbox
    entityList[2] = wall1;
    entityList[3] = wall2;
    entityList[4] = wall3;
    entityList[5] = wall4;
    entityList[6] = wall5;
    entityList[7] = wall6;
    entityList[8] = wall7;
    entityList[9] = wall8;
    entityList[10] = wall9;
    entityList[11] = wall10;
    entityList[12] = wall11;
    // Call setPosition to ensure hitboxes are updated
    player->setPosition(player->getXPos(), player->getYPos(), entityList);
    mob1->setPosition(mob1->getXPos(), mob1->getYPos(), entityList);
    wall1->setPosition(wall1->getXPos(), wall1->getYPos(), entityList);
    wall2->setPosition(wall2->getXPos(), wall2->getYPos(), entityList);
    wall3->setPosition(wall3->getXPos(), wall3->getYPos(), entityList);
    wall4->setPosition(wall4->getXPos(), wall4->getYPos(), entityList);
    wall5->setPosition(wall5->getXPos(), wall5->getYPos(), entityList);
    wall6->setPosition(wall6->getXPos(), wall6->getYPos(), entityList);
    wall7->setPosition(wall7->getXPos(), wall7->getYPos(), entityList);
    wall8->setPosition(wall8->getXPos(), wall8->getYPos(), entityList);
    wall9->setPosition(wall9->getXPos(), wall9->getYPos(), entityList);
    wall10->setPosition(wall10->getXPos(), wall10->getYPos(), entityList);
    wall11->setPosition(wall11->getXPos(), wall11->getYPos(), entityList);

    //==============================================================================================
    //------------------------END OF SPAWNING ALL THE STUFF HERE-------------------------------------
    //==============================================================================================
    bool wKeyPressed = false;
    bool sKeyPressed = false;
    bool aKeyPressed = false;
    bool dKeyPressed = false;

    float normalSpeed = 3.0f;
    float diagonalSpeed = normalSpeed * 0.70711f;
    Uint32 currentTime; //fps

    while (isRunning) { // main loop
        //fps 
        currentTime = SDL_GetTicks();
        frameCount++;
        if (currentTime > lastTime + 1000) {
            fps = frameCount * 1000.0f / (currentTime - lastTime);
            lastTime = currentTime;
            frameCount = 0;
        }

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
        
        // float moveSpeed = (wKeyPressed || sKeyPressed) && (aKeyPressed || dKeyPressed) ? diagonalSpeed : normalSpeed;
        
        // if (wKeyPressed) player->setPosition(player->getXPos(), player->getYPos() - (int)std::round(moveSpeed), entityList);
        // if (aKeyPressed) player->setPosition(player->getXPos() - (int)std::round(moveSpeed), player->getYPos(), entityList);
        // if (sKeyPressed) player->setPosition(player->getXPos(), player->getYPos() + (int)std::round(moveSpeed), entityList);
        // if (dKeyPressed) player->setPosition(player->getXPos() + (int)std::round(moveSpeed), player->getYPos(), entityList);

        //DELETE LATER ITS TEMP

        

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);

        // Render the text
        SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
        
        // Get mouse position
        int mouseX, mouseY;
        SDL_GetMouseState(&mouseX, &mouseY);
        float dx = mouseX - player->getXPos();
        float dy = mouseY - player->getYPos();
        
        // Normalize the direction vector
        float length = std::sqrt(dx * dx + dy * dy);
        if (length != 0) {
            dx /= length;
            dy /= length;
        }
        
        // Compute perpendicular vector (always counterclockwise)
        float perpX = -dy; // Leftward direction
        float perpY = dx;  // Leftward direction
        
        float moveSpeed = (wKeyPressed || sKeyPressed) && (aKeyPressed || dKeyPressed) ? diagonalSpeed : normalSpeed;
        
        // Move towards the mouse when pressing W
        if (wKeyPressed) player->setPosition(player->getXPos() + std::round(dx * moveSpeed*3), 
                                             player->getYPos() + std::round(dy * moveSpeed*3), entityList);
        
        // Move away from the mouse when pressing S
        if (sKeyPressed) player->setPosition(player->getXPos() - std::round(dx * moveSpeed), 
                                             player->getYPos() - std::round(dy * moveSpeed), entityList);
        
        // Move right (always perpendicular to the mouse direction)
        if (dKeyPressed) player->setPosition(player->getXPos() + std::round(perpX * moveSpeed), 
                                             player->getYPos() + std::round(perpY * moveSpeed), entityList);
        
        // Move left (always perpendicular to the mouse direction)
        if (aKeyPressed) player->setPosition(player->getXPos() - std::round(perpX * moveSpeed), 
                                             player->getYPos() - std::round(perpY * moveSpeed), entityList);

        // std::cout << "Angle: (" << angle << ", Mouse position( x and y ) "<< mouseX << ", " << mouseY << ")" << std::endl;
        // Draw mouse position on the screen
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White
        SDL_RenderDrawPoint(renderer, mouseX, mouseY);
            
        // get the angle for drawing
        double angle = calculateAngle(player->getXPos(), player->getYPos(), mouseX, mouseY);



        //rendering all the mobs (should be a function later! TODO)
        player->draw(renderer, angle);
        // if(mob1){
        //     mob1->draw(renderer);
        // }
        #define aggroRangeMult 200
        if(mob1){
            if (!projectile1) {  // Check if the projectile was not created yet
                std::cout << "we be spawning projectile" << std::endl;
                projectile1 = new Projectile(200, 150, 6, false, 0, 0);
            }
            if(mob1->hp <= 0){
                // vector.erase(vector.begin() + index);
                std::cout << "we delete the mob" << std::endl;
                entityList[1] = NULL;
                delete mob1;
                mob1 = NULL;
            }else{
                mob1->draw(renderer);
            }
            
            if(projectile1 && mob1){
                if(player->getXPos() >= (entityList[1]->hitbox[0])-aggroRangeMult &&  // Expand left
                   player->getXPos() <= (entityList[1]->hitbox[2])+aggroRangeMult &&  // Expand right
                   player->getYPos() >= (entityList[1]->hitbox[1])-aggroRangeMult &&  // Expand up
                   player->getYPos() <= (entityList[1]->hitbox[3])+aggroRangeMult &&  // Expand down
                   projectile1->aggroed == false){ //check if its the first time the player walked in
                    std::cout << "YOU ARE IN AGGRO RANGE!" << std::endl;
                    projectile1->aggroed = true;
                    // Compute the difference in position
                    float diffX = player->getXPos() - projectile1->getXPos();
                    float diffY = player->getYPos() - projectile1->getYPos();

                    // Compute the total distance
                    float distance = std::sqrt(diffX * diffX + diffY * diffY);

                    // Set the base movement speed (adjust this if needed)
                    float baseSpeed = 1.5f;  // You can increase or decrease this
                    float scalingFactor = std::max(distance / 20.0f, baseSpeed); // Does not go lower than the base speed

                    // Normalize the direction vector
                    if (distance > 0) {
                        diffX = (diffX / distance) * scalingFactor;
                        diffY = (diffY / distance) * scalingFactor;
                    }

                    // Apply the movement
                    projectile1->dx = std::round(diffX);
                    projectile1->dy = std::round(diffY);
                    }
                // setPosition(int newX, int newY, std::vector<Entity*>& entityList, int mobIndex)  
                }
        }
        if(projectile1){
            //add a counter to projectiles hp so as it flies hp decreases
            projectile1->setPosition(projectile1->getXPos() + projectile1->dx, projectile1->getYPos() + projectile1->dy, entityList, 1); 
            if(projectile1->hp <=0){
                delete projectile1;
                projectile1 = NULL;
            }else{
                projectile1->draw(renderer);
            }
        }


        wall1->draw(renderer);
        wall2->draw(renderer);
        wall3->draw(renderer);
        wall4->draw(renderer);
        wall5->draw(renderer);
        wall6->draw(renderer);
        wall7->draw(renderer);
        wall8->draw(renderer);
        wall9->draw(renderer);
        wall10->draw(renderer);
        wall11->draw(renderer);

        // wall1->draw(renderer, angle);

// REMOVE-------------------------------------
        // Draw a single pixel
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color
        SDL_RenderDrawPoint(renderer, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2); // Pixel at center of screen
// REMOVE-------------------------------------

        std::string fpsText = "FPS: " + std::to_string((int)fps);
        SDL_Surface* fpsSurface = TTF_RenderText_Solid(font, fpsText.c_str(), textColor);
        SDL_Texture* fpsTexture = SDL_CreateTextureFromSurface(renderer, fpsSurface);

        SDL_Rect fpsRect = {SCREEN_WIDTH - fpsSurface->w - 20, 20, fpsSurface->w, fpsSurface->h};
        SDL_RenderCopy(renderer, fpsTexture, NULL, &fpsRect);

        SDL_FreeSurface(fpsSurface);
        SDL_DestroyTexture(fpsTexture);

        SDL_RenderPresent(renderer);

        Uint32 frameTime = SDL_GetTicks() - currentTime;
        if (frameTime < 33) {
            SDL_Delay(33 - frameTime);
        }
    }
    // Cleanup

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

    return 0;
}
