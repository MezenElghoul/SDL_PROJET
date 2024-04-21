#include "joueur.h"
void initperso(Personne *p,int x,int y)
{
	p->colonne=10;		//nombre d'image fi ligne wahda barka fi spritesheet
	p->ligne=5;			//.... fi colone wahda  (check il spritesheet)
	p->position.x=x;	// position win bich yahbet
	p->position.y=y;
	p->pos_vie.x=000;	//position mta3 il affichage mta3 li9loub
	p->pos_vie.y=30;
	p->vie=3;
	p->direction=1;		//il charactere ana chira m9abel
	p->num=0;			//il awel taswira fil sprtiesheet
	p->vitesse_x=0;		
	p->acceleration=0.002; //il constant il initial
	p->acceleration_x=0;	//charactere mizel we9if
	p->vitesse_Max_x=2;		//vitesse maximum
	p->acceleration_initial_y=0.008;
	p->duree_anim=SDL_GetTicks();

	p->spritesheet[1]=IMG_Load("./player/pers.png");
	if(p->spritesheet[1]==NULL)
		printf("error spritehseet[0]\n");
	p->spritesheet[0]=IMG_Load("./player/pers1.png");
	if(p->spritesheet[0]==NULL)
		printf("error spritehseet[1]\n");
	p->animation.x=0;
	p->animation.y=0;
	p->animation.w=p->spritesheet[0]->w/p->colonne;	//3oreth mta3 taswira wahda
	p->animation.h=p->spritesheet[0]->h/p->ligne;
	initialiserScore(&p->score);	//score 0
	p->vitesse_y=0;
	p->vitesse_saut=2.5;				//constant mt3 il jump(koul maynaguez bil valeur hethi)
	p->acceleration_y=0;


	p->isjumping=0;					//il charactere mahouch 9a3id ynaguez


	p->charactere=p->spritesheet[0];		//il charactere hatineh yoghzer 3alimin par defaut
	p->afficher_vie[0]=IMG_Load("./player/heart.png");
	p->afficher_vie[1]=IMG_Load("./player/heart.png");
	p->afficher_vie[2]=IMG_Load("./player/heart.png");
	if(p->afficher_vie[0]==NULL|| p->afficher_vie[0]==NULL|| p->afficher_vie[0]==NULL)
		exit(EXIT_FAILURE);

    p->controler[0]=SDLK_UP;
    p->controler[1]=SDLK_DOWN;
    p->controler[2]=SDLK_RIGHT;
    p->controler[3]=SDLK_LEFT;

}
void initialiserScore(  Score *score )
{
	char chaine[20];
	SDL_Color couleur ={255,255,255};
	
	score->posScore.x=50;
	score->posScore.y=600;

	score->police = TTF_OpenFont("./player/score.ttf", 50);
	if(score->police==NULL){
		printf("ERROR POLICE ./player/score.ttf\n");
	}
	
	score->scoreActuel=0;			//matnajamech taffichi score direct(entier walla chaine) lezem nconvertiweh limage
	sprintf(chaine,"%d", score->scoreActuel);	//score wallet chaine de charactere
	score->texteScore=TTF_RenderText_Blended(score->police ,chaine, couleur);		
			//minba3d wallet image
}
void afficherScore(SDL_Surface *screen, Score *score)
{
	SDL_Color couleurNoire ={255,255,255};
	char chaine[20];
	score->scoreActuel+=1;	//nafess le7keya
	sprintf(chaine,"%d", score->scoreActuel);	// chaine de caractere
	SDL_FreeSurface(score->texteScore);		//nfase5 il image 9dima mta3 il score
	score->texteScore =TTF_RenderText_Blended(score->police,chaine, couleurNoire);
	SDL_BlitSurface(score->texteScore, NULL, screen, &score->posScore);
		//naffichi
}
void afficheperso(Personne p,SDL_Surface *screen)
{
	SDL_BlitSurface (p.charactere,&p.animation,screen,&p.position);
}
void affichiervie(Personne p, SDL_Surface *screen){
	SDL_Rect position_vie={
				p.pos_vie.x,
				p.pos_vie.y
	};
	for (int i = 0; i < p.vie; i++){
		SDL_BlitSurface(p.afficher_vie[i],NULL,screen,&position_vie);
		position_vie.x+=p.afficher_vie[i]->w; //nzidou 3oreth mta3 taswira barka bich ykounou wra b3athhoum
}
}

