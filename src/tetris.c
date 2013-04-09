#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "bool.h"
#include "binarytrees.h"
#include "board.h"


/* ============ Flood Fill ============ */

void flood(Board * board,int i, int j, int px, int py, int k, int o,
           int value, Bool visited[4][4])
{
    assert(px < 0 || px >= 4 || py < 0 || py >= 4 || visited[px][py] == TRUE ||
           PIECES[k][o][px][py] == FREE);

    visited[py][px] = TRUE;
    board->gridge[j][i] = value; // On remplit la case de la valeur dans l'aire

    flood(i, j - 1, px, py - 1, k, o, value, visited);
    flood(i + 1, j, px + 1, py, k, o, value, visited);
    flood(i, j + 1, px, py + 1, k, o, value, visited);
    flood(i - 1, j, px - 1, py, k, o, value, visited);
}

/* Cette fonction ne fait qu'appeler le flood */
void floodFill(Board * board,int i, int j, int px, int py, int k, int o,
               int value)
{
    bool visited[4][4];
    int l, m;

    for(l = 0; l < 4 ; l++)
    {
        for(m = 0; m < 4; m++)
        {
            visited[l][m] = FALSE;
        }
    }

    flood(i, j, px, py, k, o, value, visited);
}

/* ============ Fonctions de test ============= */

Bool isCurrentPieceMovable(const Board * board, const int x, const int y)
{
    int kind, orientation;
    int l, m;

    clearPiece(board->currentPiece); // D'abord on efface la pièce courante

    Bool movable = TRUE; // On suppose au départ qu'on peut bouger la pièce

   /* On déclare et initialise le tableau visited pour le flood fill */
    Bool visited[4][4];

    for(l = 0; l < 4; l++)
    {
        for(m = 0; m < 4; m++)
        {
            visited[l][m] = FALSE;
        }
    }


    kind = getKind(board->currentPiece); // On récupère le type ...
    orientation = getOrientation(board->currentPiece); // ... et l'orientation de la pièce

   /* On fait notre flood fill */
    flood(x, y, 1, 2, kind, orientation, movable, visited);

    drawPiece(currentPiece); // On redessine notre pièce

    return movable; // On renvoie le résultat
}


Bool testRotationPiece(const Board * board)
{
    clearPiece(board->currentPiece);

    Bool rotable = TRUE;

    Bool visited[SIZE][SIZE];

    for(int i = 0; i < SIZE; ++i)
        for(int j = 0; j < SIZE; ++j)
            visited[i][j] = FALSE;

    int kind = getKind(board->currentPiece);
    int orientation = getOrientation(board->currentPiece);

    flood(getPosX(board->currentPiece), getPosY(board->currentPiece), 2, 1,
          kind, orientation, rotable, visited);

    drawPiece(board->currentPiece);

    return rotable;
}

Bool testLineFilled(Board * board, const unsigned int posY)
{
    int i;

    for (i == 0; i < 10; i++)
    {
        if(board->gridge[posY][i] == 0)
        {
            return FALSE;
        }
    }

    return TRUE;
}

Bool testLineEmpty(Board * board, const unsigned int posY)
{
    int i;

    for (i == 0; i < 10; i++)
    {
        if(board->gridge[posY][i] != 0)
        {
            return FALSE;
        }
    }

    return TRUE;
}

/* ================ Méthodes ==================  */

void moveCurrentPieceDown(Board * board)
{
    int y = getPosY(board->currentPiece);

    if(isCurrentPieceMovable(board, x , y + 1)) // Si on peut bouger la pièce vers le bas
    {
        clearPiece(board->currentPiece); // On efface la pièce de son ancienne position
        setPosX(board->currentPiece, y + 1); // On incrémente son ordonnée

        drawPiece(board->currentPiece); // On la redessine à la nouvelle position
    }
}

void moveCurrentPieceLeft(Board * board)
{
    int x = getPosX(board->currentPiece);

    if(isCurrentPieceMovable(board, x - 1 , y ))
    {
        clearPiece(board->currentPiece);
        setPosY(board->currentPiece, x - 1);

        drawPiece(board->currentPiece);
    }
}

