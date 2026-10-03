//**************************************************************************
// Demo 0 de Isomot por Ignacio Pérez Gil                                  *
//**************************************************************************
// En esta demo tenemos una habitación de 8x8 losetas de 16 píxels         *
// de anchura, en la que evolucionan tres tipos de objetos:                *
//  1 - Diez blancos (de tipo rejilla) que no se mueven.                   *
//  2 - Cinco verdes (de tipo rejilla) que se mueven arriba y abajo.       *
//  3 - Uno azul (de tipo libre) que se mueve controlado desde el teclado, *
//      con las teclas Q, A, P, L, O y K.                                  *
//  4 - Uno rojo (de tipo libre)                                           *
// Además de esto, puedes cambiar la graduación de las sombras pulsando    *
// IZQUIERDA y DERECHA, y el porcentaje de transparencia de los objetos    *
// azul y rojo pulsando ARRIBA y ABAJO.                                    *
// Esta demo no pretende ser un tutorial exaustivo, sino ser una simple    *
// ayuda para puedas aprender a manejar Isomot sin tener que empezar el    *
// código desde cero. Hay muchas características del motor que no se       *
// utilizan en esta demo, como la posibilidad de mover y/o animar paredes, *
// etc., así que siéntete libre de experimentar por tu cuenta :)           *
// Si encuentras algún fallo o quieres hacerme llegar cualquier sugerencia *
// o comentario, no dudes en escribirme a perezg_ret@lycos.es              *
//**************************************************************************

#include "math.h"
#include "allegro.h"
#include "isomot.h"

BITMAP *losagc = NULL;
BITMAP *losago = NULL;
BITMAP *psx = NULL;
BITMAP *psy = NULL;
BITMAP *pix = NULL;
BITMAP *piy = NULL;
BITMAP *obja = NULL;
BITMAP *objb = NULL;
BITMAP *objv = NULL;
BITMAP *objr = NULL;
BITMAP *smba = NULL;
BITMAP *smbb = NULL;
BITMAP *smbr = NULL;

void inicio_allegro(void);
void fin_allegro(void);
void inicio_isomot(void);
void fin_isomot(void);
void mover_objetos_verdes(void);
int mover_objeto_azul(void);

char transp=0;

int main(void)
{
 BITMAP *buffer = NULL;
 char sombras = 50;

 // Se coloca la semilla para las funciones aleatorias. Cambiar el número
 // para generar una habitación distinta.
 srand(4);
 inicio_allegro();
 inicio_isomot();
 buffer=create_bitmap(640, 480);

 do
  {
   // Limpiamos el buffer y escribimos los mensajes.
   clear_bitmap(buffer);
   textout(buffer, font, "Demo 0 de Isomot", 420, 65, -1);
   textout(buffer, font, "2003 - Ignacio Perez Gil", 420, 80, -1);
   textout(buffer, font, "Pulsa ESC para salir", 420, 95, -1);
   textout(buffer, font, "Pulsa IZQUIERDA y DERECHA", 430, 415, -1);
   textout(buffer, font, "para cambiar las sombras", 430, 430, -1);
   textout(buffer, font, "Pulsa ARRIBA y ABAJO para", 430, 445, -1);
   textout(buffer, font, "cambiar las transparencias", 430, 460, -1);
   textout(buffer, font, "Pulsa Q, A, P, L, O y K", 20, 420, -1);
   textout(buffer, font, "para mover el objeto azul", 20, 435, -1);

   poll_keyboard();

   // Movemos los objetos verdes.
   mover_objetos_verdes();

   // Se mueve el objeto azul y se escribe el mensaje de error si ha habido algún
   // problema al hacerlo.
   if(mover_objeto_azul())
     textout_centre(buffer, font, ism_desc_error(), 320, 10, -1);

   // Modificamos la graduación de las sombras, si se pulsan las teclas al efecto
   if(key[KEY_LEFT] && !key[KEY_RIGHT] && sombras>0)
     ism_establecer_sombras(--sombras);
   if(!key[KEY_LEFT] && key[KEY_RIGHT] && sombras<100)
     ism_establecer_sombras(++sombras);
   
   // Dibujamos el mundo isométrico en el buffer
   ism_dibujar_mundo_isom(buffer, 320, 180);
   textprintf(buffer, font, 10, 10, -1,"Sombras: %i%%",sombras);
   textprintf(buffer, font, 10, 25, -1,"Transparencia azul: %i%%",transp);
   textprintf(buffer, font, 10, 40, -1,"Transparencia rojo: %i%%",100-transp);

   // Esperamos al siguiente retrazo vertical y dibujamos el buffer en la pantalla.
   vsync();
   acquire_screen();
   blit(buffer, screen, 0, 0, 0, 0, 640, 480);
   release_screen();
  }while(!key[KEY_ESC]);

 fin_isomot();
 fin_allegro();
 return 0;
}
END_OF_MAIN();

