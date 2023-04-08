

#pragma once
#ifndef COMMON_FUNCTION_H
#define COMMON_FUNCTION_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <ctime>
#include <utility>
#include <SDL_ttf.h>
//Screen dimension constants
const int SCALE = 24;
const int wSCALE = 48;
const int SCREEN_WIDTH = 1280; //1152
const int SCREEN_HEIGHT = 720; //1440
const int DOT_VEL = 10;
const int TEXT_RESOLUTION = 30;
const int TEXT_HEIGHT = 30;
const int TEXT_WIDTH = TEXT_HEIGHT * 5;

const int cols = SCREEN_WIDTH / SCALE;
const int rows = SCREEN_HEIGHT / SCALE;

const int SPEED = 2;
const int BULLET_SPEED = 10;
const int ENEMY_SPEED = 1;
const int ENEMY_AMOUNT = 25;
const int ENEMY_HEALTH = 10;

typedef struct input
{
	int left;
	int right;
	int down;
	int up;
};

#endif
