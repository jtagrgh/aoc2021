#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N_CRABS 10000

typedef struct crab {
    int val;
    int moveCost;
} crab;

int compare (const void * a, const void * b) {
    crab *crabA = (crab *)a;
    crab *crabB = (crab *)b;

    return ( crabB->moveCost - crabA->moveCost );
}

int series(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1; 
    return n + series(n - 1);
}

int costpt2 (crab crabs[N_CRABS], int nCrabs, int pos) {
    int cost = 0;

    int diff;

    for (int i = 0; i < nCrabs; i++) {
        diff = abs(crabs[i].val - pos);
        cost += ( crabs[i].moveCost * series(diff) ); 
    }

    return cost;
}

int costpt1 (crab crabs[N_CRABS], int nCrabs, int pos) {
    int cost = 0;

    int diff;

    for (int i = 0; i < nCrabs; i++) {
        diff = abs(crabs[i].val - pos);
        cost += ( crabs[i].moveCost * diff ); 
    }

    return cost;
}

int main() {

    FILE* fp = fopen("input.txt", "r");

    int crabs[N_CRABS] = {0};
    int crabsUnique[N_CRABS];
    crab crabsAsCrabs[N_CRABS];

    int crabUniqueCount = 0;

    char input[1000000];
    fscanf(fp, "%s", input);

    char* rest = input;
    char* token;
    
    int count = 0;

    int val;
    while ( (token = strtok_r(rest, ",", &rest)) ) {
        val = atoi(token);
        crabs[val]++;
        if (crabs[val] == 1) {
            crabsUnique[crabUniqueCount] = val;
            crabUniqueCount++;
        }
        count++;
    }

    for (int i = 0; i < crabUniqueCount; i++) {
        crabsAsCrabs[i].val = crabsUnique[i];
        crabsAsCrabs[i].moveCost = crabs[crabsUnique[i]];
    }

    qsort(crabsAsCrabs, crabUniqueCount, sizeof(crab), compare);

    printf("total crabs: %d, total unique: %d\n", count, crabUniqueCount);

    int minCost = 999999999;
    int cost1;

    for (int i = 0; i < 2000; i++) {
        cost1 = costpt1(crabsAsCrabs, crabUniqueCount, i);
        if (cost1 < minCost)
            minCost = cost1;
    }

    printf("min pt1: %d\n", minCost);

    minCost = 999999999;
    int cost2;

    for (int i = 0; i < 2000; i++) {
        cost2 = costpt2(crabsAsCrabs, crabUniqueCount, i);
        if (cost2 < minCost)
            minCost = cost2;
    }

    printf("min pt2: %d\n", minCost);

    return 0;
}
