#include "jezzball/LTexture.hpp"

#include <iostream>

namespace jezzball
{

LTexture::LTexture() :
    texture(NULL),
    mWidth(0),
    mHeight(0)
{
}

LTexture::~LTexture()
{
    //Deallocate
    free();
}

bool LTexture::setRenderer(SDL_Renderer* renderer)
{
    this->renderer = renderer;
}

bool LTexture::loadFromFile(std::string path)
{
    //Get rid of preexisting texture
    free();

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if(loadedSurface == NULL)
    {
        std::cout << "Unable to load image " << path.c_str() << "! SDL_image Error: " << IMG_GetError() << std::endl;;
    }
    else
    {
        //Color key image
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if(newTexture == NULL)
        {
            std::cout << "Unable to crete texture from " << path.c_str() << "! SDL Error: " << SDL_GetError() << std::endl;;
        }
        else
        {
            //Get image dimensions
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }

        //Get rid of old loaded surface
        SDL_FreeSurface(loadedSurface);
    }

    //Return success
    this->texture = newTexture;
    return this->texture != NULL;
}

#if defined(_SDL_TTF_H) || defined(SDL_TTF_H)
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
    //Get rid of preexisting texture
    free();

    //Render text surface
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
    if(textSurface != NULL)
    {
        //Create texture from surface pixels
        this->texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if(this->texture == NULL)
        {
            std::cout << "Unable to create texture from rendered text! SDL Error: " << SDL_GetError() << std::endl;;
        }
        else
        {
            //Get image dimensions
            mWidth = textSurface->w;
            mHeight = textSurface->h;
        }

        //Get rid of old surface
        SDL_FreeSurface(textSurface);
    }
    else
    {
        std::cout << "Unable to render text surface! SDL_ttf Error: " << TTF_GetError() << std::endl;;
    }

    
    //Return success
    return this->texture != NULL;
}
#endif

void LTexture::free()
{
    //Free texture if it exists
    if(this->texture != NULL)
    {
        SDL_DestroyTexture(this->texture);
        this->texture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    //Modulate texture rgb
    SDL_SetTextureColorMod(this->texture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
    //Set blending function
    SDL_SetTextureBlendMode(this->texture, blending);
}
        
void LTexture::setAlpha(Uint8 alpha)
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod(this->texture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    //Set rendering space and render to screen
    SDL_Rect renderQuad = { x, y, mWidth, mHeight };

    //Set clip rendering dimensions
    if(clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    //Render to screen
    SDL_RenderCopyEx(renderer, this->texture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
    return mWidth;
}

int LTexture::getHeight()
{
    return mHeight;
}

} // namespace jezzball
