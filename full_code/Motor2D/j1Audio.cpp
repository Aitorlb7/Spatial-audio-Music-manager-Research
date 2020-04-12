#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Audio.h"

#include "SDL/include/SDL.h"
#include "SDL_mixer\include\SDL_mixer.h"
#pragma comment( lib, "SDL_mixer/libx86/SDL2_mixer.lib" )

j1Audio::j1Audio() : j1Module()
{
	music = NULL;
	name = "audio";
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

	music_combat = Mix_LoadMUS("audio/combat.ogg");

	//TODO 1: Allocate the number of channels you'll use for the fx's(tip, look at Mix_AllocateChannels from the documentation)
	Mix_AllocateChannels(20);
	
	return ret;
}

// Called before quitting
bool j1Audio::CleanUp()
{
	if(!active)
		return true;

	LOG("Freeing sound FX, closing Mixer and Audio subsystem");

	if(music != NULL)
	{
		Mix_FreeMusic(music);
	}
	if (music_combat != NULL)//CREAR LISTA DE _Mix_Music* y eliminarla entera
	{
		Mix_FreeMusic(music_combat);
	}


	std::list<Mix_Chunk*>::iterator stl_item = stl_fx.begin();
	for (; stl_item != stl_fx.end(); stl_item++)
		Mix_FreeChunk(*stl_item);

	stl_fx.clear();

	Mix_CloseAudio();
	Mix_Quit();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);

	return true;
}

