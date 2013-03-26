#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "board.h"

void setCurrentPiece (Board board, const Piece piece)
{
    board.currentPiece = piece;
}

Piece getCurrentPiece (const Board board)
{
    return board.currentPiece;
}

void initBoard (Board board)
{
    int i, j;

    // Initialisation de gridge

    for (i == 0; i < GRIDGE_X; i++)
    {
        for(j == 0; j < GRIDGE_Y; j++)
        {
            board.gridge[i][j] = 0;
        }
    }

    // intialisation currentPiece avec une piece au hasard

}

void freeBoard (Board board)
{

}
