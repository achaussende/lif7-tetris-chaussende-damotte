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

    flood(board, i, j - 1, px, py - 1, k, o, value, visited);
    flood(board, i + 1, j, px + 1, py, k, o, value, visited);
    flood(board, i, j + 1, px, py + 1, k, o, value, visited);
    flood(board, i - 1, j, px - 1, py, k, o, value, visited);
}

void flood2(Board * board, int i, int j, int px, int py, int k, int o,
           Bool * flag, Bool visited[4][4])
{
    assert(px < 0 || px >= 4 || py < 0 || py >= 4 || visited[px][py] == TRUE ||
        PIECES[k][o][px][py] == FREE);


    visited[px][py] = TRUE;

   /* Si on dépasse les limites de l'aire de jeu
    * ou si la case sur laquelle on est n'est pas vide
    */
    if(i < 0 || i >= 10 || j < 0 || j >= 20 || board->gridge[j][i] != FREE)
    {
        flag = FALSE; // on met flag à false
        return;
    }

    flood2(board, i, j - 1, px, py - 1, k, o, flag, visited);
    flood2(board, i + 1, j, px + 1, py, k, o, flag, visited);
    flood2(board, i, j + 1, px, py + 1, k, o, flag, visited);
    flood2(board, i - 1, j, px - 1, py, k, o, flag, visited);
}

/* Cette fonction ne fait qu'appeler le flood */
void floodFill(Board * board,int i, int j, int px, int py, int k, int o,
               int value)
{
    Bool visited[4][4];
    int l, m;

    for(l = 0; l < 4 ; l++)
    {
        for(m = 0; m < 4; m++)
        {
            visited[l][m] = FALSE;
        }
    }

    flood(board, i, j, px, py, k, o, value, visited);
}

/* ============ Fonctions de test ============= */

Bool isCurrentPieceMovable(const Board * board, const int x, const int y)
{
    int kind, orientation;
    int l, m;
    Bool visited[4][4];

    kind = getKind(board->currentPiece); // On récupère le type ...
    orientation = getOrientation(board->currentPiece); // ... et l'orientation de la pièce

    clearPiece(board); // D'abord on efface la pièce courante

    Bool movable = TRUE; // On suppose au départ qu'on peut bouger la pièce

   /* On initialise le tableau visited pour le flood fill */

    for(l = 0; l < 4; l++)
    {
        for(m = 0; m < 4; m++)
        {
            visited[l][m] = FALSE;
        }
    }


   /* On fait notre flood fill */
    flood2(board,x, y, 1, 2, kind, orientation, &movable, visited);

    drawPiece(board); // On redessine notre pièce

    return movable; // On renvoie le résultat
}


Bool testRotationPiece(const Board * board)
{
    int kind = getKind(board->currentPiece);
    int orientation = getOrientation(board->currentPiece);
    Bool rotable = TRUE;
    Bool visited[4][4];
    int i,j;
    clearPiece(board);

    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 4; j++)
        {
               visited[i][j] = FALSE;
        }

    }

    flood2(board, getPosX(board->currentPiece), getPosY(board->currentPiece), 2, 1,
          kind, orientation, &rotable, visited);

    drawPiece(board);

    return rotable;
}

Bool testLineFilled(Board * board, const unsigned int posY)
{
    int i;

    for (i = 0; i < 10; i++)
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

    for (i = 0; i < 10; i++)
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
    int x = getPosX(board->currentPiece);

    if(isCurrentPieceMovable(board, x , y + 1) == TRUE) // Si on peut bouger la pièce vers le bas
    {
        clearPiece(board); // On efface la pièce de son ancienne position
        setPosX(board->currentPiece, y + 1); // On incrémente son ordonnée

        drawPiece(board); // On la redessine à la nouvelle position
    }
}

void moveCurrentPieceLeft(Board * board)
{
    int x = getPosX(board->currentPiece);
    int y = getPosY(board->currentPiece);

    if(isCurrentPieceMovable(board, x - 1 , y ) == TRUE)
    {
        clearPiece(board);
        setPosY(board->currentPiece, x - 1);
        drawPiece(board);
    }
}

