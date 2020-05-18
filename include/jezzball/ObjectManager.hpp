#pragma once

#include "jezzball/Atom.hpp"
#include "jezzball/Area.hpp"
#include "jezzball/LTexture.hpp"
#include "jezzball/Wall.hpp"

#include <vector>
#include <memory>

namespace jezzball
{

class ObjectManager
{
public:

    ObjectManager(int screenWidth, int screenHeight, LTexture &lTexture);
    ~ObjectManager() = default;

    void addAtom();
    void addWall(int x, int y, bool isCursorVertical);
    void update();
    void render();
    std::vector<Wall> getWalls();
    void splitArea(Wall wall);

private:
    
    void reassignAtoms();

    int screenWidth;
    int screenHeight;
    bool isCursorVertical;
    bool isAWallBuilding;
    int areaIndex;
    LTexture lTexture;
    std::vector<Atom> atoms;
    std::vector<Wall> walls;
    std::vector<Area> areas;
};

} // namespace jezzball

