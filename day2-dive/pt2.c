#include <stdio.h>
#include <string.h>

int main(){

    FILE* fp = fopen("input.txt", "r");
    int depth = 0;
    int hpos = 0;
    int aim = 0;
    char cmd[10];
    int val;

    while(fscanf(fp, "%s", cmd) != EOF){
        fscanf(fp, "%d", &val);
        if (strcmp(cmd, "forward") == 0){
            hpos += val;
            depth += (aim * val);
        }
        else if (strcmp(cmd, "down") == 0){
            aim += val;
        }
        else { /* up */
            aim -= val;
        }
    }

    int ans = depth * hpos;

    printf("%d\n", ans);

    return 0;
}

