#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "j1Timer.h"

class j1Timer;

class Player : public Entity
{
public:

	Player(int x, int y, EntityType type);
	~Player();

	//bool Start();

	void Update(float dt);

	//bool CleanUp();

	//void Draw();

public:
	
};

#endif
