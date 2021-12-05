#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define BOARD_SIZE 5
#define N_BOARDS_APPROX 101

typedef struct point {
    int val;
    int marked;
} point;

typedef struct board {
    point grid[BOARD_SIZE * BOARD_SIZE];
} board;


void updateBoard(board* board, int draw) {
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        if (board->grid[i].val == draw){
            board->grid[i].marked = 1;
        }
    }
}

void updateAllBoards(board** boards, int nBoards, int draw) {
    for (int i = 0; i < nBoards; i++) {
        updateBoard(boards[i], draw);
    }
}

int calculateScore(board* board, int finalDraw) {
    int score = 0;
    for (int i = 0; i < BOARD_SIZE*BOARD_SIZE; i++) {
        if (board->grid[i].marked == 0) { score += board->grid[i].val; }
    }

    return score * finalDraw;
}

/* I know I could just return the newBoards pointer and use 
for reassignment but this is funnier */
int popBoard(board*** boards, int popIndex, int* nBoards, int draw){

    int score = calculateScore( (*boards)[popIndex], draw);

    (*nBoards)--;
    board** newBoards = malloc(sizeof(board*) * (*nBoards));
    
    int newBoardsIndex = 0;
    for (int i = 0; i < *nBoards + 1; i++) {
        if (i != popIndex) {
            newBoards[newBoardsIndex] = (*boards)[i];
            newBoardsIndex++;
        } else {
            free((*boards)[i]);
        }

    }

    *boards = newBoards;

    return score;
}

int checkWin(board* board) {
    int bins[BOARD_SIZE] = {0}; 
    int rowSum = 0;

    int binIndex = 0;
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        if (board->grid[i].marked == 1) {
            rowSum++;
            bins[binIndex]++;
        }
        if (rowSum == BOARD_SIZE) { return 1; }
        binIndex++;
        if (binIndex == BOARD_SIZE) {
            binIndex = 0;
            rowSum = 0;
        }
    }

    for (int i = 0; i < BOARD_SIZE; i++) {
        if (bins[i] == BOARD_SIZE) { return 1; }
    }

    return 0;
}

int checkWinAllBoards(board** boards, int nBoards) {
    for (int i = 0; i < nBoards; i++) {
        if ( checkWin(boards[i]) == 1 ) { return i; }
    }
    return -1;
}


int main() {

    int draw[500];
    board** boards = malloc(sizeof(board*) * N_BOARDS_APPROX);
    char drawBuff[500];
    char* token;

    for (int i = 0; i < N_BOARDS_APPROX; i++) {
        boards[i] = malloc(sizeof(board));
    }

    /* Loads in bingo draw list into draw*/
    FILE* fp = fopen("input.txt", "r");
    fgets(drawBuff, 500, fp);

    int i = 0;
    token = strtok(drawBuff, ",");

    while( token != NULL ) {
        draw[i] = atoi(token);
        token = strtok(NULL, ",");
        i++;
    }

    int drawLength = i;
    /* Loads boards in to boards list */
    int nBoards = 0;
    for (int i = 0; i < N_BOARDS_APPROX; i++) {
        for (int j  = 0; j < BOARD_SIZE * BOARD_SIZE; j++){
            if (fscanf(fp, "%d", &boards[i]->grid[j].val) == EOF){ goto exit; }; 
            boards[i]->grid[j].marked = 0;
        }
        nBoards++;
    }
    exit: {}

    int winningBoard = -1;
    int losingBoard;

    int winningDraw;
    int losingDraw;

    int winScore;
    int loseScore;

    int windex = 0;

    for (int i = 0; i < drawLength; i++) {

        if (nBoards == 0) { break; }
        
        updateAllBoards(boards, nBoards, draw[i]);
        windex = checkWinAllBoards(boards, nBoards);
        while (windex != -1) {
            if (winningBoard == -1) { 
                winningBoard = windex;
                winningDraw = draw[i];
                winScore = popBoard(&boards, windex, &nBoards, winningDraw);
            } else {
                losingBoard = windex;
                losingDraw = draw[i];
                loseScore = popBoard(&boards, windex, &nBoards, losingDraw); 
            }
            windex = checkWinAllBoards(boards, nBoards);
        }
    }

    printf("\n");

    printf("winning board: %d\n", winningBoard);
    printf("losing board: %d\n", losingBoard);
    
    printf("\nwin draw: %d\n", winningDraw); 
    printf("lose draw: %d\n", losingDraw); 

    printf("\nwin score: %d\n", winScore); 
    printf("lose score: %d\n", loseScore); 

    return 0;
}
