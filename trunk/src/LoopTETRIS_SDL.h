#ifndef _LOOPTETRIS_SDL_H
#define _LOOPTETRIS_SDL_H

#include <SDL/SDL.h>
#include "tetris.h"


typedef struct
{
	Tetris tetris;
	SDL_Surface* surface_screen;
	SDL_Surface* surface_piece;
	SDL_Surface* surface_gridge;
	SDL_Surface* surface_score;
}SDL;

void sdljeuInit(SDL *sdl);
void sdljeuBoucle(SDL *sdl);
void sdljeuLibere(SDL *sdl);

void sdljeuAff(SDL *sdl);
void SDL_apply_surface( SDL_Surface* source, SDL_Surface* destination, int x, int y );
SDL_Surface *SDL_load_image(const char* filename );

void pause();
void sdltestRegression(SDL *sdl);

#endif
