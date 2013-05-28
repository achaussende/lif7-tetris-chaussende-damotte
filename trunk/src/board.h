/**
    \file [board.h]
    \brief 	Contient la déclaration des fonctions, procédures, accesseurs et mutateurs, et la structure d'une board
    \author {Damotte Alan, Chaussende Adrien}
    \version 1.0
    \date Avril 2013
*/

#ifndef BOARD_H
#define BOARD_H

#include <time.h>

#include "piece.h"



/*
* FREE : indique que le point du tableau est vide
* FILLED: indique que le point du tableau contient un bloc (1 ou 2)
*/
/**
    @enum Visited
*/
enum  { FREE = 0,  FILLED };

/**
    @struct Board
    @brief Structure d'une Board
*/
typedef struct
{
    Piece * currentPiece; // Pièce actuellement sur la grille
    Piece * nextPiece;
    int gridge[20][10]; // Grille de jeu
}Board;

/* Mutateurs & Accesseurs */

/**
    @fn setCurrentPiece
    @brief Mutateur de la piece
    @param une Board et une Piece
*/
void setCurrentPiece (Board * board, const Piece * piece);

/**
    @fn getCurrentPiece
    @brief Assesseur de la piece
    @param une Board et une Piece
    @return une Piece
*/
Piece * getCurrentPiece (const Board * board);

/* Autres méthodes */
/**
    @fn initBoard
    @brief Initialise une Board
    @param une Board
*/
void initBoard (Board * board);
/**
    @fn freeBoard
    @brief Free une Board
    @param une Board
*/
void freeBoard (Board * board);


#endif
