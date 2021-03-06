#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Scene.h"
#include "j1Entities.h"


j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{

	
	App->entities->SpawnEntity(205, 200, ENEMY1);
	App->entities->SpawnEntity(1025,200, ENEMY2);
	App->entities->SpawnEntity(1025, 700, ENEMY3);
	App->entities->SpawnEntity(600, 600, PLAYER);

	
	opening_music = App->audio->LoadMusic("audio/music/Opening.ogg");
	battle_music = App->audio->LoadMusic("audio/music/Battle.ogg");
	App->audio->PlayMusic(opening_music);

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{	
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	App->render->DrawCircle(205, 200, App->audio->scale, 255, 0, 0, 255);
	App->render->DrawCircle(1025, 200, App->audio->scale, 0, 255, 0, 255);

	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN) {
		App->audio->PauseMusic();
	}

	if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN))
		App->audio->PlayMusic(battle_music);
	if ((App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN))
		App->audio->PlayMusic(opening_music);
	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;
	
	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}
