#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node {
    char letter;
    long count;
    long countBuff;
    struct node* next;
} node;

void printAll(node list[26]) {
    node* seeker;
    for (int i = 0; i < 26; i++) {
        printf("%c", list[i].letter);
        printf(" -> ");
        seeker = list[i].next;
        while (seeker != NULL) {
            if (seeker->count == 0)
                printf("_____");
            else 
                printf(" %c:%ld ", seeker->letter, seeker->count);
            seeker = seeker->next;
        }
        printf("\n");
    }
}

void buffList(node list[26]) {
    for (int i = 0; i < 26; i++) {
        node* seeker = list[i].next;
        while (seeker != NULL) {
            seeker->count += seeker->countBuff;
            seeker = seeker->next;
        }
    }
}

void clearBuff(node list[26]) {
    for (int i = 0; i < 26; i++) {
        node* seeker = list[i].next;
        while (seeker != NULL) {
            seeker->countBuff = 0;
            seeker = seeker->next;
        }
    }
}

long getCount(node list[26], char l, char r) {
    int s = 0; /* counter */
    node* seeker = &list[0];
    while (seeker->letter != l) {
        seeker = &list[++s];
    }
    seeker = seeker->next;
    while (seeker != NULL) {
        if (seeker->letter == r) {
            /* return count | buff mod */
            return seeker->count;
        }
        seeker = seeker->next;
    }
    return -1;
}

void modBuff(node list[26], char l, char r, long mod) {
    int s = 0; /* counter */
    node* seeker = &list[0];
    while (seeker->letter != l) {
        seeker = &list[++s];
    }
    seeker = seeker->next;
    while (seeker != NULL) {
        if (seeker->letter == r) {
            seeker->countBuff += mod;
            break;
        }
        seeker = seeker->next;
    }
}

int main () {
    node list[26];
    long totals[26] = {0};

    /* create default polymer list counts */
    node* seeker;
    for (char i = 'A'; i <= 'Z'; i++) {
        list[i - 'A'].letter = i;
        seeker = &list[i - 'A'];
        for (int j = 'A'; j <= 'Z'; j++) {
            seeker->next = malloc(sizeof(node));
            seeker->next->letter = j;
            seeker->next->count = 0;
            seeker->next->countBuff = 0;
            seeker = seeker->next;
        }
        seeker->next = NULL;
    }

    FILE* fp = fopen("input.txt", "r");

    /* read in initial polymer */
    char initPoly[100]; 
    char buff;
    long c = 0; /* poly size counter */
    while ( (buff = fgetc(fp)) != '\n') {
        initPoly[c] = buff;
        totals[buff - 'A']++;
        c++;
    }
    c--;

    /* loading in initial pairs */
    for (int i = 0; i < c; i++) {
        node *seeker = list[ initPoly[i] - 'A' ].next;
        while (seeker->letter != initPoly[i+1]) {
            seeker = seeker->next;
        }
        seeker->count++;
    }

    /* read in instructions and save into array */
    char instructions[1000];
    char pairbuff[3];
    char insertbuff[2];
    int ic = 0; /* instruction array counter */
    while ( (fscanf(fp, "%s %*s %s", pairbuff, insertbuff)) != EOF ){
        instructions[ic++] = pairbuff[0];
        instructions[ic++] = pairbuff[1];
        instructions[ic++] = insertbuff[0];
    }

    /* run simulation for s steps */
    int s = 40;
    for (int sc = 0; sc < s; sc++) {
        for (int i = 0; i <= ic-3; i+=3) {
            char li = instructions[i]; /* left of pair instruction */
            char ri = instructions[i+1]; /* right of pair instruction */
            char ins = instructions[i+2]; /* char to insert */
            long mod = getCount(list, li, ri);
            modBuff(list, li, ins, mod);
            modBuff(list, ins, ri, mod);
            modBuff(list, li, ri, -mod);
            totals[ins - 'A'] += mod;
        }
        buffList(list);
        clearBuff(list);
    }

    long lc = LONG_MAX;
    long mc = LONG_MIN;
    for (int i = 0; i < 26; i++) {
        long x = totals[i]; /* count to check */
        if (x < lc && x > 0) lc = x;
        if (x > mc) mc = x;
    }
    printf("mc %ld lc %ld diff %ld\n", mc, lc, mc-lc);

    return 0;
}
