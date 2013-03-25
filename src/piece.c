/* piece.cpp */
#include "piece.h"

// *************** A regarder ****************
/*Piece()
{
    // Rien à faire
}

Piece(int k, int o)
{
    kind = k;
    orientation = o;
}

Piece(const Piece &p)
{
    kind = p.kind;
    orientation = p.orientation;
    color = p.color;
    posX = p.posX;
    posY = p.posY;
}*/

void setKind(Piece piece,int kind)
{
    piece.kind = k;
}

void setOrientation(Piece piece,int orientation)
{
    piece.orientation = orientation;
}

int getKind(Piece piece)
{
    return piece.kind;
}

int getOrientation(Piece piece)
{
    return piece.orientation;
}

void setColor(Piece piece,int color)
{
    piece.color = color;
}

int getColor(Piece piece)
{
    return piece.color;
}

void setPosX(Piece piece,int x)
{
    piece.posX = x;
}

int getPosX(Piece piece)
{
    return piece.posX;
}

void setPosY(Piece piece,int y)
{
    piece.posY = y;
}

int getPosY(Piece piece)
{
    return piece.posY;
}
