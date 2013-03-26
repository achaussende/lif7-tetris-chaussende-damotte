/* piece.h */
#ifndef PIECE_H
#define PIECE_H

#include "shapes.h"

/* Couleur de chaque pièce */

typedef enum { CYAN = 1, BLUE = 2, ORANGE = 3 , YELLOW = 4,
                        GREEN = 5, PURPLE = 6, RED = 7} Color;

typedef struct
{
    unsigned int kind; // Le type de la pièce
    unsigned int orientation; // Son orientation (sa rotation courante)
    unsigned int color; // Sa couleur

    unsigned int posX; // Son ordonnée dans l'aire de jeu
    unsigned int posY; // Son abscisse dans l'aire de jeu
}Piece;

    void initPiece(Piece * piece, const unsigned int kind, const Color color, const unsigned int orientation);
    Piece * createPiece(const unsigned int kind, const Color color, const unsigned int orientation);
    void freePiece(Piece * piece);


    void setKind(Piece * piece,int kind);
    int getKind(const Piece * piece);

    void setOrientation(Piece * piece,int orientation);
    int getOrientation(const Piece * piece);

    void setColor(Piece * piece,const int color);
    int getColor(const Piece * piece);

    void setPosX(Piece * piece,const int x);
    int getPosX(const Piece * piece);

    void setPosY(Piece * piece,const int y);
    int getPosY(const Piece * piece);


#endif
