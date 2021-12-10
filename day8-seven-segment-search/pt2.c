#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum digits {
    one = 2,
    four = 4,
    seven = 3,
    eight = 7,
};

struct digit {
    int val;
    int comb[10];
};

int diffCount(char* str1, char* str2) {

    int count = 0;

    char c1;
    char c2;
    
    int i = 0;
    while ( (c1 = str1[i++]) != '\0' ) {
        int found = 0;

        int j = 0;
        while ( (c2 = str2[j++]) != '\0' ) {
            if (c1 == c2) found = 1;      
        }

        if (found == 0) count++;
    }

    return -count;
}


void mapDigits(char digits[10][10], char patterns[10][10]) {

    for (int i = 0; i < 10; ++i){

        int length = 0;
        for (; patterns[i][length] != '\0'; ++length);

        if (length == 2) strcpy(digits[1], patterns[i]);
        if (length == 4) strcpy(digits[4], patterns[i]);
        if (length == 3) strcpy(digits[7], patterns[i]);
        if (length == 7) strcpy(digits[8], patterns[i]);

    }


    for (int i = 0; i < 10; ++i) {

        int length = 0;
        for (; patterns[i][length] != '\0'; ++length);

        if (length == 5) {
            if (diffCount(patterns[i], digits[4]) == -3) {
                strcpy(digits[2], patterns[i]);
            }
            else if (diffCount(patterns[i], digits[1]) == -3) {
                strcpy(digits[3], patterns[i]);
            }
            else {
                strcpy(digits[5], patterns[i]);
            }
        }
        if (length == 6) {
            if (diffCount(patterns[i], digits[1]) == -5) {
                strcpy(digits[6], patterns[i]);
            }
            else if (diffCount(patterns[i], digits[4]) == -2) {
                strcpy(digits[9], patterns[i]);
            }
            else {
                strcpy(digits[0], patterns[i]);
            }
        }
    }
}


int main() {

    FILE* fp = fopen("input.txt", "r");
    
    char patterns[10][10];
    char outdigit[10];
    char outseq[10];

    char digits[10][10];

    char buff[5];

    int outSum = 0;

    while (1) {

        for (int i = 0; i < 10; ++i) {
            if (fscanf(fp, "%s", patterns[i]) == EOF) goto exit;
        }

        fscanf(fp, "%s", buff);

        mapDigits(digits, patterns); 

        for (int i = 0; i < 4; ++i){
            fscanf(fp, "%s", outdigit);

            for (int j = 0; j < 10; ++j) {

                if (diffCount(outdigit, digits[j]) == 0
                    && diffCount(digits[j], outdigit) == 0) {

                    outseq[i] = (j + '0');                    
                }
            }
        }
        outSum += atoi(outseq);
    }
    exit:


    printf("Total: %d\n", outSum);
    
    return 0;
}
