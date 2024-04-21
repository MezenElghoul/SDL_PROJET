#include "./background/backg.h"
#include "./player/joueur.h"
#include "enigme/enigme.h"
int jeu(SDL_Surface*screen,int mode);
int main(void){
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	SDL_Surface*screen=SDL_SetVideoMode(SCREEN_W,SCREEN_H,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
	if(screen==NULL)
	{
		printf("unable to set video mode:%s\n",SDL_GetError());
		return 1;
	}
	if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024)==-1)printf("FAIL AUDIO %s\n",Mix_GetError());
			//1 = multijoueur
			//0= wahdou
	jeu(screen,0);
	
	Mix_CloseAudio();
	SDL_Quit();
	return 0;
}

int jeu(SDL_Surface*screen,int mode)
{	
	int continuer=1;
	int quiz=1;
	background back,back2;
	Personne perso,perso2;
    SDL_Event event;
 

	uint32_t dt,chrono;
	SDL_Surface*partage_ecran=screen;
	int posinit;
	initBack(&back);
	SDL_Rect position_enigme={400,600};
	initperso(&perso,20,400);
	initialiserScore(&perso.score);
	if(mode){
		partage_ecran=SDL_CreateRGBSurface(0,screen->w/2,screen->h,32,0,0,0,0); //creation fenetre bchtar ecran
		initBack(&back2);
		initperso(&perso2,20,400);
		perso2.controler[0]=SDLK_z;
		perso2.controler[1]=SDLK_s;
		perso2.controler[2]=SDLK_d;
		perso2.controler[3]=SDLK_q;
	}

	while (continuer)
	{	
		chrono=SDL_GetTicks();
		while((SDL_PollEvent(&event)))
        {
        
        	switch (event.type)
		{
			case SDL_QUIT:
				continuer=0;
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
        			{
					case SDLK_ESCAPE:
						continuer=0;
						break;
            		case SDLK_UP:
						if(perso.isjumping==0){
            					perso.isjumping=1;
								perso.vitesse_y=-perso.vitesse_saut;
								posinit=perso.position.y;
            					perso.acceleration_y=perso.acceleration_initial_y;
						}
            					break;
                    case SDLK_LEFT:
                        perso.direction=-1;
                        perso.acceleration_x=perso.acceleration;     
                        break;
                    case SDLK_RIGHT:
                        perso.direction=1;
                        perso.acceleration_x=perso.acceleration;
                        break;
            		case SDLK_SPACE:
            				perso.acceleration_x*=0.1;
                			break;


                	case SDLK_z:
						if(perso2.isjumping==0){
            					perso2.isjumping=1;
								perso2.vitesse_y=-perso.vitesse_saut;
								posinit=perso2.position.y;
            					perso2.acceleration_y=perso2.acceleration_initial_y;
						}
            					break;
                    case SDLK_q:
                        perso2.direction=-1;
                        perso2.acceleration_x=perso2.acceleration;     
                        break;
                    case SDLK_d:
                        perso2.direction=1;
                        perso2.acceleration_x=perso2.acceleration;
                        break;
            		case SDLK_LSHIFT:
            				perso2.acceleration_x*=0.1;
                			break;		
                				
                	}break;		
            case SDL_KEYUP:
				if(event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT )
                    	perso.acceleration_x=-perso.acceleration;	
						printf("stop\n");
				if(event.key.keysym.sym == SDLK_d || event.key.keysym.sym == SDLK_q )
                    	perso2.acceleration_x=-perso2.acceleration;	
						printf("stop\n");
 				break;		
        }
			}	

 			if(mode){
				affiche_multiscreen(back,perso,back2,perso2,screen);	//affichage mta3 les deux ecrans
				afficherScore(screen,&perso.score);
    			affichiervie(perso,screen);
			}
			else
				{
						
					afficher_back(back,partage_ecran);
					afficheperso(perso,partage_ecran);
					afficherScore(partage_ecran,&perso.score);
    				affichiervie(perso,partage_ecran);
					
				}
			printf("person: x:%d y:%d vx:%f vy:%f accx:%f accv:%f backg:x:%d y:%d\n",perso.position.x,
								perso.position.y,
								perso.vitesse_x,
								perso.vitesse_y,
								perso.acceleration_x,
								perso.acceleration_y,
								back.camera.x,
								back.camera.y
								);
 			animation(&back);
			animerperso(&perso);
				dt = SDL_GetTicks() - chrono;
				
				
				
				if(perso.position.x>partage_ecran->w/4 && back.camera.x+partage_ecran->w<back.mask_background->w && perso.direction==1)
					{printf("%d",back.camera.x+partage_ecran->w-back.mask_background->w);
						scrolling(&back,0,perso.vitesse_x*dt,partage_ecran);
						maj_vitesse(&perso,dt);
					}
				else if(back.camera.x!=0&&perso.position.x<partage_ecran->w/4 && perso.direction==-1)
					{
						scrolling(&back,1,perso.vitesse_x*dt,partage_ecran);
						maj_vitesse(&perso,dt);
					}
				else
					if(perso.position.x+perso.animation.w>partage_ecran->w)
						perso.position.x=partage_ecran->w-perso.animation.w;
					else moveperso(&perso,dt);				
					
				saut(&perso,dt,posinit);

				scrolling(&back,2,perso.vitesse_y*dt,partage_ecran);

			if(mode){
				animation(&back2);
				animerperso(&perso2);
				if(perso2.position.x>partage_ecran->w/4 && back2.camera.x+partage_ecran->w<back2.mask_background->w && perso2.direction==1)
					{
						scrolling(&back2,0,perso2.vitesse_x*dt,partage_ecran);
						maj_vitesse(&perso2,dt);
					}
				else if(back2.camera.x!=0&&perso2.position.x<partage_ecran->w/4 && perso2.direction==-1)
					{
						scrolling(&back2,1,perso2.vitesse_x*dt,partage_ecran);
						maj_vitesse(&perso2,dt);
					}
				else
					if(perso2.position.x+perso2.animation.w>partage_ecran->w)
						perso2.position.x=partage_ecran->w-perso.animation.w;
					else moveperso(&perso2,dt);				
					
				saut(&perso2,dt,posinit);

				scrolling(&back2,2,perso2.vitesse_y*dt,partage_ecran);
			}
			//affichemask(back,screen);

			// ENIGME
			if(quiz==1 &&perso.position.x+back.camera.x>position_enigme.x )
				{
					Enigme(screen);
					quiz=0;
		}
			SDL_Flip(screen);
			SDL_Delay(20);
	}


	liberation(&back,&perso);
	if(mode)liberation(&back2,&perso2);
	Mix_CloseAudio();
	SDL_Quit();
	return 0;
}

