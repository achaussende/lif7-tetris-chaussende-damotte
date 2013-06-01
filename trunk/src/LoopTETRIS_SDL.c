/**
    \file [LoopTETRIS_SDL.c]
    \brief 	Contient les fonctions d'affichage du jeu via SDL
    \author {Damotte Alan, Chaussende Adrien}
    \version 1.1
    \date Avril-Mai 2013
*/

#include <time.h>
#include "LoopTETRIS_SDL.h"
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "../lib/FMOD/inc/fmod.h"
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

SDL_Surface* SDLdisplaypiece(SDL_Surface* screen, SDL_Surface* nextpiecebackground, SDL_Surface* kind[8], Piece * piece, int positionX, int positionY)
{
    SDL_apply_surface(nextpiecebackground,screen, positionX, positionY);
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

/*SDLclearpiece(SDL_Surface* screen, SDL_Surface* reset, int positionX, int positionY)
{
    int i,j;
    for(j = 0; j < 4; j++)
        {
            for(i = 0; i < 4; i++)
            {
                SDL_apply_surface(reset,screen, positionX+(i*20), positionY+(j*20));

            }
        }

}*/

void sdljeuInit(SDL *sdl)
{
    /* ------------------------ INIT ----------------------- */

    SDL_Surface *screen = NULL;
    SDL_Surface *screen2 = NULL;
    SDL_Surface *gridge = NULL;
    SDL_Surface *scorebackground = NULL;
    SDL_Surface *playerbackground = NULL;
    SDL_Surface *kind[8];
    SDL_Surface *nextpiecebackground = NULL;
    SDL_Surface *holdpiecebackground = NULL;


        // Surfaces Textes
    SDL_Surface * text = NULL;
    SDL_Surface * textgameover = NULL;
    SDL_Surface * textpause = NULL;
    SDL_Surface * tuto = NULL;
    SDL_Surface * tuto2 = NULL;

        // Rectangle de position
    SDL_Rect position1;

        // FMOD
    FMOD_SYSTEM *system;
    FMOD_System_Create(&system);

    FMOD_SOUND *explosion = NULL;
    FMOD_SOUND *maintheme = NULL;
    FMOD_SOUND *f_legendary1 = NULL;
    FMOD_SOUND *f_legendary2 = NULL;
    FMOD_SOUND *f_defeat = NULL;
    FMOD_SOUND *f_unstoppable = NULL;


        //Initialisation de screen
    /*assert(SDL_Init(SDL_INIT_EVERYTHING)!= -1); */
    SDL_Init(SDL_INIT_VIDEO);
    screen = SDL_SetVideoMode(1000, 600, 32, SDL_SWSURFACE| SDL_RESIZABLE | SDL_DOUBLEBUF);

        // Initialisation de TTF
    if(TTF_Init() == -1)
    {
        printf("Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

        // Initialisation de FMOD
            // 32 est le nombre de sons gérés par FMOD
    FMOD_System_Init(system, 32, FMOD_INIT_NORMAL, NULL);
    FMOD_System_CreateSound(system, "../data/sounds/explode.wav",
                            FMOD_CREATESAMPLE, 0, &explosion);
        //Initialisation des samples
    FMOD_System_CreateSound(system, "../data/sounds/f_legendary1.mp3",
                            FMOD_CREATESAMPLE, 0, &f_legendary1);
    FMOD_System_CreateSound(system, "../data/sounds/f_legendary2.mp3",
                            FMOD_CREATESAMPLE, 0, &f_legendary2);
    FMOD_System_CreateSound(system, "../data/sounds/f_defeat.mp3",
                            FMOD_CREATESAMPLE, 0, &f_defeat);
    FMOD_System_CreateSound(system, "../data/sounds/f_unstoppable.mp3",
                            FMOD_CREATESAMPLE, 0, &f_unstoppable);
        // Initialisation des musiques
    FMOD_System_CreateSound(system,
                            "../data/sounds/theglitchmob_howtobeeatenbyawoman.mp3",
                            FMOD_SOFTWARE | FMOD_2D
                            | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0, &maintheme);
            //On active la répétition en boucle puis on joue la musique
    FMOD_Sound_SetLoopCount(maintheme, -1);
    FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, maintheme, 0, NULL);

        // Coloration de la surface ecran en gris
    SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 31, 31, 31));
    gridge = SDL_load_image("../data/gridge.bmp");

        //Initialisation de kind avec les images des couleurs des pièces
    kind[0]=SDL_load_image("../data/piecejaune.bmp");
    kind[1]=SDL_load_image("../data/piececyan.bmp");
    kind[2]=SDL_load_image("../data/piecevert.bmp");
    kind[3]=SDL_load_image("../data/piecerouge.bmp");
    kind[4]=SDL_load_image("../data/pieceorange.bmp");
    kind[5]=SDL_load_image("../data/piecebleue.bmp");
    kind[6]=SDL_load_image("../data/pieceviolet.bmp");
    //kind[7]=SDL_load_image("../data/piecevide.bmp");
    //reset=IMG_Load("../data/piecevide.png");

        //Chargement de l'image d'écran de jeu et la pièce suivante
    screen2 = SDL_load_image("../data/screen.bmp");
    nextpiecebackground = SDL_load_image("../data/nextpiece.bmp");
    holdpiecebackground = SDL_load_image("../data/nextpiece.bmp");
    scorebackground = SDL_load_image("../data/score.bmp");
    playerbackground = SDL_load_image("../data/score.bmp");


    /* ---------- Essai de Menu ---------------- */
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



    /*  Variables de la SDL */

    SDL_apply_surface(screen2,screen, 0, 0);

    position1.x = screen->w / 2 - gridge->w / 2;
	position1.y = (screen->h / 2 - gridge->h / 2);

    SDL_apply_surface(gridge,screen, position1.x, position1.y);
    SDL_apply_surface(scorebackground,screen, position1.x-177, position1.y+84);
    SDL_apply_surface(playerbackground,screen, position1.x-177, position1.y+19);
    SDL_WM_SetCaption("LegendaryTetris", NULL);

    /*SDL_Rect positionpiece;

    positionpiece.x = position1.x+(5*20);
    positionpiece.y = position1.y;*/

    /* Variables pour le TTF */

    TTF_Font * font = NULL ;
    font = TTF_OpenFont("../data/gameover.ttf", 65);

    TTF_Font * font1 = NULL ;
    font1 = TTF_OpenFont("../data/gameover.ttf", 30);

    /* Couleurs pour les polices TTF */
    /* colorBlack = {0 ,0 ,0};*/
    SDL_Color colorWhite = {255, 255, 255};

    /* Variables pour le Tetris */

    Board * board = (Board *)malloc(sizeof(Board));
    /*Piece * piece = NULL;*/
    Piece * nextpiece = NULL;
    Piece * holdpiece = NULL;
    /*Tree * tree = (Tree *)malloc(sizeof(Tree));*/
    Tetris * tetris;
    tetris = startTetris(); // Lancement du tetris

    int destructlines;
    destructlines = 0;
    int n_lines = 0;
    int posx, posy;
    int score = 0;
    int temp = 0;

    int sound_played = 0; //Pour les sons de palier de score

    char s_score[20];

    /* Initialisation texte du score */
    sprintf(s_score, "%u", score);
    text = TTF_RenderText_Blended(font, s_score, colorWhite);


    // GROSSE PARTIE A NETTOYER ET COMMENTER !!! (Adrien)
    //board = sdl->tetris.board;
    srand(time(NULL));

    initBoard(board);

    nextpiece = getTetrisNextPiece(tetris);
    SDLdisplayscreen(screen,gridge, kind, tetris, position1.x,position1.y);
    SDLdisplaypiece(screen,nextpiecebackground, kind, nextpiece, position1.x+280,position1.y+50);
    SDL_apply_surface(holdpiecebackground,screen, position1.x+280,position1.y+250);
    tuto = TTF_RenderText_Blended(font1, "P = Pause", colorWhite);
    tuto2 = TTF_RenderText_Blended(font1, "C = Hold a line", colorWhite);
    SDL_apply_surface(tuto,screen, 50,500); // Blit de text
    SDL_apply_surface(tuto2,screen, 50,520); // Blit de text


    //--------------------- BOUCLE -----------------------

            // Dans la fonction sdljeuboucle ? (à mettre en anglais aussi)

    SDL_Event event;
    SDL_Event newevent;
    int tempsPrecedent = 0, tempsActuel = 0;

    int next = 1;
    int change,pausebutton,endgame;
    change = 1;
    pausebutton=0;
    endgame=0;
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
                    if (pausebutton==0){
                        rotationPiece(tetris->board);
                        SDLdisplayscreen(screen,gridge, kind, tetris, position1.x,position1.y);
                        temp = 0;
                    }
                        break;

                    case SDLK_DOWN: // Flèche bas
                    if (pausebutton==0){
                        moveCurrentPieceDown(tetris->board);
                        SDLdisplayscreen(screen,gridge, kind, tetris, position1.x,position1.y);
                    }
                        break;

                    case SDLK_RIGHT: // Flèche droite
                    if (pausebutton==0){
                        moveCurrentPieceRight(tetris->board);
                        SDLdisplayscreen(screen,gridge, kind, tetris, position1.x,position1.y);
                        temp = 0;
                    }
                        break;

                    case SDLK_LEFT: // Flèche gauche
                    if (pausebutton==0){
                        moveCurrentPieceLeft(tetris->board);
                        SDLdisplayscreen(screen,gridge, kind, tetris, position1.x,position1.y);
                        temp = 0;
                    }
                        break;

                    case SDLK_SPACE: // Barre espace
                    if (pausebutton==0){
                        dropCurrentPiece(tetris->board);
                        SDLdisplayscreen(screen,gridge, kind, tetris, position1.x,position1.y);
                        temp = 2;
                        break;
                    }
                    case SDLK_c: // Touche c
                    if (pausebutton==0){
                        if (change)
                        {
                            holdPiece(tetris);
                            holdpiece = tetris->holdpiece;
                            SDLdisplaypiece(screen,holdpiecebackground, kind, holdpiece, position1.x+280,position1.y+250);
                            SDLdisplayscreen(screen,gridge, kind, tetris, position1.x,position1.y);
                            change = 0;
                        }
                    }

                        break;
                    case SDLK_p: // Touche p
                            if(pausebutton==0)
                                pausebutton=1;
                            else if(pausebutton==1)
                                pausebutton=0;
                        break;

                    case SDLK_ESCAPE: // Bouton ECHAP
                    sdljeuLibere(sdl);
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
        if (pausebutton==0)
        {
            if (tempsActuel - tempsPrecedent > 1000-(10*destructlines)) /* Si 1000 ms se sont écoulées depuis le dernier tour de boucle */
            {
                moveCurrentPieceDown(tetris->board);
                SDLdisplayscreen(screen,gridge, kind, tetris, position1.x,position1.y);
                tempsPrecedent = tempsActuel; /* Le temps "actuel" devient le temps "precedent" pour nos futurs calculs */
                temp++;

                /*posx = getPosX(tetris->board->currentPiece);
                posy = getPosY(tetris->board->currentPiece);
                if(isCurrentPieceMovable(tetris->board, posx, posy + 1) == FALSE && testFallPiece(tetris->board) == FALSE)
                   {
                       destructlines = destructlines + destructLines(tetris->board);
                       gameStep(tetris);
                   }*/
            }
        }
        else
        {
          textpause = TTF_RenderText_Blended(font, "PAUSE", colorWhite);
          SDL_apply_surface(textpause,screen, 460, 275); // Blit de text
        }
        /* Après pose de la currentPiece, la nextPiece devient la currentPiece
       puis nouvelle nextPiece*/

       posx = getPosX(tetris->board->currentPiece);
       posy = getPosY(tetris->board->currentPiece);
       if(isCurrentPieceMovable(tetris->board, posx, posy + 1) == FALSE && testFallPiece(tetris->board) == FALSE && temp >= 2)
               {
                   /* Destruction des lignes et Calcul du score */
                   n_lines = destructLines(tetris->board);
                   FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, explosion,
                                          0, NULL);
                    if(n_lines != 0)
                    {
                        //FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, explosion2);
                    }
                   destructlines = destructlines + n_lines;
                   score = calcScore(score, n_lines);
                   printf("lignes détruites : %u \n score : %u \n", destructlines, score);


                    if(score >= 50000 && sound_played == 0)
                    {
                        FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE,
                                              f_unstoppable, 0, NULL);
                        sound_played = 1;
                    }

                    if(score >= 100000 && sound_played == 1)
                    {
                        FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE,
                                              f_legendary1, 0, NULL);
                        sound_played = 2;
                    }
                    if(score >= 150000 && sound_played == 2)
                    {
                        FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE,
                                              f_legendary2, 0, NULL);
                        sound_played = 3;
                    }

                    /* Affichage du score */
                    sprintf(s_score, "%u", score);
                    SDL_FreeSurface(text);

                    text = TTF_RenderText_Blended(font, s_score, colorWhite);
                    //TTF_RenderText_Shaded(font, s_score, colorWhite); peut aussi marcher comme sur fond uni
                    if(testGameOver(tetris->board) == TRUE)
                    {
                        printf("je suis passé ici");
                        next=0;
                        endgame=1;
                        FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE,
                                              f_defeat, 0, NULL);
                        textgameover = TTF_RenderText_Blended(font, "GAME OVER ! TRY AGAIN ? Y/N", colorWhite);
                        SDL_apply_surface(textgameover,screen, 320, 275); // Blit de text
                    }
                   else
                   {
                   gameStep(tetris);
                   nextpiece = getTetrisNextPiece(tetris);
                   SDLdisplaypiece(screen,nextpiecebackground, kind, nextpiece, position1.x+280,position1.y+50);
                   change = 1;
                   }
               }

        SDL_Flip(screen);
        SDL_apply_surface(scorebackground,screen, position1.x-177, position1.y+84);
        SDL_apply_surface(text,screen, position1.x-172, position1.y+100); // Blit de text
    }
    /* Boucle de nouvelle partie */
    while (endgame)
    {
        SDL_WaitEvent(&newevent);
        //if(SDL_PollEvent(&event))
        switch(newevent.type)
        {
            case SDL_QUIT:
                endgame = 0;
                break;
            case SDL_KEYUP:
                switch(newevent.key.keysym.sym)
                {
                    case SDLK_y: // Touche y
                        sdljeuInit(sdl);
                    break;

                    case SDLK_n: // Touche n
                            sdljeuLibere(sdl);
                    break;

                    default:
                    break;
                }
        }
    }
    pause();


}


