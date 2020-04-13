#ifndef __ENEMY_H__
#define __ENEMY_H__


#include "P2Point.h"
#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy(int x, int y, EntityType type);
	~Enemy();

	//bool Start();

	void Update(float dt);

	//bool CleanUp();


public:
	uint death_1 = 0u;
	uint death_2 = 0u;
	uint death_3 = 0u;

};

#endif
