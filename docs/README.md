# Spatial Audio Music Manager Research

This project was developed by [Aitor Luque Bodet](<https://www.linkedin.com/in/aitor-luque-bodet-ab93a4175/>) , a second year student of the [Bachelor's degrees in Video Game Design and Development at CITM/TTC](<https://www.citm.upc.edu/ing/estudis/graus-videojocs/>) as of 14/04/2020. 

This content was generated for the Project II subject under the supervision of lecturer [Ramón Santamaria](<https://www.linkedin.com/in/raysan/>).

The main focus of this research was:
- Develop a music manager, capable of chaining a playlist with fading.
- Play Audio and Fx spatially, managing all entities capable of generating audio.

## First approach

### What is spatial audio?

Spatial Audio is any audio which gives you a sense of space beyond conventional stereo, allowing the user to pinpoint where sound is coming from, whether this is above, below, or a full 360 degrees around you. For example stereo allows you to hear things in front left and right, but you can’t get a sense of surround, height or sounds from below you. With the introduction of the 3rd dimension, you have a sense of the exact location of sound sources from all around. This definition also appeals to 3D audio.

![Image](https://github.com/Aitorlb7/Spatial-audio-Music-manager-Research/blob/master/docs/images/Spatial_Demonstration.jpg?raw=true)

When it comes to game development it's still being developed, but there are some approaches that simulates those conditions, and others softwares that already recreate real spatial audio.
Even in virtual reality, while you are interacting with 3D images, the sound should also give you the sense of space to compliment the immersive experience. As the human field of vision is at best around 110 degreess so, as in real life, in the 3D virtual world we rely on audio to tell us where we should be looking and what we should be interacting with.
[Here](https://docs.google.com/spreadsheets/d/1OGi40yAonUDL6UcQaIIfGbhT1XY44JVs9lipk0x6QRg/edit#gid=634347005) you can find a list with some games using real 3D spatial audio.

Each game developer has to make the decision whether to invest in spatial audio or stick to stereo or a simulated approach, but in some games it's highly recommended to implement it as it improves the immersion and player experience.
In the first minute of this [video](https://www.youtube.com/watch?v=oVXFpbpNQDc) you can really tell the difference between one and another, please take a quick look at it.

### What are we refering with music manager?

The music manager is a module or code structure selfmade that allow the developer to handle different audio inputs from several sources, load and erasing those fx's or audio at will. In this research we will be using j1Audio.h and j1Audio.cpp.
In orther to follow the explanation it's recommended to take a look to the [SDL_Mixer documentation](https://www.libsdl.org/projects/SDL_mixer/docs/SDL_mixer.pdf).

## My approach and implementation

Real spatial audio it's very hard to achieve with the resources available for this project, so here it is an approximate simulation of how spatial audio would work in a 2D environment.
First of all we will take a look to those essential functions we must know about:

![image](https://github.com/Aitorlb7/Spatial-audio-Music-manager-Research/blob/master/docs/images/Audio_functions.png?raw=true)
*Module Audio header file*
### Core SDL_Mixer

- **Mix_Chunk**: Is the internal format for an audio chunk and where is stored the sample data, the length in bytesof that data, and the volume to use when mixing the sample.

- **Mix_Music**: This is an opaque data type used for Music data. We will use it to store our music files

- **Channel**: Is where the chunk will be played.

- **Mix_SetPosition**:This effect emulates a simple 3D audio effect. It’s not all that realistic, but it can help improve some level of realism. By giving it the angle and distance from the camera’s point of view, the effect pans and attenuates volumes.

- **Mix_PlayChannel**: Play chunk on the referenced channel, or if channel is -1, takes the first free unreserved channel. The sample will play for loops +1 number of times

### Functions

- **LoadMusic**: In charge of storing into memory a given path to an audio, more specifically to the previously created list. Returns a pointer to the sample as a Mix_Music. NULL is returned on error

- **PlayMusic**: Given an id and a fade time, iterates the music list and plays the desired one.

- **LoadFx**: Store into the fx list the audio passed by reference. Returns a pointer to the sample as a Mix_Chunk. NULL is returned on error

- **PlayFx**: This function uses Mix_PlayChannel and given an id iterates the fx list and plays or even loops the fx.

- **UnloadFx**: This function will remove the fx from the list.

- **PlaySpatialFx**: Play a WAV simulating a 3D audio reciving an fx, a channel, an angle and a distance.

- **GetAngle**: Calculate the angle with the atan2 given the Dot product and the determinant.

- **GetDistance**: With this function we calculate the distance between the player and the entitie generating the sound.

## Exercises - TODO's

Now that we have reviewed the functions and concepts we will use, we can start with the exercise. We will try to relate 2 entities(emitter and receiver) with an a fx. This fx will be assigned to the emitter, and the receiver(Player) will hear it different from a different direction and distance. We will also handle the music manager, and how to chain a playlist.

### TODO 1
Allocate those channels that we will use to play the chunks later, we must have control of this chunks.
![image](https://github.com/Aitorlb7/Spatial-audio-Music-manager-Research/blob/master/docs/images/TODO1.png?raw=true)

### TODO 2
Set a channel in a position given a channel, an angle and a distance, There is a SDL_Mixer function already explained 
![image](https://github.com/Aitorlb7/Spatial-audio-Music-manager-Research/blob/master/docs/images/TODO2.png?raw=true)

### TODO 3
Calculate the distance between the player and the enemy passed by reference using pythagoras
![image](https://github.com/Aitorlb7/Spatial-audio-Music-manager-Research/blob/master/docs/images/TODO3.png?raw=true)

### TODO 4
Once the key is pressed play the fx using PlaySpatialFx() 
![image](https://github.com/Aitorlb7/Spatial-audio-Music-manager-Research/blob/master/docs/images/TODO4.png?raw=true)

### TODO 5
Load the audio path given into a Mix_Music variable
![image](https://github.com/Aitorlb7/Spatial-audio-Music-manager-Research/blob/master/docs/images/TODO5.png?raw=true)

### TODO 6
Iterate all the music audios stored in the list (already created in the header file)

### TODO 7
Given the fade_time implement a fade in and fade out using Mix_Fade(Out/In)Music, take into account that for the next audio to start playing the last fading must be completed.
![image](https://github.com/Aitorlb7/Spatial-audio-Music-manager-Research/blob/master/docs/images/TODO6-7.png?raw=true)

