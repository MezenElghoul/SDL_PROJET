#ifndef PERS_H_INCLUDED
#define PERS_H_INCLUDED
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

typedef struct
{
  	SDL_Surface *image_p;
  	SDL_Rect pos_perso;
	int controler[4];
}Personne;

void initialiserperso(Personne*perso,SDL_Surface*screen);
void deplacer_perso(Personne *perso,SDL_Event event,background back,SDL_Surface*screen);
void afficher_perso(SDL_Surface *screen,Personne perso);
void free_perso(Personne perso);








#endif

