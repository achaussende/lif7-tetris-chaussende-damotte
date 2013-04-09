#include <stdlib.h>
#include <stdio.h>

#include <time.h>
#include "LoopTETRIS_SDL.h"
#include "tetris.h"

#include <SDL/SDL_ttf.h>

int main()
{
    SDL sdl;
    sdltestRegression(&sdl);
    /*sdljeuInit(&sdl);
    sdljeuBoucle(&sdl);
    sdljeuLibere(&sdl);*/

    return 0;
}
