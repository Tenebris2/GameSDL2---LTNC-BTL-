#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H
#include "CommonFunc.h"
#include "LTexture.h"
class Character : public LTexture
{
public:
	Character();
	~Character();
	void charRender(SDL_Renderer* renderer, SDL_Rect* clip);
	void charLoadTexture(std::string path, SDL_Renderer* renderer);
	void DoInput(SDL_Event event);
	void DoPlayer(int SNAKE_SPEED);
	int charWidth();
	int charHeight();
	int charPosX();
	int charPosY();
	SDL_Rect charRect();
private:
	input input_type;
	SDL_Rect player;
};


#endif
