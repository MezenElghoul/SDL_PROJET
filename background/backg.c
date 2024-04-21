#include "backg.h"


void initBack(background*b){

	b->img_background=IMG_Load("./background/sheet.png");
		if(!b->img_background)printf("%s\n","error failed to load background");
	b->mask_background=IMG_Load("./background/mask1.png");
		if(!b->mask_background)printf("%s\n","error failed to load mask");
	b->pos_background.x=0;
	b->pos_background.y=0;
	b->camera.x=0;
	b->camera.y=280;

	b->anime.x=0;
	b->anime.y=0;
	b->anime.h=b->mask_background->h;	
	b->anime.w=b->mask_background->w;

	b->temp=0;
	b->son=Mix_LoadMUS("./background/music.mp3");
	if(!b->son)printf("no sound\n");
	Mix_PlayMusic(b->son,-1);
	int volume=10;
	Mix_VolumeMusic(volume);
}
void afficher_back (background back, SDL_Surface *ecran)
{
		back.anime.x=back.camera.x;
		back.anime.y+=back.camera.y;
SDL_BlitSurface(back.img_background,&back.anime,ecran,NULL);
}
void affiche_multiscreen(background back,Personne p,background back2,Personne p2,SDL_Surface*screen){
	afficher_back(back,screen);
	afficheperso(p,screen);

SDL_Rect translation_background={screen->w/2,
0}; 
SDL_Rect translation_player={p2.position.x+screen->w/2,p2.position.y};	
		back2.anime.x=back2.camera.x;
		back2.anime.y+=back2.camera.y;
SDL_BlitSurface(back2.img_background,&back2.anime,screen,&translation_background);
SDL_BlitSurface(p2.charactere,&p2.animation,screen,&translation_player);
	SDL_Rect position_vie={
				screen->w/2+p.pos_vie.x,
				p.pos_vie.y
	};
	for (int i = 0; i < p.vie; i++){
		SDL_BlitSurface(p.afficher_vie[i],NULL,screen,&position_vie);
		position_vie.x+=p.afficher_vie[i]->w; //nzidou 3oreth mta3 taswira barka bich ykounou wra b3athhoum
}
}
void affichemask(background back,SDL_Surface*screen){
	SDL_Rect position={-back.camera.x,-back.camera.y};
	SDL_BlitSurface(back.mask_background,NULL,screen,&position);
}


void scrolling (background*back,int direction,int pas,SDL_Surface *screen)
{
if (direction ==0)			//direction a droite
	{
		if((back->camera.x+screen->w)<back->mask_background->w)	//ken il camera mizelit mafettitch il background 
				back->camera.x+= pas;	
		else 
			back->camera.x=back->mask_background->w-screen->w;	//sinon nafichi e5ir il map
	}

else if (direction ==1)		//gauche
{
	if(back->camera.x-pas>0)	//ken mizelt mawsiltech lchefa 3allimin mta3 il map
		back->camera.x-=pas;
	else 
		back->camera.x=0; 
}
else if (direction ==2){		//scrolling verticale
	if(pas>0){					//scrolling vers louta
	    if(back->camera.y+pas+screen->h<back->mask_background->h)		//ken il camera.h + toul mta3 il ecran asgher mil toul il stage
			back->camera.y+= pas;
		else back->camera.y=back->mask_background->h-screen->h;			//sinon 5rajna mil level milouta => donc nsal7ouha
}else{					//srolling il fo9
	if(back->camera.y+pas<0)				//ken 5rajna mil map
		back->camera.y=0;				
	else 
		back->camera.y+= pas;					//sinon najmou nescroliw il fo9
}
}
}
void liberation_background(background*b){
	SDL_FreeSurface(b->img_background);
	SDL_FreeSurface(b->mask_background);
	Mix_FreeMusic(b->son);
}
void liberation(background*b,Personne*P){
	liberation_background(b);
	SDL_FreeSurface(P->charactere);
}
void animation(background*b){
	if(SDL_GetTicks()-b->temp>300){
		b->anime.y+=b->img_background->h/nombre_imag_sprite;
		if(b->anime.y>=b->img_background->h){
			b->anime.y=0;
		}
	b->temp=SDL_GetTicks();
	}
}
