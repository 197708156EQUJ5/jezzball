#include "jezzball/ObjectManager.hpp"

#include "jezzball/Point.hpp"
#include "jezzball/CollisionDirection.hpp"

#include <iostream>
#include <stdlib.h>

namespace jezzball
{

ObjectManager::ObjectManager(int screenWidth, int screenHeight, LTexture &lTexture) :
    screenWidth(screenWidth),
    screenHeight(screenHeight),
    isCursorVertical(true),
    isAWallBuilding(false),
    lTexture(lTexture)
{
    this->areas.push_back(Area{0, 2, 2, screenWidth, screenHeight});
}

void ObjectManager::addAtom()
{
    int startX = rand() % (this->screenWidth - 40) + 20;
    int startY = rand() % (this->screenHeight - 40) + 20;
    Atom atom{Point{startX, startY}};
    atoms.push_back(atom);
}

void ObjectManager::addWall(int x, int y, bool isCursorVertical)
{
    if (!isAWallBuilding)
    {
        Wall wall{x - 10, y - 10, 20, 20, true, isCursorVertical};
        walls.push_back(wall);
        isAWallBuilding = true;
    }
}

void ObjectManager::update()
{
    for (Atom &atom : atoms)
    {
        atom.move();
        Point p = atom.getPoint();
        for (Area area : this->areas)
        {
            if (atom.getAreaIndex() == area.index)
            {
                if (p.x < area.x)
                {
                    atom.changeDirection(CollisionDirection::WEST);
                }
                else if (p.x + 20 > area.width)
                {
                    atom.changeDirection(CollisionDirection::EAST);
                }
                else if (p.y < area.y)
                {
                    atom.changeDirection(CollisionDirection::NORTH);
                }
                else if (p.y + 20 > area.height)
                {
                    atom.changeDirection(CollisionDirection::SOUTH);
                }
            }
        }
    }

    for (Wall &wall : walls)
    {
        if (wall.isBuilding)
        {
            if (wall.isVertical)
            {
                if (wall.height == this->screenHeight)
                {
                    isAWallBuilding = false;
                    wall.isBuilding = false;
                    break;
                }
                if (wall.y > 0)
                {
                    wall.y -= 1;
                }
                if (wall.y + wall.height > this->screenHeight - 2)
                {
                    wall.y -= 1;
                }
                wall.height += 2;
            }
            else
            {
                if (wall.width == this->screenWidth)
                {
                    isAWallBuilding = false;
                    wall.isBuilding = false;
                    break;
                }
                if (wall.x > 0)
                {
                    wall.x -= 1;
                }
                if (wall.x + wall.width > this->screenWidth - 2)
                {
                    wall.x -= 1;
                }
                wall.width += 2;
            }
        }
    }
}

void ObjectManager::render()
{
    for (Atom &atom : atoms)
    {
        Point p = atom.getPoint();
        lTexture.render(p.x, p.y);
    }
}

std::vector<Wall> ObjectManager::getWalls()
{
    return walls;
}

} // namespace jezzball

