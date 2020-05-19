#pragma once

#include <sstream>
#include <string>

namespace jezzball
{

struct Area
{
    int index;
    int x;
    int y;
    int width;
    int height;
    
    std::string toString()
    {
        std::stringstream ss;
        ss << index << ": (" << x << "," << y << ") (" 
            << (x + width) << "," << (y + height) << ")"
            << " width: " << width << " height: " << height;

        return ss.str();
    }
};

} // namespace jezzball

