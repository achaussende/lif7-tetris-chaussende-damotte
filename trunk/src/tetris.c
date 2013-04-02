#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "bool.h"
#include "binarytrees.h"
#include "board.h"

/* ============ Fonctions de test ============= */

Bool testFallPiece(const Piece piece)
{

}
Bool testRotationPiece(const Piece piece)
{

}
Bool testLineFilled(Board * board, const unsigned int posY)
{
    int i;

    for (i == 0; i < 10; i++)
    {
        if(board->gridge[i][posY] == 0)
        {
            return FALSE;
        }
    }

    return TRUE;
}
Bool testCollision(const Piece piece);
{

}
Bool testLineEmpty(Board * board, const unsigned int posY)
{
    int i;

    for (i == 0; i < 10; i++)
    {
        if(board->gridge[i][posY] != 0)
        {
            return FALSE;
        }
    }

    return TRUE;
}

/* ================ Méthodes ==================  */

void fallPiece(Piece * piece)
{

}

void rotationPiece(Piece * piece)
{

}

int destructLines(Board * board)
{
    int y = 0;
    int i;
    int n_lines = 0;

    while(testLineEmpty(board, y) == FALSE )
    {
        if(testLineFilled(board, y) == TRUE)
        {
            for(i == 0; i < 10; i++)
            {
                board->gridge[i][y] = 0; // Destruction de la ligne
            }
            n_lines++;
        }
        y++;
    }
    // TODO : - Chute des blocs supérieurs de 1 en ordonnée Y
    return n_lines;
}

void drawPiece(Piece * ppiece)
{

}
void clearPiece(Piece * ppiece)
{

}

int calcScore(const unsigned int currentScore, const unsigned int n_lines)
{

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
