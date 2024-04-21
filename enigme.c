#include"enigme.h"
#define nombre_de_question 3

/**
* @brief To know if the user is in 
* @param pos enigme
* @param x int
* @param y int
* @return int
*/
int input(SDL_Rect pos,int x,int y){
if(x>pos.x&&x<pos.x+pos.w&&y>pos.y&&y<pos.y+pos.h)
return 1;
return 0;
}
//initialisation
/**
* @brief To initialize the enigme.
* @param *e enigme
* @param *nomfichier
* @return Nothing
*/
void initialisation_enigme(enigme*e,char*nomfichier){
    init_timer(e); 


    e->enigme=1;        
    e->background=IMG_Load("./source/m_enigme_back.png");
    if(!e->background)printf("error background cannot be loaded\n");
    e->img_fail=IMG_Load("./source/failed.png");
    if(!e->img_fail)printf("error fail.png cannot be loaded\n");
    e->img_passed=IMG_Load("./source/pass.png");
    if(!e->img_passed)printf("error passed.png cannot be loaded\n");
    e->animation_background.x=0;
    e->animation_background.y=0;
    e->animation_background.w=e->background->w;
    e->animation_background.h=e->background->h/42;
    e->animation_timer=SDL_GetTicks();
    e->question=0;              
    for(int i=0;i<3;i++)
        e->img_reponse[i]=NULL; 
    
    int taille_font_reponse=25; 
    int taille_font_question=35;

    e->font_question=TTF_OpenFont("./source/Norse.ttf",taille_font_question);
    e->font_reponse=TTF_OpenFont("./source/RobotoSlab-VariableFont_wght.ttf",taille_font_reponse);
    e->pos_question.x=e->animation_background.w/6;   
    e->pos_question.y=e->animation_background.h/3;

    for(int i=0;i<3;i++){
        e->pos_reponse[0].x=0;
        e->pos_reponse[0].y=0;
    }

    e->historique=NULL; 

    e->duree_question=30;      
    e->duree_reponse=0;        

    e->nombre_question=0;      
    e->reponse=0;               
    e->question=0;              
    e->solution=0;              
    e->permission=0;            

    e->color_question.r=255;
    e->color_question.g=255;      
    e->color_question.b=255;

    e->color_reponse.b=0;
    e->color_reponse.g=255;       
    e->color_reponse.r=255;
    
    FILE*F=fopen(nomfichier,"r");
    char temp[255];
    while(fscanf(F,"%99[^'\n']\n%99[^'\n']\n%99[^'\n']\n%99[^'\n']\n%99[^'\n']\n",temp,temp,temp,temp,temp)!=EOF)//yakra el ligne kemel
        e->nombre_question++;
    fclose(F);
                            

}

/**
* @brief To initialize the timer.
* @param *e enigme
* @return Nothing
*/

void init_timer(enigme*e){
    e->timer=SDL_GetTicks();//yatiik el temp meli bdiit tkhadeem el prog
    e->img_timer=IMG_Load("./source/timer.png");
}


/**
* @brief genererEnigme.
* @param *e enigme
* @param *nomfichier
* @return Nothing
*/
void genererEnigme(enigme*e, char*nomfichier)
{
    //srand(time(NULL));
    if(e->nombre_question==0)printf("il n'y a pas de question dans la liste\n");
    else{
    e->duree_reponse=0;


    int random_value=rand()%e->nombre_question;    //genaration ta random
    int nmb_deja_repondu=nombre_question_deja_repondu(e->historique);//kadeeh men sou2eel jawabeet aliih
                    
    if(nmb_deja_repondu< e->nombre_question)
    {
        e->timer=SDL_GetTicks();     //timer commence   
        e->permission=1;             //joueuer maintenant est 
                                     //capable de repondre
        e->duree_reponse=0;          //initialise compteur
        e->reponse=0;                //reponse d'utilisateur
    while(verification_historique(e->historique,random_value))
    {
        srand(time(NULL));
        random_value=rand()%e->nombre_question;     //boucle justqu'a elle 
                                                    // a une question non repondu
    }
    e->question=random_value;
    e->historique=ajouter_historique(e->historique,e->question);//nhotouh fel hist

    

    get_detaille_du_question(nomfichier,e->question,e->question_text,e->reponse_text,&e->solution);

    if(e->img_question)SDL_FreeSurface(e->img_question);
    e->img_question=TTF_RenderText_Blended(e->font_question,e->question_text,e->color_question);    

    for (int i = 0; i < 3; i++){
        if(e->img_reponse[i])SDL_FreeSurface(e->img_reponse[i]);
        e->img_reponse[i]=TTF_RenderText_Blended(e->font_reponse,e->reponse_text[i],e->color_reponse);//text tconvertiih taswira
    }
    //la premier question aura au dessous le question de facon automatique
    //si on change les cordonnes de la question les cordonnes de les reponses
    // seront changées
    e->pos_reponse[0].x=e->pos_question.x;
    e->pos_reponse[0].y=e->pos_question.y+e->img_question->h+30;
            
    if(e->img_reponse[0]->w<(e->img_question->w/2))
        e->pos_reponse[1].x=e->pos_reponse[0].x+e->img_question->w/2;
    else
        e->pos_reponse[1].x=e->pos_reponse[0].x+e->img_reponse[0]->w+40;
    e->pos_reponse[1].y=e->pos_reponse[0].y;
    
    e->pos_reponse[2].x=e->pos_reponse[0].x;
    if(e->img_reponse[0]->h>e->img_reponse[1]->h)
        e->pos_reponse[2].y=e->pos_reponse[0].y+e->pos_reponse[0].h+80;
    else 
        e->pos_reponse[2].y=e->pos_reponse[0].y+e->pos_reponse[1].h+80;
    
    
    }else{

    }
    e->reponse=0;
    }
}
/**
* @brief afficher Enigme
* @param e enigme*
* @param screen SDL_Surface*
* @return Nothing
*/
void afficherEnigme(enigme e, SDL_Surface*screen){
    SDL_BlitSurface(e.background,&e.animation_background,screen,NULL);
    SDL_BlitSurface(e.img_question,NULL,screen,&e.pos_question);
    for (int i = 0; i <3; i++)
        SDL_BlitSurface(e.img_reponse[i],NULL,screen,&e.pos_reponse[i]);
    afficher_timer(e,screen);
}
void animation_background(enigme*e){
    if(SDL_GetTicks()-e->animation_timer>50){
    int nombre_image=42;
    int height=e->background->h/nombre_image;
    e->animation_background.y+=height;
    if(e->animation_background.y>=e->background->h)
        e->animation_background.y=0;
    e->animation_timer=SDL_GetTicks();

    }
}