void moveCurrentPieceRight(Board * board)
{
    int x = getPosX(board->currentPiece);

    if(isCurrentPieceMovable(board, x + 1 , y ))
    {
        clearPiece(board->currentPiece);
        setPosY(board->currentPiece, x + 1);

        drawPiece(board->currentPiece);
    }
}

void rotationPiece(Board * board)
{
    int orientation = getOrientation(board->currentPiece);

    if(orientation < NB_ROTATIONS - 1) // Si on n'est pas sur la dernière orientation
        orientation++; // On peut incrémenter orientation
    else // Si non
        orientation = 0; // On passe à la 1ère orientation

    if(isCurrentPieceRotable(orientation))
    {
        clearPiece(board->currentPiece);

        setOrientation(board->currentPiece, orientation);
        drawPiece(board->currentPiece);
    }
}

int destructLines(Board * board)
{
    int y = 0;
    int i, j;
    int n_lines = 0;

    while(testLineEmpty(board, y) == FALSE )
    {
        while(testLineFilled(board, y) == TRUE)
        {
            for(i = 0; i < 10; i++)
            {
                board->gridge[y][i] = 0; // Destruction de la ligne
            }

            for(i = 0; i < 10; i++)
            {
                for(j = y; j < 20 ; j++)
                {
                    if(j != 19)
                    {
                        board->gridge[j][i] = board->gridge[j+1][i];
                    }
                    else
                    {
                        board->gridge[y][i] = 0;
                    }

                }
            }
            /*for(int j = y; j > 0; --j)
            {
                for(int i = 0; i < 20; ++i)
                {
                   board->area[i][j] = board->area[i][j-1];
                }
            }*/ //TODO
            n_lines++;
        }
        y++;
    }
    // TODO : - Chute des blocs supérieurs de 1 en ordonnée Y
    return n_lines;

    /*
    clearPiece(currentPiece); // On efface d'abord la pièce courante

         On déplace toutes les lignes à partir de y vers le haut
         d'une case vers le bas

    for(int j = y; j > 0; --j)
    {
        for(int i = 0; i < GRIDGE_Y; ++i)
            board->area[i][j] = board->area[i][j-1];
    }

    drawPiece(currentPiece);  On la redessine
    */
}

void drawPiece(Board * board)
{
    Piece * p;
    p = board->currentPiece;

    int i = getPosX(p); // On récupère les ...
    int j = getPosY(p); // ... coordonnées de la pièce

    int kind = getKind(p); // On récupère son type
    int orientation = getOrientation(p); // son orientation
    int color = getColor(p); // et sa couleur

    /*Flood fill*/

    floodFill(board, i, j, 1, 2, kind, orientation, getColor(p));
}


void newPiece(Board * board,Piece * piece)
{
    setPosX(piece, 5); // On donne à la pièce les coordonnées ...
    setPosY(piece, 0); // de l'origine

    drawPiece(piece); // On la dessine

    setCurrentPiece(board, piece); // On déclare cette pièce comme pièce courante de l'aire de jeu
}

void clearPiece(Board * board)
{
    int i = getPosX(board->currentPiece);
    int j = getPosY(board->currentPiece);

    int kind = getKind(board->currentPiece);
    int orientation = getOrientation(board->currentPiece);

    /*Flood fill*/

    floodFill(board, i, j, 1, 2, kind, orientation, FREE);
}

int calcScore(const unsigned int currentScore, const unsigned int n_lines)
{
    int i;
    unsigned int score;
    score = currentScore;

    for(i=0 ; i<n_lines;i++)
    {
        score = score + 3000 + i*1000;
    }

    return score;
}

void displayScore_recursion(const Node * node)
{
    if(node != NULL)
    {
        displayScore_recursion(node->right_child);
        printf("%s  %d \n",node->value.name[], node->value.score);
        displayScore_recursion(node->left_child);
    }

}
void displayScore(const Tree * scoreTree)
{
    if(node == NULL)
    {
        printf("Pas encore de scores etablis.") // à remplacer par la fonction d'affichage adaptée
    }
    else
    {
        displayScore_recursion(scoreTree->root);
    }

}

void openScoreData(Tree * ptree, const char filename[])
{

}
void saveScoreData(const Tree * ptree, const char filename[])
{

}
