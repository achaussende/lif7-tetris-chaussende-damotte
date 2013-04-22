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
    Piece * p;

    srand(time(NULL)); // initialisation de rand

    /* Initialisation de gridge */

    for (i = 0; i < 20; i++)
    {
        for(j = 0; j < 10; j++)
        {
            board->gridge[i][j] = 0;
        }
    }

    /* Initialisation currentPiece avec une piece au hasard */

    p = createPiece(rand() % 7, rand() % 4);
    setPosX(p, 1);
    setPosY(p, 5);
    setCurrentPiece(board, p);

}

void freeBoard (Board * board)
{
    initBoard(board); //mets toutes les cases de gridge à 0
    freePiece(board->currentPiece);
    free(board);
}
