#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "image.h"
#include "perso.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 480
#define SPRITE_WIDTH 32
#define SPRITE_HEIGHT 32

int main(int argc, char *argv[])
{
Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
        music = Mix_LoadMUS("music.mp3") ;
        Mix_PlayMusic(music,-1);


    // Initialisation des variables pour l'utilisation dans le main
    SDL_Surface *screen = NULL;
    SDL_Surface *background = NULL;
    SDL_Surface *sprite = NULL;
    SDL_Surface *scaledSprite[5];
    SDL_Event event;
    int quit = 0;
    // Chargement du sprite
    SDL_Surface *sprites[5];
    sprites[0] = loadImage("Perso/cR0.png");
    sprites[1] = loadImage("Perso/cR1.png");
    sprites[2] = loadImage("Perso/cR2.png");
    sprites[3] = loadImage("Perso/cR3.png");
    sprites[4] = loadImage("Perso/cR4.png");
    scaledSprite[0] = scaleImage(sprites[0], 72, 72);
    scaledSprite[1] = scaleImage(sprites[1], 72, 72);
    scaledSprite[2] = scaleImage(sprites[2], 72, 72);
    scaledSprite[3] = scaleImage(sprites[3], 72, 72);
    scaledSprite[4] = scaleImage(sprites[4],72, 72);

    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Ouverture de la fenêtre
    screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE);
    if (screen == NULL)
    {
        fprintf(stderr, "Impossible d'ouvrir la fenêtre : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    // Chargement de l'arrière-plan
    background = loadImage("background.png");
    if (background == NULL)
    {
        fprintf(stderr, "Impossible de charger l'image de fond : %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }

    // Chargement du sprite

    int atEnd = 0;    // Has the character reached the end of the screen?
    int onSecond = 0; // Is the cracter currently on the second background?

    if (sprites == NULL)
    {
        fprintf(stderr, "Impossible de charger le sprite : %s\n", IMG_GetError());
        exit(EXIT_FAILURE);
    }

    // Création du personnage
    Perso perso;
    initPerso(&perso, 0, SCREEN_HEIGHT - 64 - SPRITE_HEIGHT, scaledSprite);

    // Boucle principale
    while (!quit)
    {
        if (!atEnd && perso.pos.x >= SCREEN_WIDTH - 72)
        {
            atEnd = 1;
        }
        if (atEnd)
        {
            initPerso(&perso, 0, SCREEN_HEIGHT - 72 - SPRITE_HEIGHT, scaledSprite);
            atEnd = 0;
        }

        // Gestion des événements
        while (SDL_PollEvent(&event))
        {
            Perso_handleEvent(&perso, &event);
            if (event.type == SDL_QUIT)
            {
                quit = 1;
            }
        }

        // Mise à jour de la position du personnage
        updatePerso(&perso, SCREEN_WIDTH, SCREEN_HEIGHT);

        // Affichage de l'arrière-plan
        SDL_BlitSurface(background, NULL, screen, NULL);

        // Affichage du personnage

        
            SDL_BlitSurface(perso.sprite, NULL, screen, &perso.pos);
        
        // Rafraîchissement de l'écran
        SDL_Flip(screen);
    }

    // Libération des surfaces
    SDL_FreeSurface(background);
    for (int i = 0; i < 5; i++)
    {
        SDL_FreeSurface(sprites[i]);
        SDL_FreeSurface(scaledSprite[i]);
    }

    // Fermeture de SDL
    SDL_Quit();

    return 0;
}
