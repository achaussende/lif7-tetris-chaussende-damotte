/**
    \file [binarytrees.h]
    \brief 	Contient la déclaration des fonctions
    et structure nécessaires aux arbres de scores
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
        @param pointeur sur un Tree et pointeur sur un Node
*/
void setTreeRoot(Tree * tree, const Node * root);

/**

        @brief assesseur de la racine d'un arbre
        @param pointeur sur un Tree
        @return pointeur sur un Node
*/
Node * getTreeRoot(const Tree * tree);

/**

        @brief mutateur du nombre d'éléments d'un  arbre
        @param pointeur sur un Tree et un entier
*/
void setTreeNb_Elements(Tree * tree, const unsigned int n);

/**

        @brief assesseur du nombre d'éléments d'un  arbre
        @param pointeur sur un Tree
        @return un entier
*/
unsigned int getTreeNb_Elements(const Tree * tree);

/* ============= Tree : Méthodes =============== */
/**

        @brief méthode d'initialisation d'un arbre
        @param pointeur sur un Tree
*/
void initTree (Tree * tree);

/**

        @brief méthode d'initialisation d'un arbre
        par récursivité sur le noeud
        @param pointeur sur un Node

*/
void freeTree_recursion(Node * node);

/**

        @brief méthode de libération d'un arbre
        @param pointeur sur un Tree
*/
void freeTree (Tree * tree);

/**

        @brief méthode d'initialisation d'un joueur
        dans l'arbre par récursivité sur le noeud
        @param pointeur sur un Node (double pointeur)
        et pointeur sur un Player

*/
void insertPlayerInTree_recursion(Node ** node, Player * player);

/**

        @brief méthode d'initialisation d'un joueur dans l'arbre
        @param pointeur sur un Tree et pointeur sur un Player

*/
void insertPlayerInTree(Tree * tree, Player * player);

/**

        @brief méthode de suppression du minimum dans un arbre
        @param pointeur sur un Tree

*/
void deleteTreeMin(Tree * tree);

#endif
