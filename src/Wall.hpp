/* Wall.hpp */
#ifndef WALL_HPP
#define WALL_HPP

#include "Entity.hpp"

class Wall : public Entity {
public:
    Wall(int x, int y, int width);
    void draw(SDL_Renderer* renderer) const override;
};

#endif // WALL_HPP