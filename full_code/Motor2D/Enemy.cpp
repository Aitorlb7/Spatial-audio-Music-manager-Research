#include "P2Defs.h"
#include "P2Log.h"
#include "Enemy.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Entities.h"
#include "j1Timer.h"
#include "Enemy.h"
#include "Player.h"
#include "j1Input.h"


Enemy::Enemy(int x, int y, EntityType type) : Entity(x, y, type) {

	bool ret = true;

	rect = { x,y,50,50 };

	death_1 = App->audio->LoadFx("audio/fx/death_1.wav", DEATH);
	death_2 = App->audio->LoadFx("audio/fx/death_2.wav", DEATH);
	death_3 = App->audio->LoadFx("audio/fx/death_3.wav", DEATH);
}
Enemy::~Enemy()
{
	LOG("Freeing the enemy");
	App->audio->UnLoadFx(death_1, DEATH);
	App->audio->UnLoadFx(death_2, DEATH);
	App->audio->UnLoadFx(death_3, DEATH);
}

void Enemy::Update(float dt)
{
	if ((App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_KP_1) == KEY_DOWN) && this->type == ENEMY1)
		App->audio->PlaySpatialFx(App->audio->ChooseFx(DEATH), App->audio->GetAngle(App->entities->GetPlayer()->position, this->position), App->audio->GetDistance(App->entities->GetPlayer()->position, this->position), DEATH);

	if ((App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_KP_2) == KEY_DOWN) && this->type == ENEMY2)
		App->audio->PlaySpatialFx(App->audio->ChooseFx(DEATH), App->audio->GetAngle(App->entities->GetPlayer()->position, this->position), App->audio->GetDistance(App->entities->GetPlayer()->position, this->position), DEATH);

	if ((App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN || App->input->GetKey(SDL_SCANCODE_KP_3) == KEY_DOWN) && this->type == ENEMY3)
		App->audio->PlaySpatialFx(App->audio->ChooseFx(DEATH), App->audio->GetAngle(App->entities->GetPlayer()->position, this->position), App->audio->GetDistance(App->entities->GetPlayer()->position, this->position), DEATH);
}