/**
    \file [main.c]
    \brief 	Main du jeu
    \author {Damotte Alan, Chaussende Adrien}
    \version 1.0.1
    \date Juin 2013
*/

#include <stdlib.h>
#include <stdio.h>
#include "LoopTETRIS_SDL.h"
#include <SDL/SDL_ttf.h>

int main()
{
    SDL sdl;

    sdljeuInit(&sdl);
    sdljeuBoucle(&sdl);
    sdljeuLibere(&sdl);

    //tetrisTestRegression();

    return 0;
}
