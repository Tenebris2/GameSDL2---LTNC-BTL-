#ifndef FOOD_OBJECT_H
#define FOOD_OBJECT_H

#include "CommonFunc.h"
#include "LTexture.h"
class FoodObject : public LTexture
{
public:
    FoodObject();
    ~FoodObject();
    void foodRender(SDL_Renderer* renderer, SDL_Rect* clip,int frame,
                    double angle, SDL_Point* center, SDL_RendererFlip flip);
    void foodLoadTexture(std::string path, SDL_Renderer* renderer);
    void addFood();
    bool foodCheckCollision(SDL_Rect a, SDL_Rect b);
    SDL_Rect foodRect();
private:
    SDL_Rect food;
    SDL_Rect gSpriteClips[FOOD_ANIMATION_FRAMES];
};


#endif // FOOD_OBJECT_H

