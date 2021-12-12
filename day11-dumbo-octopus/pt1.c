#include <stdio.h>
#define SIZE 100


int flash( int grid[SIZE][SIZE], int x, int y ) {

    int nFlashed = 1;

    grid[x][y] = 0;

    for (int i = x-1; i <= x+1; i++) {
        for (int j = y-1; j <= y+1; j++) {
            if (i == x && j == y) continue;
            if (grid[i][j] == 0) continue;
            if (++grid[i][j] > 9) {
                nFlashed += flash(grid, i, j);
            }
        }
    }

    
    return nFlashed;
}

int step(int grid[SIZE][SIZE], int row, int col) {
    int nFlashed = 0;

    for (int i = 1; i < row; i++) {
        for (int j = 1; j < col; j++) {
            ++grid[j][i];
        }
    }

    for (int i = 1; i < row; i++) {
        for (int j = 1; j < col; j++) {
            if (grid[j][i] > 9) nFlashed += flash(grid, j, i);
        }
    }

    return nFlashed;
}

int checkSynch(int grid[SIZE][SIZE], int row, int col) {

    int save = grid[1][1];

    for (int i = 1; i < row; i++) {
        for (int j = 1; j < col; j++){
            if (grid[j][i] != save) return 0;
        }
    }

    return 1;
}


int main() {

    FILE* fp = fopen("input.txt", "r");

    int grid[SIZE][SIZE];


    int col = 1; 
    int row = 1;

    int maxCol = 0;

    char buff;

    while ( (buff = fgetc(fp)) != EOF) {
        if (buff == '\n') {
            ++row;
            col = 1;
            continue;
        }
        if (col > maxCol) maxCol = col;

        grid[col][row] = buff - '0';
        ++col;

    }
    maxCol++;

    printf("%d\n", grid[1][0]);

    int nFlashed = 0;

    int synchStep = -1;

    /* this is set for pt2 rn, for pt1 change it to
     * a for loop for n many steps */

    int stepc = 1;
    while (synchStep == -1) {
        nFlashed += step(grid, row, maxCol);

        int save = grid[1][1];
        int check;

        if (checkSynch(grid, row, maxCol) == 1
            && synchStep == -1) synchStep = stepc;

        ++stepc;

    }

    printf("Flashed: %d\n", nFlashed);
    printf("Synch Step: %d\n", synchStep);

    for (int i = 0; i <= row; ++i){
        for (int j = 0; j <= maxCol; ++j){
            if (grid[j][i] == 0) grid[j][i] = '.' - '0';
            printf("%c ", grid[j][i] + '0');
        }
        printf("\n");
    }

    return 0;
}
