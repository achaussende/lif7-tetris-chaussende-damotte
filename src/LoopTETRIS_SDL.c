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

    SDL_Surface *screen = NULL;
    SDL_Surface *gridge = NULL;
    SDL_Surface *piece = NULL;
    SDL_Rect position1;


    /*assert(SDL_Init(SDL_INIT_EVERYTHING)!= -1); */
    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(1000, 600, 32, SDL_SWSURFACE| SDL_RESIZABLE | SDL_DOUBLEBUF);

    // Coloration de la surface ecran en gris
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 31, 31, 31));
    gridge = SDLChargeImage("../data/gridge.bmp");
    piece = SDLChargeImage("../data/piece.bmp");
    // gridge = IMG_Load("gridge.png");
    position1.x = screen->w / 2 - gridge->w / 2;
	position1.y = screen->h / 2 - gridge->h / 2;

    SDL_apply_surface(gridge,screen, position1.x, position1.y);


    SDL_WM_SetCaption("LegendaryTetris", NULL);


    //*************** Boucle d'évènement, à compléter *******************
    //** Gestion des touches
    //** Affichage pièce
    //** Gestion Lignes
    //** Etc...
    /*SDL_Surface *screen;
    screen = sdl->screen;
    SDL_Surface *gridge;
    gridge = sdl->gridge;
    SDL_Surface *piece;
    piece = sdl->piece;*/
    SDL_Rect positionpiece;
    //positionpiece.x = screen->w / 2 - piece->w / 2;
	//positionpiece.y = screen->h / 2 - piece->h / 2;
    positionpiece.x = position1.x;
    positionpiece.y = position1.y;
    Board* board;
    board = sdl->tetris.board;
    initBoard(board);
	Piece * piece2;
    piece2 = createPiece(rand()%7, 0);
    /*setPosX(piece2, position1.x);
    setPosY(piece2, position1.y);*/

    newPiece(board, piece2);
	//SDL_apply_surface(piece,screen, positionpiece.x, positionpiece.y);


    SDL_Event event;

    int next = 1;
    //SDL_EnableKeyRepeat(10, 10);
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
                        //positionpiece.y=positionpiece.y-20;
                        //SDL_apply_surface(piece,screen, positionpiece.x, positionpiece.y);
                        //SDL_Flip(screen);

                        rotationPiece(board);
                        //positionpiece.x = (getPosX(piece2))*20;
                        SDL_apply_surface(piece,screen, positionpiece.x, positionpiece.y);
                        SDL_Flip(screen);
                        break;
                    case SDLK_DOWN: // Flèche bas
                        /*positionpiece.y=positionpiece.y+20;
                        SDL_apply_surface(piece,screen, positionpiece.x, positionpiece.y);
                        SDL_Flip(screen);*/

                        moveCurrentPieceDown(board);
                        positionpiece.y = (getPosY(piece2))*20;
                        SDL_apply_surface(piece,screen, positionpiece.x, positionpiece.y);
                        SDL_Flip(screen);

                        break;
                    case SDLK_RIGHT: // Flèche droite
                        //positionpiece.x=positionpiece.x+20;
                        //
                        moveCurrentPieceRight(board);
                        positionpiece.x = (getPosX(piece2))*20;
                        SDL_apply_surface(piece,screen, positionpiece.x, positionpiece.y);
                        SDL_Flip(screen);

                        break;
                    case SDLK_LEFT: // Flèche gauche
                        //positionpiece.x=positionpiece.x-20;
                        //SDL_apply_surface(piece,screen, positionpiece.x, positionpiece.y);
                        //SDL_Flip(screen);

                        moveCurrentPieceLeft(board);
                        positionpiece.x = (getPosX(piece2))*20;
                        SDL_apply_surface(piece,screen, positionpiece.x, positionpiece.y);
                        SDL_Flip(screen);
                        break;

                    default:
                    break;
                }
                break;

                default:
                break;
        }

        SDL_Flip(screen);
    }
pause();
SDL_FreeSurface(piece);
SDL_FreeSurface(screen);
SDL_Quit(); // Arrêt de la SDL (libération de la mémoire)

}


void sdljeuBoucle(SDL *sdl)
{

}


void sdljeuLibere(SDL *sdl)
{

    SDL_Quit(); // Arrêt de la SDL (libération de la mémoire)

}

void sdltestRegression(SDL *sdl)
{
    sdljeuInit(sdl);
    sdljeuBoucle(sdl);

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

