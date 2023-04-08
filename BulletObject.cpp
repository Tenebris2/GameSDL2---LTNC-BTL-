#include "BulletObject.h"


BulletObject::BulletObject()
{
	bullet.x = SCREEN_WIDTH + SCALE;
	bullet.y = SCREEN_HEIGHT + SCALE;
	bullet.w = 16;
	bullet.h = 16;
	left_m = false;
	bulletDir.up = false;
	bulletDir.down = false;
	bulletDir.left = false;
	bulletDir.right = false;
    health = 0;
}

BulletObject::~BulletObject()
{

}

void BulletObject::bulletRender(SDL_Renderer* renderer)
{
	render(bullet.x, bullet.y, renderer, &bullet);
}
void BulletObject::Fire(SDL_Event event, int x, int y)
{
    if (event.type == SDL_KEYDOWN)
    {
        if (event.key.keysym.sym == SDLK_s and health == 0)
        {
            bulletDir.down = 1;
            bulletDir.up = 0;
            bulletDir.left = 0;
            bulletDir.right = 0;
            bullet.x = x;
            bullet.y = y;
            health = 1;
        }
        else if (event.key.keysym.sym == SDLK_w and health == 0)
        {
            bulletDir.down = 0;
            bulletDir.up = 1;
            bulletDir.left = 0;
            bulletDir.right = 0;
            bullet.x = x;
            bullet.y = y;
            health = 1;
        }
        else if (event.key.keysym.sym == SDLK_a and health == 0)
        {
            bulletDir.down = 0;
            bulletDir.up = 0;
            bulletDir.left = 1;
            bulletDir.right = 0;
            bullet.x = x;
            bullet.y = y;
            health = 1;
        }
        else if (event.key.keysym.sym == SDLK_d and health == 0)
        {
            bulletDir.down = 0;
            bulletDir.up = 0;
            bulletDir.left = 0;
            bulletDir.right = 1;
            bullet.x = x;
            bullet.y = y;
            health = 1;
        }
    }
}
void BulletObject::bulletMove()
{
    if (bulletDir.up == 1)
    {
        bullet.y -= BULLET_SPEED;
    }
    if (bulletDir.down == 1)
    {
        bullet.y += BULLET_SPEED;
    }
    if (bulletDir.left == 1)
    {
        bullet.x -= BULLET_SPEED;
    }
    if (bulletDir.right == 1)
    {
        bullet.x += BULLET_SPEED;
    }

    if (bullet.x < 0 || bullet.x > SCREEN_WIDTH) health = 0;
    if (bullet.y < 0 || bullet.y > SCREEN_HEIGHT) health = 0;
   // if (bulletCheckCollision) health = 0;
}
void BulletObject::bulletLoadTexture(std::string path, SDL_Renderer* renderer)
{
	loadTexture(path.c_str(), renderer);
}
SDL_Rect BulletObject::bulletRect()
{
    return bullet;
}
void BulletObject::bulletCheckCollision(SDL_Rect a, SDL_Rect b)
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
        health = 0;
    }

    if (topA >= bottomB)
    {
        health = 0;
    }

    if (rightA <= leftB)
    {
        health = 0;
    }

    if (leftA >= rightB)
    {
        health = 0;
    }
    //If none of the sides from A are outside B
}
