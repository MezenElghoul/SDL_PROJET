#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "joueur.h"
int main(int argc, char *argv[])
{
    Personne p;
    int quitter=0;
    Uint32 dt, t_prev;
    SDL_Surface *screen=NULL;
    SDL_Surface *background=NULL;


    SDL_Event event;
    TTF_Init();
    SDL_Init(SDL_INIT_VIDEO);
    screen=SDL_SetVideoMode (SCREEN_W,SCREEN_H,32, SDL_HWSURFACE | SDL_DOUBLEBUF) ;
    SDL_WM_SetCaption("perso",NULL);
    background=IMG_Load("niveau.png");
    initperso(&p,20,400);

int posinit=0;
    while(quitter==0)
    {
    t_prev = SDL_GetTicks();
    SDL_BlitSurface (background,NULL,screen,NULL);

    afficherScore(screen,&p.score);
    affichiervie(p,screen);

    	afficheperso(p,screen);
        while((SDL_PollEvent(&event)))
        {
        
        	switch (event.type)
		{
			
			case SDL_QUIT:
				quitter=1;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
        			{
					case SDLK_ESCAPE:
						quitter=1;
						break;
            		case SDLK_UP:
						if(p.isjumping==0){
            					p.isjumping=1;
								p.vitesse_y=-p.vitesse_saut;
								posinit=p.position.y;
            					p.acceleration_y=p.acceleration_initial_y;
								printf("accele %f\t",p.acceleration_y);
						
						}
            					break;
                    case SDLK_LEFT:
                        p.direction=-1;
                        p.acceleration_x=p.acceleration;     
                        break;
                    case SDLK_RIGHT:
                        p.direction=1;
                        p.acceleration_x=p.acceleration;
                        break;
            		case SDLK_SPACE:
            				p.acceleration=0.1;
                			break;
                			
                				
                	}break;		
            case SDL_KEYUP:
				if(event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT )
                    	p.acceleration_x=-p.acceleration;	
 				break;		
              	}
			}


	animerperso(&p);
	dt = SDL_GetTicks() - t_prev;
	moveperso(&p,dt);
	saut(&p,dt,posinit);
	//}
			
			printf("x:%d y:%d vx:%.2f vy:%.2f\n",p.position.x,p.position.y,p.vitesse_x,p.vitesse_y);
	    	SDL_Flip(screen);
    	SDL_Delay(50);
    	    }
    
liberer_perso(&p);
    SDL_Quit();
return 0;
}
