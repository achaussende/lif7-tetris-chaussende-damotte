/**
    \file [binarytrees.h]
    \brief 	Contient la déclaration des fonctions et structures nécessaires aux arbres de scores
    \author {Damotte Alan, Chaussende Adrien}
    \version 0.1
    \date Mars 2013
*/
#ifndef BINARYTREES_H
#define BINARYTREES_H

#include "node.h"



/* ============ Structure : Tree ============== */
/**
    @struct Tree
    @brief Structure d'un Arbre
*/
typedef struct
{
    Node * root;
    unsigned int nb_elements;
}Tree;

/* ======= Tree : Mutateurs & Accesseurs ======= */
/**

        @brief mutateur de la racine d'un arbre
        @param un Tree et un Node
*/
void setTreeRoot(Tree * tree, const Node * root);

/**

        @brief assesseur de la racine d'un arbre
        @param un Tree
        @return un Node
*/
Node * getTreeRoot(const Tree * tree);

/**

        @brief mutateur du nombre d'éléments d'un  arbre
        @param un Tree et un int
*/
void setTreeNb_Elements(Tree * tree, const unsigned int n);

/**

        @brief assesseur du nombre d'éléments d'un  arbre
        @param un Tree
        @return un int
*/
unsigned int getTreeNb_Elements(const Tree * tree);

/* ============= Tree : Méthodes =============== */
/**

        @brief méthode d'initialisation d'un arbre
        @param un Tree
*/
void initTree (Tree * tree);

/**

        @brief méthode d'initialisation d'un arbre par récursivité sur le noeud
        @param un Node

*/
void freeTree_recursion(Node * node);

/**

        @brief méthode de libération d'un arbre
        @param un Tree
*/
void freeTree (Tree * tree);

/**

        @brief méthode d'initialisation d'un joueur dans l'arbre par récursivité sur le noeud
        @param un Node (double pointeur) et un Player

*/
void insertPlayerInTree_recursion(Node ** node, Player * player);

/**

        @brief méthode d'initialisation d'un joueur dans l'arbre
        @param un Tree et un Player

*/
void insertPlayerInTree(Tree * tree, Player * player);

/**

        @brief méthode de suppression du minimum dans un arbre
        @param un Tree

*/
void deleteTreeMin(Tree * tree);

#endif
