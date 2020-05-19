#pragma once

#include "jezzball/Area.hpp"

#include <sstream>
#include <string>

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

    static const int THICKNESS = 10;
    
    std::string toString()
    {
        std::stringstream ss;
        ss << area.index << ": (" << x << "," << y << ") (" 
            << (x + width) << "," << (y + height) << ")"
            << " width: " << width << " height: " << height
            << " isBuilding? " << std::boolalpha << isBuilding 
            << " isVertical? " << isVertical;
        return ss.str();
    }

};

} // namespace jezzball

