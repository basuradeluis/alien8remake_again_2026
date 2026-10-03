//**************************************************************************
// Isomot's Demo 0 by Ignacio Pérez Gil                                    *
//**************************************************************************
// On this demo we have a room  of an 8x8 grid, where each floor tile is   *
// 16 pixels wide, with three kind of objects:                             * 
//  1 - Ten white grid one that don't move.                                *
//  2 - Five green ones (that are grid objects too) that move up and down. *
//  3 - One blue free one that is controlled by the keyboard, with the     *
//      Q, A, P, L, O and K keys.                                          *
//  4 - A red object                                                       *
// Appart from that, you can change the shadowing percentage with the      *
// LEFT and RIGHT keys, and the transparency percentages with the UP and   *
// DOWN ones.                                                              *
// This demo is not intended to be an exaustive tutorial, but a simple     *
// help so you can learn using Isomot withouth starting your test code     *
// from zero. There are a lot of features from the engine that are not     *
// used here, like moving/animating walls, etc., so feel free to           *
// experiment by yourself :)                                               *
// If you find a bug, or you want to tell me any comments, you can e-mail  *
// me at perezg_ret@lycos.es                                               *
//**************************************************************************

#include "math.h"
#include "allegro.h"
#include "isomot.h"

BITMAP *ftilelg = NULL;
BITMAP *ftiledg = NULL;
BITMAP *uwx = NULL;
BITMAP *uwy = NULL;
BITMAP *lwx = NULL;
BITMAP *lwy = NULL;
BITMAP *bobj = NULL;
BITMAP *wobj = NULL;
BITMAP *gobj = NULL;
BITMAP *robj = NULL;
BITMAP *bshdw = NULL;
BITMAP *gshdw = NULL;
BITMAP *rshdw = NULL;

void allegro_start(void);
void allegro_end(void);
void isomot_start(void);
void isomot_end(void);
void move_green_objects(void);
int move_blue_object(void);

char transp=0;

int main(void)
{
 BITMAP *buffer = NULL;
 char shadows = 50;

 // We set the seed for thr random functions. Change this number to get
 // a different room.
 srand(4);
 allegro_start();
 isomot_start();
 buffer=create_bitmap(640, 480);

 do
  {
   // We clear the buffer and write the messages.
   clear_bitmap(buffer);
   textout(buffer, font, "Isomot's Demo 0", 420, 65, -1);
   textout(buffer, font, "2003 - Ignacio Perez Gil", 420, 80, -1);
   textout(buffer, font, "Press ESC to exit", 420, 95, -1);
   textout(buffer, font, "Press LEFT and RIGHT", 440, 415, -1);
   textout(buffer, font, "to change shadows", 440, 430, -1);
   textout(buffer, font, "Press UP and Down to", 440, 445, -1);
   textout(buffer, font, "change transparencies", 440, 460, -1);
   textout(buffer, font, "Press Q, A, P, L, O and K", 20, 420, -1);
   textout(buffer, font, "to move the blue object", 20, 435, -1);

   poll_keyboard();

   // We move the green objects.
   move_green_objects();

   // We move the blue object and write the error message if something
   // went wrong.
   if(move_blue_object())
     textout_centre(buffer, font, ism_error_desc(), 320, 10, -1);

   // We change here the shadowing percentage, if the right keys are pressed.
   if(key[KEY_LEFT] && !key[KEY_RIGHT] && shadows>0)
     ism_set_shadowing_percentage(--shadows);
   if(!key[KEY_LEFT] && key[KEY_RIGHT] && shadows<100)
     ism_set_shadowing_percentage(++shadows);
   
   // Now we draw the isometric world on the buffer
   ism_draw_isom_world(buffer, 320, 180);
   textprintf(buffer, font, 10, 25, -1,"Shadows: %i%%",shadows);
   textprintf(buffer, font, 10, 40, -1,"Red object's transparency:  %i%%",transp);
   textprintf(buffer, font, 10, 55, -1,"Blue object's transparency: %i%%",100-transp);

   // We wait for the next retrace and then blit the buffer on the screen.
   vsync();
   acquire_screen();
   blit(buffer, screen, 0, 0, 0, 0, 640, 480);
   release_screen();
  }while(!key[KEY_ESC]);

 isomot_end();
 allegro_end();
 return 0;
}
END_OF_MAIN();

//************************************************
// We initialise Isomot and put the white objects.
//************************************************
void isomot_start(void)
{
 char f,n;
 
 // We set an 8x8 grid with 16 pixels wide.
 ism_set_grid(8, 8, 16);

 // We put the floor tiles like on a chess board.
 for(f=0;f<8;f+=2)
   for(n=0;n<8;n+=2)
    {
     ism_set_floor_tile(ftilelg, f, n);
     ism_set_floor_tile(ftilelg, f+1, n+1);
     ism_set_floor_tile(ftiledg, f+1, n);
     ism_set_floor_tile(ftiledg, f, n+1);
    }

 // Setting the upper and lower walls from the x and y axis.
 ism_set_wall(uwx, HIGH_X, ALL);
 ism_set_wall(uwy, HIGH_Y, ALL);
 ism_set_wall(lwx, LOW_X, ALL);
 ism_set_wall(lwy, LOW_Y, ALL);

 // Finally, we put ten white grid objects on random places, and with
 // z=TOP. As we are not goin to move or modify them, we don't need
 // to store their ids.
 for(f=0;f<10;f++)
  {int y = (int)fmod(rand(),8);
   int x = (int)fmod(rand(),8);
   ism_put_grid_object(x, y, TOP, 19, wobj, NULL);
  } 
}

