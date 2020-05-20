#pragma once

#include <sstream>
#include <string>
#include <iomanip>

namespace jezzball
{

struct Area
{
    int index;
    int x;
    int y;
    int width;
    int height;
    bool isEmpty = false;
    
    std::string toString()
    {
        std::stringstream ss;
        ss << index << ": (" << std::setw(3) << x << "," << std::setw(3) << y << ") (" 
            << std::setw(3) << (x + width) << "," << std::setw(3) << (y + height) << ")"
            << " width: " << std::setw(3) << width << " height: " << std::setw(3) << height;

        return ss.str();
    }
};

} // namespace jezzball

