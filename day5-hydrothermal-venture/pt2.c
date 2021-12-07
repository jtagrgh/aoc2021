#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#define GRID_SIZE 10

typedef struct point {
    int x;
    int y;
} point;

int compPoints(point point1, point point2){
    if (point1.x == point2.x && point1.y == point2.y)
        return 1;
    else
        return 0;
}

void createLine(int grid[GRID_SIZE][GRID_SIZE], point point1, point point2) {
    point incPoint;

    int xMod = 0;
    int yMod = 0;

    int diff = 0;
    
    if (point1.x == point2.x) {
        incPoint.x = point1.x;
        incPoint.y = min(point1.y, point2.y);

        diff = abs(point1.y - point2.y);
        yMod = 1;

    } /* Horizontal */
    else if (point1.y == point2.y) {
        incPoint.x = min(point1.x, point2.x);
        incPoint.y = point1.y;

        diff = abs(point1.x - point2.x);
        xMod = 1;

    } else { /* Diagonal */
        incPoint.x = min(point1.x, point2.x);
        incPoint.y = min(point1.y, point2.y);
        
        /* If angle is 45 deg */
        if (compPoints(incPoint, point1) || compPoints(incPoint, point2)){
            diff = abs(point1.x - point2.x);
            xMod = 1;
            yMod = 1;

        } else { /* If angle is 135 deg */
            incPoint.x = min(point1.x, point2.x);
            incPoint.y = max(point1.y, point2.y);

            diff = abs(point1.x - point2.x);
            xMod = 1;
            yMod = -1;

        }
    }

    for (int i = 0; i <= diff; i++){
        grid[incPoint.x][incPoint.y]++;
        incPoint.x += xMod;
        incPoint.y += yMod;
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
    
    FILE* fp = fopen("input3.txt", "r");

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
    
    for (int i = 0; i < GRID_SIZE; i++){
        for (int j = 0; j < GRID_SIZE; j++){
            if (grid[j][i] == 0)
                printf(". ");
            else
                printf("%d ", grid[j][i]);
        }
        printf("\n");
    }

    printf("\nScore: %d\n", calcScore(grid));


    return 0;
}
