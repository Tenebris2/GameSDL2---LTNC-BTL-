

#include "CommonFunc.h"
#ifndef LTEXTURE_H
#define LTEXTURE_H
class LTexture
{
public:
    //Initializes variables
    LTexture();
    //Deallocates memory
    ~LTexture();
    void loadTexture(std::string path, SDL_Renderer* renderer);
    void free();
    void loadFont(std::string textureText, TTF_Font* gFont, SDL_Renderer* renderer, std::string text, int x, int y);
    void render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip);
    void cameraRender(std::string path, SDL_Renderer* renderer, SDL_Rect cameraRect);
    void close();
private:
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
};
#endif
