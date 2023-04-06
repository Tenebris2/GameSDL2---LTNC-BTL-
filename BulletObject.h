
#ifndef BULLET_OBJECT_H
#define BULLET_OBJECT_H
#include "LTexture.h"
#include "Character.h"
class BulletObject : public LTexture
{
public:
	BulletObject();
	~BulletObject();
	void bulletRender(SDL_Renderer* renderer);
	void bulletMove();
	void Fire(SDL_Event event, int x, int y);
	void bulletLoadTexture(std::string path, SDL_Renderer* renderer);
	SDL_Rect bulletRect();
	void bulletCheckCollision(SDL_Rect a, SDL_Rect b);
private:
	SDL_Rect bullet;
	bool left_m;
	input bulletDir;
	int health;
};
#endif
