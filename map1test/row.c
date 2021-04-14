#include "row.h"

/* Looks for uneven number of quotation marks in token */
int qCheck(char *token){
    int len = strlen(token);
    int counter = 0;
    char search = '"';
    for(int i = 0; i < len; i++){
        if(token[i] == search){
            counter++;
        }
    }
    if(counter % 2 == 0){
        return 0;
    }
    else{
        return 1;
    }
}

/* Creates Row Structure and fills it with data */
row_t *createRow(char *line){
    
    /* Sets up arrays */
    char arr[NUM_OF_ATR][MAX_STRING_SIZE]; 
    char *token; 
    char s[2] = ",";
    int i = 0, qcount = 0;    
    
    /* get the first token */
    token = strtok(line, s);    
    
    /* initialize curr row */
    row_t *curr = malloc(sizeof(row_t));
    
    /* walk through tokens */
    while(token != NULL){
        char temptoken[128];
        /* Adding token into an array */
        
        /* If uneven number of quotation marks */
        if((qCheck(token) == 1) && (qcount == 0)){
            strcat(temptoken, token);
            qcount = 1;
            i--;
        }
        
        /* If there was previously a quotation mark but none in current token */
        /* Append token to previous token */
        else if((qCheck(token) == 0) && (qcount == 1)){
            strcat(temptoken, s);
            strcat(temptoken, token);
            i--;
        }
        
        /* If previous tokens had uneven quotation mark, append this token to previous token */
        else if(qcount == 1) {
            strcpy(arr[i], temptoken);
            strcat(arr[i], s);
            strcat(arr[i], token);
            temptoken[0] = '\0';
            qcount = 0;
        }
        
        /* Append token to array */
        else{
            strcpy(arr[i], token);
        }
        i++;
        token = strtok(NULL, s);
    }
    
    /* Filling with data */
    curr->censusYear = strdup(arr[0]);
    curr->blockID = strdup(arr[1]);
    curr->propertyID = strdup(arr[2]);
    curr->basepropertyID = strdup(arr[3]);
    curr->clueSmallArea = strdup(arr[4]);
    curr->tradingName = strdup(arr[5]);
    curr->industryCode = strdup(arr[6]);
    curr->industryDesc = strdup(arr[7]);
    curr->xCo = strdup(arr[8]);
    curr->yCo = strdup(arr[9]);
    curr->location = strdup(arr[10]);
    
    return curr;
}