#include "j1App.h"
#include "Entity.h"
#include "j1Render.h"
#include "j1Input.h"
#include "j1Textures.h"

Entity::Entity(int x, int y, EntityType type) : position(x, y), type(type)
{
	W = { 64,33,16,15 };
	WPressed = { 64,131,16,13 };
	A = { 48,49,16,15 };
	APressed = { 48,147,16,13 };
	D = { 80,49,16,15 };
	DPressed = { 80,147,16,13 };
	F = { 96,49,16,15 };
	FPressed = { 96,148,16,13 };
	P = { 192,33,16,15 };
	PPressed = { 192,131,16,13 };
	posA = { 205 -A.w, 200 -A.h };
	posW = { 1025-W.w, 200-W.h };
	posD = { 1025,700 };
	posF = { 1075, 700 };
	posP = { 1125,700 };
	offset = 3;
	keys = App->tex->Load("textures/keys.png");
}

Entity::~Entity()
{
}

void Entity::Draw()
{
	switch (type) {
	case PLAYER:
		SDL_SetRenderDrawColor(App->render->renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(App->render->renderer, &rect);
		break;
	case ENEMY1:
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			App->render->Blit(keys, posA.x, posA.y, &APressed,1.0f,2.0f);
		else
			App->render->Blit(keys, posA.x, posA.y - offset, &A,1.0f, 2.0f);
		break;
	case ENEMY2:
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
			App->render->Blit(keys, posW.x, posW.y, &WPressed, 1.0f, 2.0f);
		else
			App->render->Blit(keys, posW.x, posW.y - offset, &W, 1.0f, 2.0f);

	case ENEMY3:
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			App->render->Blit(keys, posD.x, posD.y, &DPressed, 1.0f, 2.0f);
		else
			App->render->Blit(keys, posD.x, posD.y - offset, &D, 1.0f, 2.0f);

	case ENEMY4:
		if (App->input->GetKey(SDL_SCANCODE_F) == KEY_REPEAT)
			App->render->Blit(keys, posF.x, posF.y, &FPressed, 1.0f, 2.0f);
		else
			App->render->Blit(keys, posF.x, posF.y - offset, &F, 1.0f, 2.0f);

	case ENEMY5:
		if (App->input->GetKey(SDL_SCANCODE_P) == KEY_REPEAT)
			App->render->Blit(keys, posP.x, posP.y, &PPressed, 1.0f, 2.0f);
		else
			App->render->Blit(keys, posP.x, posP.y - offset, &P, 1.0f, 2.0f);

		break;
		break;
	default:
		break;
	}



}