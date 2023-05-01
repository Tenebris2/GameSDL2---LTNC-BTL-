

#pragma once
#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include <SDL.h>
#include <SDL_image.h>
#include <bits/stdc++.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <fstream>
//Screen dimension constants
const int SCALE = 24;
const int wSCALE = 48;
const int SCREEN_WIDTH = 1280; //1152
const int SCREEN_HEIGHT = 720; //1440
const int LEVEL_WIDTH = SCREEN_WIDTH * 2;
const int LEVEL_HEIGHT = SCREEN_HEIGHT * 2;
const int TEXT_RESOLUTION = 30;
const int TEXT_HEIGHT = 30;
const int TEXT_WIDTH = TEXT_HEIGHT * 5;

const int cols = SCREEN_WIDTH / SCALE;
const int rows = SCREEN_HEIGHT / SCALE;

const int SPEED = 2;
const int BULLET_SPEED = 10;
const int ENEMY_SPEED = 1;
const int ENEMY_AMOUNT = 15;
const int ENEMY_HEALTH = 10;
const int ENEMY_ANIMATION_FRAMES = 12;
const int BULLET_ANIMATION_FRAMES = 8;
const int BULLET_SCALE = 48;
const int ANIMATION_TIME = 400;
const int DELAY_TIME = 50;

typedef struct input
{
	int left;
	int right;
	int down;
	int up;
};

#endif
