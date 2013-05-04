#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "tetris.h"
#include "bool.h"
#include "shapes.h"


/* ============ Flood Fill ============ */

void flood(Board * board,int i, int j, int px, int py, int k, int o,
           Color color, Bool visited[4][4])
{

    if(px >= 0 && px < 4 && py >= 0 && py < 4 && visited[py][px] == FALSE &&
                PIECES[k][o][py][px] != 0)
    {
        visited[py][px] = TRUE;
        board->gridge[j][i] = color; // On remplit la case de la valeur dans l'aire

        flood(board, i -1 , j, px - 1, py, k, o, color, visited); // à gauche
        flood(board, i + 1, j, px + 1, py, k, o, color, visited); // à droite
        flood(board, i, j - 1, px, py - 1, k, o, color, visited); // en haut
        flood(board, i, j + 1, px, py + 1, k, o, color, visited); // en bas (ces soirées là !)
    }

}

void flood2(Board * board, int i, int j, int px, int py, int k, int o,
           Bool * flag, Bool visited[4][4])
{


    if(px >= 0 && px < 4 && py >= 0 && py < 4 && visited[py][px] == FALSE &&
            PIECES[k][o][py][px] != 0)
    {
        visited[py][px] = TRUE;

       /* Si on est toujours dans l'aire de jeu
       et si la case sur laquelle on est vide :
       on continue le flood */

        if(i >= 0 && i < 10 && j >= 0 && j < 20 && board->gridge[i][j] == FREE)
        {
            flood2(board, i, j - 1, px, py - 1, k, o, flag, visited);
            flood2(board, i + 1, j, px + 1, py, k, o, flag, visited);
            flood2(board, i, j + 1, px, py + 1, k, o, flag, visited);
            flood2(board, i - 1, j, px - 1, py, k, o, flag, visited);
        }
        else
        {
            /* Sinon la pièce ne peut pas être bougée */
            *flag = FALSE;
        }
    }
}

/* Cette fonction ne fait qu'appeler le flood */
void floodFill(Board * board,int i, int j, int px, int py, int k, int o,
               Color color)
{
    Bool visited[4][4];
    int l, m;

    for(l = 0 ; l < 4 ; l++)
    {
        for(m = 0 ; m < 4 ; m++)
        {
            visited[l][m] = FALSE;
        }
    }

    flood(board, i, j, px, py, k, o, color, visited);
}

/* ========== Mutateurs & Accesseurs ==========  */

void setTetrisBoard(Tetris * tetris, const Board * board)
{
    tetris->board = board;
}

Board * getTetrisBoard(const Tetris * tetris)
{
    return tetris->board;
}

void setTetrisNextPiece(Tetris * tetris, const Piece * piece)
{
    tetris->nextpiece = piece;
}

Piece * getTetrisNextPiece(const Tetris * tetris)
{
    return tetris->nextpiece;
}

void setTetrisTreeScores(Tetris * tetris, const Tree * tree)
{
    tetris->treescores = tree;
}

Tree * getTetrisTreeScores(const Tetris * tetris)
{
    return tetris->treescores;
}

/* ============ Fonctions de test ============= */

Bool isCurrentPieceMovable(Board * board, const int x, const int y)
{
    int kind, orientation;
    int l, m;
    Bool visited[4][4];
    Bool * movable = (Bool *)malloc(sizeof(Bool));
    *movable = TRUE; // On suppose au départ qu'on peut bouger la pièce

    kind = getKind(board->currentPiece); // On récupère le type ...
    orientation = getOrientation(board->currentPiece); // ... et l'orientation de la pièce

    clearPiece(board); // D'abord on efface la pièce courante



   /* On initialise le tableau visited pour le flood fill */

    for(l = 0; l < 4; l++)
    {
        for(m = 0; m < 4; m++)
        {
            visited[l][m] = FALSE;
        }
    }


   /* On fait notre flood fill */
    flood2(board,x, y, 2, 1, kind, orientation, movable, visited);

    drawPiece(board); // On redessine notre pièce

    return *movable; // On renvoie le résultat
}


Bool testRotationPiece(Board * board)
{
    int kind = getKind(board->currentPiece);
    int orientation = getOrientation(board->currentPiece);
    Bool * rotable = (Bool *)malloc(sizeof(Bool));
    Bool visited[4][4];
    int i,j;
    clearPiece(board);

    *rotable = TRUE;

    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 4; j++)
        {
               visited[i][j] = FALSE;
        }

    }

    flood2(board, getPosY(board->currentPiece), getPosX(board->currentPiece), 2, 1,
          kind, orientation, rotable, visited);

    drawPiece(board);

    return *rotable;
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

/* initTetris : initialise les champs de la structure tetris */

void initTetris(Tetris * tetris, Board * board, Piece * piece, Tree * tree)
{
    setTetrisBoard(tetris, board);
    setTetrisNextPiece(tetris, piece);
    setTetrisTreeScores(tetris, tree);
}

void freeTetris(Tetris * tetris)
{
    freeBoard(tetris->board);
    freePiece(tetris->nextpiece);
    freeTree(tetris->treescores);
    free(tetris);
}

Tetris * createTetris(Board * board, Piece * piece, Tree * tree)
{
    Tetris * tetris = (Tetris *)malloc(sizeof(Tetris));

    initTetris(tetris, board, piece, tree);

    return tetris;
}

void moveCurrentPieceDown(Board * board)
{
    int y = getPosY(board->currentPiece);
    int x = getPosX(board->currentPiece);

    if(isCurrentPieceMovable(board, x , y + 1) == TRUE) /* Si on peut bouger la pièce vers le bas*/
    {
        clearPiece(board); /* On efface la pièce de son ancienne position */
        setPosY(board->currentPiece, y + 1); /* On incrémente son ordonnée */

        drawPiece(board); /* On la redessine à la nouvelle position */
    }
}

