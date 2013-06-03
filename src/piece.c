/**
    \file [piece.c]
    \brief 	Contient les fonctions, procédures,
    accesseurs et mutateurs nécessaires à la création d'une pièce
    \author {Damotte Alan, Chaussende Adrien}
    \version 1.1
    \date Avril 2013
*/

#include "piece.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


void initPiece(Piece * piece, unsigned int kind, const Color color,
               unsigned int orientation)
{
    setColor(piece, color);
    setKind(piece, kind);
    setOrientation(piece, orientation);
}

Piece * createPiece(unsigned int kind, unsigned int orientation)
{
    Piece* piece=(Piece*)malloc(sizeof(Piece));

    switch (kind) {

        case 0:
        {
            initPiece(piece, kind, YELLOW, orientation);
        }
        break;

        case 1:
        {
            initPiece(piece, kind, CYAN, orientation);
        }
        break;
        case 2:
        {
            initPiece(piece, kind, GREEN, orientation);
        }
        break;
        case 3:
        {
            initPiece(piece, kind, RED, orientation);
        }
        break;
        case 4:
        {
            initPiece(piece, kind, ORANGE, orientation);
        }
        break;
        case 5:
        {
            initPiece(piece, kind, BLUE, orientation);
        }
        break;
        case 6:
        {
            initPiece(piece, kind, PURPLE, orientation);
        }
        break;
        default:
        {
           printf("Erreur. \n");
        }
        break;
}
    return piece;
}

void freePiece(Piece * piece)
{
    free(piece);
}


void setKind(Piece * piece,int kind)
{
    piece->kind = kind;
}

void setOrientation(Piece * piece,int orientation)
{
    piece->orientation = orientation;
}

int getKind(const Piece * piece)
{
    return piece->kind;
}

int getOrientation(const Piece * piece)
{
    return piece->orientation;
}

void setColor(Piece * piece, Color color)
{
    piece->color = color;
}

Color getColor(const Piece * piece)
{
    return piece->color;
}

void setPosX(Piece * piece,int x)
{
    piece->posX = x;
}

int getPosX(const Piece * piece)
{
    return piece->posX;
}

void setPosY(Piece * piece,int y)
{
    piece->posY = y;
}

int getPosY(const Piece * piece)
{
    return piece->posY;
}
