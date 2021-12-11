#include <stdio.h>
#include <stdlib.h>
#define LENGTH 200

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
    if (c == ')') return 3;
    if (c == ']') return 57;
    if (c == '}') return 1197;
    if (c == '>') return 25137;
    return 0;
}

char getOpp( char c ){
    if (c == ')') return '(';
    if (c == ']') return '[';
    if (c == '}') return '{';
    if (c == '>') return '<';
    return '0';
}

int errorScore(char* line, int length) {
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
                return lookupVal( line[i] );
            }
        }
    }

    return 0;
}

int main() {

    FILE* fp = fopen("input.txt", "r");
    char lines[LENGTH][LENGTH] = {0};

    int row = 0;
    while (fscanf( fp, "%s", lines[row] ) != EOF) {
        ++row;
    }

    int score = 0;

    for (int i = 0; i < row; ++i) {
        int len = 0;
        for (; lines[i][len] != '\0'; ++len);
        score += errorScore(lines[i], len);
    }


    printf("Score: %d\n", score);

    return 0;
}
