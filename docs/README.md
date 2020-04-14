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






```markdown
Syntax highlighted code block

# Header 1
## Header 2
### Header 3

- Bulleted
- List

1. Numbered
2. List

**Bold** and _Italic_ and `Code` text

[Link](url) and ![Image](src)
```

For more details see [GitHub Flavored Markdown](https://guides.github.com/features/mastering-markdown/).

### Jekyll Themes

Your Pages site will use the layout and styles from the Jekyll theme you have selected in your [repository settings](https://github.com/Aitorlb7/Spatial-audio-Music-manager-Research/settings). The name of this theme is saved in the Jekyll `_config.yml` configuration file.

### Support or Contact

Having trouble with Pages? Check out our [documentation](https://help.github.com/categories/github-pages-basics/) or [contact support](https://github.com/contact) and we’ll help you sort it out.
