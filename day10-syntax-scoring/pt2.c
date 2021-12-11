#include <stdio.h>
#include <stdlib.h>
#define LENGTH 300

struct node { char val; struct node* next; };

/* top acts as as dummy top */
struct stack { struct node *top, *s, *t; };

void stackInit(struct stack* stack) {
    stack->top = malloc( sizeof(struct node) );
    stack->t = malloc( sizeof(struct node) );
    stack->top->next = stack->t;
    stack->t->next = stack->t;
}

void push( struct stack* stack, char val ) {
    stack->s = malloc( sizeof(struct node) ); 
    stack->s->val = val;
    stack->s->next = stack->top->next;
    stack->top->next = stack->s;
}

int isEmpty(struct stack* stack) {
    return stack->top->next == stack->t;
}

char pop( struct stack* stack ) {
    if (isEmpty( stack )) return -1;
    char save;
    stack->s = stack->top->next;
    save = stack->s->val;
    stack->top->next = stack->s->next;
    free(stack->s);
    return save;
}

int lookupVal(char c) {
    if (c == '(') return 1;
    if (c == '[') return 2;
    if (c == '{') return 3;
    if (c == '<') return 4;
    return 0;
}

char getOpp( char c ){
    if (c == ')') return '(';
    if (c == ']') return '[';
    if (c == '}') return '{';
    if (c == '>') return '<';
    return '0';
}

long errorScore(char* line, int length) {
    struct stack bStack;
    stackInit( &bStack );
    for (int i = 0; i < length; ++i) {

        if (line[i] == '(' 
            || line[i] == '['
            || line[i] == '{'
            || line[i] == '<') {

            push( &bStack, line[i] );
        }
        else {
            char popVal = pop( &bStack );
            if (popVal != getOpp( line[i] )) {
                return 0;
            } 
        }
    }

    long score = 0;

    while (!isEmpty( &bStack )) {
        char c = pop( &bStack );
        score *= 5;
        score += lookupVal(c);
    }

    return score;
}

int comp( const void* p1, const void *p2 ) {
    long a = *(long*)(p1);
    long b = *(long*)(p2);
    if ( a > b ) return 1;
    if ( a < b ) return -1;
    return 0;
}

int main() {

    FILE* fp = fopen("input.txt", "r");
    char lines[LENGTH][LENGTH] = {0};

    int row = 0;
    while (fscanf( fp, "%s", lines[row] ) != EOF) {
        ++row;
    }
    
    printf("%s\n", lines[0]);

    long score = 0;

    int outIndex = 0;
    long outs[LENGTH];


    for (int i = 0; i < row; ++i) {
        int len = 0;
        for (; lines[i][len] != '\0'; ++len);
        score = errorScore(lines[i], len);

        if (score != 0) {
            outs[outIndex] = score;
            ++outIndex;
        }
    }

    qsort( outs, outIndex, sizeof(long), comp);

    printf("Median: %lu\n", outs[outIndex/2]);

    return 0;
}
