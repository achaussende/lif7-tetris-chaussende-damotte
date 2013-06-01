/**
    \file [board.c]
    \brief 	Contient les fonctions, procédures, accesseurs et mutateurs nécessaires à la création d'une board
    \author {Damotte Alan, Chaussende Adrien}
    \version 1.0
    \date Avril 2013
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "board.h"


void setCurrentPiece (Board * board, const Piece * piece)
{
    board->currentPiece = piece;
}

Piece * getCurrentPiece (const Board * board)
{
    return board->currentPiece;
}

void initBoard (Board * board)
{
    int i, j;

    /* Initialisation de gridge */

    for (i = 0; i < 20; i++)
    {
        for(j = 0; j < 10; j++)
        {
            board->gridge[i][j] = 0;
        }
    }

    setCurrentPiece(board, NULL); // Pas de pièce de courante

}

void freeBoard (Board * board)
{
    initBoard(board); //mets toutes les cases de gridge à 0
    freePiece(board->currentPiece);
    free(board);
}
