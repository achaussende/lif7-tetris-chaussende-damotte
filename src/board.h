#ifndef BOARD_H
#define BOARD_H

#include "piece.h"



/*
* FREE : indique que le point du tableau est vide
* FILLED: indique que le point du tableau contient un bloc (1 ou 2)
*/
enum  { FREE = 0,  FILLED };

typedef struct
{
    Piece * currentPiece; // Pièce actuellement sur la grille
    int gridge[20][10]; // Grille de jeu
}Board;

/* Mutateurs & Accesseurs */

void setCurrentPiece (Board * board, const Piece * piece);
Piece * getCurrentPiece (const Board * board);

/* Autres méthodes */

void initBoard (Board * board);
void freeBoard (Board * board);


#endif
