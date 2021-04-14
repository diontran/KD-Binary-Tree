#ifndef ROW
#define ROW
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#define NUM_OF_ATR 15
#define MAX_STRING_SIZE 130

typedef struct row{
    char *censusYear;
    char *blockID;
    char *propertyID;
    char *basepropertyID;
    char *clueSmallArea;
    char *tradingName;
    char *industryCode;
    char *industryDesc;
    char *xCo;
    char *yCo;
    char *location;
} row_t;

row_t *createRow(char *line);
int qCheck(char *token);

#endif