#include "Enemy.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"


Enemy::Enemy() : j2Entity(ENTITY_TYPE::ENEMY)
{
}

Enemy::~Enemy()
{
}

bool Enemy::Start()
{
	entity_rect = {62,4,32,57};
	entity_tex = App->tex->Load("textures/sprites.png");
	
	

	return true;
}

bool Enemy::Update(float dt, bool do_logic)
{
	


	return true;
}

bool Enemy::CleanUp()
{
	App->tex->UnLoad(entity_tex);
	return true;
}

void Enemy::Draw()
{
	App->render->Blit(entity_tex, position.x -16, position.y -64, &entity_rect);
}
