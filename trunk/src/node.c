#include <stdlib.h>
#include <stdio.h>

#include <assert.h> /* Pour la fonction assert */
#include <string.h> /* Pour les fonctions sur les chaines de caractères */

#include "node.h"

/* ======== Mutateurs et Accesseurs ========== */

void setNodeValue (Node * node, const Player * player)
{
    node->value = player;
}

Player * getNodeValue(const Node * node)
{
    return node->value;
}

void setNodeLeft_Child(Node * node, const Node * pnode)
{
    node->left_child = pnode;
}

Node * getNodeLeft_Child(const Node * node)
{
    return node->left_child;
}

void setNodeRight_Child(Node * node, const Node * pnode)
{
    node->right_child = pnode;
}

Node * getNodeRight_Child(const Node * node)
{
    return node->right_child;
}

/* ================ Méthodes ================= */

void initNode(Node * node, const Player * player)
{
    /* Vérification fiche joueur valide */

    assert(player->score >= 0 && strlen(player->name)>0);

    /* Initialisation */

    setNodeValue(node, player);
    setNodeLeft_Child(node, NULL);
    setNodeRight_Child(node, NULL);
}

Node * createNode(const Player * player)
{
    Node * node = (Node *)malloc(sizeof(Node));

    initNode(node, player);
    return node;
}

void freeNode(Node * node)
{
    setNodeLeft_Child(node, NULL);
    setNodeRight_Child(node, NULL);
    free(node->value);
    free(node);
}
