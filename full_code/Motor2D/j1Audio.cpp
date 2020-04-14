#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Audio.h"
#include "j1Input.h"
#include <math.h>
#include <time.h>

#include "SDL/include/SDL.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

j1Audio::j1Audio() : j1Module()
{
	//music = NULL;
	name.create("audio");
}


// Destructor
j1Audio::~j1Audio()
{}

// Called before render is available
bool j1Audio::Awake(pugi::xml_node& config)
{
	LOG("Loading Audio Mixer");
	bool ret = true;
	SDL_Init(0);
	srand(time(NULL));
	if(SDL_InitSubSystem(SDL_INIT_AUDIO) < 0)
	{
		LOG("SDL_INIT_AUDIO could not initialize! SDL_Error: %s\n", SDL_GetError());
		active = false;
		ret = true;
	}

	// load support for the JPG and PNG image formats
	int flags = MIX_INIT_OGG;
	int init = Mix_Init(flags);

	if((init & flags) != flags)
	{
		LOG("Could not initialize Mixer lib. Mix_Init: %s", Mix_GetError());
		active = false;
		ret = true;
	}

	//Initialize SDL_mixer
	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		LOG("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		active = false;
		ret = true;
	}

	Mix_AllocateChannels(360);										// Allocate the channels we will use 

	volume = config.child("music").attribute("volume").as_int();	// Load the volume from XML

	scale = config.child("distance").attribute("scale").as_int();	// Load the distance scale if you want to change it

	Mix_VolumeMusic(volume);
	Mix_Volume(-1, volume);
	
	return ret;
}
bool j1Audio::Update(float dt)
{
	if (!active)
		return true;

	if (App->input->GetKey(SDL_SCANCODE_KP_PLUS) == KEY_DOWN)	// Increase volume
	{
		Mix_VolumeMusic(Mix_VolumeMusic(-1) + 10);
		Mix_Volume(-1, Mix_Volume(-1, -1) + 10);

		volume = Mix_VolumeMusic(-1);
	}

	if (App->input->GetKey(SDL_SCANCODE_KP_MINUS) == KEY_DOWN)	// Decrease volume
	{
		if (Mix_VolumeMusic(-1) <= 8)
			Mix_VolumeMusic(0);
		else
			Mix_VolumeMusic(Mix_VolumeMusic(-1) - 10);

		if (Mix_Volume(-1, -1) <= 8)
			Mix_Volume(-1, 0);
		else
			Mix_Volume(-1, Mix_Volume(-1, -1) - 10);

		volume = Mix_VolumeMusic(-1);
	}

	return true;
}
// Called before quitting
bool j1Audio::CleanUp()
{
	if(!active)
		return true;

	LOG("Freeing sound FX, closing Mixer and Audio subsystem");

	std::list<Mix_Music*>::iterator stl_item = music.begin(); //Release music list
	for (; stl_item != music.end(); stl_item++)
	{
		Mix_FreeMusic(*stl_item);
	}

	std::list<Mix_Chunk*>::iterator stl_item2 = fx.begin(); //Release fx list
	for (; stl_item2 != fx.end(); stl_item2++)
	{
		Mix_FreeChunk(*stl_item2);
	}

	fx.clear();

	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);

	return true;
}

unsigned int j1Audio::LoadMusic(const char* path) // Loads the audio on the Mix_Music* 
{
	unsigned int ret = 0;

	if (!active)
		return 0;

	Mix_Music* chunk = Mix_LoadMUS(path);

	if (chunk == NULL)
	{
		LOG("Cannot load wav %s. Mix_GetError(): %s", path, Mix_GetError());
	}
	else
	{

		music.push_back(chunk);
		ret = music.size();
	}

	return ret;
}

// Play a music file
bool j1Audio::PlayMusic(unsigned int id, float fade_time)
{
	bool ret = true;

	if(!active)
		return false;

	if (id > 0 && id <= music.size())
	{
		std::list <Mix_Music*>::const_iterator it;
		it = std::next(music.begin(), id - 1);
		if (*it != NULL)
		{
			if (fade_time > 0.0f)
			{
				Mix_FadeOutMusic(int(fade_time * 1000.0f));
			}
			else
			{
				Mix_HaltMusic();
			}
		}
		if (fade_time > 0.0f)
		{
			Mix_FadeInMusic(*it, -1, (int)(fade_time * 1000.0f));
		}
		
	}

	return ret;
}

