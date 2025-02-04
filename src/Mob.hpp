/* Mob.hpp */
#ifndef MOB_HPP
#define MOB_HPP

#include "Entity.hpp"

class Mob : public Entity {
public:
    Mob(int x, int y, int width);
    void draw(SDL_Renderer* renderer) const override;
};

#endif // MOB_HPP