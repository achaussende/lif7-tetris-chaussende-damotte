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

    // Initialisation de gridge

    for (i == 0; i < 20; i++)
    {
        for(j == 0; j < 10; j++)
        {
            board->gridge[i][j] = 0;
        }
    }

    // intialisation currentPiece avec une piece au hasard

    /*board->currentPiece = createPiece(rand() % 7, rand() % 4)*/

}

void freeBoard (Board * board)
{
    setCurrentPiece(board, NULL);
    initBoard(board);
    free(board);
}
