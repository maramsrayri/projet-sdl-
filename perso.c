#include "perso.h"
#include "image.h"
void initPerso(Perso *perso, int x, int y, SDL_Surface *sprites[NUM_FRAMES])
{
    perso->pos.x = x;
    perso->pos.y = y;
    perso->vx = 0;
    perso->vy = 0;
    perso->jump = 0;
    perso->jump_vel = -20;
    perso->gravity = 1;
    perso->currentFrame = 0;
    perso->animation_timer = 0;
    perso->numFrames = 5;
    // Load sprite frames for animation
    for (int i = 0; i <= NUM_FRAMES; i++)
    {
        perso->sprites[i] = sprites[i];
    }

   
    perso->sprite = perso->sprites[perso->currentFrame];
}

void Perso_crouch(Perso *perso)
{
    perso->crouch = 1;
    

    perso->sprite = perso->sprites[NUM_FRAMES + 1];          
    perso->pos.y += perso->sprite->h - perso->sprites[0]->h; 
}

void Perso_uncrouch(Perso *perso)
{
    perso->crouch = 0;
   
    perso->sprite = perso->sprites[perso->currentFrame];
    perso->pos.y -= perso->sprite->h - perso->sprites[0]->h; 
}

void Perso_destroy(Perso *perso)
{
    SDL_FreeSurface(perso->sprite);
    free(perso);
}

void Perso_render(Perso *perso, SDL_Surface *screen)
{
    if (perso->crouch)
    {
        perso->sprite = perso->sprites[NUM_FRAMES + 1];

        
        perso->pos.x /= 2;
        perso->pos.y += perso->sprite->h - perso->sprites[0]->h;
    }
    else
    {
        
        perso->sprite = perso->sprites[perso->currentFrame];
        perso->pos.y = 72;
    }

    
    SDL_BlitSurface(perso->sprite, NULL, screen, &perso->pos);
}
void Perso_jump(Perso *perso)
{
    if (!perso->jump)
    {
        perso->jump = 1;
        perso->vy = perso->jump_vel;
        perso->moveUp = 1;
    }
}

void Perso_handleEvent(Perso *perso, SDL_Event *event)
{
    if (event->type == SDL_KEYDOWN)
    {
        switch (event->key.keysym.sym)
        {
        case SDLK_LEFT:
            perso->moveLeft = 1;
            break;
        case SDLK_RIGHT:
            perso->moveRight = 1;
            break;
        case SDLK_SPACE:
            Perso_jump(perso);
            break;
        case SDLK_UP:
            Perso_jump(perso);
            break;
        case SDLK_DOWN:
            Perso_crouch(perso);
            break;
        case SDLK_LCTRL:
            Perso_uncrouch(perso);
            break;
        default:
            break;
        }
    }
    else if (event->type == SDL_KEYUP)
    {
        switch (event->key.keysym.sym)
        {
        case SDLK_LEFT:
            perso->moveLeft = 0;
            break;
        case SDLK_RIGHT:
            perso->moveRight = 0;
            break;
        case SDLK_DOWN:
            Perso_uncrouch(perso);
            break;
        case SDLK_LCTRL:
            Perso_uncrouch(perso);
            break;
        default:
            break;
        }
    }
}
void updatePerso(Perso *perso, int screenWidth, int screenHigh)
{
    const int FPS = 60;

    
    int lastUpdateTime = 0;

    
    int deltaTime = SDL_GetTicks() - lastUpdateTime;
    
    
    if (deltaTime >= (1000 / FPS))
    {
        if (perso->moveLeft)
        {
            perso->currentFrame = (perso->currentFrame + 1) % perso->numFrames;
            perso->pos.x -= 2;
            perso->sprite = perso->sprites[perso->currentFrame];
        }
        else if (perso->moveRight)
        {
            perso->currentFrame = (perso->currentFrame - 1 + perso->numFrames) % perso->numFrames;
            perso->pos.x += 2;
            perso->sprite = perso->sprites[perso->currentFrame];
        }
        else
        {
            perso->sprite = perso->sprites[1];
        }
        lastUpdateTime = SDL_GetTicks();
    }
    
    if (perso->pos.y >= screenHigh - perso->sprite->h)
    {
        
        if (perso->moveUp)
        {
            perso->vy = -20;
            perso->moveUp = 0; 
        }
    }
    else
    {
        
        perso->vy += 1.5 * perso->gravity;
    }

    
    perso->pos.y += perso->vy;

    
    if (perso->pos.x < 0)
    {
        perso->pos.x = 0;
    }
    else if (perso->pos.x > (screenWidth - perso->sprite->w))
    {
        perso->pos.x = screenWidth - perso->sprite->w;
    }

   
    if (perso->pos.y >= screenHigh - perso->sprite->h)
    {
        perso->pos.y = screenHigh - perso->sprite->h;
        perso->vy = 0;
        perso->jump = 0;
    }

   if (perso->crouch)
{
    perso->sprite = perso->sprites[NUM_FRAMES + 1];          
    perso->sprite = scaleImage(perso->sprite,50,50) ; 
    perso->pos.y += perso->sprites[0]->h - perso->sprite->h; 
}
else
{
    perso->sprite = perso->sprites[perso->currentFrame];
    perso->pos.y += perso->sprites[0]->h - perso->sprite->h; 
}

}
