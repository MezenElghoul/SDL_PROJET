#ifndef HEADER_H_INCLUDED
#define HEADER_H_INCLUDED
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>

#ifndef SCREEN_W
#define SCREEN_W 1200
#define SCREEN_H 720
#endif
typedef struct
{
   	SDL_Surface *texteScore;
   	SDL_Rect posScore;
   	int scoreActuel;
   	TTF_Font *police;
}Score;

typedef struct
{
    SDL_Rect position;      //position mta3 il charactere
    SDL_Rect animation;
    SDL_Surface *charactere;    //spritesheet ili ena feha tawa (ili 9e3id ne5dem beha)
    SDL_Surface*spritesheet[2]; //les deux spritesheet fil reserve
    int colonne,ligne;
    Uint32 duree_anim;          //delay mta3 il animation
    int direction;              //direction ken ya 1 wala -1
    int num;                    //numero mta3 il image fil spritesheet
    double vitesse_Max_x;       //vitesse maximum horizental
    double acceleration;        //valeur acceleration par defaut
    double vitesse_x;           //vitesse x
    double acceleration_x;
    double vitesse_saut;        //(constant)vitesse initial mta3 il saut
    double acceleration_initial_y;  //
    double vitesse_y;            
    double acceleration_y; 
    int controler[4];
    SDL_Rect pos_vie;           //positio mta3 affichage mta3 li9loub
    SDL_Surface *afficher_vie[3];       //tsawer mta3 il 9loub
    Score score;                //affichage score   
    int vie;                    //nombre de vie
    int isjumping;              //variable na3rfou bih ken il charactere ynaguez walla le
}Personne;

void initperso(Personne *p,int x,int y);
void afficheperso(Personne p,SDL_Surface *screen);

void initialiserScore(  Score *score );
void afficherScore(SDL_Surface *screen, Score *score);

void affichiervie(Personne p, SDL_Surface *screen);
void animerperso(Personne *p );
void moveperso(Personne *p, Uint32 dt);
void maj_vitesse(Personne*p,Uint32 dt); //zidneha 5ater il moveperso() manajmouch n3aytoulha ki til9aha famma scrolling
void saut(Personne *p, Uint32 dt, int posinit);
void liberer_perso(Personne*p);
#endif
