#ifndef enigme_H
#define enigme_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define screen_width 1080
#define screen_height 607

/**
* @struct question_historique
* @brief list_des_questions_deja_repondu
*/
typedef struct question_historique question_historique;
struct question_historique
{
    int nombre;
    question_historique*suivant;
};


/**
* @struct enigme
* @brief enime
*/
typedef struct{
    SDL_Surface*background;
    SDL_Rect pos_reponse[3],pos_question;
    SDL_Color color_reponse,color_question;
    SDL_Surface*img_question,*img_reponse[3],*img_fail,*img_passed;
    SDL_Rect animation_background;
    Uint32 animation_timer;
    question_historique*historique;
    
    TTF_Font*font_question,*font_reponse;
    int reponse,question,solution,nombre_question;
    char reponse_text[3][100],question_text[100];
    int reponse_clicked[3];
    int enigme;

    Uint32 timer;

    int duree_question,duree_reponse;
    SDL_Surface*img_timer;
    int permission;
}enigme;

void initialisation_enigme(enigme*e,char*nomfichier);
void genererEnigme(enigme*e,char*nomfichier);
question_historique*verification_historique(question_historique*neoud,int valeur);
int nombre_question_deja_repondu(question_historique*noeud);
question_historique*ajouter_historique(question_historique*noued,int valeur);
void get_detaille_du_question(char*nomfichier,int question,char*question_txt,char reponse[][100],int*reponse_indice);
void afficherEnigme(enigme e, SDL_Surface*screen);
void animation_background(enigme*e);
void free_historique(question_historique*noeud);
void freeenigme(enigme*Enigme);

int evaluation(enigme e);
void affich_resultat(enigme*e,SDL_Surface*screen);

void init_timer(enigme*e);
void afficher_timer(enigme e,SDL_Surface*screen);
void duree(enigme*e);

#endif
