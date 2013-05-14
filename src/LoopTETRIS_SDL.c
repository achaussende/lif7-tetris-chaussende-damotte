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

SDL_Surface* SDL_load_image(const char* filename){
	/* Temporary storage for the image that's loaded */
	SDL_Surface* loadedImage = NULL;

    SDL_Surface* optimizedImage = NULL;

	/* Load the image */
	loadedImage = SDL_LoadBMP( filename );


	/* If nothing went wrong in loading the image */
	if ( loadedImage == NULL )
    {
        printf("image non chargée ! \n");
    }

	else
	{
	    //Création de l'image optimisée
        optimizedImage = SDL_DisplayFormat( loadedImage );

        //Libération de l'ancienne image
        SDL_FreeSurface( loadedImage );

        //Si l'image optimisée créée est bonne
    	if( optimizedImage != NULL )
    	{
            //Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0, 0xFF, 0xFF );
            Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 255, 255, 255 );

        //On met tous les pixels de couleur R 0, G 0xFF, B 0xFF transparent
            SDL_SetColorKey( optimizedImage, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey );
        //On retourne l'image optimisée
        return optimizedImage;
    	}
	}
}



SDL_Surface* SDLdisplayscreen(SDL_Surface* screen, SDL_Surface* gridge, SDL_Surface* kind[8], Tetris* tetris, int positionX, int positionY)
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

                switch (tetris->board->gridge[j][i]) {

        case 1:
        {
            SDL_apply_surface(kind[0],screen, positionX+(i*20), positionY+(j*20));

        }
        break;

        case 2:
        {
            SDL_apply_surface(kind[1],screen, positionX+(i*20), positionY+(j*20));

        }
        break;
        case 3:
        {
            SDL_apply_surface(kind[2],screen, positionX+(i*20), positionY+(j*20));

        }
        break;
        case 4:
        {
            SDL_apply_surface(kind[3],screen, positionX+(i*20), positionY+(j*20));

        }
        break;
        case 5:
        {
            SDL_apply_surface(kind[4],screen, positionX+(i*20), positionY+(j*20));

        }
        break;
        case 6:
        {
            SDL_apply_surface(kind[5],screen, positionX+(i*20), positionY+(j*20));

        }
        break;
        case 7:
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

SDL_Surface* SDLdisplaypiece(SDL_Surface* screen, SDL_Surface* gridge, SDL_Surface* kind[8], Piece * piece, int positionX, int positionY)
{
    //SDL_apply_surface(gridge,screen, positionX, positionY);
    int i,j;
    for(j = 0; j < 4; j++)
        {
            for(i = 0; i < 4; i++)
            {
                if ((PIECES[piece->kind][piece->orientation][j][i])!=0)
                {

                switch (getKind(piece)) {

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
        {
           // SDL_apply_surface(kind[7],screen, positionX+(i*20), positionY+(j*20));
        }
        break;
                }

            }
        }
        }
}

SDLclearpiece(SDL_Surface* screen, Piece * piece , int positionX, int positionY)
{
    int i,j;
    for(j = 0; j < 4; j++)
        {
            for(i = 0; i < 4; i++)
            {
                (PIECES[piece->kind][piece->orientation][j][i])=0;
            }
        }
}

void sdljeuInit(SDL *sdl)
{
    // ------------------------ INIT -----------------------
    SDL_Surface *screen = NULL;
    SDL_Surface *screen2 = NULL;
    SDL_Surface *gridge = NULL;
    SDL_Surface *kind[8];
    SDL_Rect position1;

    /*assert(SDL_Init(SDL_INIT_EVERYTHING)!= -1); */
    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(1000, 600, 32, SDL_SWSURFACE| SDL_RESIZABLE | SDL_DOUBLEBUF);

    // Coloration de la surface ecran en gris
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 31, 31, 31));
    gridge = SDL_load_image("../data/gridge.bmp");


    kind[0]=SDL_load_image("../data/piecejaune.bmp");
    kind[1]=SDL_load_image("../data/piececyan.bmp");
    kind[2]=SDL_load_image("../data/piecevert.bmp");
    kind[3]=SDL_load_image("../data/piecerouge.bmp");
    kind[4]=SDL_load_image("../data/pieceorange.bmp");
    kind[5]=SDL_load_image("../data/piecebleue.bmp");
    kind[6]=SDL_load_image("../data/pieceviolet.bmp");
    //kind[7]=SDL_load_image("../data/piecevide.bmp");
    kind[7]=IMG_Load("../data/piecevide.png");
    screen2 = SDL_load_image("../data/screen.bmp");

    // ---------- Essai de Menu ----------------
    /*int quit;
    quit = 1;
    SDL_Event event;
    while(quit)
    {
        if( event.type == SDL_MOUSEBUTTONDOWN )
        {
          //les coordonnées de la souris
          int x = event.button.x;
          int y = event.button.y;

          if ((x>245)&& (x<395) && (y>120) && (y<180))


            if ( SDL_BUTTON_LEFT)
              quit = 0;
        }
    }
    */
    //-------------------------------------------

    SDL_apply_surface(screen2,screen, 0, 0);

    position1.x = screen->w / 2 - gridge->w / 2;
	position1.y = (screen->h / 2 - gridge->h / 2);

    SDL_apply_surface(gridge,screen, position1.x, position1.y);

    SDL_WM_SetCaption("LegendaryTetris", NULL);

    SDL_Rect positionpiece;

    positionpiece.x = position1.x+(5*20);
    positionpiece.y = position1.y;


    Board * board = (Board *)malloc(sizeof(Board));
    Piece * piece = NULL;
    Piece * nextpiece = NULL;
    Tree * tree = (Tree *)malloc(sizeof(Tree));
    Tetris * tetris;

    tetris = startTetris(); // Lancement du tetris
    int destructlines;
    destructlines = 0;
    int posx, posy;



    //board = sdl->tetris.board;
    srand(time(NULL));

    initBoard(board);
    printf("Création de la board + initialisation ... OK \n");

    piece = createPiece(rand() % 7, 0);
    //nextpiece = createPiece(rand() % 7, 0);

     printf("Current piece : \n kind = %u , orientation = %u \n",
          tetris->board->currentPiece->kind,
          tetris->board->currentPiece->orientation);
    printf("Next piece : \n kind = %u , orientation = %u \n",
          tetris->nextpiece->kind,
          tetris->nextpiece->orientation);
    /*printf("Création d'une piece de type : %u et d'orientation : %u \n",
            piece->kind + 1, piece->orientation + 1);*/
    /*tetris = createTetris(board, piece, tree);*/
    printf("Création du Tetris ... OK \n");
    //newPiece(tetris->board, piece);
    nextpiece = getTetrisNextPiece(tetris);
    SDLdisplayscreen(screen,gridge, kind, tetris, position1.x,position1.y);
    SDLdisplaypiece(screen,gridge, kind, nextpiece, position1.x+275,position1.y+50);


    //--------------------- BOUCLE -----------------------
    SDL_Event event;
    int tempsPrecedent = 0, tempsActuel = 0;

    int next = 1;
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
            /*posx = getPosX(tetris->board->currentPiece);
            posy = getPosY(tetris->board->currentPiece);
            if(isCurrentPieceMovable(tetris->board, posx, posy + 1) == FALSE && testFallPiece(tetris->board) == FALSE)
               {
                   destructlines = destructlines + destructLines(tetris->board);
                   gameStep(tetris);
               }*/
        }

        /* Après pose de la currentPiece, la nextPiece devient la currentPiece
       puis nouvelle nextPiece*/
       //destructlines = destructlines + destructLines(tetris->board);
       posx = getPosX(tetris->board->currentPiece);
       posy = getPosY(tetris->board->currentPiece);
       if(isCurrentPieceMovable(tetris->board, posx, posy + 1) == FALSE && testFallPiece(tetris->board) == FALSE)
               {
                   destructlines = destructlines + destructLines(tetris->board);
                   SDLclearpiece(screen, nextpiece, position1.x+275,position1.y+50);
                   gameStep(tetris);
                   nextpiece = getTetrisNextPiece(tetris);
                   SDLdisplaypiece(screen,gridge, kind, nextpiece, position1.x+275,position1.y+50);
               }
       /*if(testFallPiece(tetris->board) == TRUE)
        {
            printf("On entre dans cette putain de boucle");
            gameStep(tetris);

        }*/


        //SDLdisplayscreen(screen,gridge, kind, tetris, position1.x,position1.y);
        /*if(testFallPiece(tetris->board))
        {
            SDL_apply_surface(kind[1], screen, position1.x, position1.y );
        }*/

        SDL_Flip(screen);

    }
pause();

// -------------------- FREE AND QUIT -----------------------
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

