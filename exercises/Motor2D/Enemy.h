#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "j2Entity.h"

class Enemy : public j2Entity
{
public:
	Enemy();
	~Enemy();

	bool Start();

	bool Update(float dt, bool do_logic);

	bool CleanUp();

	void Draw();

};

#endif
