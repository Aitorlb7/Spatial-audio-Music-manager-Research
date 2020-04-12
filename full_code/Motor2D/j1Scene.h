#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"


struct SDL_Texture;
class j2Entity;

class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool debug = true; 
	bool encounter = false;
	
	

private:
	SDL_Texture* debug_tex;

	

	

public:
	//TODO 2.2: Create the entities(you can start with the player(P1) and 2 enemies
	j2Entity* P1 = nullptr;
	j2Entity* DO = nullptr;
	j2Entity* RE = nullptr;
	j2Entity* MI = nullptr;
	j2Entity* FA = nullptr;
	j2Entity* SOL = nullptr;
	j2Entity* LA = nullptr;
	j2Entity* SI = nullptr;
	j2Entity* DO2 = nullptr;
	j2Entity* TEST = nullptr;
	
	//TODO 2.3: Create the fx that our entities will use(do at least 3)
	unsigned int fx_player = 0;
	unsigned int fx_test_spatial = 0;
	unsigned int fx_do = 0;
	unsigned int fx_re = 0;
	unsigned int fx_mi = 0;
	unsigned int fx_fa = 0; 
	unsigned int fx_sol = 0;
	unsigned int fx_la = 0;
	unsigned int fx_si = 0; 
	unsigned int fx_do2 = 0;
	
};

#endif // __j1SCENE_H__