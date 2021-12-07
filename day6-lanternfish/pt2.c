#include <stdio.h>
#define DAYS_TO_SIM 256

/* Called on the first day a fish produces - first production day (FPD) of a fish */
unsigned long simFish(int daysLeftAtFPD) {
    
    /* 1 for the parent fish */
    unsigned long fish = 1;

    /* The number of children the parent will produce */
    /* 1 is added for the first fish produced on the parents FPD */
    unsigned long subFish = (daysLeftAtFPD / 7) + 1;

    /* This catches fish who's FPDs are valid, but there
    aren't enought days left to produce again,
    so counts parent and only child */
    if (daysLeftAtFPD < 7 && daysLeftAtFPD >= 0) {
        return 2;
    } /* This catches fish whose FPDs are negative, thus they produce
    no children */
    else if (daysLeftAtFPD < 0) {
        return 1;
    }

    /* Otherwise apply same logic recursively to each child fish */
    for (int i = 0; i < subFish; i++){
        /* Day of the subfishe's FPD */
        fish += simFish(daysLeftAtFPD - 9); 
        
        /* Day the subfish is produced */
        daysLeftAtFPD -= 7;
    }

    return fish;
}

int main() {
    
    /* using pre-inputs doesn't work for some reason, weird.
    unsigned long saveSet[6] = {0L, 6206821033LU, 5617089148LU, 5217223242LU, 4726100874LU, 4368232009LU};
    */

    FILE* fp = fopen("input.txt", "r");

    unsigned long saveSet[6];
    for (int i = 1; i <= 5; i++) {
        saveSet[i] = simFish(DAYS_TO_SIM - i - 1);
        printf("If a fish starts at: %d, You will end with: %lu fish.\n", i, saveSet[i]);
    }

    unsigned long totalFish = 0;

    while (1){
        totalFish += saveSet[fgetc(fp) - '0'];
        if (fgetc(fp) == EOF) break;
    }

    printf("Total fish: %lu 🐟\n", totalFish); 

    return 0;
}
