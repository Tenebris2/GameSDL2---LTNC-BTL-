#ifndef BUTTON_H
#define BUTTON_H

#include "LTexture.h"
#include "CommonFunc.h"

class Button : public LTexture
{
public:
    void buttonRender(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip);
    void buttonLoadTexture();
    bool IsInside();
};
#endif // BUTTON_H
