Recompilation and update of
Alien 8 2008 remake by Ignacio Perez Gil and D-o-S (2008)


Recompilation and update author: Basuradeluis
2026


Based on:
Source:
https://retrospec.sgn.net/info.htm?id=alien8&t=g
Isomot engine:
https://retrospec.sgn.net/info.htm?id=isomot&t=u



+++
See isomot demo and its html
The exe run to fast on a wine under linux modern cpu
Download bot source code AND windows version (and fedora version maybe)
+++

Compilation
Allegro 4 developers files are needed. Use your distribution package to install them.

sudo apt install liballegro4-dev build-essential libasound2-dev libcurl4-openssl-dev


Download fmodengine (FMOD Engine, for the Core API). Version linux 2.03
Then do a
    sudo cp api/core/inc/* /usr/local/include/
    sudo cp api/core/lib/x86_64/* /usr/local/lib/
And a sudo ldconfig. Ignore the "this is not a symbolic link", or remove the .14 and .15 files and create symbolinks to the main .so file. Maybe this step is unnecesary or there are other ways to use the library


Some updates to the old code:
-Fix the internet.c file to use the linux version of curl
-Fix some old fmod library issues (see commits)
    Add FMOD_VERSION in  FMOD_System_Create(&sistema, FMOD_VERSION);
    Others
-Fix juego.c with some C / CPP issues. Lvalues and Rvalues. Undef has no parameters


First compile the .c files into .o files:
gcc -c *.c

Then, link them:
gcc *.o -o mi_programa -lalleg -lcurl -lfmod

The .dat files must be next to the generated executable created. If not and full screen mode enabled, probably a black scren with no error will be shown. Use Ctrl+Alt+F3 to kill the program. Go back to initial (Ctrl+Alt+F2) and readjust your screen resolution.
Changed the game, so if no initial configuration exists, use window mode as default (to prevent issues with higher resolutions and black screens)
