
/* Player.hpp */
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"

class Player : public Entity {
public:
    Player(int x, int y);

    void draw(SDL_Renderer* renderer) const override;  // Overrides Entity
    void draw(SDL_Renderer* renderer, double angle) const;  // Overloaded version
};

#endif // PLAYER_HPP
