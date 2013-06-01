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


void SDL_apply_surface( SDL_Surface* source, SDL_Surface* destination,
                        int positionX, int positionY )
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



SDL_Surface* SDLdisplayscreen(SDL_Surface* screen, SDL_Surface* gridge,
                               SDL_Surface* kind[7], Tetris* tetris,
                                int positionX, int positionY)
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

SDL_Surface* SDLdisplaypiece(SDL_Surface* screen,
                             SDL_Surface* nextpiecebackground,
                             SDL_Surface* kind[7], Piece * piece,
                             int positionX, int positionY)
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
                    SDL_apply_surface(kind[0],screen, positionX+(i*20),
                                       positionY+(j*20));

                }
                break;

                case 1:
                {
                    SDL_apply_surface(kind[1],screen, positionX+(i*20),
                                       positionY+(j*20));

                }
                break;
                case 2:
                {
                    SDL_apply_surface(kind[2],screen, positionX+(i*20),
                                       positionY+(j*20));

                }
                break;
                case 3:
                {
                    SDL_apply_surface(kind[3],screen, positionX+(i*20),
                                       positionY+(j*20));

                }
                break;
                case 4:
                {
                    SDL_apply_surface(kind[4],screen, positionX+(i*20),
                                       positionY+(j*20));

                }
                break;
                case 5:
                {
                    SDL_apply_surface(kind[5],screen, positionX+(i*20),
                                       positionY+(j*20));

                }
                break;
                case 6:
                {
                    SDL_apply_surface(kind[6],screen, positionX+(i*20),
                                       positionY+(j*20));

                }
                break;

                default:
                {
                   /* SDL_apply_surface(kind[7],screen, positionX+(i*20),
                                         positionY+(j*20));*/
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
    /* Initialisation des champs de sdl*/
        /* SDL Surfaces */
    sdl->screen = NULL;
    sdl->screen2 = NULL;
    sdl->piece = NULL;
    sdl->gridge = NULL;
    sdl->nextpiecebackground = NULL;
    sdl->holdpiecebackground = NULL;
    sdl->scorebackground = NULL;
    sdl->playerbackground = NULL;



        /* Surfaces pour le texte */
    sdl->text = NULL;
    sdl->textgameover = NULL;
    sdl->textpause = NULL;
    sdl->tuto = NULL;
    sdl->tuto2 = NULL;
    sdl->textplayername = NULL;
    sdl->playername = NULL;

        /* Rectangle de position */
    sdl->position1.x = 0;
    sdl->position1.y = 0;
    sdl->positionpiece.x = 0;
    sdl->positionpiece.y = 0;
    sdl->positionName.x = 0;
    sdl->positionName.y = 0;

        /* FMOD */
    FMOD_System_Create(&sdl->system);

    sdl->explosion = NULL;
    sdl->maintheme = NULL;
    sdl->f_legendary1 = NULL;
    sdl->f_legendary2 = NULL;
    sdl->f_defeat = NULL;
    sdl->f_unstoppable = NULL;


        /* Initialisation de screen */
    SDL_Init(SDL_INIT_VIDEO);
    sdl->screen = SDL_SetVideoMode(1000, 600, 32,
                                   SDL_SWSURFACE| SDL_RESIZABLE |
                                   SDL_DOUBLEBUF);

        /* Initialisation de TTF */
    if(TTF_Init() == -1)
    {
        printf("Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

        /* Initialisation de FMOD */
            /* 32 est le nombre de sons gérés par FMOD */
    FMOD_System_Init(sdl->system, 32, FMOD_INIT_NORMAL, NULL);
    FMOD_System_CreateSound(sdl->system, "../data/sounds/explode.wav",
                            FMOD_CREATESAMPLE, 0, &(sdl->explosion));

        /* Initialisation des samples */
    FMOD_System_CreateSound(sdl->system, "../data/sounds/f_legendary1.mp3",
                            FMOD_CREATESAMPLE, 0, &(sdl->f_legendary1));
    FMOD_System_CreateSound(sdl->system, "../data/sounds/f_legendary2.mp3",
                            FMOD_CREATESAMPLE, 0, &(sdl->f_legendary2));
    FMOD_System_CreateSound(sdl->system, "../data/sounds/f_defeat.mp3",
                            FMOD_CREATESAMPLE, 0, &(sdl->f_defeat));
    FMOD_System_CreateSound(sdl->system, "../data/sounds/f_unstoppable.mp3",
                            FMOD_CREATESAMPLE, 0, &(sdl->f_unstoppable));

        /* Initialisation des musiques */
    FMOD_System_CreateSound(sdl->system,
                    "../data/sounds/theglitchmob_howtobeeatenbyawoman.mp3",
                            FMOD_SOFTWARE | FMOD_2D
                            | FMOD_CREATESTREAM | FMOD_LOOP_NORMAL, 0,
                             &(sdl->maintheme));

            /* On active la répétition en boucle puis on joue la musique */
    FMOD_Sound_SetLoopCount(sdl->maintheme, -1);
    FMOD_System_PlaySound(sdl->system, FMOD_CHANNEL_FREE, sdl->maintheme, 0, NULL);

        /* Coloration de la surface ecran en gris */
    SDL_FillRect(sdl->screen, NULL, SDL_MapRGB(sdl->screen->format, 0, 0, 0));
    sdl->gridge = SDL_load_image("../data/gridge.bmp");

        //Initialisation de kind avec les images des couleurs des pièces
    sdl->kind[0]=SDL_load_image("../data/piecejaune.bmp");
    sdl->kind[1]=SDL_load_image("../data/piececyan.bmp");
    sdl->kind[2]=SDL_load_image("../data/piecevert.bmp");
    sdl->kind[3]=SDL_load_image("../data/piecerouge.bmp");
    sdl->kind[4]=SDL_load_image("../data/pieceorange.bmp");
    sdl->kind[5]=SDL_load_image("../data/piecebleue.bmp");
    sdl->kind[6]=SDL_load_image("../data/pieceviolet.bmp");

        //Chargement de l'image d'écran de jeu et la pièce suivante
    sdl->screen2 = SDL_load_image("../data/screen.bmp");
    sdl->nextpiecebackground = SDL_load_image("../data/nextpiece.bmp");
    sdl->holdpiecebackground = SDL_load_image("../data/nextpiece.bmp");
    sdl->scorebackground = SDL_load_image("../data/score2.bmp");
    sdl->playerbackground = SDL_load_image("../data/score2.bmp");

    SDL_WM_SetCaption("LegendaryTetris", NULL);

    /* Variables pour le TTF */

    sdl->font = TTF_OpenFont("../data/gameover.ttf", 65);
    sdl->font1 = TTF_OpenFont("../data/gameover.ttf", 30);
    sdl->font2 = TTF_OpenFont("../data/gameover.ttf", 40);

    /* Lancement du Tetris */
    sdl->tetris = startTetris();
    openScoreData(sdl->tetris->treescores, "../data/scores.txt");

}


void sdljeuBoucle(SDL *sdl)
{
    /* Variables temporaires */

    /* Couleurs pour les polices TTF */
    SDL_Color colorWhite = {255, 255, 255};

    /* Autres variables */
    Piece * nextpiece = NULL;
    Piece * holdpiece = NULL;
    Player * player = NULL;

    int destructlines = 0;
    int n_lines = 0;
    int posx, posy;
    int score = 0;
    int temp = 0;

    int sound_played = 0; /* Pour les sons de palier de score */

    char s_score[20];

    /* Score */
    sprintf(s_score, "%u", score);
    sdl->text = TTF_RenderText_Blended(sdl->font, s_score, colorWhite);

    /* ------------ Boucle de nom de joueur -------------- */
    sdl->textplayername = TTF_RenderText_Blended(sdl->font, "Player Name ?",
                                                 colorWhite);
    /* Blit de text */
    SDL_apply_surface(sdl->textplayername, sdl->screen, 420, 275);

    SDL_Event beginevent;

    int nbLetters = 1;
    int begin=1;

    char *playername1;
    playername1 = (char*)calloc(nbLetters,sizeof(char));
    playername1[nbLetters-1] = '\0';

    sdl->positionName.x = 420;
    sdl->positionName.y = 320;

    while(begin)
    {
        SDL_WaitEvent(&beginevent);
        switch(beginevent.type)
        {
            case SDL_QUIT:
            begin = 0;
            break;

            case SDL_KEYDOWN:
            if(beginevent.key.keysym.sym == SDLK_RETURN)
            {
                begin = 0;
            }
            else if((beginevent.key.keysym.sym == SDLK_BACKSPACE) &&
                    (nbLetters > 1))
            {
                SDL_FillRect(sdl->screen,&(sdl->positionName),
                             SDL_MapRGB(sdl->screen->format,0,0,0));
                nbLetters--;

                playername1=(char*)realloc(playername1, nbLetters*sizeof(char));
                playername1[nbLetters-1] = '\0';

                sdl->playername = TTF_RenderText_Solid(sdl->font,
                                                       playername1, colorWhite);
                SDL_BlitSurface(sdl->playername, NULL, sdl->screen,
                                &(sdl->positionName));
            }

            else
            {

                if(beginevent.key.keysym.sym != SDLK_BACKSPACE)
                {
                    if(nbLetters<26)
                    {
                        SDL_FillRect(sdl->screen,&(sdl->positionName),
                                     SDL_MapRGB(sdl->screen->format,0,0,0));
                        SDL_Flip(sdl->screen);
                        playername1 = (char*)realloc(playername1,(nbLetters + 1)*sizeof(char));

                        playername1[nbLetters-1] = beginevent.key.keysym.sym;
                        playername1[nbLetters] = '\0';
                        nbLetters++;
                    }
                }
            }
            SDL_FillRect(sdl->screen,&(sdl->positionName),
                         SDL_MapRGB(sdl->screen->format,0,0,0));
            sdl->playername = TTF_RenderText_Solid(sdl->font,
                                                   playername1,colorWhite);
            SDL_BlitSurface(sdl->playername, NULL,
                            sdl->screen, &(sdl->positionName));

            SDL_Flip(sdl->screen);
        }
    }


    SDL_apply_surface(sdl->screen2,sdl->screen, 0, 0);

    sdl->position1.x = sdl->screen->w / 2 - sdl->gridge->w / 2;
	sdl->position1.y = (sdl->screen->h / 2 - sdl->gridge->h / 2);

    SDL_apply_surface(sdl->gridge,sdl->screen, sdl->position1.x,
                      sdl->position1.y);
    SDL_apply_surface(sdl->scorebackground,sdl->screen, sdl->position1.x-307,
                      sdl->position1.y+82);
    SDL_apply_surface(sdl->playerbackground,sdl->screen, sdl->position1.x-307,
                      sdl->position1.y+19);

    nextpiece = getTetrisNextPiece(sdl->tetris);

    SDLdisplayscreen(sdl->screen, sdl->gridge, sdl->kind, sdl->tetris,
                     sdl->position1.x, sdl->position1.y);
    SDLdisplaypiece(sdl->screen, sdl->nextpiecebackground, sdl->kind, nextpiece,
                    sdl->position1.x+280, sdl->position1.y+50);
    SDL_apply_surface(sdl->holdpiecebackground, sdl->screen,
                      sdl->position1.x+280, sdl->position1.y+250);

    sdl->tuto = TTF_RenderText_Blended(sdl->font1, "P = Pause", colorWhite);
    sdl->tuto2 = TTF_RenderText_Blended(sdl->font1, "C = Hold a line", colorWhite);

    SDL_apply_surface(sdl->tuto, sdl->screen, 50, 500); /* Blit de tuto */
    SDL_apply_surface(sdl->tuto2, sdl->screen, 50, 520); /* Blit de tuto2 */

    createPlayer(playername1,score);
    sdl->playername = TTF_RenderText_Blended(sdl->font2, playername1,
                                             colorWhite);
    /* Blit du nom du joueur */
    SDL_apply_surface(sdl->playername, sdl->screen,
                      sdl->position1.x-295, sdl->position1.y+40);


    /* Fin boucle nom de joueur */

    /*--------------------- BOUCLE -----------------------*/

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
                    if (pausebutton == 0)
                    {
                        rotationPiece(sdl->tetris->board);
                        SDLdisplayscreen(sdl->screen, sdl->gridge, sdl->kind,
                                         sdl->tetris, sdl->position1.x,
                                         sdl->position1.y);
                        temp = 0;
                    }
                        break;

                    case SDLK_DOWN: // Flèche bas
                    if (pausebutton == 0)
                    {
                        moveCurrentPieceDown(sdl->tetris->board);
                        SDLdisplayscreen(sdl->screen, sdl->gridge, sdl->kind,
                                         sdl->tetris, sdl->position1.x,
                                         sdl->position1.y);
                    }
                        break;

                    case SDLK_RIGHT: // Flèche droite
                    if (pausebutton == 0)
                    {
                        moveCurrentPieceRight(sdl->tetris->board);
                        SDLdisplayscreen(sdl->screen, sdl->gridge, sdl->kind,
                                         sdl->tetris, sdl->position1.x,
                                         sdl->position1.y);
                        temp = 0;
                    }
                        break;

                    case SDLK_LEFT: // Flèche gauche
                    if (pausebutton == 0){
                        moveCurrentPieceLeft(sdl->tetris->board);
                        SDLdisplayscreen(sdl->screen, sdl->gridge, sdl->kind,
                                         sdl->tetris, sdl->position1.x,
                                         sdl->position1.y);
                        temp = 0;
                    }
                        break;

                    case SDLK_SPACE: // Barre espace
                    if (pausebutton == 0){
                        dropCurrentPiece(sdl->tetris->board);
                        SDLdisplayscreen(sdl->screen, sdl->gridge, sdl->kind,
                                         sdl->tetris, sdl->position1.x,
                                         sdl->position1.y);;
                        temp = 2;
                        break;
                    }
                    case SDLK_c: // Touche c
                    if (pausebutton == 0){
                        if (change)
                        {
                            holdPiece(sdl->tetris);
                            holdpiece = getTetrisHoldPiece(sdl->tetris);
                            SDLdisplaypiece(sdl->screen,
                                            sdl->holdpiecebackground,
                                            sdl->kind, holdpiece,
                                            sdl->position1.x+280,
                                            sdl->position1.y+250);
                            SDLdisplayscreen(sdl->screen, sdl->gridge,
                                             sdl->kind,
                                             sdl->tetris, sdl->position1.x,
                                             sdl->position1.y);
                            change = 0;
                        }
                    }

                        break;
                    case SDLK_p: // Touche p
                            if(pausebutton == 0)
                                pausebutton = 1;
                            else if(pausebutton == 1)
                                pausebutton = 0;
                        break;

                    case SDLK_ESCAPE: // Bouton ECHAP
                    next = 0;
                    return;
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
        if (pausebutton == 0)
        {
            /* Si 1000 ms se sont écoulées depuis le dernier tour de boucle */

            if (tempsActuel - tempsPrecedent > 1000-(10*destructlines))
            {
                moveCurrentPieceDown(sdl->tetris->board);
                SDLdisplayscreen(sdl->screen, sdl->gridge, sdl->kind,
                                 sdl->tetris, sdl->position1.x,
                                 sdl->position1.y);
                tempsPrecedent = tempsActuel; /* Le temps "actuel" devient le temps "precedent" pour nos futurs calculs */
                temp++;
            }
        }
        else
        {
          sdl->textpause = TTF_RenderText_Blended(sdl->font, "PAUSE", colorWhite);
          SDL_apply_surface(sdl->textpause, sdl->screen, 460, 275); // Blit de text
        }

        /* Après pose de la currentPiece, la nextPiece devient la currentPiece
           puis nouvelle nextPiece*/

        posx = getPosX(sdl->tetris->board->currentPiece);
        posy = getPosY(sdl->tetris->board->currentPiece);
        if(isCurrentPieceMovable(sdl->tetris->board, posx, posy + 1) == FALSE
           &&
           testFallPiece(sdl->tetris->board) == FALSE && temp >= 2)
        {
           /* Destruction des lignes et Calcul du score */
           n_lines = destructLines(sdl->tetris->board);
           FMOD_System_PlaySound(sdl->system, FMOD_CHANNEL_FREE, sdl->explosion,
                                  0, NULL);

           destructlines = destructlines + n_lines;
           score = calcScore(score, n_lines);

            if(score >= 50000 && sound_played == 0)
            {
                FMOD_System_PlaySound(sdl->system, FMOD_CHANNEL_FREE,
                                      sdl->f_unstoppable, 0, NULL);
                sound_played = 1;
            }

            if(score >= 100000 && sound_played == 1)
            {
                FMOD_System_PlaySound(sdl->system, FMOD_CHANNEL_FREE,
                                      sdl->f_legendary1, 0, NULL);
                sound_played = 2;
            }
            if(score >= 150000 && sound_played == 2)
            {
                FMOD_System_PlaySound(sdl->system, FMOD_CHANNEL_FREE,
                                      sdl->f_legendary2, 0, NULL);
                sound_played = 3;
            }

            /* Affichage du score */
            sprintf(s_score, "%u", score);
            SDL_FreeSurface(sdl->text);

            sdl->text = TTF_RenderText_Blended(sdl->font, s_score, colorWhite);

            if(testGameOver(sdl->tetris->board) == TRUE)
            {
                next=0;
                endgame=1;
                FMOD_System_PlaySound(sdl->system, FMOD_CHANNEL_FREE,
                                      sdl->f_defeat, 0, NULL);
                sdl->textgameover = TTF_RenderText_Blended(sdl->font,
                                    "GAME OVER ! TRY AGAIN ? Y/N",
                                    colorWhite);

                /* Blit de textgameover */
                SDL_apply_surface(sdl->textgameover, sdl->screen, 320, 275);

                /* Enregistrement du score */
                    player = createPlayer(playername1, score);
                    insertPlayerInTree(sdl->tetris->treescores, player);
                    saveScoreData(sdl->tetris->treescores, "../data/scores.txt");
                    displayScore(sdl->tetris->treescores);

            }
            else
            {
                gameStep(sdl->tetris);
                nextpiece = getTetrisNextPiece(sdl->tetris);
                SDLdisplaypiece(sdl->screen, sdl->nextpiecebackground,
                                sdl->kind, nextpiece, sdl->position1.x+280,
                                sdl->position1.y+50);
                change = 1;
            }
        }

        SDL_Flip(sdl->screen);
        SDL_apply_surface(sdl->scorebackground, sdl->screen,
                          sdl->position1.x-307, sdl->position1.y+82);
        /* Blit de text */
        SDL_apply_surface(sdl->text, sdl->screen, sdl->position1.x-295,
                          sdl->position1.y+100);
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
<<<<<<< .mine
                    FMOD_Sound_Release(sdl->maintheme);
                    sdljeuLibere(sdl);
                    sdljeuInit(sdl);
                    sdljeuBoucle(sdl);

=======
                        FMOD_Sound_Release(sdl->maintheme);
                        sdljeuInit(sdl);
>>>>>>> .r118
                    break;

                    case SDLK_n: // Touche n
                            return;
                    break;

                    default:
                    break;
                }
        }
    }
    pause();


}


