#ifndef PERSO_H
#define PERSO_H

#include <SDL/SDL.h>
#define  NUM_FRAMES 5
#define ANIMATION_DELAY 10
/
typedef struct Perso {
    SDL_Rect pos;           
    SDL_Surface *sprite;    
    int vx;                 
    int vy;                 
    int moveLeft;           
    int moveRight;          
    int moveUp;            
    int jump;               
    int jump_vel;           
    float gravity;          
    int currentFrame;       
    int numFrames;          
    int animation_timer;
    SDL_Surface *sprites[NUM_FRAMES]; 
     int crouch; 
} Perso;


void initPerso(Perso *perso, int x , int y, SDL_Surface *sprite[]) ;
void Perso_destroy(Perso *perso);
void Perso_handleEvent(Perso *perso, SDL_Event *event);
void updatePerso(Perso *perso, int x ,int y);
void Perso_render(Perso *perso, SDL_Surface *screen);
void Perso_jump(Perso *perso);
void Perso_crouch(Perso *perso) ;
void Perso_uncrouch(Perso *perso);

#endif /* PERSO_H */
