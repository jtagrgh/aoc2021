#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define BIN_SIZE 12

int main() {
    
    FILE* fp = fopen("input.txt", "r");
    char bin[BIN_SIZE + 1];
    int gamma[BIN_SIZE] = {0};

    int lineCount = 0;

    while(fscanf(fp, "%s", bin) != EOF){
        lineCount++;
        for (int i = 0; i < BIN_SIZE; i++){
            gamma[i] += (bin[i] - '0');
        }
    }

    int eps[BIN_SIZE];

    int dgamma = 0;
    int deps = 0;

    int pos = BIN_SIZE - 1;

    for (int i = 0; i < BIN_SIZE; i++){
        if (gamma[i] < lineCount/2){
            deps += pow(2, BIN_SIZE - i - 1);
            gamma[i] = 0;
            eps[i] = 1;
        } else {
            dgamma += pow(2, BIN_SIZE - i - 1);
            gamma[i] = 1;
            eps[i] = 0;
        }
    }

    printf("%d \n", dgamma*deps);


    for (int i = 0; i < BIN_SIZE; i++){
        printf("%d", gamma[i]);
    }
    printf("\n");
    for (int i = 0; i < BIN_SIZE; i++){
        printf("%d", eps[i]);
    }

    

    printf("\n%d\n", gamma[0]);

    return 0;
}
