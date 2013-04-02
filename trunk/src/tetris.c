#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "bool.h"
#include "binarytrees.h"
#include "board.h"

/*Flood Fill*/

/*
* (i, j): Les coordonnées de la case à partir de laquelle floodfiller dans l'aire de jeu
* (px, py): Les coordonnées de la case à partir de laquelle floodfiller dans la matrice de la pièce
* k: pour kind (type), le type de la pièce
* o: pour orientation, l'orientation de la pièce
* value: valeur avec laquelle remplir l'aire de jeu
*/
void flood(Board * board,int i, int j, int px, int py, int k, int o, int value, Bool visited[][SIZE])
{
    assert(px < 0 || px >= SIZE || py < 0 || py >= SIZE || visited[px][py] || PIECES[k][o][px][py] == FREE);

    visited[px][py] = true;
    board->gridge[j][i] = value; // On remplit la case de la valeur dans l'aire

    flood(i, j - 1, px, - 1, k, o, value, visited);
    flood(i + 1, j, px + 1, py, k, o, value, visited);
    flood(i, j + 1, px, py + 1, k, o, value, visited);
    flood(i - 1, j, px - 1, py, k, o, value, visited);
}

/* Cette fonction ne fait qu'appeler le flood */
void floodFill(Board * board,int i, int j, int px, int py, int k, int o, int value)
{
    bool visited[SIZE][SIZE];

    for(int l = 0; l < SIZE; ++l)
        for(int m = 0; m < SIZE; ++m)
            visited[l][m] = false;

    flood(i, j, px, py, k, o, value, visited);
}

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

void drawPiece(Piece * ppiece)
{
    int i = piece.getPosX(); // On récupère les ...
    int j = piece.getPosY(); // ... coordonnées de la pièce

    int k = piece.getKind(); // On récupère son type
    int o = piece.getOrientation(); // et sa rotation

    switch(k) // En fonction de son type
    {
        case I:
            piece.setColor(CYAN); // On lui affecte la couleur appropriée
            break;
        case J:
            piece.setColor(BLUE);
            break;
        case L:
            piece.setColor(ORANGE);
            break;
        case O:
            piece.setColor(YELLOW);
            break;
        case S:
            piece.setColor(GREEN);
            break;
        case T:
            piece.setColor(PURPLE);
            break;
        case Z:
            piece.setColor(RED);
            break;
        default:
            break;
    }

    /*Flood fill*/

    floodFill(i, j, PIVOT_X, PIVOT_Y, k, o, piece.getColor());
}
void clearPiece(Piece * ppiece)
{
    int i = piece.getPosX();
    int j = piece.getPosY();

    int k = piece.getKind();
    int o = piece.getOrientation();

    /*Flood fill*/

    floodFill(i, j, PIVOT_X, PIVOT_Y, k, o, FREE);
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
