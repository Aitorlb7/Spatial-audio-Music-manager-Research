#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "j2Entity.h"
#include "j1Timer.h"

class j1Timer;

class Player : public j2Entity
{
public:
	Player();
	~Player();

	bool Start();

	bool Update(float dt, bool do_logic);

	bool CleanUp();

	void Draw();

public:
	j1Timer timer;
	bool clock = false;
	
	
	
};

#endif
