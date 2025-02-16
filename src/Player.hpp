
/* Player.hpp */
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"

class Player : public Entity {
public:
    Player(int x, int y, int width);

    
    void draw(SDL_Renderer* renderer, double angle) const;  // Overloaded version
private:
    void collisionLogic(Entity* collidedEntity) override; // Override collision logic
    void draw(SDL_Renderer* renderer) const override;  // Overrides Entity
};

#endif // PLAYER_HPP
