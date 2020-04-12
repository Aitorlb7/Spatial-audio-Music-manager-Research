# AUDIO MANAGER & SPATIAL AUDIO RESEARCH

Hi, i'm <a href="https://www.linkedin.com/in/oscar-larios-088270185/">Oscar Larios</a>, student of the [Bachelor’s Degree in Video Games by UPC at CITM](https://www.citm.upc.edu/ing/estudis/graus-videojocs/ "Link to the Degree"). This content is generated for the second year’s subject Project 2, under supervision of lecturer <a href="https://www.linkedin.com/in/ricardpillosu/">Ricard Pillosu</a>


## A little bit of history

  Sound has become a very important theme in the world of the videogames nowadays, it's inexplicable for us to play to a game and to not   have some type of music or fx's. But this hasn't always been the case.
  If we look a few years ago, more exactly in the 70's, when Pong was released as an arcade videogame, it already had some fx's to show   when the players collided with the ball or when the ball collided with the walls, but it was just a change of the pitch in the "beep"   sound. This small fx already creates the sensation of different actions(padding the ball, collisding with the wall or scoring)
  
  Later in the 80's with the NES in the market, the sound in videogames improved, but the size memeory that 1 NES game had as an      
  average(384kb) didn't left music composers too much space for work, so most of the sound in that time were simple(4 tracks per game)   
  and it was simple and basic computer sounding waveforms.
  Nowadays it's totally different, we can create a videogame with lots of cool fx's and music without catching our fingers with some 
  memory issues

## Audio Manager & Spatial Audio, what are they?

### Audio Manager

  An Audio Manager is a tool/part of the code of our videogame, that let's us create, manipulate or erase Music and Fx's in a game.
  In our case, we will be using j1Audio.h and j1Audio.cpp files to do so.
### Spatial Sound

  <a href="https://www.youtube.com/watch?v=WYdIidUIbAs">Spatial Sound</a> is a sound effect that allows us the player/listener 
  to recognize the space, direction of the sound and distance between us and that sound while listening to it. Some people   
  call it the 3d sound effect. Nowadays is a really common sound effect in the videogames, as we can see in fps games this is key for     example, to figure out the position of the enemy player.
  
   <p align="center"><img src="https://github.com/Megaoski/Audio_Manager-Spatial_Sound-Research/blob/master/docs/images/apex.jpg"></p>
   
  A good example is Apex Legends, in this fps we can hear from where position the enemy is shooting us, or from which way he is walking.
  This feature allows the players to train that sound accuracy to figure out faster and more effectively from which direction he will     face an unseen enemy.
  
   <p align="center"><img src="https://github.com/Megaoski/Audio_Manager-Spatial_Sound-Research/blob/master/docs/images/vr.png"></p>
   
  Vr games also need the Spatial Audio sound effect to simulate the sound for the player
  
## How to manage it?
  In this research we will see how we can manage this spatial sound effect for our games, using the well known SDL_Mixer library.
  Check the <a href="https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_frame.html">doc</a>
    
    
### SDL_Mixer
  SDL_Mixer is an audio library that belongs to SDL(SimpleDirectMediaLayer) and that is open source software. Its very easy to use and     has some good functionalities, but to achieve spatial sound effect it gets a little bit short. If after the exercise you're interested   in how to achieve better spatial sound effects, i encourage you to inform about OpenAL by Creative Labs.
### Core concepts & functions
  <ul>
  <li><strong>_Mix_Music*:</strong> This is an opaque data type used for Music data. We will use it to store our music files</li> 
    <li><strong>Mix_Chunk*:</strong>  The internal format for an audio chunk. This structure is what we will use to store our fx's</li> 
    <li><strong>PlayMusic():</strong> Play the loaded music loop times through from start to finish. The previous music will be halted, or if fading out     it waits (blocking) for that to finish.</li>
    <li><strong>LoadFx():</strong> Returns: a pointer to the sample as a Mix_Chunk. NULL is returned on errors. We can load WAV files , but we can also       use Mix_LoadWAV_RW() to call other formats like vorbis</li>
    <li><strong>StopFx(): </strong>We call  Mix_HaltChannel(), this receives a channel and stops it. If -1 stops all channels</li>
    <li><strong>Mix_SetPosition():</strong> This effect emulates a simple 3D audio effect. It’s not all that realistic, but it can help
    improve some level of realism. By giving it the angle and distance from the camera’s point
    of view, the effect pans and attenuates volumes.</li> 
    <li><strong>Mix_PlayChannel():</strong> Play chunk on channel, or if channel is -1, pick the first free unreserved channel. The sample
    will play for loops +1 number of times</li> 
    <li><strong>Mix_VolumeChunk():</strong> This function receives a chunk and puts that chunk channel volume to the new indicated</li> 
    <li><strong>PlayFx():</strong>This function uses Mix_PlayChannel to play an fx, it will be one of the functions we will modify during the   
     exercise</li>
  </ul>
  
