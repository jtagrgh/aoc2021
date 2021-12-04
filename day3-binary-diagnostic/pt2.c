#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define BIN_SIZE 12

char** oxReduce(char** rows, int index, int* length);
char** coReduce(char** rows, int index, int* length);

int main() {
    
    FILE* fp = fopen("input.txt", "r");

    char** rows = malloc(sizeof(char*));
    *rows = malloc(sizeof(char) * BIN_SIZE);

    int lineCount = 0;
    while(fscanf(fp, "%s", *(rows + lineCount)) != EOF){
        lineCount++;
        rows = realloc(rows, sizeof(char*) * (lineCount+1));
        *(rows + lineCount) = malloc(sizeof(char) * BIN_SIZE);
    }

    for (int i = 0; i < BIN_SIZE; i++){
        rows = oxReduce(rows, i, &lineCount);
    }
    char* oxRate = *rows;


    free(rows);
    rewind(fp);


    rows = malloc(sizeof(char*));
    *rows = malloc(sizeof(char) * BIN_SIZE);

    lineCount = 0;
    while(fscanf(fp, "%s", *(rows + lineCount)) != EOF){
        lineCount++;
        rows = realloc(rows, sizeof(char*) * (lineCount+1));
        *(rows + lineCount) = malloc(sizeof(char) * BIN_SIZE);
    }

    for (int i = 0; i < BIN_SIZE; i++){
        rows = coReduce(rows, i, &lineCount);
    }
    char* coRate = *rows;



    int dox = 0;
    int dco = 0;

    for (int i = 0; i < BIN_SIZE; i++){
        if (oxRate[i] == '1') {
            dox += pow(2, BIN_SIZE - i - 1);
        }
        if (coRate[i] == '1') {
            dco += pow(2, BIN_SIZE - i - 1);
        }
    }


    printf("out: %d\n", dox * dco);


    return 0;
}


char** oxReduce(char** rows, int index, int* length){

    if (*length <= 1) {
        return rows;
    }

    int indexSum = 0;

    for (int i = 0; i < *length; i++) {
        indexSum += ( *(*(rows+i) + index) - '0');
    }


    int ceilLength = *length % 2 == 0 ? *length : *length + 1;

    char gamma = indexSum >= ceilLength/2 ? '1' : '0';


    char** newRows = malloc(sizeof(char*));
    *newRows = malloc(sizeof(char) * BIN_SIZE);

    int lineCount = 0;
    for (int i = 0; i < *length; i++) {
        if ( *(*(rows+i) + index) == gamma ){
            lineCount++;
            strcpy( *(newRows + (lineCount-1)), *(rows+i));
            newRows = realloc(newRows, sizeof(char*) * (lineCount+1));
            *(newRows + lineCount) = malloc(sizeof(char) * BIN_SIZE);
        }
    }

    free(rows);

    *length = lineCount;


    return(newRows);
}

char** coReduce(char** rows, int index, int* length){

    if (*length <= 1) {
        return rows;
    }

    int indexSum = 0;

    for (int i = 0; i < *length; i++) {
        indexSum += ( *(*(rows+i) + index) - '0');
    }


    int ceilLength = *length % 2 == 0 ? *length : *length + 1;

    char gamma = indexSum >= ceilLength/2 ? '0' : '1';


    char** newRows = malloc(sizeof(char*));
    *newRows = malloc(sizeof(char) * BIN_SIZE);

    int lineCount = 0;
    for (int i = 0; i < *length; i++) {
        if ( *(*(rows+i) + index) == gamma ){
            lineCount++;
            strcpy( *(newRows + (lineCount-1)), *(rows+i));
            newRows = realloc(newRows, sizeof(char*) * (lineCount+1));
            *(newRows + lineCount) = malloc(sizeof(char) * BIN_SIZE);
        }
    }

    free(rows);

    *length = lineCount;


    return(newRows);
}

