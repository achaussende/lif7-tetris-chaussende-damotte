#include <time.h>
#include "LoopTETRIS_SDL.h"
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
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

SDL_Surface* SDLChargeImage(const char* nomfichier){
	/* Temporary storage for the image that's loaded */
	SDL_Surface* loadedImage = NULL;

	/* Load the image */
	loadedImage = SDL_LoadBMP( nomfichier );


	/* If nothing went wrong in loading the image */
	if ( loadedImage == NULL ) printf("image non chargée ! \n");


	/* Return the optimized image */
	return loadedImage;
}

void sdljeuInit(SDL *sdl)
{

    SDL_Surface *surface_screen = NULL;
    SDL_Surface *gridge = NULL;
    SDL_Rect position1;


    /*assert(SDL_Init(SDL_INIT_EVERYTHING)!= -1); */
    SDL_Init(SDL_INIT_VIDEO);
    surface_screen = SDL_SetVideoMode(1000, 600, 32, SDL_SWSURFACE| SDL_RESIZABLE | SDL_DOUBLEBUF);

    // Coloration de la surface ecran en gris
    SDL_FillRect(surface_screen, NULL, SDL_MapRGB(surface_screen->format, 31, 31, 31));
    gridge = SDLChargeImage("../data/gridge.bmp");
    // gridge = IMG_Load("gridge.png");
    position1.x = surface_screen->w / 2 - gridge->w / 2;
	position1.y = surface_screen->h / 2 - gridge->h / 2;

    SDL_apply_surface(gridge,surface_screen, position1.x, position1.y);


    SDL_Surface *surface_piece = NULL;
    surface_piece = SDLChargeImage("../data/piece.bmp");

    SDL_Rect positionpiece;
    positionpiece.x = surface_screen->w / 2 - surface_piece->w / 2;
    positionpiece.y = surface_screen->h / 2 - surface_piece->h / 2;
    SDL_apply_surface(surface_piece,surface_screen, positionpiece.x, positionpiece.y);

    SDL_Event event;
    /*Board* board;
    board = sdl->tetris.board;*/
    int next = 1;
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
                        positionpiece.y=positionpiece.y-20;
                        SDL_Flip(surface_piece);
                        //rotationPiece(board);
                        break;
                    case SDLK_DOWN: // Flèche bas
                    positionpiece.y=positionpiece.y+20;
                    SDL_Flip(surface_piece);
                        //moveCurrentPieceDown(board);
                        break;
                    case SDLK_RIGHT: // Flèche droite
                    positionpiece.y=positionpiece.x-20;
                    SDL_Flip(surface_piece);
                        //moveCurrentPieceRight(board);
                        break;
                    case SDLK_LEFT: // Flèche gauche
                    positionpiece.y=positionpiece.x+20;
                    SDL_Flip(surface_piece);
                        //moveCurrentPieceLeft(board);
                        break;
                    default:
                        break;
                }
                break;
                default:
                    break;
        }

        SDL_Flip(surface_screen);
    }
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
    SDL_Surface *surface_piece = NULL;
    surface_piece = SDLChargeImage("../data/piece.bmp");

    SDL_Rect positionpiece;
    positionpiece.x = surface_screen->w / 2 - surface_piece->w / 2;
    positionpiece.y = surface_screen->h / 2 - surface_piece->h / 2;
    SDL_apply_surface(surface_piece,surface_screen, positionpiece.x, positionpiece.y);

    SDL_Event event;
    /*Board* board;
    board = sdl->tetris.board;*/

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
                        positionpiece.y=positionpiece.y-20;
                        //rotationPiece(board);
                        break;
                    case SDLK_DOWN: // Flèche bas
                    positionpiece.y=positionpiece.y+20;
                        //moveCurrentPieceDown(board);
                        break;
                    case SDLK_RIGHT: // Flèche droite
                    positionpiece.y=positionpiece.x-20;
                        //moveCurrentPieceRight(board);
                        break;
                    case SDLK_LEFT: // Flèche gauche
                    positionpiece.y=positionpiece.x+20;
                        //moveCurrentPieceLeft(board);
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