// Play a music file
bool j1Audio::PlayMusic(const char* path, float fade_time)
{
	bool ret = true;

	if(!active)
		return false;

	if(music != NULL)
	{
		if(fade_time > 0.0f)
		{
			Mix_FadeOutMusic(int(fade_time * 1000.0f));
		}
		else
		{
			Mix_HaltMusic();
		}

		// this call blocks until fade out is done
		Mix_FreeMusic(music);
	}

	music = Mix_LoadMUS(path);

	if(music == NULL)
	{
		LOG("Cannot load music %s. Mix_GetError(): %s\n", path, Mix_GetError());
		ret = false;
	}
	else
	{
		if(fade_time > 0.0f)
		{
			if(Mix_FadeInMusic(music, -1, (int) (fade_time * 1000.0f)) < 0)
			{
				LOG("Cannot fade in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
		else
		{
			if(Mix_PlayMusic(music, -1) < 0)
			{
				LOG("Cannot play in music %s. Mix_GetError(): %s", path, Mix_GetError());
				ret = false;
			}
		}
	}

	LOG("Successfully playing %s", path);
	return ret;
}

//TODO 2.1: LOOK AT WHAT IT DOES 
 //Load WAV
unsigned int j1Audio::LoadFx(const char* path)
{
	unsigned int ret = 0;

	if(!active)
		return 0;

	Mix_Chunk* chunk = Mix_LoadWAV(path);
	
	if(chunk == NULL)
	{
		LOG("Cannot load wav %s. Mix_GetError(): %s", path, Mix_GetError());
	}
	else
	{
		
		stl_fx.push_back(chunk);
		ret = stl_fx.size();
	}

	return ret;
}


//TODO 3.1 : WE WANT TO MODIFY PlayFx, WE WILL PASS THEM AN FX ID, A CHANNEL TO PLAY ON, IF IT REPEATS, THE VOLUME AND A Sint16 angle and Uint8 distance
// Play WAV
bool j1Audio::PlayFx(unsigned int id, int channel, int repeat, int volume, Sint16 angle, Uint8 distance)
{
	bool ret = false;

	if(!active)
		return false;
	

	if (id > 0 && id <= stl_fx.size())
	{
		std::list <Mix_Chunk*>::const_iterator it;
		it = std::next(stl_fx.begin(), id - 1);
		//TODO 3.2: WE ADD THE METHODS Mix_VolumeChunk(*it, volume) TO MODIFY THE VOLUME OF THE CHUNK AND WE ALSO ADD Mix_SetPosition(channel, angle, distance);
		Mix_VolumeChunk(*it, volume);
		Mix_SetPosition(channel, angle, distance); 
		Mix_PlayChannel(channel, *it, repeat);
	}

	LOG("PLAYING WAV: %d", id);
	return ret;
}

void j1Audio::PauseMusic()
{
	Mix_PauseMusic();
}

void j1Audio::ResumeMusic()
{
	Mix_ResumeMusic();
}


void j1Audio::MusicPos(double second)
{
	Mix_SetMusicPosition(second);
}

void j1Audio::SetVolume(int channel, int volume)
{
	Mix_Volume(channel, volume);
}



int j1Audio::Channels(int num)
{
	return Mix_AllocateChannels(num);
}

int j1Audio::ChannelsPlaying(int num)
{
	return Mix_Playing(num);
}

void j1Audio::FadeOut(int ms)
{
	Mix_FadeOutMusic(ms);
}

void j1Audio::FadeIn(_Mix_Music* music, int loops, int ms)
{
	Mix_FadeInMusic(music, loops, ms);
}

int j1Audio::Decoders()
{
	return Mix_GetNumMusicDecoders();
	
}

void j1Audio::ChangeTrack()
{
	
	music = music_combat;
}

int j1Audio::StopFx(int channel)
{
	return Mix_HaltChannel(channel);
}

//TODO 3.3 :WE PASS TO SPATIAL: j2Entity* emiter & j2Entity* receiver, this will be the 2 entities that will interact with the sound, an fx, a channel and volume
void j1Audio::Spatial(j2Entity* emiter,j2Entity* receiver, unsigned int fx, int channel, int volume)
{

	//TODO 4.1: WE ARE GOING TO CREATE THE ANGLE AND DISTANCE(USE Sint16 & Uint8), AND 3 AREAS(CLOSE, MEDIUM AND LONG),THIS AREAS SHOULD BE UINT.
	//WE WILL ASIGNATE 250/1000/2000 TO THE AREAS(CLOSE, MEDIUM,LONG) AND WE WILL SET THE ANGLE AND DISTANCE TO 0.

	uint close_area = 250;
	uint medium_area = 1000;
	uint long_area = 2000;
	Sint16 angle = 0;
	Uint8 distance = 0;
	int repeat = 0;

	//TODO 4.2:  THIS ACTS AS A COMPASS TO THE PLAYER, THIS FIRST PACK GETS IF THE PLAYER IS MOVING TOWARDS THE ENEMY ENTITY FROM THE LEFT-LOW DIAGONAL.
	//IF IT IS WE WANT TO CHANGE THE VALUE OF THE ANGLE TO  90deg(the sound will come from the right), A DISTANCE(10/120/230) DEPENDING OF THE AREA
	//AND A VOLUME(128/50/10) DEPENDING OF THE AREA
	//CLOSE AREA-MID AREA-LONG AREA
	if (emiter->position.x - receiver->position.x <= close_area && receiver->position.y - emiter->position.y <= close_area)//diagonal izq-abajo
	{
		angle = 90;
		distance = 10;
		volume = 128;
		
	}
	else if (emiter->position.x - receiver->position.x <= medium_area && receiver->position.y - emiter->position.y <= medium_area)//diagonal izq-abajo
	{
		angle = 90;
		distance = 120;
		volume = 50;
		
	}
	else if (emiter->position.x - receiver->position.x <= long_area && receiver->position.y - emiter->position.y <= long_area)//diagonal izq-abajo
	{
		angle = 90;
		distance = 230;
		volume = 10;
		
	}

	if (receiver->position.x - emiter->position.x <= close_area && receiver->position.y - emiter->position.y <= close_area)//diagonal der-abajo
	{
		angle = 270;
		distance = 10;
		volume = 128;
		
	}
	else if (receiver->position.x - emiter->position.x <= medium_area && receiver->position.y - emiter->position.y <= medium_area)//diagonal der-abajo
	{
		angle = 270;
		distance = 120;
		volume = 50;
	
	}
	else if (receiver->position.x - emiter->position.x <= long_area && receiver->position.y - emiter->position.y <= long_area)//diagonal der-abajo
	{
		angle = 270;
		distance = 230;
		volume = 10;
		
	}

	if (emiter->position.x - receiver->position.x <= close_area && emiter->position.y - receiver->position.y <= close_area)//diagonal izq-arriba
	{
		angle = 90;
		distance = 10;
		volume = 128;
		
	}
	else if (emiter->position.x - receiver->position.x <= medium_area && emiter->position.y - receiver->position.y <= medium_area)//diagonal izq-arriba
	{
		angle = 90;
		distance = 120;
		volume = 50;
		
	}
	else if (emiter->position.x - receiver->position.x <= long_area && emiter->position.y - receiver->position.y <= long_area)//diagonal izq-arriba
	{
		angle = 90;
		distance = 230;
		volume = 10;
		
	}
	////TODO 4.3, SEEING HOW THE OTHER 3 DIAGONALS WORK, TRY TO  FIGURE OUT HOW TO DO THE LAST ONE(DIAGONAL FROM RIGHT TO UPWARDS)

	if (receiver->position.x - emiter->position.x <= close_area && emiter->position.y - receiver->position.y <= close_area)//diagonal der-arriba
	{
		angle = 270;
		distance = 10;
		volume = 128;
		
	}
	else if (receiver->position.x - emiter->position.x <= medium_area && emiter->position.y - receiver->position.y <= medium_area)//diagonal der-arriba
	{
		angle = 270;
		distance = 120;
		volume = 50;
		
	}
	else if (receiver->position.x - emiter->position.x <= long_area && emiter->position.y - receiver->position.y <= long_area)//diagonal der-arriba
	{
		angle = 270;
		distance = 230;
		volume = 10;
		
	}

	
	
	
	
	//TODO 3.4 : WE CALL TO PlayFx()
	PlayFx(fx, channel, repeat, volume, angle, distance);
	
}

int j1Audio::FxPosition(int channel, Sint16 angle, Uint8 distance)
{
	int ret = Mix_SetPosition(channel, angle, distance);
	if (!Mix_SetPosition(channel, angle, distance)) {
		printf("Mix_SetPosition: %s\n",Mix_GetError());
		// no position effect, is it ok?
	}
	return ret;
}