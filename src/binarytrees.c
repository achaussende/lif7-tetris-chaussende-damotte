/**
    \file [binarytrees.c]
    \brief 	Contient les fonctions et structures nécessaires aux arbres de scores
    \author {Damotte Alan, Chaussende Adrien}
    \version 1.1
    \date Mars-Avril 2013
*/
#include <stdlib.h>
#include <stdio.h>

#include "binarytrees.h"

/* ======== Mutateurs et Accesseurs ========== */

void setTreeRoot(Tree * tree, const Node * root)
{
    tree->root = root;
}

Node * getTreeRoot(const Tree * tree)
{
    return tree->root;
}

void setTreeNb_Elements(Tree * tree, const unsigned int n)
{
    tree->nb_elements = n;
}

unsigned int getTreeNb_Elements(const Tree * tree)
{
    return tree->nb_elements;
}
void initTree (Tree * tree)
{
    setTreeRoot(tree, NULL);
    setTreeNb_Elements(tree, 0);
}

void freeTree_recursion(Node * node)
{
    if(node != NULL)
    {
        freeTree_recursion(node->left_child);
        freeTree_recursion(node->right_child);
        free(node);
    }
}

void freeTree (Tree * tree)
{
    freeTree_recursion(tree->root);
}

/* ================ Méthodes ================= */

void insertPlayerInTree_recursion(Node ** node, Player * player)
{
    if((*node) == NULL)
    {
        (*node) = createNode(player);
    }
    else
    {
        if(player->score >= (*node)->value->score)
        {
            insertPlayerInTree_recursion(&((*node)->right_child), player);
        }
        else
        {
            insertPlayerInTree_recursion(&((*node)->left_child), player);
        }
    }
}
void insertPlayerInTree (Tree * tree, Player * player)
{
    insertPlayerInTree_recursion(&tree->root, player);
    tree->nb_elements++;

    if(tree->nb_elements > 50)
    {
        deleteTreeMin(tree);
        tree->nb_elements--;
    }
}

void deleteTreeMin(Tree * tree)
{
    Node * n;
    n = tree->root;

    Node * p;
    p = NULL;


    while(n->left_child != NULL)
    {
        n = n->left_child;
    }

    if(n->right_child == NULL)
    {
        freeNode(n);
    }
    else
    {
        p = n->right_child;
        n = p;
        freeNode(p);

    }
}