void moveCurrentPieceRight(Board * board)
{
    int x = getPosX(board->currentPiece);
    int y = getPosY(board->currentPiece);

    if(isCurrentPieceMovable(board, x + 1 , y) == TRUE)
    {
        clearPiece(board);
        setPosY(board->currentPiece, x + 1);
        drawPiece(board);
    }
}

void rotationPiece(Board * board)
{
    int orientation = getOrientation(board->currentPiece);

    if(orientation < 4 - 1) // Si on n'est pas sur la dernière orientation
        orientation++; // On peut incrémenter orientation
    else // Si non
        orientation = 0; // On passe à la 1ère orientation

    if(testRotationPiece(board) == TRUE)
    {
        clearPiece(board);
        setOrientation(board->currentPiece, orientation);
        drawPiece(board);
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
            for(j = y; j > 0; j--)
            {
                for(i = 0; i < 20; i++)
                {
                    board->gridge[i][j] = board->gridge[i-1][j];
                }
            }

            n_lines++;
        }
        y++;
    }
    return n_lines;
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

    floodFill(board, i, j, 1, 2, kind, orientation, color);
}


void newPiece(Board * board,Piece * piece)
{
    setPosX(piece, 5); // On donne à la pièce les coordonnées ...
    setPosY(piece, 0); // de l'origine
    setCurrentPiece(board, piece); // On déclare cette pièce comme pièce courante de l'aire de jeu
    drawPiece(board); // On la dessine

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
        printf("%s  %u \n",node->value.name[], node->value.score);
        displayScore_recursion(node->left_child);
    }

}
void displayScore(const Tree * scoreTree)
{
    if(node == NULL)
    {
        printf("Pas encore de scores etablis."); // à remplacer par la fonction d'affichage adaptée
    }
    else
    {
        displayScore_recursion(scoreTree->root);
    }

}

void openScoreData(Tree * ptree, const char filename[])
{
    FILE * f;
    f=fopen(filename, "r");

    Player player;

    unsigned int nb_elem, score;
    int i;
    char * nickname;

    if(f == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier de scores %s \n",
                filename);
        assert(f);
    }

    assert( fscanf( f , "PS \n%u \nEnd \n", &nb_elem ) == 1 );


    initTree(ptree);

    for(i = 0; i < ptree->nb_elements; i++)
    {
        assert(fscanf(f, "%s %u", nickname, &score) == 2 ||
                strlen(nickname) <= 25);
        setTreeNb_Elements(ptree, nb_elem);
        setName (player, nickname);
        setScore (player, score);
        insertPlayerInTree(ptree, player);
    }

    fclose(f);
    printf("Lecture des scores %s ... OK \n", filename);
}

void saveScoreData_Node(const Node * pnode, FILE * f)
{
    if(pnode != NULL)
    {
        saveScoreData_Node(Node->left_child, f);
        fprintf(f, "%s %u \n", Node->value.name, Node->value.score);
        saveScoreData_Node(Node->right_child, f);
    }
}
void saveScoreData(const Tree * ptree, const char filename[])
{
    FILE * f;

    f = fopen(filename, "w");

    if(f == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier de scores %s\n", filename);
        assert( f );
    }

    fprintf(f, "PS \n"); //Players et scores
    fprintf(f, "%u \n", getTreeNb_Elements(ptree) ); // Nombres de Players/Scores
    saveScoreData_Node(Tree->root, f);
    fprintf(f, "End \n");

    printf("Sauvegarde des scores dans %s ...OK\n", filename);
    fclose(f);

}

/* HARD-DROP */
void dropCurrentPiece(Board * board)
{
    int x = getPosX(board->currentPiece);
    int y = getPosY(board->currentPiece);

    while(isCurrentPieceMovable(board, x, y++)) // Tant qu'on peut toujours bouger la pièce vers le bas
    {
        moveCurrentPieceDown(board);
    }
}

Bool testGameOver(Board * board)
{
    int i;

    for(i = 0; i < 10; ++i)
    {
        if(area[0][i] != FREE) // Si il y a un bloc sur la première ligne de l'aire
        {
            return TRUE; // C'est que la partie est finie
        }
    }

    return FALSE;
}
