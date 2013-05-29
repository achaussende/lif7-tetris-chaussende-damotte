/**
    @file [piece.h]
    @brief 	Contient la déclaration des fonctions, procédures, accesseurs et mutateurs, et la structure d'une pièce
    @author {Damotte Alan, Chaussende Adrien}
    @version 1.0
    @date Mars 2013
*/

/* piece.h */
#ifndef PIECE_H
#define PIECE_H

#include "shapes.h"

/* Couleur de chaque pièce */
/**
    @enum Color
*/
typedef enum {YELLOW = 1, CYAN = 2, GREEN = 3, RED = 4, ORANGE = 5, BLUE = 6, PURPLE = 7} Color;

/**
    @struct Piece
    @brief Structure d'une Piece
*/
typedef struct
{
    unsigned int kind; // Le type de la pièce
    unsigned int orientation; // Son orientation (sa rotation courante)
    Color color; // Sa couleur

    unsigned int posX; // Son ordonnée dans l'aire de jeu
    unsigned int posY; // Son abscisse dans l'aire de jeu
}Piece;

    /**

        @brief Procédure d'initialisation d'une piece
        @param une Piece, un entier kind, une Color, et entier orientation
    */
    void initPiece(Piece * piece, const unsigned int kind, const Color color, const unsigned int orientation);

    /**

        @brief Fonction de creation de Piece
        @param un entier kind, un entier orientation
        @return une Piece
    */
    Piece * createPiece(const unsigned int kind, const unsigned int orientation);

    /**

        @brief Procédure de libération d'une piece
        @param une Piece
    */
    void freePiece(Piece * piece);

    /**

        @brief Mutateur du kind de la piece
        @param une Piece et un entier kind
    */
    void setKind(Piece * piece,int kind);

    /**

        @brief Assesseur du kind de la piece
        @param une Piece
        @return un entier
    */
    int getKind(const Piece * piece);

    /**

        @brief Mutateur de l'orientation de la piece
        @param une Piece et un entier orientation
    */
    void setOrientation(Piece * piece,int orientation);

    /**

        @brief Assesseur de l'orientation de la piece
        @param une Piece
        @return un entier
    */
    int getOrientation(const Piece * piece);

    /**

        @brief Mutateur de la couleur de la piece
        @param une Piece et une Color
    */
    void setColor(Piece * piece,const Color color);

    /**

        @brief Assesseur de la couleur de la piece
        @param une Piece
        @return une Color
    */
    Color getColor(const Piece * piece);

    /**

        @brief Mutateur de la position x de la piece
        @param une Piece et un entier
    */
    void setPosX(Piece * piece,const int x);

    /**

        @brief Assesseur de la position x de la piece
        @param une Piece
        @return un entier
    */
    int getPosX(const Piece * piece);

    /**

        @brief Mutateur de la position y de la piece
        @param une Piece et un entier
    */
    void setPosY(Piece * piece,const int y);

    /**

        @brief Assesseur de la position y de la piece
        @param une Piece
        @return un entier
    */
    int getPosY(const Piece * piece);


#endif
