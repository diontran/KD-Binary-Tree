#include "leaf.h"

/* Creates Node with row data and a pointer to next */
node_t *createLeaf(row_t *row){
    node_t *temp = (node_t *)malloc(sizeof(node_t));
    temp->row = row;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

/* Prints leaf to file */
void printNode(node_t *leaf, FILE *file){
    fprintf(file, "%s %s --> Census year: %s || Block ID: %s || Property ID: %s || Base Property ID: %s || CLUE small area: %s || Industry (ANZSIC4) code: %s || Industry (ANZSIC4) description: %s || x coordinate: %s || y coordinate: %s || Location: (%s, %s) ||\n\n", leaf->row->xCo, leaf->row->yCo, leaf->row->censusYear, leaf->row->blockID, leaf->row->propertyID, leaf->row->basepropertyID, leaf->row->clueSmallArea, leaf->row->industryCode, leaf->row->industryDesc, leaf->row->xCo, leaf->row->yCo, leaf->row->yCo, leaf->row->xCo);
}

void printLeaf(node_t *leaf, FILE *file){
    fprintf(file, "%s %s --> Industry (ANZSIC4) code: %s || Trading Name: %s || Location:  (%s, %s) ||\n\n", leaf->row->xCo, leaf->row->yCo, leaf->row->industryCode, leaf->row->tradingName, leaf->row->yCo, leaf->row->xCo);
}



/* Calculate Distance between node and a point*/
double calcDist(double x1, double y1, node_t *node){
    double x2, y2;
    double dist, result;
    char *px2, *py2;
    
    x2 = strtod(node->row->xCo, &px2);
    y2 = strtod(node->row->yCo, &py2);
    
    dist = ((x1-x2)*(x1-x2))+((y1-y2)*(y1-y2));
    result = sqrt(dist);    
    return result;
}
    
    