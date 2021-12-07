#include <stdio.h>
#include <stdlib.h>

typedef struct fish {
    int val;
    int new;
} fish;

void updateFishes(fish* fishes, int *findex) {
    int lastFindex = *findex;

    for (int i = 0; i < lastFindex; i++){

        if (fishes[i].new == 1 && fishes[i].val == 8)
            fishes[i].new = 0;

        if (fishes[i].new == 0) {
            if (fishes[i].val == 0){
                fishes[i].val = 7;
                fishes[*findex].val = 8;
                fishes[*findex].new = 1;
                (*findex)++;
            }
            fishes[i].val--;
        }
    }
}

int main() {

    FILE* fp = fopen("input.txt", "r");
    fish* fishes = malloc(sizeof(fish) * 1000000000);

    int findex = 0;
    while (1) {
        fishes[findex].val = fgetc(fp) - '0';
        fishes[findex].new = 0;
        if (fgetc(fp) == EOF) break;
        findex++;
    }

    for (int day = 0; day < 128; day++){
        /*
        printf("findex %d\n", findex);
        for (int i = 0; i < findex; i++) {
            printf("%d ", fishes[i].val);
        }
        printf("\n");
        */
        updateFishes(fishes, &findex);    
    }

    printf("%d\n", findex);

    return 0;
}
