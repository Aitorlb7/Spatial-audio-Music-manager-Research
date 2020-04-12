#ifndef __j1AUDIO_H__
#define __j1AUDIO_H__

#include "j1Module.h"
#include "j2Entity.h"
#include<list>
#include<string>

#define DEFAULT_MUSIC_FADE_TIME 2.0f
#define DEFAULT_FX_VOLUME 100

struct _Mix_Music;
struct Mix_Chunk;
class j2Entity;

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

	// Load a WAV in memory
	unsigned int LoadFx(const char* path);


	// Play a previously loaded WAV
	bool PlayFx(unsigned int fx, int channel, int repeat, int volume, Sint16 angle, Uint8 distance);

	//TESTING FUNCTIONS FOR RESEARCH
	void PauseMusic();
	void ResumeMusic();
	void MusicPos(double second);
	void FadeOut(int ms);
	void FadeIn(_Mix_Music* music, int loops, int ms);
	void SetVolume(int channel, int volume);
	int Channels(int num);
	int ChannelsPlaying(int num);
	int Decoders();
	void ChangeTrack();
	int StopFx(int channel);

	
	void Spatial(j2Entity* emiter, j2Entity* receiver, unsigned int fx, int channel,  int volume); 
	int FxPosition(int channel, Sint16 angle, Uint8 distance);

	_Mix_Music*			music_combat = NULL;
	
private:
	
	_Mix_Music*			music = NULL;
	std::list<Mix_Chunk*> stl_fx;
};

#endif // __j1AUDIO_H__