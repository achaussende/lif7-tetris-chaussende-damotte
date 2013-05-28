/**
    \file [LoopTETRIS_SDL.h]
    \brief 	Contient la déclaration des fonctions et structures nécessaires à l'affichage du jeu
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
	Tetris tetris;
	SDL_Surface* screen;
	SDL_Surface* screen2;
	SDL_Surface* piece;
	SDL_Surface* gridge;
	SDL_Surface* score;
	SDL_Surface* kind[8];
	SDL_Surface *nextpiecebackground;
    SDL_Surface *holdpiecebackground;
    SDL_Surface *scorebackground;
    SDL_Surface *playerbackground;
    SDL_Surface *text;
    SDL_Surface *textgameover;

    SDL_Color colorBlack;
    SDL_Color colorWhite;

    SDL_Rect position1;
    SDL_Rect positionpiece;

    TTF_Font * font;

	FMOD_SYSTEM *system;
    FMOD_SOUND *explosion;
    FMOD_SOUND *maintheme;
    FMOD_SOUND *f_legendary1;
    FMOD_SOUND *f_legendary2;
    FMOD_SOUND *f_defeat;
    FMOD_SOUND *f_unstoppable;
}SDL;

/**
        @fn sdljeuInit
        @brief Procédure d'initialisation d'une SDL
        @param une SDL
*/
void sdljeuInit(SDL *sdl);

/**
        @fn sdljeuBoucle
        @brief Boucle SDL
        @param une SDL
*/
void sdljeuBoucle(SDL *sdl);

/**
        @fn sdljeuLibere
        @brief Procédure de libération d'une SDL
        @param une SDL
*/
void sdljeuLibere(SDL *sdl);

/**
        @fn sdljeuAff
        @brief Procédure d'affichage d'une SDL
        @param une SDL
*/
void sdljeuAff(SDL *sdl);

/**
        @fn SDL_apply_surface
        @brief Procédure d'application de surface
        @param une SDL_surface source, une SDL_surface destination, int x, int y
*/
void SDL_apply_surface( SDL_Surface* source, SDL_Surface* destination, int x, int y );

/**
        @fn SDL_load_image
        @brief Fonction de chargement d'image dans une SDL_surface
        @param une chaine de caractères de nom de fichier
*/
SDL_Surface *SDL_load_image(const char* filename );

/**
        @fn SDLdisplayscreen
        @brief Fonction d'affichage de la grille de jeu (10x20)
        @param deux SDL_surfaces screen et gridge, un tableau de SDL_Surface pour le kind, un Tetris, deux entiers de position
*/
SDL_Surface* SDLdisplayscreen(SDL_Surface* screen, SDL_Surface* gridge, SDL_Surface* kind[8], Tetris* tetris, int positionX, int positionY);

/**
        @fn SDLdisplaypiece
        @brief Fonction d'affichage d'une pièce dans un tableau 4x4
        @param deux SDL_surfaces screen et nextholdpiecebakcground, un tableau de SDL_Surface pour le kind, une Piece, deux entiers de position
*/
SDL_Surface* SDLdisplaypiece(SDL_Surface* screen, SDL_Surface* nextholdpiecebackground, SDL_Surface* kind[8], Piece * piece, int positionX, int positionY);

/**
        @fn pause
        @brief Fonction de pause
*/
void pause();

/**
        @fn sdltestRegression
        @brief procédure de test regression
        @param une SDL
*/
void sdltestRegression(SDL *sdl);

#endif