void moveCurrentPieceLeft(Board * board)
{
    int x = getPosX(board->currentPiece);
    int y = getPosY(board->currentPiece);

    if(isCurrentPieceMovable(board, x - 1 , y ) == TRUE)
    {
        clearPiece(board);
        setPosX(board->currentPiece, x - 1);
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
        setPosX(board->currentPiece, x + 1);
        drawPiece(board);
    }
}

void rotationPiece(Board * board)
{
    int orientation = getOrientation(board->currentPiece);

    if(orientation < 4 - 1) /* Si on n'est pas sur la dernière orientation */
        orientation++; /* On peut incrémenter orientation */
    else /* Si non */
        orientation = 0; /* On passe à la 1ère orientation*/

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

    int i = getPosX(p); /* On récupère les ...*/
    int j = getPosY(p); /* ... coordonnées de la pièce */

    int kind = getKind(p); /* On récupère son type */
    int orientation = getOrientation(p); /*son orientation*/
    Color color = getColor(p); /* et sa couleur*/

    /*Flood fill*/

    floodFill(board, i, j, 2, 1, kind, orientation, color);
}


void newPiece(Board * board,Piece * piece)
{
    setPosX(piece, 8); /* On donne à la pièce les coordonnées ...*/
    setPosY(piece, 0); /* de l'origine */
    setCurrentPiece(board, piece); /* On déclare cette pièce comme pièce courante de l'aire de jeu*/
    drawPiece(board); /* On la dessine*/

}

void clearPiece(Board * board)
{
    int i = getPosX(board->currentPiece);
    int j = getPosY(board->currentPiece);

    int kind = getKind(board->currentPiece);
    int orientation = getOrientation(board->currentPiece);

    /*Flood fill*/

    floodFill(board, i, j, 2, 1, kind, orientation, FREE);
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
        printf("%s  %u \n",node->value.name, node->value.score);
        displayScore_recursion(node->left_child);
    }

}
void displayScore(const Tree * scoreTree)
{
    if(scoreTree->root == NULL)
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
    char * nickname = NULL;

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
        saveScoreData_Node(pnode->left_child, f);
        fprintf(f, "%s %u \n", pnode->value.name, pnode->value.score);
        saveScoreData_Node(pnode->right_child, f);
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
    saveScoreData_Node(ptree->root, f);
    fprintf(f, "End \n");

    printf("Sauvegarde des scores dans %s ...OK\n", filename);

    fclose(f);

}

/* HARD-DROP */
void dropCurrentPiece(Board * board)
{
    int x = getPosX(board->currentPiece);
    int y = getPosY(board->currentPiece);

    while(isCurrentPieceMovable(board, x, y+1) == TRUE) // Tant qu'on peut toujours bouger la pièce vers le bas
    {
        moveCurrentPieceDown(board);
    }
}

Bool testGameOver(Board * board)
{
    int i;

    for(i = 0; i < 10; ++i)
    {
        if(board->gridge[0][i] != FREE) // Si il y a un bloc sur la première ligne de l'aire
        {
            return TRUE; // C'est que la partie est finie
        }
    }

    return FALSE;
}

void tetrisTestRegression()
{
    Board * board = (Board *)malloc(sizeof(Board));
    Piece * piece = NULL;
    Tree * tree = (Tree *)malloc(sizeof(Tree));
    Tetris * tetris;
    int i, j;

    srand(time(NULL));

    initBoard(board);
    printf("Création de la board + initialisation ... OK \n");

    piece = createPiece(rand() % 7, 0);
    printf("Création d'une piece de type : %u et d'orientation : %u \n",
            piece->kind + 1, piece->orientation + 1);
    tetris = createTetris(board, piece, tree);
    printf("Création du Tetris ... OK \n");

    for(i = 0; i < 20; i++) // affichage grille
    {
        for(j = 0; j < 10; j++)
        {
            printf("%u ", tetris->board->gridge[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for(i = 0; i < 4; i++) //affichage pièce créée
    {
        for(j = 0; j < 4; j++)
        {
            printf("%u ", PIECES[piece->kind][piece->orientation][i][j]);
        }

        printf("\n");
    }
    printf("\n");
    newPiece(tetris->board, piece);

    for(i = 0; i < 20; i++) // affichage grille
    {
        for(j = 0; j < 10; j++)
        {
            printf("%u ", tetris->board->gridge[i][j]);
        }

        printf("\n");
    }
    printf("\n");
    printf("\n");
    moveCurrentPieceDown(tetris->board);

    for(i = 0; i < 20; i++) // affichage grille
    {
        for(j = 0; j < 10; j++)
        {
            printf("%u ", tetris->board->gridge[i][j]);
        }

        printf("\n");
    }
    printf("\n");
    printf("\n");
    moveCurrentPieceRight(tetris->board);

    for(i = 0; i < 20; i++) // affichage grille
    {
        for(j = 0; j < 10; j++)
        {
            printf("%u ", tetris->board->gridge[i][j]);
        }

        printf("\n");
    }
    printf("\n");
    printf("\n");

    dropCurrentPiece(tetris->board);

    for(i = 0; i < 20; i++) // affichage grille
    {
        for(j = 0; j < 10; j++)
        {
            printf("%u ", tetris->board->gridge[i][j]);
        }

        printf("\n");
    }
    printf("\n");
    printf("\n");

    freeTetris(tetris);
    printf("Libération de tetris et de tout ses champs ... OK\n");
}
