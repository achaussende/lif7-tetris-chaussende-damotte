/**
    \file [board.h]
    \brief 	Contient la déclaration des fonctions, procédures,
    accesseurs et mutateurs, et la structure d'une board
    \author {Damotte Alan, Chaussende Adrien}
    \version 1.0
    \date Avril 2013
*/

#ifndef BOARD_H
#define BOARD_H
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
    Piece * currentPiece; /* Pièce actuellement sur la grille*/
    int gridge[20][10]; /* Grille de jeu*/
}Board;

/* Mutateurs & Accesseurs */

/**

    @brief Mutateur de la piece
    @param pointeur sur une Board et pointeur sur une Piece
*/
void setCurrentPiece (Board * board, const Piece * piece);

/**

    @brief Assesseur de la piece
    @param pointeur sur une Board
    @return pointeur sur une Piece
*/
Piece * getCurrentPiece (const Board * board);

/* Autres méthodes */
/**

    @brief Initialise une Board
    @param pointeur sur une Board
*/
void initBoard (Board * board);
/**

    @brief Free une Board
    @param pointeur sur une Board
*/
void freeBoard (Board * board);


#endif
