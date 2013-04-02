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
Bool isCurrentPieceMovable(const Board * board, const int x, const int y);


/* ================ Méthodes ==================  */

void moveCurrentPieceDown(Board * board);
void moveCurrentPieceLeft(Board * board);
void moveCurrentPieceRight(Board * board);
void rotationPiece(Board * board);

int destructLines(Board * board);

void drawPiece(Piece * piece);
void clearPiece(Piece * piece);
void newPiece(Board *board, Piece * piece);

int calcScore(const unsigned int currentScore, const unsigned int n_lines);
void displayScore_recursion(const Node * node);
void displayScore(const Tree * scoreTree);

void openScoreData(Tree * ptree, const char filename[]);
void saveScoreData(const Tree * ptree, const char filename[]);


#endif
