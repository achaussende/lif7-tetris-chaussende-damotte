#include <time.h>
#include "LoopTETRIS_SDL.h"
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include "SDL.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

void SDL_apply_surface( SDL_Surface* source, SDL_Surface* destination, int positionX, int positionY )
{
    /* Make a temporary rectangle to hold the offsets */
	SDL_Rect offset;

	/* Give the offsets to the rectangle */
	offset.x = positionX;
	offset.y = positionY;

	/* Blit the surface */
	SDL_BlitSurface( source, NULL, destination, &offset );
}

void sdljeuInit(SDL *sdl)
{

    SDL_Surface *surface_screen = NULL;
    SDL_Surface *gridge = NULL;
    SDL_Rect position1;
    position1.x = 200;
	position1.y = 20;

    /*assert(SDL_Init(SDL_INIT_EVERYTHING)!= -1); */
    SDL_Init(SDL_INIT_VIDEO);
    surface_screen = SDL_SetVideoMode(1280, 720, 32, SDL_SWSURFACE);

    // Coloration de la surface ecran en gris
    SDL_FillRect(surface_screen, NULL, SDL_MapRGB(surface_screen->format, 31, 31, 31));
    gridge = SDL_LoadBMP("gridge.bmp");
    SDL_BlitSurface(gridge, NULL, surface_screen, &position1);
   /* SDL_apply_surface( gridge, surface_screen, 100, 100 );*/

    SDL_WM_SetCaption("LegendaryTetris", NULL);

	SDL_Flip(surface_screen);
	pause();


}


void sdljeuBoucle(SDL *sdl)
{
    //*************** Boucle d'évènement, à compléter *******************
    //** Gestion des touches
    //** Affichage pièce
    //** Gestion Lignes
    //** Etc...
    int next=1;

    SDL_Surface *surface_screen = NULL;
   /* SDL_Surface *surface_gridge = NULL;
    SDL_Surface *surface_piece = NULL;
	SDL_Surface *surface_score = NULL;*/
    SDL_Event event;
    Board* board;
    board = sdl->tetris.board;

     SDL_EnableKeyRepeat(10, 10);
     while (next)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                next = 0;
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_UP: // Flèche haut
                        rotationPiece(board);
                        break;
                    case SDLK_DOWN: // Flèche bas
                        moveCurrentPieceDown(board);
                        break;
                    case SDLK_RIGHT: // Flèche droite
                        moveCurrentPieceRight(board);
                        break;
                    case SDLK_LEFT: // Flèche gauche
                        moveCurrentPieceLeft(board);
                        break;
                    default:
                        break;
                }
                break;
                default:
                    break;
        }

        SDL_Flip(surface_screen);

        /* On efface l'écran */
        //SDL_FillRect(surface_screen, NULL, SDL_MapRGB(surface_screen->format, 255, 255, 255));
        /* On place Zozor à sa nouvelle position */
        //SDL_BlitSurface(zozor, NULL, surface_screen, &positionZozor);
        /* On met à jour l'affichage */
        //SDL_Flip(ecran);
    }
}


void sdljeuLibere(SDL *sdl)
{

    SDL_Quit(); // Arrêt de la SDL (libération de la mémoire)

}

void sdltestRegression(SDL *sdl)
{
    sdljeuInit(sdl);
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
