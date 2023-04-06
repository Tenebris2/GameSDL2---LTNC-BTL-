
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
	void enemyLoadTexture(std::string path, SDL_Renderer* renderer);
	void enemyRender(SDL_Renderer* renderer, SDL_Rect* clip);
	int enemyWidth();
	int enemyHeight();
	int enemyPosX();
	int enemyPosY();
	SDL_Rect enemyRect();
	void Spawn();
	bool CheckCollision(SDL_Rect a, SDL_Rect b);
	void enemyDelete(int randLoc);
	void enemyHealthCheck(SDL_Rect a, SDL_Rect b, int randLoc);
private:
	SDL_Rect enemy;
	int health;
};


#endif