void sdljeuBoucle(SDL *sdl)
{

}


void sdljeuLibere(SDL *sdl)
{
    // -------------------- FREE AND QUIT -----------------------
    int i=0;
    SDL_FreeSurface(sdl->screen);
    SDL_FreeSurface(sdl->screen2);
    SDL_FreeSurface(sdl->gridge);
    for (i=0;i<8;i++)
    {
        SDL_FreeSurface(sdl->kind[i]);
    }
    SDL_FreeSurface(sdl->nextpiecebackground);
    SDL_FreeSurface(sdl->scorebackground);
    SDL_FreeSurface(sdl->playerbackground);

    SDL_FreeSurface(sdl->text);
    SDL_FreeSurface(sdl->textgameover);
    SDL_FreeSurface(sdl->tuto);
    SDL_FreeSurface(sdl->tuto2);
    SDL_FreeSurface(sdl->textpause);

    /* Fermeture des polices avant l'arrêt de la TTF
    NB : Toutes les polices doivent être fermées */
    TTF_CloseFont(sdl->font);
    TTF_CloseFont(sdl->font1);

    /* Fermeture et libération de system et des sons*/
    FMOD_System_Close(sdl->system);
    FMOD_System_Release(sdl->system);

    FMOD_Sound_Release(sdl->explosion);
    FMOD_Sound_Release(sdl->maintheme);
    FMOD_Sound_Release(sdl->f_legendary1);
    FMOD_Sound_Release(sdl->f_legendary2);
    FMOD_Sound_Release(sdl->f_defeat);
    FMOD_Sound_Release(sdl->f_unstoppable);

    TTF_Quit(); // Arrêt de la TTF
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
            case SDLK_p:
                continuer = 0;
        }
    }
}

