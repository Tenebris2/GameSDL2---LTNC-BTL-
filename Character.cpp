#include "Character.h"

Character::Character()
{
    input_type.down = 0;
    input_type.up = 0;
    input_type.right = 0;
    input_type.left = 0;
    player.x = SCREEN_WIDTH/2;
    player.y = SCREEN_HEIGHT/2;
    player.w = PLAYER_HIT_BOX;
    player.h = PLAYER_HIT_BOX;
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
void Character::charRender(SDL_Renderer* renderer,SDL_Rect* clip,int frame,
                           double angle, SDL_Point* center, SDL_RendererFlip flip, bool bDir)
{
     //Render current frame
    SDL_Rect* currentClip = &gSpriteClips[frame/PLAYER_ANIMATION_FRAMES];

    if (input_type.right == 1 || bDir == true) render(player.x,player.y,renderer,currentClip,angle,center,SDL_FLIP_NONE);
    else render(player.x,player.y,renderer,currentClip,angle,center,SDL_FLIP_HORIZONTAL);
}
void Character::charLoadTexture(std::string path, SDL_Renderer* renderer)
{
    loadTexture(path,renderer);

    //Set sprite clips
    for (int i = 0; i < PLAYER_ANIMATION_FRAMES; i++)
    {
        gSpriteClips[i].x = SCALE*2*i;
        gSpriteClips[i].y = 0;
        gSpriteClips[i].w = SCALE*2;
        gSpriteClips[i].h = SCALE*2;
    }
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
    else if (player.x > SCREEN_WIDTH - SCALE*2) player.x -= SNAKE_SPEED;
    else if (player.y < 0) player.y += SNAKE_SPEED;
    else if (player.y > SCREEN_HEIGHT - SCALE*2) player.y -= SNAKE_SPEED;
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
