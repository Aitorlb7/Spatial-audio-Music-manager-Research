#ifndef __ENTITY_H__
#define __ENTITY_H__
#include "SDL/include/SDL.h"
#include "P2Point.h"
#include "j1Entities.h"

class Entity
{
protected:

	bool key_entities_speed = false;

public:
	Entity(int x, int y, EntityType type);
	virtual ~Entity();

	virtual void Update(float dt) {};
	virtual void Draw();
	virtual void SetEntitiesSpeed(float dt) {};

public:
	SDL_Rect W, WPressed, A, APressed, D, DPressed, F, FPressed, P, PPressed;
	iPoint posA, posD, posW, posF , posP;
	SDL_Texture* keys;
	int offset;

	iPoint position = iPoint(0, 0);
	EntityType type = EntityType::NO_TYPE;
	int number = 0;
	bool to_destroy = false;
	SDL_Rect rect = { 0,0,0,0 };
};

#endif // __ENTITY_H__