#ifndef TETRIS_H
#define TETRIS_H

#include "binarytrees.h"
#include "board.h"

/* Fonctions de test */

Bool testFallPiece(const Piece piece);
Bool testRotationPiece(const Piece piece);
Bool testLineFilled(const unsigned int posY);
Bool testCollision(const Piece piece);
Bool testLineEmpty(const unsigned int posY);


/* Methodes */

void fallPiece(Piece * piece);
void rotationPiece(Piece * piece);

int destructLines(Board * board);

void drawPiece(Piece * ppiece);
void clearPiece(Piece * ppiece);

int calcScore(const unsigned int currentScore, const unsigned int n_lines);
void displayScore(const Tree tree);

void openScoreData(Tree * ptree, const char filename[]);
void saveScoreData(const Tree * ptree, const char filename[]);


#endif
