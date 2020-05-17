#pragma once

#include "jezzball/Atom.hpp"
#include "jezzball/LTexture.hpp"

#include <vector>
#include <memory>

namespace jezzball
{

class ObjectManager
{
public:

    ObjectManager(uint32_t screenWidth, uint32_t screenHeight, LTexture &lTexture);
    ~ObjectManager() = default;

    void addAtom();
    void update();
    void render();

private:

    uint32_t screenWidth;
    uint32_t screenHeight;
    LTexture lTexture;
    std::vector<Atom> atoms;
    std::shared_ptr<Atom> atom;
};

} // namespace jezzball

