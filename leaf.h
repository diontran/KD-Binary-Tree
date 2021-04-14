#ifndef LEAF
#define LEAF
#include "row.h"

typedef struct node{
    row_t *row;
    struct node *left;
    struct node *right;
    struct node *next;
} node_t;

node_t *createLeaf(row_t *row);
void printNode(node_t *leaf, FILE *file);
void printLeaf(node_t *leaf, FILE *file);
double calcDist(double x1, double y1, node_t *node);

#endif