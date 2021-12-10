#include <stdio.h>

enum digits {
    one = 2,
    four = 4,
    seven = 3,
    eight = 7,
};

int main() {

    FILE* fp = fopen("input.txt", "r");
    
    char pattern[10];
    char output[10];

    int count = 0;

    while (1) {

        for (int patDigit = 0; patDigit < 11; ++patDigit) {
            if (fscanf(fp, "%s", pattern) == EOF) goto exit;
        }

        for (int outDigit = 0; outDigit < 4; ++outDigit){
            fscanf(fp, "%s", output);

            int length = 0;
            for (; output[length] != '\0'; ++length);

            if (length == one || length == four || length == seven || length == eight){
                ++count;
            }
        }
    }
    exit:

    printf("%d", count);
    
    
    return 0;
}
