#ifndef _LOOPTETRIS_SDL_H
#define _LOOPTETRIS_SDL_H

#include <SDL/SDL.h>
#include "Tetris.h"


typedef struct
{
	Tetris tetris;
	SDL_Surface* surface_screen;
	SDL_Surface* surface_piece;
	SDL_Surface* surface_gridge;
	SDL_Surface* surface_score;
} sdlTetris;

void sdljeuInit(sdlTetris *);
void sdljeuBoucle(sdlTetris *);
void sdljeuLibere(sdlTetris *);

#endif
