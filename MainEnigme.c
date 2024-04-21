#include"enigme.h"

/**
* @file MainEnigme.c
* @brief tache enigme
* @author mezen ghoul
* @version 1
* @date May 09, 2023
*
* Testing program for background scrollilng
*
*/

int main(){
SDL_Init (SDL_INIT_EVERYTHING);
TTF_Init();
SDL_Surface *screen;
screen= SDL_SetVideoMode(screen_width,screen_height,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
SDL_WM_SetCaption("enigme",NULL);
 /*if(Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024)==-1)
    {
        printf("FAIL %s\n",Mix_GetError());
    }*/

enigme Enigme;
Uint32 frames=20,start_loop=0;
srand(time(NULL));
initialisation_enigme(&Enigme,"question.txt");
genererEnigme(&Enigme,"question.txt");
SDL_Event event;
SDL_Rect mouse={0,0};
while (Enigme.enigme)
{
    start_loop=SDL_GetTicks();
    while (SDL_PollEvent(&event))
    {
        switch (event.type){
                case SDL_QUIT:
                    Enigme.enigme=0;
                    break;
                case SDL_MOUSEMOTION:
                    mouse.x=event.motion.x;
                    mouse.y=event.motion.y;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if(Enigme.permission)
                    for(int i=0;i<3;i++){
                        if((mouse.x>Enigme.pos_reponse[i].x)&&(mouse.x<(Enigme.pos_reponse[i].x+Enigme.img_reponse[i]->w)))
                            if((mouse.y>Enigme.pos_reponse[i].y)&&(mouse.y<(Enigme.pos_reponse[i].y+Enigme.img_reponse[i]->h)))
                                {
                                    Enigme.reponse=i+1;
                                    Enigme.permission=0;
                                    break;
                                    //printf("%d\n",mouse.x);
                                }
                    }   
                break;
                case SDL_KEYDOWN : 
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        Enigme.enigme=0;
                        break;
                    case SDLK_LEFT:
                    case SDLK_e:
                    if(nombre_question_deja_repondu(Enigme.historique)<Enigme.nombre_question)
                        genererEnigme(&Enigme,"question.txt");
                    else Enigme.enigme=0;
                        break;
                    case SDLK_a:
                        if(Enigme.permission){
                            Enigme.reponse=1;
                            Enigme.permission=0;
                        }
                        break;
                    case SDLK_b:
                            if(Enigme.permission){
                                Enigme.reponse=2;
                                Enigme.permission=0;
                            }
                            break;
                    case SDLK_c:
                        if(Enigme.permission){
                                Enigme.reponse=3;
                                Enigme.permission=0;
                            }
                            break;
                    default:
                        if(Enigme.permission)
                            Enigme.reponse=0;
                        break;
                    }
        }
    }
    duree(&Enigme);
    afficherEnigme(Enigme,screen);
    animation_background(&Enigme);
    if(Enigme.reponse||(Enigme.duree_reponse>(Enigme.duree_question*1000))){
        affich_resultat(&Enigme,screen);
    }
    SDL_Flip (screen);
    uint32_t delay=SDL_GetTicks()-start_loop;
    //printf("%d\n",delay);
    if(delay>frames)printf("slow\n");
    else if(delay<frames)SDL_Delay(frames-delay);
}
freeenigme(&Enigme);
TTF_Quit;
SDL_Quit;
return 0;}
