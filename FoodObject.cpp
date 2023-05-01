
#include "FoodObject.h"
FoodObject::FoodObject()
{
    food.x = 0;
    food.y = 0;
    food.w = SCALE;
    food.h = SCALE;
}
FoodObject::~FoodObject()
{

}
void FoodObject::foodRender(SDL_Renderer* renderer, SDL_Rect* clip,
                             double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    render(food.x,food.y,renderer,clip, angle, center, flip);
}
void FoodObject::foodLoadTexture(std::string path,SDL_Renderer* renderer)
{
    loadTexture(path.c_str(),renderer);
}
void FoodObject::addFood()
{
    int x = 0;
    int y = 0;
    x = rand() % cols * SCALE;
    y = rand() % rows * SCALE;
    food.x = x;
    food.y = y;
}
bool FoodObject::foodCheckCollision(SDL_Rect a, SDL_Rect b)
{
        //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if (bottomA <= topB)
    {
        return false;
    }

    if (topA >= bottomB)
    {
        return false;
    }

    if (rightA <= leftB)
    {
        return false;
    }

    if (leftA >= rightB)
    {
        return false;
    }
    return true;
    //If none of the sides from A are outside B
}
SDL_Rect FoodObject::foodRect()
{
    return food;
}
