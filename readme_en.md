# Recompilation and update of
Alien 8 2008 remake by Ignacio Perez Gil and D-o-S (2008) for Retrospec

Recompilation and update author: Basuradeluis
2026 (and 2016)

Based on:
Source:
https://retrospec.sgn.net/info.htm?id=alien8&t=g
Isomot engine:
https://retrospec.sgn.net/info.htm?id=isomot&t=u

## About:
Alien 8 was a videogame developed by Ultimate for computer in 80's. In 2008 Ignacio Perez Gil and D-o-S for the retrospec webpage made a remake for Windows, Mac and Linux written in C with Allegro library.
On 2016 I made some experiments with it just for fun. And 2026 I recovered them.
This is just some little changes to the code, with some instructions about it.
The original source code was in spanish, although there are some tricks to make functions available in English (defines)
Download bot source code AND windows version (and fedora version maybe) from the retrospec webpage. Or use the provided here, they are copys of them.
alien8_win/
isomot/

## About the Engine (isomot):
See isomot demo folder and its html.
The provided original precompiled exe for windows runs to fast on a wine under linux modern cpu. And under linux even recompiled, probably because it has no fps/speed limit.

To compile them under linux, copy the isomot files (.c .h and ism_lng.h) next to .c demo files (or viceversa).
Then compile .c with:
gcc -c demoesp.c isomot.c
Then link them, adding the math library (fmod floating-point remainder function is used):
gcc *.o -o salida  -lalleg  -lm



## Instructions to compile the game
Library Allegro 4 development files are needed. Also curl library (the game has an option to send scores to the internet, altough it doesnt work anymore). Use your distribution package to install them. Like:

sudo apt install liballegro4-dev build-essential libasound2-dev libcurl4-openssl-dev

Also the sound uses the fmod library. To download them, just register in fmod web page, and download the FMOD Engine (for the Core API). I downloaded the 2.03.15 version for linux. Other version may work. Keep in mind some Fmod library may have little changes. You may have to adapt some code to FMOD.

Then do a
    sudo cp api/core/inc/* /usr/local/include/
    sudo cp api/core/lib/x86_64/* /usr/local/lib/
And a sudo ldconfig. Ignore the "this is not a symbolic link", or remove the .14 and .15 files and create symbolinks to the main .so file. Maybe this step is unnecesary or there are other ways to use the library. Google/any AI may help you.

See also git tags 'OriginalSourceCode' and 'FMODFixes'

## Some updates to the original old code to compile it:
-Fix the internet.c file to use the linux version of curl acording to your Operating System (internet.c has a #DEFINE for diferent OS)
-Fix some old fmod library issues (see tag 'FMODFixes' in git history)
    Add FMOD_VERSION in  FMOD_System_Create(&sistema, FMOD_VERSION);
    Others
-Fix juego.c with some C / CPP issues. Lvalues and Rvalues. Undef has no parameters

As a sugestion to compile the game:
First compile the .c files into .o files:
gcc -c *.c

Then, link them with alegro, fmod and curl:
gcc *.o -o executable -lalleg -lcurl -lfmod

You may create alias for these previous comands. Or adjust you IDE.
Run the executable in a terminal, if possible.

The .dat files must be next to the generated executable created. If there aren't and full screen mode enabled, probably a black scren with no error will be shown. In linux, use Ctrl+Alt+F3 to kill the program. Go back to initial (Ctrl+Alt+F2) and readjust your screen resolution.
I changed the game, so if no initial configuration exists, it uses window mode as default (to prevent issues with higher resolutions and black screens).

The anims.dat file was modified adding some extra images (althoug not all are used). Use the included in this package.
Use grabber program (instaled with allegro library development package) to examine/modify the dat files. Some of the images/fonts of this .dat files are extracted into 'extradata/miniaturas/' folder


## Feature added:
Parameters.
Some cheats (inmunity was already present).

