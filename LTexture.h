

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
    void blit(SDL_Texture* texture, SDL_Renderer* renderer, int x, int y);
    void free();
    void loadFont(std::string textureText, TTF_Font* gFont, SDL_Renderer* renderer, std::string text, int textX, int textY);
    void render(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip);
    void cameraRender(std::string path, SDL_Renderer* renderer, SDL_Rect cameraRect);
private:
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
};
#endif
