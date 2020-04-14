#include "Player.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Audio.h"
#include "j1Scene.h"
#include "p2Log.h"
#include <math.h>

Player::Player(int x, int y, EntityType type) : Entity(x, y, type) {

	bool ret = true;

	rect = { x,y,20,20 };

}

Player::~Player()
{
}

void Player::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT && rect.y < 750) {
		rect.y += 10;
	/*	App->render->camera.y += 10;*/
	}
	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT && rect.y > 0) {
		rect.y -= 10;
		//App->render->camera.y -= 10;
	}
	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT && rect.x < 1230) {
		rect.x += 10;
		//App->render->camera.x += 10;
	}
	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT && rect.x > 0) {
		rect.x -= 10;
		//App->render->camera.x -= 10;
	}

	position.x = rect.x;
	position.y = rect.y;
}

