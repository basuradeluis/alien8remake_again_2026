Current recompilation and update of
Alien 8 remake by Ignacio Perez Gil and D-o-S (2008)



Recompilation and update author: Basuradeluis
2026


Based on:
Source:
https://retrospec.sgn.net/info.htm?id=isomot&t=u

https://retrospec.sgn.net/info.htm?id=alien8&t=g

+++
See isomot demo and its html
The exe run to fast on a wine under linux modern cpu

+++

Compilation
Allegro 4 developers files are needed. Use your distribution package to install them.

sudo apt install liballegro4-dev build-essential libasound2-dev libcurl4-openssl-dev


Download fmodengine (FMOD Engine, for the Core API). Version linux 2.03
Then do a
    sudo cp api/core/inc/* /usr/local/include/
    sudo cp api/core/lib/x86_64/* /usr/local/lib/
And a sudo ldconfig. Ignore the "this is not a symbolic link", or remove the .14 and .15 files and create symbolinks to the main .so file). Maybe this step is unnecesary or there are other ways to use the library


Some updates to the old code:
-Fix the internet.c file to use the linux version of curl
-Fix some old fmod library issues (see commits)
    Add FMOD_VERSION in  FMOD_System_Create(&sistema, FMOD_VERSION);
-Fix juego.c with some C / CPP issues. Lvalues and Rvalues. Undef has no parameters



First compile the .c files into .o files:
gcc -c *.c

Then, link them:

gcc *.o -o mi_programa -lalleg -lcurl -lfmod

Changed the game, so if no initial configuration exists, use window mode (to prevent issues with higher resolutions and black screens)
