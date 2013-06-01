/**
    \file [tetris.h]
    \brief 	Contient la déclaration des fonctions, procédures, accesseurs et mutateurs, et la structure d'un tetris, module principal du jeu
    \author {Damotte Alan, Chaussende Adrien}
    \version 1.2
    \date Avril-Mai 2013
*/

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
/**

    @brief Algorithme de flood fill méthode récursive (1)
*/
void flood(Board * board,int i, int j, int px, int py, int k, int o,
           Color color, Bool visited[4][4]);

/**

    @brief Algorithme de flood fill méthode récursive (2)
*/
void flood2(Board * board, int i, int j, int px, int py, int k, int o,
           Bool * flag, Bool visited[4][4]);

/* Appel de flood + initialisation de visited */
/**

    @brief Algorithme de flood fill
    @param
    (i, j): Les coordonnées de la case à partir de laquelle floodfiller dans l'aire de jeu
    (px, py): Les coordonnées de la case à partir de laquelle floodfiller dans la matrice de la pièce
    k: pour kind (type), le type de la pièce
    o: pour orientation, l'orientation de la pièce
    color: couleur avec laquelle remplir l'aire de jeu
*/
void floodFill(Board * board, int i, int j, int px, int py, int k, int o,
               Color color);

/* ========== Structure : Tetris ==============  */
/**
    @struct Tetris
    @brief Structure d'un Tetris
*/
typedef struct
{
	Board* board;
	Piece* nextpiece;
	Piece* holdpiece;
	Tree * treescores;

} Tetris;

/* ========== Mutateurs & Accesseurs ==========  */
/**

    @brief Mutateur de la board du Tetris
    @param une Board et un Tetris
*/
void setTetrisBoard(Tetris * tetris, const Board * board);

/**

    @brief Assesseur de la board du Tetris
    @param un Tetris
    @return une Board
*/
Board * getTetrisBoard(const Tetris * tetris);

/**

    @brief Mutateur de la pièce suivante
    @param une Piece et un Tetris
*/
void setTetrisNextPiece(Tetris * tetris, const Piece * piece);

/**

    @brief Assesseur de la piece suivante
    @param un Tetris
    @return une Piece
*/
Piece * getTetrisNextPiece(const Tetris * tetris);

/**

    @brief Mutateur de l'arbre des scores du Tetris
    @param un arbre et un Tetris
*/
void setTetrisTreeScores(Tetris * tetris, const Tree * tree);

/**

    @brief Assesseur de l'arbre des scores du Tetris
    @param un Tetris
    @return un Tree
*/
Tree * getTetrisTreeScores(const Tetris * tetris);

/**

    @brief Mutateur de la pièce retenue
    @param une Piece et un Tetris
*/
void setTetrisHoldPiece(Tetris * tetris, const Piece * piece);

/**

    @brief Assesseur de la piece retenue
    @param un Tetris
    @return une Piece
*/
Piece * getTetrisHoldPiece(const Tetris * tetris);


/* ============ Fonctions de test ============= */
/**

    @brief Fonction de test permettant de savoir si une pièce est tombée
    @param une Board
    @return un Bool
*/
Bool testFallPiece(Board * board);

/**

    @brief Fonction de test permettant de savoir si une pièce peut subir une rotation
    @param une Board, un int orientation
    @return un Bool
*/
Bool testRotationPiece(Board * board, const int orientation);

/**

    @brief Fonction de test permettant de savoir si une ligne est complète
    @param une Board, un int de position
    @return un Bool
*/
Bool testLineFilled(Board * board, const unsigned int posY);

/**

    @brief Fonction de test permettant de savoir si une pièce est vide
    @param une Board, un int de position
    @return un Bool
*/
Bool testLineEmpty(Board * board, const unsigned int posY);

/**

    @brief Fonction de test permettant de savoir si une pièce peut être bougée
    @param une Board, deux int de positions
    @return un Bool
*/
Bool isCurrentPieceMovable(Board * board, const int x, const int y);


/* ================ Méthodes ==================  */
/**

    @brief Procédure d'initialisation du Tetris
    @param une Board, un Tetris, une Piece, une holdpiece et un Tree
*/
void initTetris(Tetris * tetris, Board * board, Piece * piece, Piece * holdpiece, Tree * tree);

/**

    @brief Procédure de libération du Tetris
    @param un Tetris
*/
void freeTetris(Tetris * tetris);

/**

    @brief Fonction de création du Tetris
    @param une Board, une Piece, une holdpiece et un Tree
    @return un Tetris
*/
Tetris * createTetris(Board * board, Piece * piece, Piece * holdpiece, Tree * tree);

/**

    @brief Procédure d'étape du Tetris, permettant de changer de pièce
    @param un Tetris
*/
void gameStep(Tetris * tetris);

/**

    @brief Procédure permettant de retenir une pièce
    @param un Tetris
*/
void holdPiece(Tetris * tetris);

/**

    @brief Procédure permettant bouger la pièce vers le bas
    @param une Board
*/
void moveCurrentPieceDown(Board * board);

/**

    @brief Procédure permettant bouger la pièce vers la gauche
    @param une Board
*/
void moveCurrentPieceLeft(Board * board);

/**

    @brief Procédure permettant bouger la pièce vers la droite
    @param une Board
*/
void moveCurrentPieceRight(Board * board);

/**

    @brief Procédure permettant faire subir une rotation à la pièce
    @param une Board
*/
void rotationPiece(Board * board);

/**

    @brief Procédure permettant de détruire toutes les lignes pleines et de mettre à jour la grille de jeu
    @param une Board
*/
int destructLines(Board * board);

/**

    @brief Procédure permettant de dessiner la pièce dans la grille de jeu
    @param une Board
*/
void drawPiece(Board * board);

/**

    @brief Procédure permettant de supprimer la pièce de la grille de jeu
    @param une Board
*/
void clearPiece(Board * board);

/**

    @brief Procédure permettant de créer et initialiser une nouvelle pièce puis l'affiche
    @param une Board et une Piece
*/
void newPiece(Board *board, Piece * piece);

/**
    @brief Fonction de calcul du score
    @param un int currentScore et un int n_lines
    @return un int
*/
int calcScore(const unsigned int currentScore, const unsigned int n_lines);

/**
    @brief Procédure d'affichage du score dans la console (récursive)
    @param un Node
*/
void displayScore_recursion(const Node * node);

/**
    @brief Procédure d'affichage du score dans la console (main)
    @param un Tree
*/
void displayScore(const Tree * scoreTree);

/**
    @brief Procédure d'ouverture d'un fichier de score et le met dans un arbre de score
    @param un Tree et un char de nom de fichier
*/
void openScoreData(Tree * ptree, const char filename[]);

/**
    @brief Procédure d'écriture d'une score dans un fichier (récursive)
    @param un Node et un FILE
*/
void saveScoreData_Node(const Node * pnode, FILE * f);

/**
    @brief Procédure d'écriture d'une score dans un fichier (main)
    @param un Tree et un char de nom de fichier
*/
void saveScoreData(const Tree * ptree, const char filename[]);

/**
    @brief Procédure qui envoie une pièce en bas de la grille de jeu
    @param une Board
*/
void dropCurrentPiece(Board * board);

/**
    @brief Fonction de test de fin de jeu
    @param une Board
    @return un Bool
*/
Bool testGameOver(Board * board);

/* Création d'un tetris */
/**
    @brief Fonction d'initialisation d'un Tetris
    @return un Tetris
*/
Tetris * startTetris();

/* Test régression des fonctions */
/**
    @brief Fonction de test regression
*/
void tetrisTestRegression();

#endif
