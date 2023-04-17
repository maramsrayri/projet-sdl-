#ifndef IMAGE_H
#define IMAGE_H

#include <SDL/SDL.h>

//chargement des images 
SDL_Surface *loadImage(char *filename);
//modification sur la taille de l'image
SDL_Surface *scaleImage(SDL_Surface *image, int width, int height);

#endif

