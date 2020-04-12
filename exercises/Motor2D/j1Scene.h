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
	
	
	//TODO 2.3: Create the fx that our entities will use(do at least 3) 
	unsigned int fx_player = 0;
	unsigned int fx_do = 0;
	
	
};

#endif // __j1SCENE_H__