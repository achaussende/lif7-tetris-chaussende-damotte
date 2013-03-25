#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "binarytrees.h"

void setNodeValue (Node node, const Player player)
{
    node.value = player;
}

Player getNodeValue(const Node node)
{
    return node.value;
}

void setNodeLeft_Child(Node node, const Node * pnode)
{
    node.left_child = pnode;
}

Node * getNodeLeft_Child(const Node node)
{
    return node.left_child;
}

void setNodeRight_Child(Node node, const Node * pnode)
{
    node.right_child = pnode;
}

Node * getNodeRight_Child(const Node node)
{
    return node.right_child;
}

void setTreeRoot(Tree tree, const Node * root)
{
    tree.root = root;
}

Node * getTreeRoot(const Tree tree)
{
    return tree.root;
}

void setTreeNb_Elements(Tree tree, const int n)
{
    tree.nb_elements = n;
}

int getTreeNb_Elements(const Tree tree)
{
    return tree.nb_elements;
}

void initTree (Tree * tree)
{
    Node * pnode;
    pnode = (Node *) malloc(sizeof(Node));

//    setTreeRoot(&tree, pnode); // Soucis pour le type d'arguments => cf tp LIF5


}
//void freeTree (Tree * tree);
