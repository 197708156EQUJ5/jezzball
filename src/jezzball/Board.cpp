#include "jezzball/Board.hpp"

#include "jezzball/Atom.hpp"
#include "jezzball/Point.hpp"
#include "jezzball/CollisionDirection.hpp"

#include <iostream>

namespace jezzball
{

Board::Board() :
    isCursorVertical(true),
    cursor(nullptr),
    window(nullptr),
    renderer(nullptr)
{
}

bool Board::init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;;
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            std::cout << "Warning: Linear texture filtering not enabled!" << std::endl;;
        }

        //Create window
        window = SDL_CreateWindow("Jezzball", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, 
                SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            std::cout << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;;
            success = false;
        }
        else
        {
            //Create vsynced renderer for window
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (renderer == NULL)
            {
                std::cout << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;;
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    std::cout << "SDL_image could not initialize! SDL_image Error: " << IMG_GetError() << std::endl;;
                    success = false;
                }
            }
            cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENS);
            SDL_SetCursor(cursor);
        }
    }
    
    atomTexture.setRenderer(renderer);

    if (!loadMedia())
    {
        success = false;
    }

    return success;    
}

void Board::gameLoop()
{
    bool quit = false;
    SDL_Event e;

    this->objectManager = std::make_unique<ObjectManager>(SCREEN_WIDTH, SCREEN_HEIGHT, atomTexture);
    this->objectManager->addAtom();
    this->objectManager->addAtom();

    while(!quit)
    {
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        
        //Handle events on queue
        while(SDL_PollEvent(&e) != 0)
        {
            //User requests quit
            switch (e.type)
            {
                case SDL_QUIT:
                {
                    quit = true;
                    break;
                }
                case SDL_MOUSEBUTTONUP:
                {
                    mousePressed(e.button);
                    break;
                }
            }
        }
        
        this->objectManager->update();
        
        for (Wall wall : this->objectManager->getWalls())
        {
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
            SDL_Rect wallRect;
            wallRect.x = wall.x;
            wallRect.y = wall.y;
            wallRect.w = wall.width;
            wallRect.h = wall.height;

            SDL_RenderDrawRect(renderer, &wallRect);
        }

        this->objectManager->render();

        //Update screen
        SDL_RenderPresent(renderer);
    }
}

bool Board::loadMedia()
{
    //Loading success flag
    bool success = true;

    //Load dot texture
    if(!atomTexture.loadFromFile("resources/red_dot_20x20.png"))
    {
        std::cout << "Failed to load dot texture!" << std::endl;
        success = false;
    }

    return success;
}

void Board::mousePressed(SDL_MouseButtonEvent& b)
{
    if (b.button == SDL_BUTTON_LEFT)
    {
        //SDL_Log("Left button clicked! loc: %d, %d", b.x, b.y);
        this->objectManager->addWall(b.x, b.y, isCursorVertical);
    }
    else if (b.button == SDL_BUTTON_RIGHT)
    {
        if (cursor != nullptr)
        {
            SDL_FreeCursor(cursor);
        }
        if (this->isCursorVertical)
        {
            cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEWE);
            SDL_SetCursor(cursor);
            this->isCursorVertical = false;
        }
        else
        {
            cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZENS);
            SDL_SetCursor(cursor);
            this->isCursorVertical = true;
        }
    }
}

void Board::close()
{
    //Free loaded images
    atomTexture.free();

    //Destroy window    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
}

} // namespace jezzball

