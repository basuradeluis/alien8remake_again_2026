# Recompilation and update of Alien 8 remake by Ignacio Perez Gil and D-o-S (2008) for Retrospec

2026 (and 2016) Recompilation and update author: Basuradeluis

Based on:
Source:
https://retrospec.sgn.net/info.htm?id=alien8&t=g
Isomot engine:
https://retrospec.sgn.net/info.htm?id=isomot&t=u

## About:
Alien 8 was a videogame developed by Ultimate for computers in 80's. In 2008 Ignacio Perez Gil and D-o-S for the retrospec webpage made a remake for Windows, Mac and Linux written in C with Allegro library.  
On 2016 I made some experiments with it just for fun, and in 2026 I recovered them.  
This is just some little changes to the code, with some instructions about it.  
The original source code was in spanish, although there are some tricks to make functions available in English (defines).  
Download both source code AND windows version (and fedora version maybe) from the retrospec webpage. Or use the ones provided here, they are copies of them.  
alien8_win/
isomot/

## About the Engine (isomot):
See isomot demo folder and its html.
The provided original precompiled exe for windows runs to fast on a wine under linux modern cpu. And under linux even recompiled, probably because it has no fps/speed limit.

To compile them under linux, copy the isomot files (.c .h and ism_lng.h) next to .c demo files (or viceversa).
Then compile .c with:

```bash
gcc -c demoesp.c isomot.c
```

Then link them, adding the math library (fmod floating-point remainder function is used):

```bash
gcc *.o -o salida  -lalleg  -lm
```



## Instructions to compile the game
Library Allegro 4 development files are needed. Also curl library (the game has an option to send scores to the internet, altough it doesnt work anymore). Use your distribution package to install them. Like:

```bash
sudo apt install liballegro4-dev build-essential libasound2-dev libcurl4-openssl-dev
```

Also the sound uses the fmod library. To download them, just register in fmod web page, and download the FMOD Engine (for the Core API). I downloaded the 2.03.15 version for linux. Other version may work. Keep in mind some Fmod library may have little changes. You may have to adapt some code to FMOD.

Then do the following:

```bash
sudo cp api/core/inc/* /usr/local/include/
sudo cp api/core/lib/x86_64/* /usr/local/lib/
sudo ldconfig
```

Ignore the "this is not a symbolic link" message, or remove the .14 and .15 files and create symlinks to the main .so file. Maybe this step is unnecessary or there are other ways to use the library. Google/any AI may help you.

See also git tags 'OriginalSourceCode' and 'FMODFixes'

## Some updates to the original old code to compile it:
-Fix the internet.c file to use the linux version of curl acording to your Operating System (internet.c has a #DEFINE for diferent OS)
-Fix some old fmod library issues (see tag 'FMODFixes' in git history)
    Add FMOD_VERSION in  FMOD_System_Create(&sistema, FMOD_VERSION);
    Others
-Fix juego.c with some C / CPP issues. Lvalues and Rvalues. Undef has no parameters

As a suggestion to compile the game:
First compile the .c files into .o files:

```bash
gcc -c *.c
```

Then, link them with Allegro, FMOD and curl:

```bash
gcc *.o -o executable -lalleg -lcurl -lfmod
```

You may create alias for these previous comands. Or adjust you IDE.
Run the executable in a terminal, if possible.

The .dat files must be next to the generated executable created. If there aren't and full screen mode enabled, probably a black scren with no error will be shown. In linux, use Ctrl+Alt+F3 to kill the program. Go back to initial (Ctrl+Alt+F2) and readjust your screen resolution.
I changed the game, so if no initial configuration exists, it uses window mode as default (to prevent issues with higher resolutions and black screens).

The anims.dat file was modified adding some extra images (althoug not all are used). Use the included in this package.
Use grabber program (instaled with Allegro library development package) to examine/modify the dat files. Some of the images/fonts of this .dat files are extracted into 'extradata/miniaturas/' folder.


## Features added:
- Parameters
- Some cheats (inmunity was already present). Infinite lifes and time.
- Choose the iniital room via argument (previously there was something similar using F1-F4 keys).
- Skip intro, and skip menu, to go to play the game instantly.
- Show the end sequence.
- Quit the game instantly.
- Debug info (current room, lines drawn on the floor).
 - Hability to appear an auxiliar temporary block to make jumps easier.
- Hability to shoot!

