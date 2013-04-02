#include <assert.h>
#include <time.h>
#include "loopTETRIS_SDL.h"
#include <SDL/SDL_ttf.h>

const int TAILLE_SPRITE=32;

void sdljeuInit(sdlTetris *pSdlTetris)
{
    Tetris *pTetris;
    int dimx, dimy;

    pTetris = &(pSdlTetris->tetris);
    jeuInit(pTetris);

    assert(   SDL_Init( SDL_INIT_EVERYTHING )!= -1 );

    dimx = 10 * TAILLE_SPRITE;
	dimy = 20 * TAILLE_SPRITE;
	pSdlJeu->surface_screen = SDL_SetVideoMode(   dimx, dimy, 32, SDL_SWSURFACE );
	assert( pSdlJeu->surface_screen!=NULL);
	SDL_WM_SetCaption( "Tetris v0.1", NULL );



}


void sdljeuBoucle(sdlTetris *)
{

}


void sdljeuLibere(sdlTetris *)
{

}
