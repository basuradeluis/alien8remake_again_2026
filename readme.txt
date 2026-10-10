Basuradeluis
2026
Based on:
Source:
https://retrospec.sgn.net/info.htm?id=isomot&t=u

https://retrospec.sgn.net/info.htm?id=alien8&t=g



+++

Compilation

sudo apt install build-essential
sudo apt install build-essential libasound2-dev
sudo apt install libcurl4-openssl-dev


bajarse fmodengine version linux 2.03
Descomprimir
IA:
    sudo cp api/core/inc/* /usr/local/include/
    sudo cp api/core/lib/x86_64/* /usr/local/lib/


Añadir  FMOD_System_Create(&sistema, FMOD_VERSION);
CORREGIR OTRA ACTUALIZACION DE SONIDO


PRIMERO :
gcc -c *.c

Y DESPUES
gcc *.o -o mi_programa -lalleg -lcurl -lfmod

Al arrancar sale pantalla negra y nada mas


SUCIO{
gcc -llibfmod -lalleg -lcurl *.c
gcc -libfmod -lalleg -lcurl *.c
gcc *.o -o mi_programa -lalleg -lcurl
}


falso + falso12
basurade




-Corregir en internet.c el define
-Corregir juego.c con particularidades mal hechas
+++


See isomot demo and its html
The exe run to fast on a wine under linux modern cpu
TODO:
It uses Allegro 4 library
Migrate to allegro 5?
Migrate to other library (java? sdl?)

