
#ifndef BULLET_OBJECT_H
#define BULLET_OBJECT_H
#include "LTexture.h"
#include "Character.h"
class BulletObject : public LTexture
{
public:
	BulletObject();
	~BulletObject();
	void bulletRender(SDL_Renderer* renderer, SDL_Rect* clip,int startTime,
 double angle, SDL_Point* center);
	void bulletMove();
	void Fire(SDL_Event event, int x, int y);
	void bulletLoadTexture(SDL_Renderer* renderer);
	SDL_Rect bulletRect();
	void bulletReload();
	void bulletCheckCollision(SDL_Rect a, SDL_Rect b);
private:
	SDL_Rect bullet;
    SDL_Rect gSpriteClips[ENEMY_ANIMATION_FRAMES];
	bool left_m;
	input bulletDir;
	int health;
};
#endif
