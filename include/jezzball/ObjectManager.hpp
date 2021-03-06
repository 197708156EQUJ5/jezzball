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

    ObjectManager(int boardX, int boardY, int boardWidth, int boardHeight, LTexture &lTexture);
    ~ObjectManager() = default;

    void addAtom();
    void addWall(int x, int y, bool isCursorVertical);
    void updateAtoms();
    void updateWalls();
    void render();
    std::vector<Wall> getWalls();
    std::vector<Area> getAreas();

    void splitArea(Wall wall);

private:
    
    void reassignAtoms();
    void calculateCleared();

    int boardX;
    int boardY;
    int boardWidth;
    int boardHeight;
    double boardArea;
    bool isCursorVertical;
    bool isAWallBuilding;
    int areaIndex;
    double percentCleared;
    LTexture lTexture;
    std::vector<Atom> atoms;
    std::vector<Wall> walls;
    std::vector<Area> areas;
};

} // namespace jezzball