void j1Audio::PauseMusic(float fade_time)
{
	if (active)
	{
		if (Mix_PlayingMusic() == 1)	// Sees if there is music playing
		{
			if (Mix_PausedMusic() == 1)	// If there is resume it
			{
				Mix_ResumeMusic();
			}
			else
			{
				Mix_PauseMusic();
			}
		}
	}
}
 //Load WAV
unsigned int j1Audio::LoadFx(const char* path)
{
	unsigned int ret = 0;

	if (!active)
		return 0;

	Mix_Chunk* chunk = Mix_LoadWAV(path);

	if (chunk == NULL)
	{
		LOG("Cannot load wav %s. Mix_GetError(): %s", path, Mix_GetError());
	}
	else
	{

		fx.push_back(chunk);
		ret = fx.size();
	}

	return ret;
}

// Play WAV
bool j1Audio::PlayFx(unsigned int id, int repeat)
{
	bool ret = false;

	if (!active)
		return false;


	if (id > 0 && id <= fx.size())
	{
		std::list <Mix_Chunk*>::const_iterator it;
		it = std::next(fx.begin(), id - 1);
		Mix_PlayChannel(-1, *it, repeat);//put channel , if -1 gets the next free channel available
	}

	LOG("PLAYING WAV: %d", id);
	return ret;
}

// UnLoad WAV
bool j1Audio::UnLoadFx(uint id)
{
	if (!active)
		return true;

	bool ret = false;

	Mix_Chunk* chunk = NULL;

	if (id > 0 && id <= fx.size())
	{
		std::list <Mix_Chunk*>::const_iterator it;
		it = std::next(fx.begin(), id - 1);
		chunk = *it;
	}
	if (chunk != nullptr)
	{
		Mix_FreeChunk(chunk);
		chunk = nullptr;
		ret = true;
	}

	return ret;
}

bool j1Audio::PlaySpatialFx(uint id, uint channel_angle, uint distance,int repeat)
{
	bool ret = false;

	if (!active)
		return false;

	Mix_Chunk* chunk = NULL;

	if (id > 0 && id <= fx.size())
	{
		std::list <Mix_Chunk*>::const_iterator it;
		it = std::next(fx.begin(), id - 1);
		chunk = *it;
	}
	if (chunk != nullptr)
	{
		while (Mix_Playing(channel_angle) == 1)	// If the channel is already playing, choose the next channel that we already allocated with Mix_AllocateChannels()
		{
			channel_angle++;

			if (channel_angle > 360)
				channel_angle = 0;
		}
		// Play the channel that we already placed with Mix_SetPosition()
		Mix_SetPosition(channel_angle, channel_angle, distance);	// Set a channel in a position given a channel, an angle and a distance

		Mix_PlayChannel(channel_angle, chunk, repeat);				// Play the channel that we already placed with Mix_SetPosition()

		ret = true;
	}

	return ret;
}

uint j1Audio::GetAngle(iPoint player_pos, iPoint enemy_pos)
{
	iPoint vector_pos = player_pos - enemy_pos;				// The vector of the player and enemy positions
	iPoint vector_axis = { 0, 1 };							// We use the this vector because we want the angle that is formed with the Y axis

	double dot_x = vector_axis.y * vector_pos.y;			// Product of the two vectors to get the X position
	double det_y = -(vector_axis.y * vector_pos.x);			// Determinant of the two vectors to get the Y position

	float f_angle = (atan2(det_y, dot_x)) * RAD_TO_DEG;		// Arc tangent of the previous X and Y, multiply the result with RAD_TO_DEG to get the result in degrees instead of radiants

	if (f_angle < 0)										// If the angle is negative we add +360 because in PlaySpatialFx() we need the channel to be positive
		f_angle += 360;

	return uint(f_angle);
}

uint j1Audio::GetDistance(iPoint player_pos, iPoint enemy_pos)
{
	uint distance = sqrt(pow(player_pos.x - enemy_pos.x, 2) + pow(player_pos.y - enemy_pos.y, 2));	// Calculate the distance with Pythagoras

	uint distance_scaled = (distance * MAX_DISTANCE) / scale;										// We can scale the maximum hear distance by modifying scale in the config XML

	if (distance_scaled > MAX_DISTANCE)																// If the distance is greater than the MAX_DISTANCE(255), keep it in 255
		distance_scaled = MAX_DISTANCE;

	return distance_scaled;
}
