#include "jezzball/ObjectManager.hpp"

#include "jezzball/Point.hpp"
#include "jezzball/CollisionDirection.hpp"

#include <iostream>
#include <stdlib.h>

namespace jezzball
{

ObjectManager::ObjectManager(uint32_t screenWidth, uint32_t screenHeight, LTexture &lTexture) :
    screenWidth(screenWidth),
    screenHeight(screenHeight),
    lTexture(lTexture),
    atom(nullptr)
{
}

void ObjectManager::addAtom()
{
    int startX = rand() % (this->screenWidth - 40) + 20;
    int startY = rand() % (this->screenHeight - 40) + 20;
    Atom atom{Point{startX, startY}};
    atoms.push_back(atom);
}

void ObjectManager::update()
{
    for (Atom &atom : atoms)
    {
        atom.move();
        Point p = atom.getPoint();
        if (p.x < 2)
        {
            atom.changeDirection(CollisionDirection::WEST);
        }
        else if (p.x > screenWidth - 20)
        {
            atom.changeDirection(CollisionDirection::EAST);
        }
        else if (p.y < 2)
        {
            atom.changeDirection(CollisionDirection::NORTH);
        }
        else if (p.y > screenHeight - 20)
        {
            atom.changeDirection(CollisionDirection::SOUTH);
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

} // namespace jezzball

