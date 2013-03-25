/* piece.h */
#ifndef PIECE_H
#define PIECE_H

#include "shapes.h"

enum { CYAN = 1, BLUE, ORANGE, YELLOW, GREEN, PURPLE, RED}; // Les couleurs de chaque pièce, GHOST est pour la pièce fantôme

/* Les coordonnées du point de pivot de la pièce */
const int PIVOT_X = 1;
const int PIVOT_Y = 2;

typedef struct
{
    int kind; // Le type de la pièce
    int orientation; // Son orientation (sa rotation courante)
    int color; // Sa couleur

    int posX; // Son ordonnée dans l'aire de jeu
    int posY; // Son abscisse dans l'aire de jeu
}Piece;

    Piece();
    Piece(int k, int o);
    Piece(const Piece &p);

    void setKind(Piece piece,int kind);
    int getKind(Piece piece);

    void setOrientation(Piece piece,int orientation);
    int getOrientation(Piece piece);

    void setColor(Piece piece,int color);
    int getColor(Piece piece);

    void setPosX(Piece piece,int x);
    int getPosX(Piece piece);

    void setPosY(Piece piece,int y);
    int getPosY(Piece piece);


#endif
