#pragma once

#include "jezzball/Area.hpp"

#include <sstream>
#include <string>
#include <iomanip>

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
        ss << area.index << ": (" << std::setw(3) << x << "," << std::setw(3) << y << ") (" 
            << std::setw(3) << (x + width) << "," << std::setw(3) << (y + height) << ")"
            << " width: " << std::setw(3) << width << " height: " << std::setw(3) << height
            << " isBuilding? " << std::boolalpha << isBuilding 
            << " isVertical? " << isVertical;
        return ss.str();
    }

};

} // namespace jezzball

