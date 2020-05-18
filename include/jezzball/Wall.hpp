#pragma once

#include "jezzball/Area.hpp"

namespace jezzball
{

struct Wall
{
    struct Area area;
    int x;
    int y;
    int width;
    int height;
    bool isBuilding;
    bool isVertical;

    static const int THICKNESS = 14;
};

} // namespace jezzball

