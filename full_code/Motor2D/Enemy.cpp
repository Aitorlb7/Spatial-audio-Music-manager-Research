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

	//rect = { x,y,50,50 };

	level_up_fx = App->audio->LoadFx("audio/fx/Level_Up.wav");
	trade_fx = App->audio->LoadFx("audio/fx/Trade.wav");

}
Enemy::~Enemy()
{
	LOG("Freeing the enemy");
	App->audio->UnLoadFx(level_up_fx);
	App->audio->UnLoadFx(trade_fx);
}

void Enemy::Update(float dt)
{
	if ((App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN ) && this->type == ENEMY1)
		App->audio->PlaySpatialFx(level_up_fx, App->audio->GetAngle(App->entities->GetPlayer()->position, this->position), App->audio->GetDistance(App->entities->GetPlayer()->position, this->position));

	if ((App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN ) && this->type == ENEMY2)
		App->audio->PlaySpatialFx(trade_fx, App->audio->GetAngle(App->entities->GetPlayer()->position, this->position), App->audio->GetDistance(App->entities->GetPlayer()->position, this->position));


}