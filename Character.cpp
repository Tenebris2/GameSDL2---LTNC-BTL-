#include "Character.h"

Character::Character()
{
    input_type.down = 0;
    input_type.up = 0;
    input_type.right = 0;
    input_type.left = 0;
    player.x = SCREEN_WIDTH/2;
    player.y = SCREEN_HEIGHT/2;
    player.w = SCALE;
    player.h = SCALE;
}
Character::~Character(){}
void Character::DoInput(SDL_Event event)
{
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_DOWN)
                {
                    input_type.down = 1;
                    input_type.up = 0;
                    input_type.left = 0;
                    input_type.right = 0;
                }
                else if (event.key.keysym.sym == SDLK_UP)
                {
                    input_type.down = 0;
                    input_type.up = 1;
                    input_type.left = 0;
                    input_type.right = 0;
                }
                else if (event.key.keysym.sym == SDLK_LEFT)
                {
                    input_type.down = 0;
                    input_type.up = 0;
                    input_type.left = 1;
                    input_type.right = 0;
                }
                else if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    input_type.down = 0;
                    input_type.up = 0;
                    input_type.left = 0;
                    input_type.right = 1;
                }
            }
}
void Character::charRender(SDL_Renderer* renderer,SDL_Rect* clip,
                           double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    render(player.x, player.y, renderer,clip, angle, center, flip);
}
void Character::charLoadTexture(std::string path, SDL_Renderer* renderer)
{
    loadTexture(path.c_str(), renderer);
}
void Character::DoPlayer(int SNAKE_SPEED)
{
    if (input_type.up == 1)
    {
        player.y -= SNAKE_SPEED;
    }
    if (input_type.down == 1)
    {
        player.y += SNAKE_SPEED;
    }
    if (input_type.left == 1)
    {
        player.x -= SNAKE_SPEED;
    }
    if (input_type.right == 1)
    {
        player.x += SNAKE_SPEED;
    }

    if (player.x < 0) player.x += SNAKE_SPEED;
    else if (player.x > SCREEN_WIDTH - SCALE) player.x -= SNAKE_SPEED;
    else if (player.y < 0) player.y += SNAKE_SPEED;
    else if (player.y > SCREEN_HEIGHT - SCALE) player.y -= SNAKE_SPEED;
}
int Character::charWidth()
{
    return player.w;
}
int Character::charHeight()
{
    return player.h;
}
int Character::charPosX()
{
    return player.x;
}
int Character::charPosY()
{
    return player.y;
}
SDL_Rect Character::charRect()
{
    return player;
}
void Character::returnSpawn()
{
    player.x = (SCREEN_WIDTH - player.w)/2;
    player.y = (SCREEN_HEIGHT - player.h)/2;
}
