/**
    \file [node.h]
    \brief 	Contient la déclaration des fonctions et
    structure pour les noeuds des arbres
    \author {Damotte Alan, Chaussende Adrien}
    \version 1.1
    \date Mai 2013
*/

#ifndef NODE_H
#define NODE_H

#include "player.h"

/* ============= Structure Node ============== */

/**
    @struct Node
    @brief Structure d'un Noeud
*/
typedef struct Node
{
    Player * value;
    struct Node * left_child;
    struct Node * right_child;
}Node;

/* ====== Node : Mutateurs & Accesseurs ======= */

/**

        @brief mutateur de valeur d'un noeud
        @param pointeur sur un Node et pointeur sur un Player
*/
void setNodeValue (Node * node, const Player * player);

/**

        @brief assesseur de la valeur d'un noeud
        @param pointeur sur un Node
        @return pointeur sur un Player
*/
Player * getNodeValue(const Node * node);

/**

        @brief mutateur de valeur du fils gauche d'un noeud
        @param pointeur sur un Node et un pointeur sur Noeud
*/
void setNodeLeft_Child(Node * node, const Node * pnode);

/**

        @brief assesseur de la valeur du fils gauche d'un noeud
        @param pointeur sur un Node
        @return pointeur sur un Node
*/
Node * getNodeLeft_Child(const Node * node);

/**

        @brief mutateur de valeur du fils droit d'un noeud
        @param pointeur sur un Node et un pointeur sur Noeud
*/
void setNodeRight_Child(Node * node, const Node * pnode);

/**

        @brief assesseur de la valeur du fils droit d'un noeud
        @param pointeur sur un Node
        @return pointeur sur un Node
*/
Node * getNodeRight_Child(const Node * node);

/* ============= Node : Méthodes ============== */
/**

        @brief méthode d'initialisation d'un noeud
        @param pointeur sur un Node et pointeur sur un Player
*/
void initNode(Node * node, const Player * player);

/**

        @brief méthode de création d'un noeud
        @param pointeur sur un Player
        @return pointeur sur un Node
*/
Node * createNode(const Player * player);

/**

        @brief méthode de libération d'un noeud
        @param pointeur sur un Node
*/
void freeNode(Node * node);

#endif
