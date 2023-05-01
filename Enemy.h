
#pragma once
#ifndef ENEMY_H
#define ENEMY_H
#include "CommonFunc.h"
#include "LTexture.h"
class Enemy : public LTexture
{
public:
	Enemy();
	~Enemy();
	void enemyFollow(int SNAKE_SPEED, int x, int y);
	void enemyLoadTexture(SDL_Renderer* renderer);
	void enemyRender(SDL_Renderer* renderer, SDL_Rect* clip,int frame,
                   double angle, SDL_Point* center, SDL_RendererFlip flip);
	int enemyWidth();
	int enemyHeight();
	int enemyPosX();
	int enemyPosY();
	SDL_Rect enemyRect();
	void Spawn();
	bool CheckCollision(SDL_Rect a, SDL_Rect b);
	void enemySpawn(int randLoc);
	bool enemyHealthCheck(SDL_Rect a, SDL_Rect b);
private:
	SDL_Rect enemy;
	SDL_Rect gSpriteClips[ENEMY_ANIMATION_FRAMES];
	int health;
	bool is_killed;
};


#endif
