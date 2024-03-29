/**
    \file [LoopTETRIS_SDL.h]
    \brief 	Contient la déclaration des fonctions et
    structures nécessaires à l'affichage du jeu
    \author {Damotte Alan, Chaussende Adrien}
    \version 1.1
    \date Avril-Mai 2013
*/

#ifndef _LOOPTETRIS_SDL_H
#define _LOOPTETRIS_SDL_H
#include <SDL/SDL_image.h>
#include "../lib/FMOD/inc/fmod.h"
#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>
#include "tetris.h"

/**
    @struct SDL
    @brief Structure d'une SDL
*/
typedef struct
{

	FMOD_SYSTEM * system;
    FMOD_SOUND * explosion;
    FMOD_SOUND * maintheme;
    FMOD_SOUND * f_legendary1;
    FMOD_SOUND * f_legendary2;
    FMOD_SOUND * f_defeat;
    FMOD_SOUND * f_unstoppable;

    SDL_Rect position1;
    SDL_Rect positionpiece;
    SDL_Rect positionName;

	SDL_Surface * screen;
	SDL_Surface * screen2;
	SDL_Surface * piece;
	SDL_Surface * gridge;
	SDL_Surface * kind[7];
	SDL_Surface * nextpiecebackground;
    SDL_Surface * holdpiecebackground;
    SDL_Surface * scorebackground;
    SDL_Surface * playerbackground;
    SDL_Surface * text;
    SDL_Surface * textgameover;
    SDL_Surface * textpause;
    SDL_Surface * tuto;
    SDL_Surface * tuto2;
    SDL_Surface * tuto3;
    SDL_Surface * entername;
    SDL_Surface * textplayername;
    SDL_Surface * playername;

	Tetris * tetris;

    TTF_Font * font;
    TTF_Font * font1;
    TTF_Font * font2;

}SDL;

/**

        @brief Procédure d'initialisation d'une SDL
        @param pointeur sur une SDL
*/
void sdlgameInit(SDL *sdl);

/**

        @brief Boucle SDL
        @param pointeur sur une SDL
*/
void sdlgameLoop(SDL *sdl);

/**

        @brief Procédure de libération d'une SDL
        @param pointeur sur une SDL
*/
void sdlgameFree(SDL *sdl);

/**

        @brief Procédure d'application de surface
        @param pointeur sur une SDL_surface source,
        pointeur sur une SDL_surface destination,
        entier pour coordonnées x, entier pour coordonnées y
*/
void SDL_apply_surface( SDL_Surface* source, SDL_Surface* destination,
                       int x, int y );

/**

        @brief Fonction de chargement d'image dans une SDL_surface
        @param pointeur sur une chaine de caractères de nom de fichier
*/
SDL_Surface *SDL_load_image(const char* filename );

/**

        @brief Fonction d'affichage de la grille de jeu (10x20)
        @param deux pointeurs sur  SDL_surfaces screen et gridge,
        pointeur sur un tableau de SDL_Surface pour le kind,
        pointeur sur un Tetris, deux entiers de position
*/
SDL_Surface* SDLdisplayscreen(SDL_Surface* screen, SDL_Surface* gridge,
                              SDL_Surface* kind[8], Tetris* tetris,
                              int positionX, int positionY);

/**

        @brief Fonction d'affichage d'une pièce dans un tableau 4x4
        @param deux pointeurs sur SDL_surfaces screen et
        nextholdpiecebakcground,
        pointeur sur un tableau de SDL_Surface pour le kind,
        pointeur sur une Piece, deux entiers de position
*/
SDL_Surface* SDLdisplaypiece(SDL_Surface* screen,
                             SDL_Surface* nextholdpiecebackground,
                             SDL_Surface* kind[8], Piece * piece,
                             int positionX, int positionY);

/**

        @brief Fonction de pause
*/
void pause();

/**

        @brief procédure de test regression
        @param pointeur sur une SDL
*/
void sdltestRegression(SDL *sdl);

#endif