void sdljeuLibere(SDL *sdl)
{
    // -------------------- FREE AND QUIT -----------------------
    int i;

    freeTetris(sdl->tetris);

    SDL_FreeSurface(sdl->gridge);
    for (i=0;i<7;i++)
    {
        SDL_FreeSurface(sdl->kind[i]);
    }
    SDL_FreeSurface(sdl->piece);
    SDL_FreeSurface(sdl->nextpiecebackground);
    SDL_FreeSurface(sdl->scorebackground);
    SDL_FreeSurface(sdl->playerbackground);
    SDL_FreeSurface(sdl->holdpiecebackground);
    SDL_FreeSurface(sdl->text);
    SDL_FreeSurface(sdl->textgameover);
    SDL_FreeSurface(sdl->tuto);
    SDL_FreeSurface(sdl->tuto2);
    SDL_FreeSurface(sdl->textpause);
    SDL_FreeSurface(sdl->textplayername);
    SDL_FreeSurface(sdl->playername);

    SDL_FreeSurface(sdl->screen);
    SDL_FreeSurface(sdl->screen2);

    /* Fermeture des polices avant l'arrêt de la TTF
    NB : Toutes les polices doivent être fermées */
    TTF_CloseFont(sdl->font);
    TTF_CloseFont(sdl->font1);
    TTF_CloseFont(sdl->font2);

    /* Fermeture et libération de system et des sons*/


    FMOD_Sound_Release(sdl->explosion);

    FMOD_Sound_Release(sdl->f_legendary1);
    FMOD_Sound_Release(sdl->f_legendary2);
    FMOD_Sound_Release(sdl->f_defeat);
    FMOD_Sound_Release(sdl->f_unstoppable);
    FMOD_Sound_Release(sdl->maintheme);

    FMOD_System_Close(sdl->system);
    FMOD_System_Release(sdl->system);

    TTF_Quit(); // Arrêt de la TTF
    SDL_Quit(); // Arrêt de la SDL (libération de la mémoire)

}

void sdltestRegression(SDL *sdl)
{
    sdljeuInit(sdl);
    sdljeuBoucle(sdl);
    sdljeuLibere(sdl);

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

