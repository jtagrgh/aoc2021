#include <stdio.h>

int main() {
    
    FILE* fp;
    int read1;
    int read2;
    fp = fopen("input.txt", "r");

    int depth_count = 0;

    fscanf(fp, "%d", &read1);

    while(1){
        if (fscanf(fp, "%d", &read2) == EOF){break;}
        
        if (read2 > read1) { 
            depth_count++; 
        }

        read1 = read2;
    }

    printf("%d\n", depth_count);

    return 0;
}
