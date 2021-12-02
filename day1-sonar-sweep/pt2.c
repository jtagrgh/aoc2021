#include <stdio.h>


int main(){

    FILE* fp;
    int window[3];
    int sum1 = 0;
    int sum2 = 0;
    fp = fopen("input.txt", "r");

    int depth_count = 0;

    for(int i = 0; i < 3; i++){
        fscanf(fp, "%d", &window[i]);
    }

    while(1){
        for (int i = 0; i < 3; i++){
            sum1 += window[i];
        }
        
        window[0] = window[1];
        window[1] = window[2];
        
        if (fscanf(fp, "%d", &window[2]) == EOF){ break; }

        for (int i = 0; i < 3; i++){
            sum2 += window[i];
        }

        if (sum2 > sum1){ depth_count++; }

        sum1 = sum2 = 0;
    }

    printf("%d\n", depth_count); 

    return 0;
}
