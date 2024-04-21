#include "backg.h"
#include "perso.h"
void initialiserperso(Personne *perso,SDL_Surface*screen)
{	
	perso->image_p=IMG_Load("./background/src/perso.png");
    if(!perso->image_p)
        printf("%s","error failed to load person");
	perso->pos_perso.x=20;
	perso->pos_perso.y=screen->h-perso->image_p->h-90;
	perso->pos_perso.w=perso->image_p->w;
	perso->pos_perso.h=perso->image_p->h;
    perso->controler[0]=SDLK_UP;
    perso->controler[1]=SDLK_DOWN;
    perso->controler[2]=SDLK_RIGHT;
    perso->controler[3]=SDLK_LEFT;
}

void afficher_perso(SDL_Surface *screen,Personne perso)
{	
	SDL_BlitSurface(perso.image_p,NULL,screen,&perso.pos_perso);
}

void deplacer_perso(Personne *perso,SDL_Event event, background back,SDL_Surface*screen)
{	
    if(perso->pos_perso.x<0)perso->pos_perso.x=4;
    else if(perso->pos_perso.x+perso->pos_perso.w>screen->w)perso->pos_perso.x=screen->w-perso->pos_perso.w-10;
    if(perso->pos_perso.y<0)perso->pos_perso.y=5;
    int vitesse=2;
          switch(event.type)
            {
                case SDL_KEYDOWN:

                        
                        if(event.key.keysym.sym==perso->controler[0])
                        {
                            perso->pos_perso.y=perso->pos_perso.y-2;
                         }
                        else if(event.key.keysym.sym==perso->controler[1])
                            perso->pos_perso.y=perso->pos_perso.y+2;
                         
                        else if(event.key.keysym.sym==perso->controler[2])
                            {
                            if(perso->pos_perso.x+perso->pos_perso.w<screen->w)
                            perso->pos_perso.x=perso->pos_perso.x+2;
                            }

                        else if(event.key.keysym.sym==perso->controler[3])
                            {
                            if (perso->pos_perso.x>5)
                            {
                                perso->pos_perso.x=perso->pos_perso.x-2;
                            }
                            }
             }
}


void free_perso(Personne perso)
{
	SDL_FreeSurface(perso.image_p);
}