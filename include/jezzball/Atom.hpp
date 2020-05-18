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

private:

    static const uint32_t WIDTH = 20;
    static const uint32_t HEIGHT = 20;

    Direction direction;
    Point point;
    int areaIndex;
};

} // namespace jezzball

