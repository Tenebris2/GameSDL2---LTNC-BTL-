
#include "Enemy.h"

Enemy::Enemy()
{
    enemy.x = 0;
    enemy.y = 0;
    enemy.w = SCALE;
    enemy.h = SCALE;
    health = ENEMY_HEALTH;
}
Enemy::~Enemy()
{

}
void Enemy::enemyFollow(int SNAKE_SPEED, int x, int y)
{
    if (y > enemy.y)
    {
        enemy.y += SNAKE_SPEED ;
    }
    if (y < enemy.y)
    {
        enemy.y -= SNAKE_SPEED ;
    }
    if (x > enemy.x)
    {
        enemy.x += SNAKE_SPEED ;
    }
    if (x < enemy.x)
    {
        enemy.x -= SNAKE_SPEED ;
    }
}
void Enemy::enemyRender(SDL_Renderer* renderer,SDL_Rect* clip,int frame,
                        double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    //Render current frame
    SDL_Rect* currentClip = &gSpriteClips[frame/ENEMY_ANIMATION_FRAMES];

    render(enemy.x,enemy.y,renderer,currentClip,angle,center,flip);
}
void Enemy::enemyLoadTexture(SDL_Renderer* renderer)
{
    loadTexture("img/enemy-sprite.png",renderer);

    //Set sprite clips
    for (int i = 0; i < ENEMY_ANIMATION_FRAMES; i++)
    {
        gSpriteClips[i].x = SCALE*2*i;
        gSpriteClips[i].y = 0;
        gSpriteClips[i].w = SCALE*2;
        gSpriteClips[i].h = SCALE*2;
    }
}
bool Enemy::CheckCollision(SDL_Rect a, SDL_Rect b)
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
int Enemy::enemyWidth()
{
    return enemy.w;
}
int Enemy::enemyHeight()
{
    return enemy.h;
}
int Enemy::enemyPosX()
{
    return enemy.x;
}
int Enemy::enemyPosY()
{
    return enemy.y;
}
SDL_Rect Enemy::enemyRect()
{
    return enemy;
}
void Enemy::enemySpawn(int randLoc)
{
    int x = rand() % (SCREEN_WIDTH)+SCREEN_WIDTH;
    int y = rand() % (SCREEN_HEIGHT)+SCREEN_HEIGHT;

    if (randLoc == 1)
    {
        x = rand() % (SCREEN_WIDTH)+SCREEN_WIDTH;
        y = rand() % (SCREEN_HEIGHT)+SCREEN_HEIGHT;
    }
    if (randLoc == 2)
    {
        x = rand() % (SCREEN_WIDTH)-SCREEN_WIDTH;
        y = rand() % (SCREEN_HEIGHT)+SCREEN_HEIGHT;
    }
    if (randLoc == 3)
    {
        x = rand() % (SCREEN_WIDTH)+SCREEN_WIDTH;
        y = rand() % (SCREEN_HEIGHT)-SCREEN_HEIGHT;
    }
    if (randLoc == 4)
    {
        x = rand() % (SCREEN_WIDTH)-SCREEN_WIDTH;
        y = rand() % (SCREEN_HEIGHT)-SCREEN_HEIGHT;
    }
    enemy.x = x;
    enemy.y = y;
}
bool Enemy::enemyHealthCheck(SDL_Rect a, SDL_Rect b)
{
    if (CheckCollision(a,b)) health--;
    if (health == 0)
    {
        is_killed = true;
    }
    return is_killed;
}
