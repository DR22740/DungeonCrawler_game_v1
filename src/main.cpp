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
#define aggroRangeMult 200
void handleMobProjectile(SDL_Renderer* renderer, Mob*& mob, Projectile*& projectile, Player* player, std::vector<Entity*>& entityList, int entityIndex) {
    if (mob) {
        // Spawn projectile if it does not exist
        if (!projectile) {
            std::cout << "Spawning projectile for mob at (" << mob->getXPos() << ", " << mob->getYPos() << ")" << std::endl;
            projectile = new Projectile(mob->getXPos(), mob->getYPos(), 6, false, 0, 0);
        }

        // If mob dies, delete it and remove from entity list
        if (mob->hp <= 0) {
            std::cout << "Deleting mob at index " << entityIndex << std::endl;
            delete mob;
            mob = nullptr;
            entityList[entityIndex] = nullptr;  // Clear from entity list
        } else {
            mob->draw(renderer);
        }

        // Handle projectile movement
        if (projectile && mob) {


            // Check if player is in aggro range
            if (player->getXPos() >= (entityList[entityIndex]->hitbox[0]) - aggroRangeMult &&
                player->getXPos() <= (entityList[entityIndex]->hitbox[2]) + aggroRangeMult &&
                player->getYPos() >= (entityList[entityIndex]->hitbox[1]) - aggroRangeMult &&
                player->getYPos() <= (entityList[entityIndex]->hitbox[3]) + aggroRangeMult &&
                !projectile->aggroed) {
                
                std::cout << "Player entered aggro range!" << std::endl;
                projectile->aggroed = true;

                // Compute movement vector
                float diffX = player->getXPos() - projectile->getXPos();
                float diffY = player->getYPos() - projectile->getYPos();
                float distance = std::sqrt(diffX * diffX + diffY * diffY);

                float baseSpeed = 1.5f;
                float scalingFactor = std::max(distance / 20.0f, baseSpeed); // Ensure minimum speed

                // Normalize direction vector
                if (distance > 0) {
                    projectile->dx = std::round((diffX / distance) * scalingFactor);
                    projectile->dy = std::round((diffY / distance) * scalingFactor);
                }
            }
        }
    }

    // Handle projectile movement
    if (projectile) {
        projectile->setPosition(projectile->getXPos() + projectile->dx, 
                                projectile->getYPos() + projectile->dy, 
                                entityList, entityIndex);

        // Delete projectile if it runs out of HP
        if (projectile->hp <= 0) {
            std::cout << "Deleting projectile" << std::endl;
            delete projectile;
            projectile = nullptr;
        } else {
            projectile->draw(renderer);
        }
    }
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
Player* player = new Player(500, 500, 20);
Mob* mob1 = new Mob(200, 80, 10);
Mob* mob2 = new Mob(200, 240, 10);
Mob* mob3 = new Mob(200, 400, 10);
Mob* mob4 = new Mob(200, 560, 10);
Mob* mob5 = new Mob(200, 720, 10);
Mob* mob6 = new Mob(200, 880, 10);
Mob* mob7 = new Mob(1200, 80, 10);
Mob* mob8 = new Mob(1200, 240, 10);
Mob* mob9 = new Mob(1200, 400, 10);
Mob* mob10 = new Mob(1200, 560, 10);
Mob* mob11 = new Mob(1200, 720, 10);
Mob* mob12 = new Mob(350, 80, 10);
Mob* mob13 = new Mob(500, 80, 10);
Mob* mob14 = new Mob(650, 80, 10);
Mob* mob15 = new Mob(800, 80, 10);
Mob* mob16 = new Mob(950, 80, 10);
Mob* mob17 = new Mob(1200, 580, 10);
Mob* mob18 = new Mob(1200, 440, 10);
Mob* mob19 = new Mob(1200, 300, 10);
Mob* mob20 = new Mob(1200, 160, 10);


Wall* wall1 = new Wall(100, 700, 10);
Wall* wall2 = new Wall(1100, 500, 10);
Wall* wall3 = new Wall(600, 600, 10);
Wall* wall4 = new Wall(300, 750, 10);
Wall* wall5 = new Wall(900, 350, 10);
Wall* wall6 = new Wall(750, 900, 10);
Wall* wall7 = new Wall(400, 550, 10);
Wall* wall8 = new Wall(1100, 750, 10);
Wall* wall9 = new Wall(500, 350, 10);
Wall* wall10 = new Wall(1000, 650, 10);


Projectile* projectile1 = nullptr;
Projectile* projectile2 = nullptr;
Projectile* projectile3 = nullptr;
Projectile* projectile4 = nullptr;
Projectile* projectile5 = nullptr;
Projectile* projectile6 = nullptr;
Projectile* projectile7 = nullptr;
Projectile* projectile8 = nullptr;
Projectile* projectile9 = nullptr;
Projectile* projectile10 = nullptr;
Projectile* projectile11 = nullptr;
Projectile* projectile12 = nullptr;
Projectile* projectile13 = nullptr;
Projectile* projectile14 = nullptr;
Projectile* projectile15 = nullptr;
Projectile* projectile16 = nullptr;
Projectile* projectile17 = nullptr;
Projectile* projectile18 = nullptr;
Projectile* projectile19 = nullptr;
Projectile* projectile20 = nullptr;


// Vector to hold all walls
// std::vector<Wall*> walls;
std::vector<Entity*> entityList;

// Add player and mob to entity list
entityList.push_back(player);
entityList.push_back(mob1);
entityList.push_back(mob2);
entityList.push_back(mob3);
entityList.push_back(mob4);
entityList.push_back(mob5);
entityList.push_back(mob6);
entityList.push_back(mob7);
entityList.push_back(mob8);
entityList.push_back(mob9);
entityList.push_back(mob10);
entityList.push_back(mob11);
entityList.push_back(mob12);
entityList.push_back(mob13);
entityList.push_back(mob14);
entityList.push_back(mob15);
entityList.push_back(mob16);
entityList.push_back(mob17);
entityList.push_back(mob18);
entityList.push_back(mob19);
entityList.push_back(mob20);

entityList.push_back(wall1);
entityList.push_back(wall2);
entityList.push_back(wall3);
entityList.push_back(wall4);
entityList.push_back(wall5);
entityList.push_back(wall6);
entityList.push_back(wall7);
entityList.push_back(wall8);
entityList.push_back(wall9);
entityList.push_back(wall10);

// // Define wall spacing and boundaries
// const int wallSpacing = 40;


// const int margin = 40;    // Margin from the border
// const int step = 40; 
// // Generate walls surrounding the player
// for (int x = margin; x <= SCREEN_WIDTH - margin; x += step) {
//     if (x > margin + step && x < SCREEN_WIDTH - margin - step) {  // Leave corners empty
//         walls.push_back(new Wall(x, margin, 30));  // Top border
//         walls.push_back(new Wall(x, SCREEN_HEIGHT - margin, 30));  // Bottom border
//     }
// }

// // Place walls along the left and right borders
// for (int y = margin; y <= SCREEN_HEIGHT - margin; y += step) {
//     if (y > margin + step && y < SCREEN_HEIGHT - margin - step) {  // Leave corners empty
//         walls.push_back(new Wall(margin, y, 30));  // Left border
//         walls.push_back(new Wall(SCREEN_WIDTH - margin, y, 30));  // Right border
//     }
// }

// for (Wall* wall : walls) {
//     entityList.push_back(wall);
// }

// Update hitboxes
player->setPosition(player->getXPos(), player->getYPos(), entityList);
mob1->setPosition(mob1->getXPos(), mob1->getYPos(), entityList);
mob2->setPosition(mob2->getXPos(), mob2->getYPos(), entityList);
// for (Wall* wall : walls) {
//     wall->setPosition(wall->getXPos(), wall->getYPos(), entityList);
// }

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
        
        if(mob1){
            if (!projectile1) {  // Check if the projectile was not created yet
                std::cout << "we be spawning projectile" << std::endl;
                projectile1 = new Projectile(200, 80, 6, false, 0, 0);
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

        handleMobProjectile(renderer, mob2, projectile2, player, entityList, 2);
        handleMobProjectile(renderer, mob3, projectile3, player, entityList, 3);
        handleMobProjectile(renderer, mob4, projectile4, player, entityList, 4);
        handleMobProjectile(renderer, mob5, projectile5, player, entityList, 5);
        handleMobProjectile(renderer, mob6, projectile6, player, entityList, 6);
        handleMobProjectile(renderer, mob7, projectile7, player, entityList, 7);
        handleMobProjectile(renderer, mob8, projectile8, player, entityList, 8);
        handleMobProjectile(renderer, mob9, projectile9, player, entityList, 9);
        handleMobProjectile(renderer, mob10, projectile10, player, entityList, 10);
        handleMobProjectile(renderer, mob11, projectile11, player, entityList, 11);
        handleMobProjectile(renderer, mob12, projectile12, player, entityList, 12);
        handleMobProjectile(renderer, mob13, projectile13, player, entityList, 13);
        handleMobProjectile(renderer, mob14, projectile14, player, entityList, 14);
        handleMobProjectile(renderer, mob15, projectile15, player, entityList, 15);
        handleMobProjectile(renderer, mob16, projectile16, player, entityList, 16);
        handleMobProjectile(renderer, mob17, projectile17, player, entityList, 17);
        handleMobProjectile(renderer, mob18, projectile18, player, entityList, 18);
        handleMobProjectile(renderer, mob19, projectile19, player, entityList, 19);
        handleMobProjectile(renderer, mob20, projectile20, player, entityList, 20);
        

        // for (Wall* wall : walls) {
        //     wall->draw(renderer);
        // }

        // wall1->draw(renderer, angle);
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
        if (frameTime < 16) {//do 16 for 60 fps and 33 for 30
            SDL_Delay(16 - frameTime);
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
