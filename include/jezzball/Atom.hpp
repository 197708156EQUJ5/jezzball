#pragma once

#include "jezzball/Direction.hpp"
#include "jezzball/CollisionDirection.hpp"
#include "jezzball/Point.hpp"

#include <cstdint>

namespace jezzball
{

class Atom
{
public:
    
    Atom(Point point);
    ~Atom() = default;

    void move();
    Direction getDirection();
    void changeDirection(CollisionDirection collisionDirection);
    Point getPoint();
    int getAreaIndex();
    void setAreaIndex(int areaIndex);

    static const uint32_t RADIUS = 20;
    
private:

    Direction direction;
    Point point;
    int areaIndex;
};

} // namespace jezzball

