/*
* C Programming Style for Engineering Computation
* Created by Dion Tran (dion@student.unimelb.edu.au) 26/08/2020
*/
#include "tree2.h"
#include "leaf.h"
#include "row.h"
#include <unistd.h>

int main(int argc, char **argv){
    setvbuf(stdout, NULL, _IONBF, 0);
    char *filename = NULL;
    char *outputname = NULL;
    
    int lineNumber = 0;
    char *line = NULL;
    size_t lineBufferLength = 512;    
    
    if (argc < 2){
        return 0;
    } 
    
    /* Set the filenames. */
    filename = argv[1];
    outputname = argv[2];
    
    /* Open the files with the given filename for reading. */
    FILE *input = fopen(filename, "r");
    FILE *output = fopen(outputname, "w+");
    
    /* Create new K-D Binary Tree */
    tree_t *newTree = createKDTree();
    
    /* Fills Tree */
    int skipheader = 0;
    while(getline(&line, &lineBufferLength, input) > 0){
        int count = 0;
        if(skipheader){
            row_t *row = createRow(line);
            node_t *leaf = createLeaf(row);
            newTree->root = insertLeaf(leaf, newTree->root, count);   
        }
        skipheader = 1;
        lineNumber++;
    }
    printLeaf(newTree->root, stdout);
    printLeaf(newTree->root->right, stdout);
    printLeaf(newTree->root->right->right, stdout);
    
    /* Looking for closest locations */ 
    char *buffer = NULL;
    size_t bufferSize = 20000;
    
    /* getting location inputs from stdin*/
    while(getline(&buffer, &bufferSize, stdin) > 0){
        double xinp, yinp, rad, sD;
        char *pxi, *pyi, *pri;
        size_t length = strlen(buffer) - 1;
        sD = 1.00;
        
        if(*buffer && buffer[length] == '\n'){
            buffer[length] = '\0';
        }
        printf("**********THIS IS A NEW LOCATION**********\n");
        
        /* Take string inputs and convert to doubles*/
        char *token = strtok(buffer, " ");
        xinp = strtod(token, &pxi);
        token = strtok(NULL, " ");
        yinp = strtod(token, &pyi);
        token = strtok(NULL, " ");
        rad = strtod(token, &pri);
        sleep(1);
        
        /* Prints All nodes in radius */
//         printNearestNode(xinp, yinp, rad, newTree->root, sD, output);
        xinp = yinp = rad = 0.00;
    }
    
    /* Close */
    fflush(stdin);
    fflush(stdout);
    fflush(output);
    
    fclose(input);
    fclose(output);
    free(newTree);
    free(line);
    return 0;
}