#include "tree2.h"
#include "leaf.h"
#include <math.h>


/* Creates KDTree with a root pointing to nothing */
tree_t *createKDTree(){
    tree_t *tree = (tree_t *)malloc(sizeof(tree_t));
    
    tree->root = NULL;
    tree->size = 0;
    
    return tree;
}

/* Inserts leaf onto tree */
node_t *insertLeaf(node_t *leaf, node_t *par, int count){
    node_t *head = (node_t *)malloc(sizeof(node_t));
    double result1, result2, xleaf, yleaf, xhead, yhead;
    char *pxl, *pyl, *pxh, *pyh;
    head = par;
    
    /* Add node to empty child */
    if(par == NULL){
        //printf("%s %s\n", leaf->row->xCo, leaf->row->yCo);
        return leaf;
    }
    
    /* Gets Xco and Yco of leaf and Head in double */
    xleaf = strtod(leaf->row->xCo, &pxl);
    yleaf = strtod(leaf->row->yCo, &pyl);
    
    xhead = strtod(head->row->xCo, &pxh);
    yhead = strtod(head->row->yCo, &pyh);
    
    /* Checks if inserting with x or y value */
    if(count%2==0){
        //printf("%d\t", count);
        result1 = xleaf - xhead;
        result2 = yleaf - yhead;
        //printf("%lf\t%lf\t%lf\n", xleaf, xhead, result1);
    }
    else{
        //printf("%d\n", count);
        result1 = yleaf - yhead;
        result2 = xleaf - xhead;
    }
    count++;
    //printf("%d\t", count);
    
    if(result1<0){
        //printf("going left ");
        head->left = insertLeaf(leaf, head->left, count);
    }
    else if(result1>0){
        //printf("going right ");
        head->right = insertLeaf(leaf, head->right, count);
    }
    else if(result1==0){
        if(result2==0){
            //printf("going next ");
            head->next = insertLeaf(leaf, head->next, count);
        }
        else{
            //printf("going right ");
            head->right = insertLeaf(leaf, head->right, count);
        }
    }
    else{ 
        exit(1);
    }
}

void printNearestNode(double xinp, double yinp, double rad, node_t *par, double sD, int count, FILE *file) {
    node_t *curr = (node_t *)malloc(sizeof(node_t));
    node_t *list = (node_t *)malloc(sizeof(node_t));
    double result1, result2, xcurr, ycurr;
    double D, keyD;
    char *pxc, *pyc;
    curr = par;
       
    xcurr = strtod(curr->row->xCo, &pxc);
    ycurr = strtod(curr->row->yCo, &pyc);
    
    D = calcDist(xinp, yinp, curr);
    if(count%2==0){
        result1 = xcurr - xinp;
        result2 = ycurr - yinp;
    }
    else{
        result1 = ycurr - yinp;
        result2 = xcurr - xinp;
    }
    count++; 
    keyD = result1;
    if(D<sD){
        sD = D;
    }
    // if distance is less than the radius, prints node and goes next
    if(D <= rad){
        list = curr;
        while(list!=NULL){
            printf("COUNT = %d\n", count);
            printLeaf(list, stdout);
            printNode(list, file);
            list = list->next;
        }
    }    
    // if keyd is greater than shortest distance proceed down either left or right branch
    if(keyD > sD){
        // case 1: key point is smaller
        if(result1<0){
            if(curr->left != NULL){
                printNearestNode(xinp, yinp, rad, curr->left, sD, count, file);
            }
        }
        // case 2: key point is larger
        else if(result1>0){
            if(curr->right != NULL){
                printNearestNode(xinp, yinp, rad, curr->right, sD, count, file);
            }
        }
        // case 3: key point is same and secondary point is different
        else if(result1==0){
            if(result2!=0){
                if(curr->right != NULL){
                    printNearestNode(xinp, yinp, rad, curr->right, sD, count, file);
                }    
            }
        }
        // if result is wack
        else{ 
        }
    }
    // if keyd is less than or equal to shortest distance, proceed down both branches
    else{
        if(curr->right != NULL && curr->left != NULL){
            // go left or right depending on which is closer
            if(calcDist(xinp, yinp, curr->right) > calcDist(xinp, yinp, curr->left)){
                printNearestNode(xinp, yinp, rad, curr->left, sD, count, file);
            }
            else{
                printNearestNode(xinp, yinp, rad, curr->right, sD, count, file);
            }
        }
        else if(curr->right == NULL && curr->left != NULL){
            printNearestNode(xinp, yinp, rad, curr->left, sD, count, file);
        }
        else if(curr->right != NULL && curr->left == NULL){
            printNearestNode(xinp, yinp, rad, curr->right, sD, count, file);
        }
        else{
        }
    }

    free(list);;
}
