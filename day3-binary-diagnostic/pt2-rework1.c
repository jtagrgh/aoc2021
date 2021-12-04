#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define BIN_SIZE 13


struct node {
    char bin[BIN_SIZE];
    struct node* next;
};

struct linkedList {
    struct node* head;
    struct node* tail;
};


void addToTail(struct linkedList* list, char* bin) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->next = NULL;

    strcpy(list->tail->bin, bin);    
    list->tail->next = newNode;

    list->tail = newNode;
}


void reduce(struct linkedList* list, int index, int* listLength, char seek){

    if (*listLength <= 1) {
        return;
    }

    int indexSum = 0;

    struct node* seekerNode = list->head->next;

    while (seekerNode->next != NULL) {
        indexSum += (seekerNode->bin[index] - '0');
        seekerNode = seekerNode->next;
    }


    int ceilLength = *listLength % 2 == 0 ? *listLength : *listLength + 1;

    char gamma;

    if (seek == '1') {
        gamma = indexSum >= ceilLength/2 ? '1' : '0';
    } else {
        gamma = indexSum >= ceilLength/2 ? '0' : '1';
    }


    seekerNode = list->head;
    struct node* delNode = seekerNode->next; 

    while (delNode->next != NULL) {
        if (delNode->bin[index] != gamma){
            seekerNode->next = delNode->next;
            free(delNode);
            (*listLength)--;
        } else {
            seekerNode = seekerNode->next;
        }

        delNode = seekerNode->next;
    }
    
}
    

int main() {

    struct linkedList oxList; 
    oxList.head = malloc(sizeof(struct node));
    oxList.tail = malloc(sizeof(struct node));
    oxList.tail->next = NULL;
    oxList.head->next = oxList.tail;

    struct linkedList coList; 
    coList.head = malloc(sizeof(struct node));
    coList.tail = malloc(sizeof(struct node));
    coList.tail->next = NULL;
    coList.head->next = coList.tail;

    FILE* fp = fopen("input.txt", "r");
    char buff[BIN_SIZE];

    int listLength = 0;
    while (fscanf(fp, "%s", buff) != EOF) {
        addToTail(&oxList, buff);
        addToTail(&coList, buff);
        listLength++;
    }

    int oxLength = listLength;
    int coLength = listLength;
    
    struct node* seekerNode = coList.head;

    for (int i = 0; i < BIN_SIZE - 1; i++) {
        reduce(&oxList, i, &oxLength, '1');
        reduce(&coList, i, &coLength, '0');
    }

    char oxRate[BIN_SIZE];
    char coRate[BIN_SIZE];

    strcpy(oxRate, oxList.head->next->bin);
    strcpy(coRate, coList.head->next->bin);

    int dox = 0;
    int dco = 0;

    for (int i = 0; i < BIN_SIZE - 1; i++){
        if (oxRate[i] == '1') {
            dox += pow(2, BIN_SIZE - i - 2);
        }
        if (coRate[i] == '1') {
            dco += pow(2, BIN_SIZE - i - 2);
        }
    }

    printf("out: %d\n", dox * dco);


    return 0;
} 
