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
    //Atom(const Atom &other) = delete;
    //Atom(Atom &&other) = delete;
    //Atom& operator=(const Atom &other) = delete;
    //Atom& operator=(Atom &other) = delete;

    void move();
    Direction getDirection();
    void changeDirection(CollisionDirection collisionDirection);
    Point getPoint();

private:

    static const uint32_t WIDTH = 20;
    static const uint32_t HEIGHT = 20;

    Direction direction;
    Point point;
};

} // namespace jezzball