//*************************************
// Moves up and down the green objects.
//*************************************
void move_green_objects(void)
{
 static ism_id id[5]={NO_ID, NO_ID, NO_ID, NO_ID, NO_ID}; // Stores the object's ids
 static char dir[5]; // Stores the movement directions of the objects
 char f;
 
 // If it's the first time we are calling this function, we place the objects
 // at random places and with a random direction.
 if(id[0] == NO_ID)
  {
   for(f=0;f<5;f++)
    {
     // If it collides against another object when trying to place it, the
     // function returns ID_ERROR. Placing the call to ism_put_grid_object
     // inside the while, we assure it will keep on trying to put it until
     // we find a valid coordinates set.
     do
      {int z = (int)(2*fmod(rand(),101));
       int y = (int)fmod(rand(),8);
       int x = (int)fmod(rand(),8);
       id[f] = ism_put_grid_object(x, y, z, 23, gobj, gshdw);
      }while(id[f] == ID_ERROR); 
     if(rand()&1)
       dir[f]=2;
     else
       dir[f]=-2;  
    } 
  }  

 // We move now the objects
 for(f=0;f<5;f++)
  {
   // We don't allow them to be at a height higher than 200 pixels.
   if(ism_get_object_data(id[f], D_Z) == 200)
     dir[f] = -2;

   // Si no se ha podido mover, es que ha colisionado con el suelo o con otro
   // objeto, en cuyo caso cambiamos su dirección.
   // If we can't move it, that means it has collided against a the floor
   // or other object, so we change it's direction.
   if(ism_change_object_data(id[f], D_Z, dir[f], ADD) == -1)
     dir[f] *= -1;
  }   
}

//**************************************************************************
// Moves the free blue object. Returns 0 if there was any problem when doing
// so, or -1 if there wasn't.
//**************************************************************************
int move_blue_object(void)
{
 static ism_id id  = NO_ID; // The blue object's identifier.
 static ism_id idr = NO_ID; // The red object's identifier.
 char movx = 0;    // Movement on the x axis.
 char movy = 0;    // Movement on the y axis.
 char movz = 0;    // Movement on the z axis.
 char ttransp = 0; // Transparency change.
 int returns = 0;  // Returned value.
 
 // If it's the first time we call this function, we put the blue and red
 // objects on a random place, and set the red's transparency to 100%.
 if(id == NO_ID)
  {
   do
    {int x = (int)(fmod(rand(),61)*2);
     int y = (int)(fmod(rand(),56)*2+7);
     int z = (int)(fmod(rand(),201));
     id = ism_put_free_object(x, y, z, 8, 8, 39, bobj, bshdw);
    }while(id == ID_ERROR); 
  }  
 if(idr == NO_ID)
  {
   do
    {int x = (int)(fmod(rand(),61)*2);
     int y = (int)(fmod(rand(),56)*2+7);
     int z = (int)(fmod(rand(),151));
     idr = ism_put_free_object(x, y, z, 8, 16, 39, robj, rshdw);
    }while(idr == ID_ERROR); 
   ism_change_object_data(idr, D_TRANSP, 100, CHANGE);
  }  

 // We check the keyboard.
 if(key[KEY_L]) movx =  1;
 if(key[KEY_A]) movy =  1;
 if(key[KEY_Q]) movx -= 1;
 if(key[KEY_P]) movy -= 1;
 if(key[KEY_O]) movz =  1;
 if(key[KEY_K]) movz -= 1;
 if(key[KEY_UP]) ttransp = 1;
 if(key[KEY_DOWN]) ttransp -= 1;
 
 // We move the object
 if(movx || movy || movz)
   returns = ism_move_object(id, movx, movy, movz, ADD);

 // We change it's transparency
 if(ttransp)
  {
   ism_change_object_data(id, D_TRANSP, ttransp, ADD);
   ism_change_object_data(idr, D_TRANSP, -ttransp, ADD);
   transp += ttransp;
   if(transp==101) transp=100;
   if(transp==-1) transp=0;
  }

 return returns;
}

//*************************************
// Frees the memory reserved by Isomot.
//*************************************
void isomot_end(void)
{
 ism_destroy_all();
}

//********************************************
// Allegro's initializing and bitmaps loading.
//********************************************
void allegro_start(void)
{
 PALETTE p;

 allegro_init();
 set_color_depth(16);
 set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0);
 install_keyboard();
 ftilelg = load_bmp("losagc.bmp",p);
 ftiledg = load_bmp("losago.bmp",p);
 uwx = load_bmp("psx.bmp",p);
 uwy = load_bmp("psy.bmp",p);
 lwx = load_bmp("pix.bmp",p);
 lwy = load_bmp("piy.bmp",p);
 bobj = load_bmp("obja.bmp",p);
 wobj = load_bmp("objb.bmp",p);
 gobj = load_bmp("objv.bmp",p);
 robj = load_bmp("objr.bmp",p);
 bshdw = load_bmp("sombraa.bmp",p);
 gshdw = load_bmp("sombrab.bmp",p);
 rshdw = load_bmp("sombrar.bmp",p);
}

//*********************************************
// Frees the memory used by the loaded bitmaps.
//*********************************************
void allegro_end(void)
{
 destroy_bitmap(ftilelg);
 destroy_bitmap(ftiledg);
 destroy_bitmap(uwx);
 destroy_bitmap(uwy);
 destroy_bitmap(lwx);
 destroy_bitmap(lwy);
 destroy_bitmap(bobj);
 destroy_bitmap(wobj);
 destroy_bitmap(gobj);
 destroy_bitmap(robj);
 destroy_bitmap(bshdw);
 destroy_bitmap(gshdw);
 destroy_bitmap(rshdw);
}

