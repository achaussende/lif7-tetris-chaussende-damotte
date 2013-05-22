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
* color: couleur avec laquelle remplir l'aire de jeu
*/
void flood(Board * board,int i, int j, int px, int py, int k, int o,
           Color color, Bool visited[4][4]);

void flood2(Board * board, int i, int j, int px, int py, int k, int o,
           Bool * flag, Bool visited[4][4]);

/* Appel de flood + initialisation de visited */
void floodFill(Board * board, int i, int j, int px, int py, int k, int o,
               Color color);

/* ========== Structure : Tetris ==============  */

typedef struct
{
	Board* board;
	Piece* nextpiece;
	Piece* holdpiece;
	Tree * treescores;

} Tetris;

/* ========== Mutateurs & Accesseurs ==========  */

void setTetrisBoard(Tetris * tetris, const Board * board);
Board * getTetrisBoard(const Tetris * tetris);
void setTetrisNextPiece(Tetris * tetris, const Piece * piece);
Piece * getTetrisNextPiece(const Tetris * tetris);
void setTetrisTreeScores(Tetris * tetris, const Tree * tree);
Tree * getTetrisTreeScores(const Tetris * tetris);
void setTetrisHoldPiece(Tetris * tetris, const Piece * piece);
Piece * getTetrisHoldPiece(const Tetris * tetris);


/* ============ Fonctions de test ============= */

Bool testFallPiece(Board * board);
Bool testRotationPiece(Board * board, const int orientation);
Bool testLineFilled(Board * board, const unsigned int posY);
Bool testLineEmpty(Board * board, const unsigned int posY);
Bool isCurrentPieceMovable(Board * board, const int x, const int y);


/* ================ Méthodes ==================  */

void initTetris(Tetris * tetris, Board * board, Piece * piece, Piece * holdpiece, Tree * tree);
void freeTetris(Tetris * tetris);
Tetris * createTetris(Board * board, Piece * piece, Piece * holdpiece, Tree * tree);
void gameStep(Tetris * tetris);
void holdPiece(Tetris * tetris);

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
void saveScoreData_Node(const Node * pnode, FILE * f);
void saveScoreData(const Tree * ptree, const char filename[]);

void dropCurrentPiece(Board * board);
Bool testGameOver(Board * board);

/* Création d'un tetris */
Tetris * startTetris();

/* Test régression des fonctions */
void tetrisTestRegression();

#endif
