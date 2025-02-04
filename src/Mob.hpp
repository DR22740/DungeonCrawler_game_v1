/* Mob.hpp */
#ifndef MOB_HPP
#define MOB_HPP

#include "Entity.hpp"

class Mob : public Entity {
public:
    Mob(int x, int y);
    void draw(SDL_Renderer* renderer, double angle) const override;
};

#endif // MOB_HPP