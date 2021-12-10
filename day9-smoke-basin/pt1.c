#include <stdio.h>
#define SIZE 1000

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

    for (int x = 1; x < xMax; ++x) {
        for (int y = 1; y < yMax; ++y) {
            int point = grid[x][y];
            if (point < grid[x][y-1]
                && point < grid[x-1][y]
                && point < grid[x+1][y]
                && point < grid[x][y+1]) {

                risk += point + 1;

            }
        }
    }

    printf("Risk Total: %d\n", risk);


    return 0;
}
