#ifndef BACKGROUND_H_INCLUDE
#define BACKGROUND_H_INCLUDE

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#define SCREEN_W 1320
#define SCREEN_H 720
#define nombre_imag_sprite 20			//nombre d'images mta3 il spritesheet
typedef struct
{
	SDL_Surface *img_background,	//img mta3 il background
		*mask_background;			//img mta3 il masque
	SDL_Rect pos_background,		//position mta3 mta3 il background
	anime;	//animation mta3 il background
	Uint32 temp;		//chrono mta3 il animation
	SDL_Rect camera;	//effet camera mta3 il scrolling
	Mix_Music *son;
}background;

#include "../player/joueur.h"

void afficher_back(background b, SDL_Surface *ecran);
void initBack (background *b);

void affiche_multiscreen(background back,Personne p,background back2,Personne p2,SDL_Surface*screen);	//afficher deux ecrans
void scrolling (background *bac,int direction,int pas, SDL_Surface *screen);
void animation(background*b);
void liberation_background(background*b);
void liberation(background*b,Personne*P);
#endif  