void moveperso(Personne *p,Uint32 dt)
{
maj_vitesse(p,dt);
		if (p->vitesse_x!=0)
		{
			if(p->direction==1)			//ken il charactere yejri 3alimin
				p->position.x+=p->vitesse_x*dt;	//yet7arek 3alimin
			else if(p->direction==-1)
				p->position.x-=p->vitesse_x*dt;
		}



}
void maj_vitesse(Personne*p,Uint32 dt){
	if(p->acceleration_x!=0)		//ken il famma acceleration 
	p->acceleration_x*=1.05;		//n9awi fil acceleration b 5%
	p->vitesse_x+=p->acceleration_x*dt;	//vitesse yzid
	if(p->vitesse_Max_x < p->vitesse_x)	//ken il vitesse fet  vitesse maximal
	{
		p->vitesse_x=p->vitesse_Max_x;	//vitesse yo93ed maximal
		p->acceleration_x=0;
	}
	if(p->acceleration_x<0 && p->vitesse_x<=0 ){	//il deceleration
				p->acceleration_x=0;					//ken il acceleration w zeda il vitesse negative wa9tha ne9if
				p->vitesse_x=0;
		}
		if(p->position.x<0)	//charactere mayo5rejech mil ecran
			p->position.x=0;
		
}
void animerperso(Personne *P )
{
	
	if(P->direction==-1)
        P->charactere=P->spritesheet[0];        //charactere m9abel 3alisar
    else if(P->direction==1)
        P->charactere=P->spritesheet[1];       //charactere m9abel 3alimin

    if(SDL_GetTicks()-P->duree_anim > 100){		//ken il duree mta3 il animation wahda fetit 100millisecond
                P->num++;						//net3adda ili ba3dou
            }

	if(P->vitesse_y>0){                   //itha ken il charactere habet
            if( P->num<= 46 || P->num > 50 )	
			{
                P->num=47;
            }
        }
	else if(P->vitesse_y<0){                   //itha ken il charactere tale3 il fou9
            if( P->num<=40 || P->num > 46 )
			{
                P->num=41;
            }
        }
	else { //vitesse_y ==0
		if(P->vitesse_x==0 && P->num > 10)
            {
                        P->num= 1 ;     // wa9ef
            }
		else if(P->vitesse_x!=0 && P->num <= 10 || P->num> 40)
            {
                        P->num= 11 ;     // yejri
            }
	}

	int ligne=(P->num-1)/P->colonne;		//hethi na3ref beha 9adech min marra 5raj mil spritesheet
	int colonne=(P->num-1)%P->colonne;		//hethi ken il num fet colonne ywalli yarja3
	P->animation.x=colonne * P->animation.w; //exemple: num =11(image numero 18) colonne 10 : 11 na9samha 3ala 10 il reste howa il taswira fi enehi collum
	P->animation.y=ligne * P->animation.h;	//exemple: 11-1 % 10 ==> 0 :il taswira fi awel il colonne wil 11-1 / 10 = 1 : il taswira appartient fil theni ligne 

}
void saut(Personne *p, Uint32 dt, int posinit)
{
	if(p->isjumping==1)		//ken il charactere 9e3id ynaguez
	{
		p->vitesse_y+=p->acceleration_y*dt;
		int pas=p->vitesse_y*dt;
		if(p->position.y+pas<posinit)	//ken mizelit famma distance 
			{
				p->position.y+=pas;		//zid yahbet
				printf("downing");
			}
		else{		//sinon saye ye9if
			p->position.y=posinit;

			p->vitesse_y=0;
			p->acceleration_y=0;
			p->isjumping=0;
			}
	}

}
	
void liberer_perso(Personne*p){
	SDL_FreeSurface(p->spritesheet[0]);
	SDL_FreeSurface(p->spritesheet[1]);
	SDL_FreeSurface(p->afficher_vie[0]);
	SDL_FreeSurface(p->afficher_vie[1]);
	SDL_FreeSurface(p->afficher_vie[2]);
	if(p->score.texteScore !=NULL)
	SDL_FreeSurface(p->score.texteScore);
}



