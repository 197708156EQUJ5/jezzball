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
    areaIndex(0),
    lTexture(lTexture)
{
    this->areas.push_back(Area{areaIndex, 0, 0, screenWidth, screenHeight});
}

void ObjectManager::addAtom()
{
    int startX = rand() % (this->screenWidth - 40) + Atom::RADIUS;
    int startY = rand() % (this->screenHeight - 40) + Atom::RADIUS;
    Atom atom{Point{startX, startY}};
    atoms.push_back(atom);
}

void ObjectManager::addWall(int x, int y, bool isCursorVertical)
{
    std::cout << "addWall: " << x << ", " << y << std::endl;
    if (!isAWallBuilding)
    {
        Area wallArea;
        for (Area area : this->areas)
        {
            std::cout << "area: " << area.toString() << std::endl;
            if (x >= area.x && y >= area.y && x <= (area.x + area.width) && y <= (area.y + area.height))
            {
                wallArea = area;
            }
        }
        Wall wall{wallArea, x - (Wall::THICKNESS / 2), y - (Wall::THICKNESS / 2), Wall::THICKNESS, 
            Wall::THICKNESS, true, isCursorVertical};
        std::cout << "new wall: " << wall.toString() <<std::endl;
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
                if (p.x == area.x)
                {
                    atom.changeDirection(CollisionDirection::WEST);
                }
                else if (p.x + Atom::RADIUS == area.x + area.width)
                {
                    atom.changeDirection(CollisionDirection::EAST);
                }
                else if (p.y == area.y)
                {
                    atom.changeDirection(CollisionDirection::NORTH);
                }
                else if (p.y + Atom::RADIUS == area.y + area.height)
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
                if (wall.height >= wall.area.height)
                {
                    isAWallBuilding = false;
                    wall.isBuilding = false;
                    wall.height = wall.area.height;
                    splitArea(wall);
                    reassignAtoms();
                    break;
                }
                if (wall.y > 0)
                {
                    wall.y -= 1;
                }
                if (wall.y + wall.height > wall.area.height)
                {
                    wall.y -= 1;
                }
                wall.height += 2;

                //std::cout << wall.toString() << std::endl;
            }
            else
            {
                if (wall.width >= wall.area.width)
                {
                    isAWallBuilding = false;
                    wall.isBuilding = false;
                    wall.width = wall.area.width;
                    splitArea(wall);
                    reassignAtoms();
                    break;
                }
                if (wall.x > 0)
                {
                    wall.x -= 1;
                }
                if (wall.x + wall.width > wall.area.width)
                {
                    wall.x -= 1;
                }
                wall.width += 2;
                //std::cout << wall.toString() << std::endl;
            }
        }
    }
}

//bool ObjectManager::isWallFinished(int wallAspect, )
//{

//}

void ObjectManager::splitArea(Wall wall)
{
    std::cout << "splitArea()" << std::endl;
    int index = -1;
    std::cout << "wall: " << wall.toString() << std::endl;
    Area splitArea;
    for (Area area : this->areas)
    {
        std::cout << "area: " << area.toString() << std::endl;
        if (wall.x >= area.x && wall.y >= area.y && (wall.height == area.height || wall.width == area.width))
        {
            std::cout << "wall is inside area" << std::endl;
            index = area.index;
            splitArea = area;
            break;
        }
        index++;
    }
    std::cout << "splitArea: " << splitArea.toString() << std::endl;

    this->areas.erase(this->areas.begin() + index);

    if (wall.isVertical)
    {
        this->areas.push_back(Area{index, splitArea.x, splitArea.y, 
                wall.x - splitArea.x, splitArea.height});
        areaIndex++;
        this->areas.push_back(Area{areaIndex, wall.x + wall.width, splitArea.y, 
                splitArea.width - (wall.x + wall.width), splitArea.height});
    }
    else
    {
        this->areas.push_back(Area{index, splitArea.x, splitArea.y,
                splitArea.width, wall.y - splitArea.y});
        areaIndex++;
        this->areas.push_back(Area{areaIndex, wall.x, wall.y + wall.height,
                splitArea.width, splitArea.height - (wall.y + wall.height)});
    }
    
    std::cout << "All Areas" << std::endl;
    for (Area area : this->areas)
    {
        std::cout << "areas " << area.toString() << std::endl;
    }

    std::cout << std::endl;
}

void ObjectManager::reassignAtoms()
{
    //std::cout << "reassignAtoms" << std::endl;
    for (Atom &atom : atoms)
    {
        Point p = atom.getPoint();
        //std::cout << "Atom [old]: " << atom.getAreaIndex() << ": " << p.x << ", " << p.y << std::endl;
        for (Area area : this->areas)
        {
            //std::cout << "Area: " << area.index << ": " << area.x << ", " << area.y << " " << 
            //    (area.x + area.width) << "x" << (area.y + area.height) << //std::endl;
            if (p.x >= area.x && p.y >= area.y && p.x <= (area.x + area.width) && p.y <= (area.y + area.height))
            {
                atom.setAreaIndex(area.index);
                //std::cout << "Atom [new]: " << atom.getAreaIndex() << ": " << p.x << ", " << p.y << std::endl;
            }
        }
    }
    //std::cout << std::endl;
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

std::vector<Area> ObjectManager::getAreas()
{
    return areas;
}

} // namespace jezzball

