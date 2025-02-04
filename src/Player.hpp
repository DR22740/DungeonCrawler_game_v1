
/* Player.hpp */
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "Entity.hpp"

class Player : public Entity {
public:
    Player(int x, int y);
    void draw(SDL_Renderer* renderer, double angle) const override;
};

#endif // PLAYER_HPP
