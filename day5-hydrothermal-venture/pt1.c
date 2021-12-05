#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#define GRID_SIZE 1000

typedef struct point {
    int x;
    int y;
} point;

void createLine(int grid[GRID_SIZE][GRID_SIZE], point point1, point point2) {
    int diff;
    int minVal; int maxVal;

    /* if it's a horizontal line */
    if (point1.x == point2.x) {
        minVal = min(point1.y, point2.y);
        maxVal = max(point1.y, point2.y);

        diff = maxVal - minVal;

        for (int i = minVal; i <= maxVal; i++){
            grid[point1.x][i]++;
        }
    } /* Vertical line */
    else if (point1.y == point2.y) {
        minVal = min(point1.x, point2.x);
        maxVal = max(point1.x, point2.x);

        diff = maxVal - minVal;

        for (int i = minVal; i <= maxVal; i++){
            grid[i][point1.y]++;
        }
    }

    return;
}

int calcScore(int grid[GRID_SIZE][GRID_SIZE]) {
    int score = 0;

    for (int i = 0; i < GRID_SIZE; i++){
        for (int j = 0; j < GRID_SIZE; j++){
            if (grid[j][i] >= 2) score++;
        }
    }

    return score;
}

int main() {
    
    FILE* fp = fopen("input.txt", "r");

    int grid[GRID_SIZE][GRID_SIZE] = {0};

    char buff1[10];
    char buff2[10];
    char buff3[10];

    char* token;
    char* rest;

    point point1;
    point point2;

    while (fscanf(fp, "%s", buff1) != EOF){
        fscanf(fp, "%s", buff2);
        fscanf(fp, "%s", buff3);

        rest = buff1;
        point1.x = atoi(strtok_r(rest, ",", &rest));
        point1.y = atoi(strtok_r(rest, ",", &rest));

        rest = buff3;
        point2.x = atoi(strtok_r(rest, ",", &rest));
        point2.y = atoi(strtok_r(rest, ",", &rest));

        createLine(grid, point1, point2);
    }
    
    /* print the grid
    for (int i = 0; i < GRID_SIZE; i++){
        for (int j = 0; j < GRID_SIZE; j++){
            if (grid[j][i] == 0)
                printf(". ");
            else
                printf("%d ", grid[j][i]);
        }
        printf("\n");
    }
    */

    printf("\nScore: %d\n", calcScore(grid));


    return 0;
}
