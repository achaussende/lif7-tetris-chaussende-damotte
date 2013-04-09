#include <time.h>
#include "LoopTETRIS_SDL.h"
#include <SDL/SDL_ttf.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>



void sdljeuInit(SDL *sdl)
{
    SDL_Surface *surface_screen = NULL, *rectangle = NULL;
    SDL_Rect position;

    assert(SDL_Init(SDL_INIT_EVERYTHING)!= -1); // Démarrage de la SDL
    surface_screen = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_RESIZABLE | SDL_DOUBLEBUF);
    // Allocation de la surface
    rectangle = SDL_CreateRGBSurface(SDL_HWSURFACE, 220, 180, 32, 0, 0, 0, 0);
    SDL_WM_SetCaption("LegendaryTetris", NULL);

    // Coloration de la surface ecran en bleu-vert
    SDL_FillRect(surface_screen, NULL, SDL_MapRGB(surface_screen->format, 17, 206, 112));

    SDL_Flip(ecran); /* Mise à jour de l'écran avec sa nouvelle couleur */

    pause();


}

/*
void sdljeuBoucle(sdlTetris *)
{

}
*/

void sdljeuLibere(SDL *sdl)
{
    SDL_Quit(); // Arrêt de la SDL (libération de la mémoire)
    return EXIT_SUCCESS; // Fermeture du programme
}

void pause()
{
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}
