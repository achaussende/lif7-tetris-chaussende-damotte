/**
    \file [tetris.c]
    \brief 	Contient les fonctions, procédures, accesseurs et
    mutateurs du tetris
    \author {Damotte Alan, Chaussende Adrien}
    \version 2.1
    \date Avril-Mai 2013
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "tetris.h"
#include "shapes.h"


/* ============ Flood Fill ============ */

void flood(Board * board,int i, int j, int px, int py, int k, int o,
           Color color, Bool visited[4][4])
{

    if(px >= 0 && px < 4 && py >= 0 && py < 4 && visited[py][px] == FALSE &&
                PIECES[k][o][py][px] != 0)
    {
        visited[py][px] = TRUE;

        /* On remplit la case de la valeur dans l'aire*/
        board->gridge[j][i] = color;

        flood(board, i -1 , j, px - 1, py, k, o, color, visited); /*à gauche*/
        flood(board, i + 1, j, px + 1, py, k, o, color, visited); /*à droite*/
        flood(board, i, j - 1, px, py - 1, k, o, color, visited); /*en haut*/
        flood(board, i, j + 1, px, py + 1, k, o, color, visited); /*en bas*/
    }

}

void flood2(Board * board, int i, int j, int px, int py, int k, int o,
           Bool * flag, Bool visited[4][4])
{


    if(px >= 0 && px < 4 && py >= 0 && py < 4 && visited[py][px] == FALSE &&
            PIECES[k][o][py][px] != 0 && *flag != FALSE)
    {
        visited[py][px] = TRUE;
       /* Si on est toujours dans l'aire de jeu
       et si la case sur laquelle on est vide :
       on continue le flood */

        if(i >= 0 && i < 10 && j >= 0 && j < 20 && board->gridge[j][i] == FREE)
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

void setTetrisHoldPiece(Tetris * tetris, const Piece * piece)
{
    tetris->holdpiece = piece;
}

Piece * getTetrisHoldPiece(const Tetris * tetris)
{
    return tetris->holdpiece;
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

Bool testFallPiece(Board * board)
{
    int posx, posy, orientation;
    posx = getPosX(board->currentPiece);
    posy = getPosY(board->currentPiece);
    orientation = getOrientation(board->currentPiece);

    if(isCurrentPieceMovable(board, posx, posy + 1) == FALSE &&
       isCurrentPieceMovable(board, posx + 1, posy) == FALSE &&
       isCurrentPieceMovable(board, posx - 1, posy) == FALSE &&
       testRotationPiece(board, orientation) == FALSE)
    {
        return TRUE;
    }
    return FALSE;
}

Bool isCurrentPieceMovable(Board * board, const int x, const int y)
{
    int kind, orientation;
    int l, m;
    Bool visited[4][4];
    Bool * movable = (Bool *)malloc(sizeof(Bool));
    *movable = TRUE; /* On suppose au départ qu'on peut bouger la pièce*/
    Bool movable2;

    kind = getKind(board->currentPiece); /* On récupère le type ...*/
    /* ... et l'orientation de la pièce*/
    orientation = getOrientation(board->currentPiece);

    clearPiece(board); /* D'abord on efface la pièce courante*/

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

    drawPiece(board); /* On redessine notre pièce*/
    movable2 = *movable;
    free(movable);

    return movable2; /* On renvoie le résultat */
}


Bool testRotationPiece(Board * board, const int orientation)
{
    int kind = getKind(board->currentPiece);
    int posx, posy;
    int i,j;
    int k = 0;
    Bool * rotable = (Bool *)malloc(sizeof(Bool));
    Bool rotable2;
    Bool visited[4][4];

    posx = getPosX(board->currentPiece);
    posy = getPosY(board->currentPiece);
    *rotable = TRUE;

    clearPiece(board);

    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 4; j++)
        {
               visited[i][j] = FALSE;
        }

    }
    flood2(board, posx, posy, 2, 1, kind, orientation, rotable, visited);

    drawPiece(board);

    rotable2 = *rotable;
    free(rotable);
    return rotable2;
}

Bool testLineFilled(Board * board, const unsigned int posY)
{
    int i;
    Bool filled;

    for (i = 0; i < 10; i++)
    {
        if(board->gridge[posY][i] == 0)
        {
            filled = FALSE;
            return filled;
        }
    }
    filled = TRUE;
    return filled;
}

Bool testLineEmpty(Board * board, const unsigned int posY)
{
    int i;
    Bool empty;
    for (i = 0; i < 10; i++)
    {
        if(board->gridge[posY][i] != 0)
        {
            empty = FALSE;
            return empty;
        }
    }
    empty = TRUE;
    return empty;
}

/* ================ Méthodes ==================  */

/* initTetris : initialise les champs de la structure tetris */

void initTetris(Tetris * tetris, Board * board, Piece * piece,
                Piece * holdpiece, Tree * tree)
{
    setTetrisBoard(tetris, board);
    setTetrisNextPiece(tetris, piece);
    setTetrisHoldPiece(tetris, holdpiece);
    setTetrisTreeScores(tetris, tree);
}

void freeTetris(Tetris * tetris)
{
    freeBoard(tetris->board);
    freePiece(tetris->nextpiece);
    freePiece(tetris->holdpiece);
    freeTree(tetris->treescores);
    free(tetris);
}

Tetris * createTetris(Board * board, Piece * piece, Piece * holdpiece,
                      Tree * tree)
{
    Tetris * tetris = (Tetris *)malloc(sizeof(Tetris));

    initTetris(tetris, board, piece, holdpiece, tree);

    return tetris;
}

void gameStep(Tetris * tetris)
{
    Piece * piece;
    piece = createPiece(rand()%7, 0);

    freePiece(tetris->board->currentPiece);
    newPiece(tetris->board, tetris->nextpiece);
    setTetrisNextPiece(tetris, piece);
}

void holdPiece(Tetris * tetris)
{
    Piece * piecetemp;
    Piece * piece;

    if((*tetris).holdpiece == NULL)
    {

        piece = createPiece(rand()%7, 0);
        /*On efface la pièce de la grille*/
        clearPiece(tetris->board);

        /* On passe la currentpiece en hold*/
        setTetrisHoldPiece(tetris, tetris->board->currentPiece);

        /* On remet les coordonnées de la pièce en haut de grille */
        /* Et la pièce à son orientation 0*/
        setPosX(tetris->holdpiece, 5);
        setPosY(tetris->holdpiece, 0);
        setOrientation(tetris->holdpiece, 0);

        /*Nextpiece = currentpiece et nouvelle nextpiece*/
        newPiece(tetris->board, tetris->nextpiece);
        setTetrisNextPiece(tetris, piece);
    }
    else
    {
        /*On efface la pièce de la grille */
        clearPiece(tetris->board);

         /* On stocke l'adresse de la holdpiece */
        piecetemp = tetris->holdpiece;

        /* On passe la currentpiece en hold */
        setTetrisHoldPiece(tetris, tetris->board->currentPiece);

        /* L'ancienne holdpiece devient la current */
        setCurrentPiece(tetris->board, piecetemp);

        /* On remet les coordonnées de la pièce en haut de grille */
        /* Et la pièce à son orientation 0 */
        setPosX(tetris->holdpiece, 5);
        setPosY(tetris->holdpiece, 0);
        setOrientation(tetris->holdpiece, 0);

    }
}

void moveCurrentPieceDown(Board * board)
{
    int y = getPosY(board->currentPiece);
    int x = getPosX(board->currentPiece);
    /* Si on peut bouger la pièce vers le bas*/
    if(isCurrentPieceMovable(board, x , y + 1) == TRUE)
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

    /* Si on n'est pas sur la dernière orientation */
    if(orientation < 3)
    {
        /* On peut incrémenter orientation */
        orientation++;
    }
    /* Si non */
    else
    {
        orientation = 0; /* On passe à la 1ère orientation*/
    }

    if(testRotationPiece(board, orientation) == TRUE)
    {
        clearPiece(board);
        setOrientation(board->currentPiece, orientation);
        drawPiece(board);
    }
}

int destructLines(Board * board)
{
    int y = 19;
    int i, j;
    int n_lines = 0;

    while(testLineEmpty(board, y) == FALSE && y >= 0)
    {

        while(testLineFilled(board, y) == TRUE)
        {
            for(j = y; j > 0; j--)
            {
                for(i = 0; i < 10; i++)
                {
                    board->gridge[j][i] = board->gridge[j-1][i];

                }
            }

            n_lines++;
        }
        y--;
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
    setPosX(piece, 5); /* On donne à la pièce les coordonnées ...*/
    setPosY(piece, 0); /* de l'origine */
    /* On déclare cette pièce comme pièce courante de l'aire de jeu*/
    setCurrentPiece(board, piece);
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
        printf("%s  %u \n",node->value->name, node->value->score);
        displayScore_recursion(node->left_child);
    }

}
void displayScore(const Tree * scoreTree)
{
    printf("Tableau de scores :\n\n");
    if(scoreTree->root == NULL)
    {
        /*à remplacer par la fonction d'affichage adaptée*/
        printf("Pas encore de scores etablis.");
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

    Player * player;

    unsigned int nb_elem, score;
    int i;
    char * nickname[26];

    if(f == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier de scores %s \n",
                filename);
        assert(f);
    }

    if(fscanf( f , "PS \n%u \n", &nb_elem ) == 1 )
    {
        for(i = 0; i < nb_elem; i++)
        {
            assert(fscanf(f, "%s %u \n", &nickname, &score) == 2 ||
                    strlen(nickname) <= 25);
            player = malloc(sizeof(Player));
            setName (player, nickname);
            setScore (player, score);
            insertPlayerInTree(ptree, player);

        }
        printf("Lecture des scores %s ... OK \n", filename);
    }
    else
    {
        printf("Fichier de scores vide \n");
    }



    fclose(f);

}


void saveScoreData_Node(const Node * pnode, FILE * f)
{
    if(pnode != NULL)
    {
        saveScoreData_Node(pnode->left_child, f);
        fprintf(f, "%s %u \n", pnode->value->name, pnode->value->score);
        saveScoreData_Node(pnode->right_child, f);
    }
}

void saveScoreData(const Tree * ptree, const char filename[])
{
    FILE * f;

    f = fopen(filename, "w");

    if(f == NULL)
    {
        printf("Erreur lors de l'ouverture du fichier de scores %s\n",
               filename);
        assert( f );
    }

    fprintf(f, "PS \n"); /*Players et scores*/
    /* Nombres de Players/Scores*/
    fprintf(f, "%u \n", getTreeNb_Elements(ptree) );
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

    /* Tant qu'on peut toujours bouger la pièce vers le bas */
    while(isCurrentPieceMovable(board, x, y + 1) == TRUE)
    {
        clearPiece(board);
        setPosY(board->currentPiece, y + 1);
        drawPiece(board);
        y++;
    }
}

Bool testGameOver(Board * board)
{
    int i;

    for(i = 0; i < 10; ++i)
    {
        /* Si il y a un bloc sur la première ligne de l'aire */
        if(board->gridge[1][i] != FREE)
        {
            return TRUE; /* C'est que la partie est finie */
        }
    }

    return FALSE;
}

/* startTetris : renvoie un pointeur sur Tetris. Crée une structure tetris
avec une board initialisée (gridge vide, et une nouvelle currentPiece),
nextpiece créée, holdpiece vide et un arbre initialisé */

Tetris * startTetris()
{
    srand(time(NULL));

    Board * board = (Board *)malloc(sizeof(Board));
    Tree * tree = (Tree *)malloc(sizeof(Tree));
    Piece * piece;
    Piece * holdpiece;
    Tetris * tetris;

    holdpiece = NULL;

    initBoard(board); /* création ...*/
    newPiece(board, createPiece(rand()%7, 0)); /* de board */
    initTree(tree);

    piece = createPiece(rand()%7, 0); /*nextpiece */
    tetris = createTetris(board, piece, holdpiece, tree);
    return tetris;
}

void tetrisTestRegression()
{

    /* Variables nécessaires pour la première partie du test*/
    Board * board = (Board *)malloc(sizeof(Board));
    Piece * piece = NULL;
    Piece * nextpiece = NULL;
    Piece * holdpiece = NULL;
    Tree * tree = (Tree *)malloc(sizeof(Tree));
    int i, j;

    /* Variables nécessaires pour le fichier de scores */
    char name[26] = "Adrien";
    char name2[26] ="Alan";
    Player * player = NULL;


    Tetris * tetris;

    /* Premier Test */

    piece = createPiece(rand() % 7, 0);
    nextpiece = createPiece(rand() % 7, 0);
    holdpiece = createPiece(rand() % 7, 0);

    printf("Test des fonctions de créations.\n");
    initBoard(board);
    printf("Création de la board + initialisation ... OK \n");
    setCurrentPiece(board, piece);

    printf("Création d'une piece de type : %u et d'orientation : %u \n",
            piece->kind, piece->orientation);
    tetris = createTetris(board, nextpiece, holdpiece, tree);
    printf("Création du Tetris ... OK \n");

    freeTetris(tetris);
    printf("Libération de tetris et de tout ses champs ... OK\n");

    /* Test : Etapes du jeu */
    printf("Test des étapes de jeu \n");
    tetris = startTetris(); /*Lancement du tetris */
    printf("Lancement du tetris ... OK. \n");

    printf("Current piece : \n kind = %u , orientation = %u \n",
          tetris->board->currentPiece->kind,
          tetris->board->currentPiece->orientation);
    printf("Next piece : \n kind = %u , orientation = %u \n",
          tetris->nextpiece->kind,
          tetris->nextpiece->orientation);

    for(i = 0; i < 20; i++) // Affichage de la grille
    {
        for(j = 0; j < 10; j++)
        {
            printf("%u ", tetris->board->gridge[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    dropCurrentPiece(tetris->board);

    for(i = 0; i < 20; i++) // Affichage de la grille
    {
        for(j = 0; j < 10; j++)
        {
            printf("%u ", tetris->board->gridge[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    /* Après pose de la currentPiece, la nextPiece devient la currentPiece
       puis nouvelle nextPiece */
    gameStep(tetris);

    /* Vérification que le gameStep marche bien */
    printf("Après le gameStep \n");
    printf("Current piece : \n kind = %u , orientation = %u \n",
           tetris->board->currentPiece->kind,
           tetris->board->currentPiece->orientation);
    printf("Next piece : \n kind = %u , orientation = %u \n",
            tetris->nextpiece->kind,
            tetris->nextpiece->orientation);


    for(i = 0; i < 20; i++) // Affichage de la grille
    {
        for(j = 0; j < 10; j++)
        {
            printf("%u ", tetris->board->gridge[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("On bouge la piece vers le bas. \n");
    moveCurrentPieceDown(tetris->board);

    for(i = 0; i < 20; i++) // Affichage de la grille
    {
        for(j = 0; j < 10; j++)
        {
            printf("%u ", tetris->board->gridge[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("On bouge la pièce vers la gauche. \n");
    moveCurrentPieceLeft(tetris->board);

    for(i = 0; i < 20; i++) // Affichage de la grille
    {
        for(j = 0; j < 10; j++)
        {
            printf("%u ", tetris->board->gridge[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("On bouge la pièce vers la droite. \n");
    moveCurrentPieceRight(tetris->board);

    for(i = 0; i < 20; i++) // Affichage de la grille
    {
        for(j = 0; j < 10; j++)
        {
            printf("%u ", tetris->board->gridge[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("On fait tourner la pièce.\n");
    rotationPiece(tetris->board);

    for(i = 0; i < 20; i++) // Affichage de la grille
    {
        for(j = 0; j < 10; j++)
        {
            printf("%u ", tetris->board->gridge[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    freeTetris(tetris);

    printf("Libération de tetris et de tout ses champs ... OK\n");



    /* Test : Fichier de scores */

    printf("Test : Fichier de scores.\n");
    tetris = startTetris();
    printf("Lancement de Tetris ... OK.\n");

    for(i=1;i<=10;i++)
    {
        player = createPlayer(name2,i*100000);
        insertPlayerInTree(tetris->treescores, player);
    }

    player = createPlayer(name, 1100000);
    insertPlayerInTree(tetris->treescores, player);
    saveScoreData(tetris->treescores, "../data/scores.txt");
    printf("Scores correctement sauvés.\n");
    freeTree(tetris->treescores);
    printf("Libération de l'arbre de scores.\n");
    tetris->treescores = malloc(sizeof(Tree));
    initTree(tetris->treescores);
    openScoreData(tetris->treescores, "../data/scores.txt");
    displayScore(tetris->treescores);

    freeTetris(tetris);
}
