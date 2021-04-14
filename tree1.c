#include "tree1.h"
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

node_t *nearestNode(double xinp, double yinp, node_t *par, double sD, int count) {
    node_t *curr = (node_t *)malloc(sizeof(node_t));
    double result1, result2, xcurr, ycurr;
    double D, keyD;
    char *pxc, *pyc;
    
    curr = par;
    
    /* Gets current nodes xCo and yCo and dist */
    xcurr = strtod(curr->row->xCo, &pxc);
    ycurr = strtod(curr->row->yCo, &pyc);
    
    D = calcDist(xinp, yinp, curr);
    
    if(count%2==0){
        result1 = xcurr - xinp;
        result2 = ycurr - yinp;
        keyD = result1;
    }
    else{
        result1 = ycurr - yinp;
        result2 = xcurr - xinp;
        keyD = result1;
    }
    count++;
    
    if(D<sD){
        sD = D;
    }
    // if distance is 0
    if(D == 0){
//         printf("MATCHING NODE\n");
        printf("COUNT IS %d\n", count);
        return curr;
    }
    
    if(curr->right==NULL && curr->left==NULL){
//         printf("LAST NODE\n");
        printf("COUNT IS %d\n", count);
        return curr;
    }
    
    // if keyd is greater than shortest distance proceed down either left or right branch
    if(keyD > sD){
//         printf("GOING ONE BRANCH\n");
        // case 1: key point is smaller
        if(result1<0){
            if(curr->left != NULL){
                return nearestNode(xinp, yinp, curr->left, sD, count);
            }
        }
        // case 2: key point is larger
        else if(result1>0){
            if(curr->right != NULL){
                return nearestNode(xinp, yinp, curr->right, sD, count);
            }
        }
        // case 3: key point is same and secondary point is different
        else if(result1==0){
            if(result2!=0){
                if(curr->right != NULL){
                    return nearestNode(xinp, yinp, curr->right, sD, count);
                }    
            }
        }
        // if result is wack
        else{
            printf("COUNT IS %d\n", count);
            return curr;
        }
    }
    // if keyd is less than or equal to shortest distance, proceed down both branches
    else{
//         printf("GOING BOTH BRANCH\n");
        if(curr->right != NULL && curr->left != NULL){
            // go left or right depending on which is closer
            if(calcDist(xinp, yinp, curr->right) > calcDist(xinp, yinp, curr->left)){
                return nearestNode(xinp, yinp, curr->left, sD, count);
            }
            else{
                return nearestNode(xinp, yinp, curr->right, sD, count);
            }
        }
        else if(curr->right == NULL && curr->left != NULL){
            return nearestNode(xinp, yinp, curr->left, sD, count);
        }
        else if(curr->right != NULL && curr->left == NULL){
            return nearestNode(xinp, yinp, curr->right, sD, count);
        }
        else{
//             printf("THOUGH GOING BOTH THERE ARE NO CHILDEREN\n");
            printf("COUNT IS %d\n", count);
            return curr;
        }
    }

    // if the next node is empty, return current node
//     printf("NODE WAS EMPTY??\n");
    printf("COUNT IS %d\n", count);
    return curr;
}