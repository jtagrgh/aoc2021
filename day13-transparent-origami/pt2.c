#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 2000  

void foldX (int** grid, int, int*, int*); 
void foldY (int** grid, int, int*, int*);
int score (int** grid, int, int, int, int);
void printGrid (int** grid, int, int, int, int);


int main() {

    int* grid[SIZE];
    for (int i = 0; i < SIZE; i++) {
        grid[i] = (int*)malloc(sizeof(int) * SIZE);
    }

    FILE* fp = fopen("input.txt", "r");

    int xMax = 0;
    int xMin = 0;
    int yMax = 0;
    int yMin = 0;

    char buff[10];

    while (fscanf(fp, "%s", buff) ) {
        if (!strcmp(buff, "fold")) break;

        char* number = strtok(buff, ",");
        int x = atoi(number);
        if (x > xMax) xMax = x;

        number = strtok(NULL, ",");
        int y = atoi(number);
        if (y > yMax) yMax = y;

        grid[x][y]++;
    }


    while (fscanf(fp, "%s", buff) != EOF) {
        if (!strcmp(buff, "fold") || !strcmp(buff, "along")) continue;

        char* foldType;
        int val;

        foldType = strtok(buff, "=");
        val = atoi(strtok(NULL, "="));

        if (!strcmp(foldType, "x")) {
            foldX(grid, val, &xMax, &xMin);
        }
        else if (!strcmp(foldType, "y")) {
            foldY(grid, val, &yMax, &yMin);
        }
    }

    printGrid(grid, xMax, xMin, yMax, yMin);
    printf("score %d\n", score(grid, xMax, xMin, yMax, yMin));


    return 0;
}

void printGrid (int** grid, int xMax, int xMin, int yMax, int yMin){
    for (int i = yMin; i <= yMax; i++) {
        for (int j = xMin; j <= xMax; j++) {
            if (grid[j][i] == 0) printf(". ");
            else printf("%d ", grid[j][i]);
        }
        printf("\n");
    }
}

void foldX (int** grid, int x, int* xMax, int* xMin){ 
    /* This handles cases where it folds right,
     * I realize the input never even does this
     */
    if (x < *xMax/2) {
        int opp = x + 1;
        int line = x - 1;

        for (; line >= *xMin; line--) {
            for (int y = 0; y < SIZE; y++) {
                if (grid[line][y] >= 1) grid[opp][y]++;
            }
            opp++;
        }

        *xMin = x + 1;
    } 
    else {
        int opp = x - 1;
        int line = x + 1;

        for (; line <= *xMax; line++) {
            for (int y = 0; y < SIZE; y++) {
                if (grid[line][y] >= 1) grid[opp][y]++;
            }
            opp--;
        }

        *xMax = x - 1;
    }
}


void foldY (int** grid, int y, int* yMax, int* yMin){
    /* Similarily this handles cases where it fold down
     * This also does not happen in the input
     */
    if (y < *yMax/2) {
        int opp = y + 1;
        int line = y - 1;

        for (; line >= *yMin; line--) {
            printf("yes line: %d\n", line);
            printf("yes opp: %d\n", opp);
            for (int x = 0; x < SIZE; x++) {
                if (grid[x][line] >= 1) grid[x][opp]++;
            }
            opp++;
        }

        *yMin = y + 1;
    } 
    else {
        int opp = y - 1;
        int line = y + 1;

        for (; line <= *yMax; line++) {
            for (int x = 0; x < SIZE; x++) {
                if (grid[x][line] >= 1) grid[x][opp]++;
            }
            opp--;
        }

        *yMax = y - 1;

    }

}


int score (int** grid, int xMax, int xMin, int yMax, int yMin){
    int score = 0;
        
    for (int i = yMin; i <= yMax; i++){
        for (int j = xMin; j <= xMax; j++) {
            if (grid[j][i] >= 1) score++;
        }
    }

    return score;
}
