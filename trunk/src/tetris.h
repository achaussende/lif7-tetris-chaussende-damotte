#ifndef TETRIS_H
#define TETRIS_H

#include "binarytrees.h"
#include "board.h"

/* ============ Fonctions de test ============= */

//Bool testFallPiece(const Piece * piece);
Bool testRotationPiece(const Piece * piece);
Bool testLineFilled(Board * board, const unsigned int posY);
//Bool testCollision(const Piece * piece);
Bool testLineEmpty(Board * board, const unsigned int posY);
Bool isCurrentPieceMovable(Board * board, Piece * piece, int x, int y);


/* ================ Méthodes ==================  */

void moveCurrentPieceDown(Board * board, Piece *piece);
void moveCurrentPieceLeft(Board * board, Piece *piece);
void moveCurrentPieceRight(Board * board, Piece *piece);
void rotationPiece(Piece * piece);

int destructLines(Board * board);

void drawPiece(Piece * ppiece);
void clearPiece(Piece * ppiece);

int calcScore(const unsigned int currentScore, const unsigned int n_lines);
void displayScore_recursion(const Node * node);
void displayScore(const Tree * scoreTree);

void openScoreData(Tree * ptree, const char filename[]);
void saveScoreData(const Tree * ptree, const char filename[]);


#endif