//******************************************************
// Inicializamos Isomot y colocamos los objetos blancos.
//******************************************************
void inicio_isomot(void)
{
 char f,n;

 // Establecemos una rejilla de 8x8 con 16 píxels de anchura de celda.
 ism_establecer_rejilla(8, 8, 16);

 // Colocamos las losetas como si fuera un tablero de ajedrez.
 for(f=0;f<8;f+=2)
   for(n=0;n<8;n+=2)
    {
     ism_colocar_loseta(losagc, f, n);
     ism_colocar_loseta(losagc, f+1, n+1);
     ism_colocar_loseta(losago, f+1, n);
     ism_colocar_loseta(losago, f, n+1);
    }

 // Colocamos las paredes inferiores y superiores de los ejes x e y.
 ism_colocar_pared(psx, SUP_X, TODAS);
 ism_colocar_pared(psy, SUP_Y, TODAS);
 ism_colocar_pared(pix, INF_X, TODAS);
 ism_colocar_pared(piy, INF_Y, TODAS);

 // Colocamos diez objetos rejilla blancos en posiciones aleatorias,
 // y con z=ENCIMA. Dado que una vez colocados ya no los vamos a
 // modificar ni a mover, no necesitamos guardar sus identificadores.
 for(f=0;f<10;f++)
  {int y = (int)fmod(rand(),8);
   int x = (int)fmod(rand(),8);
   ism_colocar_objeto_rejilla(x, y, ENCIMA, 19, objb, NULL);
  } 
}

//*****************************************
// Mueve arriba y abajo los objetos verdes.
//*****************************************
void mover_objetos_verdes(void)
{
 static ism_id id[5]={NO_ID, NO_ID, NO_ID, NO_ID, NO_ID}; // Almacena los identificadores de los objetos
 static char dir[5]; // Almacena las direcciones en la que se mueven los objetos
 char f;
 
 // Si es la primera vez que se llama a esta función, se colocan los objetos en 
 // posiciones aleatorias y se les elige una dirección al azar.
 if(id[0] == NO_ID)
  {
   for(f=0;f<5;f++)
    {
     // Si se intenta colocar en un lugar en el que colisione con otro objeto,
     // la función devuelve ID_ERROR. Colocando la llamada a ism_colocar_objeto_rejilla
     // dentro del while nos aseguramos de que se siga intentando colocar el objeto
     // hasta que encontremos unas coordenadas en las que no colisione con nada.
     do
      {int z = (int)(2*fmod(rand(),101));
       int y = (int)fmod(rand(),8);
       int x = (int)fmod(rand(),8);
       id[f] = ism_colocar_objeto_rejilla(x, y, z, 23, objv, smbb);
      }while(id[f] == ID_ERROR); 
     if(rand()&1)
       dir[f]=2;
     else
       dir[f]=-2;  
    } 
  }  

 // Movemos los objetos
 for(f=0;f<5;f++)
  {
   // No permitimos que superen los 200 píxels de altura.
   if(ism_obtener_dato_objeto(id[f], D_Z) == 200)
     dir[f] = -2;

   // Si no se ha podido mover, es que ha colisionado con el suelo o con otro
   // objeto, en cuyo caso cambiamos su dirección.
   if(ism_cambiar_dato_objeto(id[f], D_Z, dir[f], SUMAR) == -1)
     dir[f] *= -1;
  }   
}

