#ifndef __j1AUDIO_H__
#define __j1AUDIO_H__

#include "j1Module.h"
#include "p2Point.h"
#include "SDL_mixer\include\SDL_mixer.h"
#include<list>
#include<string>

#define DEFAULT_MUSIC_FADE_TIME 3.0f
#define MAX_FX 500						// The maximum number of fx
#define RAD_TO_DEG 57.32f				// The result of 180 / 3.14 for pass radiants to degrees
#define MAX_DISTANCE 255				// The maximum distance where you can listen


struct _Mix_Music;
struct Mix_Chunk;


//enum FxPack
//{
//	LEVEL = 0,
//	TRADE,
//
//	NONE
//};
class j1Audio : public j1Module
{
public:
	//Constructor
	j1Audio();

	// Destructor
	virtual ~j1Audio();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before quitting
	bool CleanUp();

	// Play a music file
	bool PlayMusic(const char* path, float fade_time = DEFAULT_MUSIC_FADE_TIME);

	// Pause the music
	void PauseMusic(float fade_time = DEFAULT_MUSIC_FADE_TIME);

	// Load a WAV in memory
	unsigned int LoadFx(const char* path);

	// Play a previously loaded WAV
	bool PlayFx(unsigned int fx, int repeat = 0);

	// UnLoad WAV
	bool UnLoadFx(uint id);

	// Play a WAV like a 3D audio reciving an fx, a channel and an angle (in our case is the same because the reserved Channels on Mix_AllocateChannels()),
	// a distance, a pack of fx and how many times you want to repeat it
	bool PlaySpatialFx(uint id, uint channel_angle = 1, uint distance = 1,int repeat = 0);

	// Get the angle of the Y axis with the position of the enemy regard the player position
	uint GetAngle(iPoint player_pos, iPoint enemy_pos);

	// Get the distance with the position of the player and the enemy
	uint GetDistance(iPoint player_pos, iPoint enemy_pos);


	
private:

	_Mix_Music* music = NULL;
	std::list<Mix_Chunk*> fx;

public:

	int				volume = 0;
	int				scale = 0;

};

#endif // __j1AUDIO_H__