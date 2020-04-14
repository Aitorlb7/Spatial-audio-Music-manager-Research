#ifndef __ENEMY_H__
#define __ENEMY_H__


#include "P2Point.h"
#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy(int x, int y, EntityType type);
	~Enemy();

	void Update(float dt);


public:
	uint level_up_fx = 0u;
	uint trade_fx = 0u;


};

#endif