## Exercise

Now that we have reviewed the functions and concepts we will use, we can start with the exercise. The exercise will consist in inplementing a function(Spatial) that will relate 2 entities(emitter and receiver) and a fx. This fx will be assignated to the emitter, and the receiver(Player) will hear it different from a different direction or distance.

### TODO 1

 In the first TODO we will allocate as much channels as we desire. Keep in mind this channels will be used for the exercise, so    
 create at least 5(also don't create 1000!)
     
### TODO 2

 In this TODO, we will see what LoadFx does, also we will create the entities that will interact with our future Spatial function  
 * TODO 2.1 
   Look at LoadFx and see how it works, understand the fact that you're doing push_backs of the fx into our list stl_fx
 * TODO 2.2
   Declare the entities(you can start with the player(P1) and 2 enemies
 * TODO 2.3 
   Create the fx that our entities will use(do at least 3) 
 * TODO 2.4 
   Create the number of entities you want(start with 2)
 * TODO 2.5
   Load all the fx you want to use(remember one per entity)
   
   
### TODO 3
  
     
  * TODO 3.1 
  We have to modify PlayFx to work with angle and distance and simulate spatial sound
  * TODO 3.2 
  We add the Mix_VolumeChunk and Mix_SetPosition
 * TODO 3.3
  We pass to Spatial(): j2Entity* emiter & j2Entity* receiver, this will be the 2 entities that will interact with the sound,     an fx, a channel and volume 
 * TODO 3.4 
We call to PlayFx() 
    
    
### TODO 4
  
  * TODO 4.1 We are going to create some areas for our entities to react, and create an angle(Sint16) and a distance(Uint8)
   * TODO 4.2 We try to understand how the function works with the Diagonals and entities positions
   * TODO 4.3 Now is our turn to add the parameters in the last Diagonal case 
    
    
### TODO 5
   In this last TODO, we just need to call Spatial function and pass it two entities and a fx from the emitter(previous TODO'S)
      
      
## TODO Solutions
 
#### TODO 1
  
   <p align="center"><img src="https://github.com/Megaoski/Audio_Manager-Spatial_Sound-Research/blob/master/docs/images/1.PNG"></p>
  
#### TODO 2.2
  
   <p align="center"><img src="https://github.com/Megaoski/Audio_Manager-Spatial_Sound-Research/blob/master/docs/images/2.2.PNG"></p>
  
#### TODO 2.3
  
  <p align="center"><img src="https://github.com/Megaoski/Audio_Manager-Spatial_Sound-Research/blob/master/docs/images/2.3.PNG"></p>
  
#### TODO 2.4
  
 <p align="center"><img src="https://github.com/Megaoski/Audio_Manager-Spatial_Sound-Research/blob/master/docs/images/2.4.PNG"></p>
  
#### TODO 2.5
  
  <p align="center"><img src="https://github.com/Megaoski/Audio_Manager-Spatial_Sound-Research/blob/master/docs/images/2.5.PNG"></p>
  
#### TODO 3.1
  
 <p align="center"><img src="https://github.com/Megaoski/Audio_Manager-Spatial_Sound-Research/blob/master/docs/images/3.1.PNG"></p>
  
#### TODO 3.2
  
  <p align="center"><img src="https://github.com/Megaoski/Audio_Manager-Spatial_Sound-Research/blob/master/docs/images/3.2.PNG"></p>
  
#### TODO 3.3
 
  <p align="center"><img src="https://github.com/Megaoski/Audio_Manager-Spatial_Sound-Research/blob/master/docs/images/3.3.PNG"></p>
  
#### TODO 3.4
  
  <p align="center"><img src="https://github.com/Megaoski/Audio_Manager-Spatial_Sound-Research/blob/master/docs/images/3.4.PNG"></p>
  
#### TODO 4.1
  
<p align="center"><img src="https://github.com/Megaoski/Audio_Manager-Spatial_Sound-Research/blob/master/docs/images/4.1.PNG"></p>
  
#### TODO 4.3
  
  <p align="center"><img src="https://github.com/Megaoski/Audio_Manager-Spatial_Sound-Research/blob/master/docs/images/4.3.PNG"></p>
  
#### TODO 5
  
  <p align="center"><img src="https://github.com/Megaoski/Audio_Manager-Spatial_Sound-Research/blob/master/docs/images/5.PNG"></p>
   
    
## SOURCES
   
   * <a href="https://www.acmi.net.au/ideas/read/evolution-audio-videogames/">Audio Evolution in Videogames</a>
   * <a href="https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer_frame.html">SDL_Mixer documentation</a>
   * <a href="https://en.wikipedia.org/wiki/Panning_(audio)">Audio Panning</a>
   * <a href="https://en.wikipedia.org/wiki/Stereophonic_sound">Audio Stereo</a>
   * Getting Started with C++ Audio Programming for Game Development(Recommended)
  
