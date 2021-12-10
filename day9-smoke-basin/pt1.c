#include <stdio.h>
#define SIZE 1000

int getBasin(int grid[SIZE][SIZE], int x, int y) {
    int size = 1;

    int point = grid[x][y];

    /* Stops tracing back over checked vals */
    grid[x][y] = 9;

    /* 99 for border vals */
    if (point == 9 || point == 99) return 0;

    /* up */
    if (grid[x][y-1] > point) {
        size += getBasin(grid, x, y-1);
    }
    /* left */
    if (grid[x-1][y] > point) {
        size += getBasin(grid, x-1, y);
    }
    /* right */
    if (grid[x+1][y] > point) {
        size += getBasin(grid, x+1, y);
    }
    /* down */
    if (grid[x][y+1] > point) {
        size += getBasin(grid, x, y+1);
    }


    return size;
}


int main() {

    FILE* fp = fopen("input.txt", "r");
    
    int grid[SIZE][SIZE];

    for (int x = 0; x < SIZE; ++x) 
        for (int y = 0; y < SIZE; ++y)
            grid[x][y] = 99;

    int xMax = 0;
    int yMax = 1;

    char buff;

    int x = 1;

    while ( (buff = getc(fp)) != EOF ) {
        if (buff == '\n') { 
            ++yMax; 
            xMax = x;
            x = 1;
            continue; 
        }
        grid[x++][yMax] = buff - '0';
    }

    int risk = 0;

    int biggestBasins[4] = {0};

    for (int x = 1; x < xMax; ++x) {
        for (int y = 1; y < yMax; ++y) {
            int point = grid[x][y];
            if (point < grid[x][y-1]
                && point < grid[x-1][y]
                && point < grid[x+1][y]
                && point < grid[x][y+1]) {

                    int basinVal = getBasin(grid, x, y);
                    for (int i = 0; i < 3; ++i) {
                        if (basinVal > biggestBasins[i]) {
                            biggestBasins[i] = basinVal;
                            break;
                        }
                    }

            }
        }
    }

    int basinTotal = 1;
    for (int i = 0; i < 3; ++i) basinTotal *= biggestBasins[i];

    printf("Basin Total: %d\n", basinTotal);


    return 0;
}