question_historique*verification_historique(question_historique*neoud,int valeur){
    if(!neoud)return NULL;
    if(neoud->nombre==valeur)return neoud;//recursiviter
    return verification_historique(neoud->suivant,valeur);
}
int nombre_question_deja_repondu(question_historique*noeud){
    int nmb=0;
    while (noeud!=NULL)
    {
        noeud=noeud->suivant;
        nmb++;
    }return nmb;
    
}
question_historique*ajouter_historique(question_historique*noued,int valeur){
    if(noued){
        noued->suivant=ajouter_historique(noued->suivant,valeur);
        return noued;}    
    question_historique*temp=malloc(sizeof(question_historique));
    temp->nombre=valeur;
    temp->suivant=NULL;
    return temp;
}

void get_detaille_du_question(char*nomfichier,int question,char*question_txt,char reponse[][100],int*reponse_indice)
{
    int recherche=0;
    FILE*F=fopen(nomfichier,"r");
    if(!F)printf("error F\n");
    while (question>=recherche&&fscanf(F,"%99[^'\n']\n%99[^'\n']\n%99[^'\n']\n%99[^'\n']\n%d\n",question_txt,reponse[0],reponse[1],reponse[2],reponse_indice)!=EOF)
        {recherche++;       //chercher le question
        //printf("question d'indice:%d\nquestion:%s\nreponse1:%s\nreponse2:%s\nreponse3:%s\nindeice:%d\n",question,question_txt,reponse[0],reponse[1],reponse[2],*reponse_indice);
        }
}


void afficher_timer(enigme e,SDL_Surface*screen){
    SDL_Rect position_screen={screen->w-e.img_timer->w/5,10};//cordonnes de timer
                        //position_screen.x=screen->w-e.img_timer->w/5
                        //position_screen.y=10
    int duree=SDL_GetTicks()-e.timer;
    int temp=30;
    int pourcentage=(e.duree_reponse*100)/(e.duree_question*1000);
    SDL_Rect position_animation={0,0,e.img_timer->w/5,e.img_timer->h/2};
                        //ce variable nous aide a prendre un partie de spritesheet
    //printf("%d\n",pourcentage);
    if(pourcentage>=100){
        position_animation.x=e.img_timer->w-e.img_timer->w/5;
        position_animation.y=e.img_timer->h/2;
    }else{
        position_animation.x=((pourcentage/10)%5)*e.img_timer->w/5;
        position_animation.y=((pourcentage/10)/5)*e.img_timer->h/2;
    }
    SDL_BlitSurface(e.img_timer,&position_animation,screen,&position_screen);
}

void duree(enigme*e){
    if(e->permission&&e->duree_reponse<e->duree_question*1000)
        e->duree_reponse=SDL_GetTicks()-e->timer;    
}                   //si le temps n'a pas encore ecoule  et joueur n'a pas
                    // encore repondu a le question: le compteur reste marche

	
int evaluation(enigme e){
    return ((e.solution==e.reponse)&&(e.duree_reponse<(e.duree_question*1000)));     //si la reponse est vrai retour 1
}
void affich_resultat(enigme*e,SDL_Surface*screen){
    SDL_Rect position;
    int duree=SDL_GetTicks()-e->timer;
    if(evaluation(*e))
    {
        position.x=screen->w-e->img_passed->w;
        position.y=screen->h-e->img_passed->h;
        SDL_BlitSurface(e->img_passed,NULL,screen,&position);
    }else{
        position.x=screen->w-e->img_fail->w;
        position.y=screen->h-e->img_fail->h;
        SDL_BlitSurface(e->img_fail,NULL,screen,&position);
    }
}



void freeenigme(enigme*Enigme){
    if(!Enigme)return;
    if(Enigme->background)SDL_FreeSurface(Enigme->background);
    if(Enigme->img_question)SDL_FreeSurface(Enigme->img_question);
    for (int i = 0; i < 3; i++)
        if(Enigme->img_reponse[i])SDL_FreeSurface(Enigme->img_reponse[i]);
    if(Enigme->img_fail)SDL_FreeSurface(Enigme->img_fail);
    if(Enigme->img_passed)SDL_FreeSurface(Enigme->img_passed);
    if(Enigme->img_timer)SDL_FreeSurface(Enigme->img_timer);
    if(Enigme->font_question)TTF_CloseFont(Enigme->font_question);
    if(Enigme->font_reponse)TTF_CloseFont(Enigme->font_reponse);
    free_historique(Enigme->historique);
}
void free_historique(question_historique*noeud){
    question_historique*temp;//allocation dynamique 
    while (noeud)
    {
        temp=noeud;
        noeud=noeud->suivant;
        free(temp);
    }
}
