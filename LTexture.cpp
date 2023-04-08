#include "LTexture.h"
LTexture::LTexture()
{
    mTexture = nullptr;

    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{

}
void LTexture::loadTexture(std::string path, SDL_Renderer* renderer)
{
    free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
        std::cout << "Unable to load image " << path << " SDL_image Error: "
        << IMG_GetError() << std::endl;
    else {
        newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);
        if (newTexture == NULL)
            std::cout << "Unable to create texture from " << path << " SDL Error: "
            << SDL_GetError() << std::endl;
        SDL_FreeSurface(loadedSurface);
    }
    mTexture = newTexture;
}
void LTexture::free()
{
    if (mTexture != nullptr)
    {
        mTexture = nullptr;
        mWidth = 0;
        mHeight = 0;
    }
}
void LTexture::loadFont(std::string path, TTF_Font* gFont, SDL_Renderer* renderer,
                         std::string text, int x, int y)
{
    free();

    SDL_Rect textRect = {x , y, TEXT_WIDTH, TEXT_HEIGHT};
    SDL_Color textColor = { 255 , 0  , 0 };

    if (gFont == nullptr)
    {
        std::cout << "Could not load font" << std::endl;
        exit(1);
    }
    // Pixels from our text

    SDL_Surface* surfaceText = TTF_RenderText_Solid(gFont, text.c_str(), textColor);

    mTexture = SDL_CreateTextureFromSurface(renderer, surfaceText);

    SDL_FreeSurface(surfaceText);

    SDL_RenderCopy(renderer, mTexture, NULL, &textRect);

    close();
}

void LTexture::render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip)
{
    SDL_Rect renderSpace = { x, y, mWidth, mHeight };

    if (clip != nullptr)
    {
        renderSpace.w = clip->w;
        renderSpace.h = clip->h;
    }
    SDL_RenderCopy(gRenderer, mTexture, NULL, &renderSpace);
}
void LTexture::close()
{
    SDL_DestroyTexture(mTexture);
    mTexture = NULL;
}
