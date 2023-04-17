#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

SDL_Surface *loadImage(char *filename)
{
    SDL_Surface *image = IMG_Load(filename);
    if (image == NULL)
    {
        fprintf(stderr, "Impossible de charger l'image %s : %s\n", filename, IMG_GetError());
        exit(EXIT_FAILURE);
    }
    return image;
}

SDL_Surface *scaleImage(SDL_Surface *image, int width, int height)
{
    SDL_Surface *scaledImage = SDL_CreateRGBSurface(image->flags, width, height, image->format->BitsPerPixel, image->format->Rmask, image->format->Gmask, image->format->Bmask, image->format->Amask);
    SDL_SoftStretch(image, NULL, scaledImage, NULL);
    return scaledImage;
}