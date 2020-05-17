#pragma once

#include "jezzball/LTexture.hpp"
#include "jezzball/ObjectManager.hpp"
#include "jezzball/Wall.hpp"

#include <memory>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

namespace jezzball
{

class Board
{
public:
    
    Board();
    ~Board() = default;

    bool init();
    void close();
    void gameLoop();
    bool loadMedia();

private:
    //Screen dimension constants
    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    
    void mousePressed(SDL_MouseButtonEvent& b);

    bool isCursorVertical;
    SDL_Cursor* cursor;
    SDL_Window* window;
    SDL_Renderer* renderer;
    LTexture atomTexture;

    std::unique_ptr<ObjectManager> objectManager;

};

} // namespace jezzball