//**************************************************************************
// Mueve el objeto libre. Devuelve 0 si no ha habido problemas al moverlo, o
// -1 en caso contrario.
//**************************************************************************
int mover_objeto_azul(void)
{
 static ism_id idl = NO_ID; // Identificador del objeto azul.
 static ism_id idr = NO_ID; // Identificador del objeto azul.
 char movx = 0;    // Movimiento en el eje x.
 char movy = 0;    // Movimiento en el eje y.
 char movz = 0;    // Movimiento en el eje z.
 char ttransp = 0; // Cambio de transparencia de los objetos.
 int retorno = 0;  // Retorno de la función.
 
 // Si es la primera vez que se llama a esta función, se colocan los objetos
 // azul y rojo en una posición aleatoria, y se coloca la transparencia del
 // rojo al 100%.
 if(idl == NO_ID)
  {
   do
    {int x = (int)(fmod(rand(),61)*2);
     int y = (int)(fmod(rand(),56)*2+7);
     int z = (int)(fmod(rand(),201));
     idl = ism_colocar_objeto_libre(x, y, z, 8, 8, 39, obja, smba);
    }while(idl == ID_ERROR); 
  }  
 if(idr == NO_ID)
  {
   do
    {int x = (int)(fmod(rand(),61)*2);
     int y = (int)(fmod(rand(),56)*2+7);
     int z = (int)(fmod(rand(),151));
     idr = ism_colocar_objeto_libre(x, y, z, 8, 16, 39, objr, smbr);
    }while(idr == ID_ERROR); 
   ism_cambiar_dato_objeto(idr, D_TRANSP, 100, CAMBIAR);
  }  

 // Comprobamos el teclado
 if(key[KEY_L]) movx =  1;
 if(key[KEY_A]) movy =  1;
 if(key[KEY_Q]) movx -= 1;
 if(key[KEY_P]) movy -= 1;
 if(key[KEY_O]) movz =  1;
 if(key[KEY_K]) movz -= 1;
 if(key[KEY_UP]) ttransp = 1;
 if(key[KEY_DOWN]) ttransp -= 1;
 
 // Movemos el objeto
 if(movx || movy || movz)
   retorno = ism_mover_objeto(idl, movx, movy, movz, SUMAR);

 // Cambiamos la transparencia
 if(ttransp)
  {
   ism_cambiar_dato_objeto(idl, D_TRANSP, ttransp, SUMAR);
   ism_cambiar_dato_objeto(idr, D_TRANSP, -ttransp, SUMAR);
   transp += ttransp;
   if(transp==101) transp=100;
   if(transp==-1) transp=0;
  }

 return retorno;
}

//***************************************
// Liberamos la memoria usada por Isomot.
//***************************************
void fin_isomot(void)
{
 ism_destruir_todo();
}

//********************************************************
// Inicializamos la librería Allegro y cargamos los mapas.
//********************************************************
void inicio_allegro(void)
{
 PALETTE paleta;

 allegro_init();
 set_color_depth(16);
 set_gfx_mode(GFX_AUTODETECT, 640, 480, 0, 0);
 install_keyboard();
 losagc = load_bmp("losagc.bmp",paleta);
 losago = load_bmp("losago.bmp",paleta);
 psx = load_bmp("psx.bmp",paleta);
 psy = load_bmp("psy.bmp",paleta);
 pix = load_bmp("pix.bmp",paleta);
 piy = load_bmp("piy.bmp",paleta);
 obja = load_bmp("obja.bmp",paleta);
 objb = load_bmp("objb.bmp",paleta);
 objv = load_bmp("objv.bmp",paleta);
 smba = load_bmp("sombraa.bmp",paleta);
 smbb = load_bmp("sombrab.bmp",paleta);
 smbr = load_bmp("sombrar.bmp",paleta);
 objr = load_bmp("objr.bmp",paleta);
}

//***********************************
// Liberamos la memoria de los mapas.
//***********************************
void fin_allegro(void)
{
 destroy_bitmap(losagc);
 destroy_bitmap(losago);
 destroy_bitmap(psx);
 destroy_bitmap(psy);
 destroy_bitmap(pix);
 destroy_bitmap(piy);
 destroy_bitmap(obja);
 destroy_bitmap(objb);
 destroy_bitmap(objv);
 destroy_bitmap(objr);
 destroy_bitmap(smba);
 destroy_bitmap(smbb);
 destroy_bitmap(smbr);
}

