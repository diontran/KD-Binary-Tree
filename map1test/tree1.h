#ifndef TREE
#define TREE
#include "leaf.h"

typedef struct tree{
    node_t *root;
    int size;    
} tree_t;

tree_t *createKDTree();
node_t *insertLeaf(node_t *leaf, node_t *par, int count);
node_t *nearestNode(double xinp, double yinp, node_t *par, double sD);


#endif