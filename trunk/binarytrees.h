#ifndef BINARYTREES_H
#define BINARYTREES_H

#include "player.h"

/* Structure Node */

typedef struct
{
    Player value;
    Node * left_child;
    Node * right_child;
}Node;

/* Node : Mutateurs & Accesseurs */

void setNodeValue (Node node, const Player player);
Player getNodeValue(const Node node);

void setNodeLeft_Child(Node node, const Node * pnode);
Node * getNodeLeft_Child(const Node node);

void setNodeRight_Child(Node node, const Node * pnode);
Node * getNodeRight_Child(const Node node);

/* Structure : Tree */

typedef struct
{
    Node * root;
    int nb_elements;
}Tree;

/* Tree : Mutateurs & Accesseurs */

void setTreeRoot(Tree tree, const Node * root);
Node * getTreeRoot(const Tree tree);

void setTreeNb_Elements(Tree tree, const int n);
int getTreeNb_Elements(const Tree tree);

/* Méthodes */

void initTree (Tree * tree);
void freeTree (Tree * tree);

#endif
