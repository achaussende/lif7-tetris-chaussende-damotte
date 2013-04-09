#ifndef TETRIS_H
#define TETRIS_H
#include "bool.h"
#include "binarytrees.h"
#include "board.h"

/* ============ Flood Fill ============ */

/*
* Fonction flood :
* (i, j): Les coordonnées de la case à partir de laquelle floodfiller dans l'aire de jeu
* (px, py): Les coordonnées de la case à partir de laquelle floodfiller dans la matrice de la pièce
* k: pour kind (type), le type de la pièce
* o: pour orientation, l'orientation de la pièce
* value: valeur avec laquelle remplir l'aire de jeu
*/
void flood(Board * board,int i, int j, int px, int py, int k, int o,
           int value, Bool visited[4][4]);

void flood2(Board * board, int i, int j, int px, int py, int k, int o,
           Bool * flag, Bool visited[4][4]);

/* Appel de flood + initialisation de visited */
void floodFill(Board * board, int i, int j, int px, int py, int k, int o,
               int value);

typedef struct
{
	Board board;
	Piece piece;

} Tetris;


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

void drawPiece(Board * board);
void clearPiece(Board * board);
void newPiece(Board *board, Piece * piece);

int calcScore(const unsigned int currentScore, const unsigned int n_lines);
void displayScore_recursion(const Node * node);
void displayScore(const Tree * scoreTree);

void openScoreData(Tree * ptree, const char filename[]);
void saveScoreData(const Tree * ptree, const char filename[]);


#endif
