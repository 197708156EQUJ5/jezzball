#include "jezzball/Atom.hpp"

#include <iostream>

namespace jezzball
{

Atom::Atom(Point point) : 
    direction(Direction::SOUTH_EAST), 
    point(point),
    areaIndex(0)
{
}

Point Atom::getPoint()
{
    return point;
}

int Atom::getAreaIndex()
{
    return areaIndex;
}

void Atom::setAreaIndex(int areaIndex)
{
    this->areaIndex = areaIndex;
}

void Atom::move()
{
    switch (this->direction)
    {
        case Direction::NORTH_EAST:
            this->point.x++;
            this->point.y--;
            break;
        case Direction::SOUTH_EAST:
            this->point.x++;
            this->point.y++;
            break;
        case Direction::NORTH_WEST:
            this->point.x--;
            this->point.y--;
            break;
        case Direction::SOUTH_WEST:
            this->point.x--;
            this->point.y++;
            break;
    }
}

void Atom::changeDirection(CollisionDirection collisionDirection)
{
    switch (collisionDirection)
    {
        case CollisionDirection::NORTH:
           if (this->direction == Direction::NORTH_EAST)
           {
               this->direction = Direction::SOUTH_EAST;
           }
           else if (this->direction == Direction::NORTH_WEST)
           {
               this->direction = Direction::SOUTH_WEST;
           }
           break;
        case CollisionDirection::EAST:
           if (this->direction == Direction::NORTH_EAST)
           {
               this->direction = Direction::NORTH_WEST;
           }
           else if (this->direction == Direction::SOUTH_EAST)
           {
               this->direction = Direction::SOUTH_WEST;
           }
           break;
        case CollisionDirection::SOUTH:
           if (this->direction == Direction::SOUTH_EAST)
           {
               this->direction = Direction::NORTH_EAST;
           }
           else if (this->direction == Direction::SOUTH_WEST)
           {
               this->direction = Direction::NORTH_WEST;
           }
           break;
        case CollisionDirection::WEST:
           if (this->direction == Direction::NORTH_WEST)
           {
               this->direction = Direction::NORTH_EAST;
           }
           else if (this->direction == Direction::SOUTH_WEST)
           {
               this->direction = Direction::SOUTH_EAST;
           }
           break;
    }
}

Direction Atom::getDirection()
{
    return this->direction;
}

} // namespace jezzball

