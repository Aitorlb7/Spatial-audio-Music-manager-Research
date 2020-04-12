#ifndef __J2ENTITYMANAGER_H__
#define __J2ENTITYMANAGER_H__

#include "j1Module.h"
#include "p2Point.h"
#include "PugiXml\src\pugixml.hpp"
#include <list>
#include "j1Audio.h"

class j2Entity;
enum class ENTITY_TYPE;
struct Mix_Chunk;

typedef int16_t Sint16;
typedef uint8_t Uint8;

class j2EntityManager : public j1Module
{
public:

	//Constructor
	j2EntityManager();
	//Destructor
	virtual ~j2EntityManager();

	// Awake: Called before render is available
	bool Awake(pugi::xml_node& config);

	//Start
	bool Start();
	//PreUpdate
	bool PreUpdate();
	//Update
	bool Update(float dt);

	//PostUpdate
	bool PostUpdate();

	bool CleanUp();

	//Load
	bool Load(pugi::xml_node&);
	//Save
	bool Save(pugi::xml_node&) const;

public:
	j2Entity* j1Player = nullptr;
	j2Entity* enemy1 = nullptr;

	j2Entity* CreateEntity(j2Entity* entity, ENTITY_TYPE type, iPoint position, unsigned int fx, const char* fx_path, int channel, int repeat, int volume, Sint16 angle, Uint8 distance);
	void DestroyEntity(j2Entity* entity_to_destroy);
	iPoint GetPos(j2Entity* entity);

	// Return a const list of all entities
	const std::list<j2Entity*> GetEntitiesInfo() const;


private:

	void SetLastEntityPos(int x, int y);

private:

	std::list<j2Entity*> entities;

	bool	do_logic;
	int		logic_updates_per_second;
	float	update_ms_cycle;
	float   accumulated_time;

};
#endif
