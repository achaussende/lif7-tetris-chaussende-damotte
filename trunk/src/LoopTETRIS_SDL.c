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


SDL_Surface* SDLdisplayscreen(SDL_Surface* screen, SDL_Surface* gridge, SDL_Surface* kind[6], Tetris* tetris, int positionX, int positionY)
{
    SDL_apply_surface(gridge,screen, positionX, positionY);
    int i,j;
    for(j = 0; j < 20; j++)
        {
            for(i = 0; i < 10; i++)
            {
                if ((tetris->board->gridge[j][i])!=0)
                {
                     //SDL_apply_surface(kind,screen, positionX+(i*20), positionY+(j*20));

                switch (getKind(tetris->board->currentPiece)) {

        case 0:
        {
            SDL_apply_surface(kind[0],screen, positionX+(i*20), positionY+(j*20));

        }
        break;

        case 1:
        {
            SDL_apply_surface(kind[1],screen, positionX+(i*20), positionY+(j*20));

        }
        break;
        case 2:
        {
            SDL_apply_surface(kind[2],screen, positionX+(i*20), positionY+(j*20));

        }
        break;
        case 3:
        {
            SDL_apply_surface(kind[3],screen, positionX+(i*20), positionY+(j*20));

        }
        break;
        case 4:
        {
            SDL_apply_surface(kind[4],screen, positionX+(i*20), positionY+(j*20));

        }
        break;
        case 5:
        {
            SDL_apply_surface(kind[5],screen, positionX+(i*20), positionY+(j*20));

        }
        break;
        case 6:
        {
            SDL_apply_surface(kind[6],screen, positionX+(i*20), positionY+(j*20));

        }
        break;

        default:
        break;
                }

            }
        }
        }
}


void sdljeuInit(SDL *sdl)
{

    SDL_Surface *screen = NULL;
    SDL_Surface *gridge = NULL;
    SDL_Surface *kind[7];
    SDL_Rect position1;

    /*assert(SDL_Init(SDL_INIT_EVERYTHING)!= -1); */
    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(1000, 600, 32, SDL_SWSURFACE| SDL_RESIZABLE | SDL_DOUBLEBUF);

    // Coloration de la surface ecran en gris
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 31, 31, 31));
    gridge = SDLChargeImage("../data/gridge.bmp");


    kind[0]=SDLChargeImage("../data/piecejaune.bmp");
    kind[1]=SDLChargeImage("../data/piececyan.bmp");
    kind[2]=SDLChargeImage("../data/piecevert.bmp");
    kind[3]=SDLChargeImage("../data/piecerouge.bmp");
    kind[4]=SDLChargeImage("../data/pieceorange.bmp");
    kind[5]=SDLChargeImage("../data/piecebleue.bmp");
    kind[6]=SDLChargeImage("../data/pieceviolet.bmp");

    position1.x = screen->w / 2 - gridge->w / 2;
	position1.y = screen->h / 2 - gridge->h / 2;

    SDL_apply_surface(gridge,screen, position1.x, position1.y);

    SDL_WM_SetCaption("LegendaryTetris", NULL);

    SDL_Rect positionpiece;

    positionpiece.x = position1.x+(5*20);
    positionpiece.y = position1.y;


    Board * board = (Board *)malloc(sizeof(Board));
    Piece * piece = NULL;
    Tree * tree = (Tree *)malloc(sizeof(Tree));
    Tetris * tetris;
    //board = sdl->tetris.board;
    srand(time(NULL));

    initBoard(board);
    printf("Création de la board + initialisation ... OK \n");

    piece = createPiece(rand() % 7, 0);
    printf("Création d'une piece de type : %u et d'orientation : %u \n",
            piece->kind + 1, piece->orientation + 1);
    tetris = createTetris(board, piece, tree);
    printf("Création du Tetris ... OK \n");
    newPiece(tetris->board, piece);
    SDLdisplayscreen(screen,gridge, kind, tetris, position1.x,position1.y);
    SDL_Event event;
    int tempsPrecedent = 0, tempsActuel = 0;

    int next = 1;
    SDL_EnableKeyRepeat(10, 10);
     while (next)
    {
        //SDL_WaitEvent(&event);
        if(SDL_PollEvent(&event))
        switch(event.type)
        {
            case SDL_QUIT:
                next = 0;
                break;
            case SDL_KEYUP:
                switch(event.key.keysym.sym)
                {
                    case SDLK_UP: // Flèche haut
                        rotationPiece(tetris->board);
                        SDLdisplayscreen(screen,gridge, kind, tetris, position1.x,position1.y);
                        break;

                    case SDLK_DOWN: // Flèche bas
                        moveCurrentPieceDown(tetris->board);
                        SDLdisplayscreen(screen,gridge, kind, tetris, position1.x,position1.y);
                        break;

                    case SDLK_RIGHT: // Flèche droite
                        moveCurrentPieceRight(tetris->board);
                        SDLdisplayscreen(screen,gridge, kind, tetris, position1.x,position1.y);

                        break;
                    case SDLK_LEFT: // Flèche gauche
                        moveCurrentPieceLeft(tetris->board);
                        SDLdisplayscreen(screen,gridge, kind, tetris, position1.x,position1.y);

                        break;
                    case SDLK_SPACE: // Barre espace
                        dropCurrentPiece(tetris->board);
                        SDLdisplayscreen(screen,gridge, kind, tetris, position1.x,position1.y);

                        break;
                    default:
                    break;
                }
                break;

                default:

                break;
        }

        //------------ TEST LIGNE REMPLIE et NOUVELLE PIECE -----------
        //destructLines(tetris->board);

        //-------------------------------------------------------------
        tempsActuel = SDL_GetTicks();
        if (tempsActuel - tempsPrecedent > 1000) /* Si 1000 ms se sont écoulées depuis le dernier tour de boucle */
        {
            moveCurrentPieceDown(tetris->board);
            SDLdisplayscreen(screen,gridge, kind, tetris, position1.x,position1.y);
            tempsPrecedent = tempsActuel; /* Le temps "actuel" devient le temps "precedent" pour nos futurs calculs */
        }

        SDL_Flip(screen);

    }
pause();
SDL_FreeSurface(tetris);
SDL_FreeSurface(gridge);
SDL_FreeSurface(kind);
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

