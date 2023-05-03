#include "BulletObject.h"


BulletObject::BulletObject()
{
	bullet.x = SCREEN_WIDTH + SCALE;
	bullet.y = SCREEN_HEIGHT + SCALE;
	bullet.w = 16;
	bullet.h = 16;
	left_m = 0;
	bulletDir.up = false;
	bulletDir.down = false;
	bulletDir.left = false;
	bulletDir.right = false;
    health = 0;
}

BulletObject::~BulletObject()
{

}

void BulletObject::bulletRender(SDL_Renderer* renderer, SDL_Rect* clip,int startTime,
                                 double angle, SDL_Point* center)
{
    SDL_RendererFlip flip;
    if (bulletDir.right == 1)
    {
        flip = SDL_FLIP_NONE;
        angle = 0;
    }
    else if (bulletDir.left == 1)
    {
        flip = SDL_FLIP_HORIZONTAL;
        angle = 0;
    }
    else if(bulletDir.down == 1)
    {
        flip = SDL_FLIP_VERTICAL;
        angle = 90;
    }
    else if(bulletDir.up == 1)
    {
        flip = SDL_FLIP_VERTICAL;
        angle = -90;
    }
    int frameToDraw = ((SDL_GetTicks() - startTime) * BULLET_ANIMATION_FRAMES / ANIMATION_TIME) % BULLET_ANIMATION_FRAMES;
    //Render current frame
    SDL_Rect* currentClip = &gSpriteClips[frameToDraw];

	render(bullet.x, bullet.y, renderer, currentClip,angle, center, flip);
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
            bullet.y = y - SCALE/2;
            health = 1;
        }
        else if (event.key.keysym.sym == SDLK_w and health == 0)
        {
            bulletDir.down = 0;
            bulletDir.up = 1;
            bulletDir.left = 0;
            bulletDir.right = 0;
            bullet.x = x;
            bullet.y = y - SCALE/2;
            health = 1;
        }
        else if (event.key.keysym.sym == SDLK_a and health == 0)
        {
            bulletDir.down = 0;
            bulletDir.up = 0;
            bulletDir.left = 1;
            bulletDir.right = 0;
            bullet.x = x - SCALE/2;
            bullet.y = y;
            health = 1;
        }
        else if (event.key.keysym.sym == SDLK_d and health == 0)
        {
            bulletDir.down = 0;
            bulletDir.up = 0;
            bulletDir.left = 0;
            bulletDir.right = 1;
            bullet.x = x - SCALE/2;
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
void BulletObject::bulletLoadTexture(SDL_Renderer* renderer)
{
	loadTexture("img/HolyVFX.png", renderer);
    //Set sprite clips
    for (int i = 0; i < BULLET_ANIMATION_FRAMES; i++)
    {
        gSpriteClips[i].x = BULLET_SCALE*i;
        gSpriteClips[i].y = 0;
        gSpriteClips[i].w = BULLET_SCALE;
        gSpriteClips[i].h = BULLET_SCALE;
    }
}
void BulletObject::bulletReload()
{
    health = 0;
}
SDL_Rect BulletObject::bulletRect()
{
    return bullet;
}
bool BulletObject::getDir(){ return bulletDir.right;}
;
