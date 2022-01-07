#include <stdio.h>
#include <stdlib.h>

typedef struct instruction {
    char left;
    char right;
    char ins;
    struct instruction* next;
} instruction;

typedef struct insert {
    int index;
    char ins;
    struct insert* next;
} insert;

typedef struct node {
    char letter;
    int index;
    struct node* next;
} node;

struct nodeList {
    node* head;
};

struct insertList {
    insert* head;
};

struct instructionList {
    instruction* head;
};

/* hello how are you */

struct nodeList* initNodeList () {
    struct nodeList* list = malloc(sizeof(struct nodeList));
    list->head = malloc(sizeof(node));
    list->head->next = NULL;

    return list;
}

struct insertList* initInsertList () {
    struct insertList* list = malloc(sizeof(struct insertList));
    list->head = malloc(sizeof(insert));
    list->head->next = NULL;

    return list;
}

struct instructionList* initInstructionList () {
    struct instructionList* list = malloc(sizeof(struct instructionList));
    list->head = malloc(sizeof(instruction));
    list->head->next = NULL;

    return list;
}

void indexList (struct nodeList* list) {
    node* seeker = list->head->next;

    int i = 0;
    while (seeker != NULL){
        seeker->index = i;
        ++i;
        seeker = seeker->next;
    }
}

void pushNode (struct nodeList* list, char letter){
    node* newNode = malloc(sizeof(node));
    newNode->letter = letter;
    newNode->next = list->head->next;
    list->head->next = newNode;
}

void pushInsert (struct insertList* list, int index, char ins) {
    insert* newInsert = malloc(sizeof(insert));
    newInsert->next = list->head->next;
    newInsert->index = index;
    newInsert->ins = ins;
    list->head->next = newInsert;
}

void pushInstruction (struct instructionList* list, char left, char right, char ins) {
    instruction* newInstruction = malloc(sizeof(instruction));
    newInstruction->next = list->head->next;
    newInstruction->left = left;
    newInstruction->right = right;
    newInstruction->ins = ins;
    list->head->next = newInstruction;
}


void runSim(struct nodeList* nodeList,
    struct instructionList* instructList) {

    indexList(nodeList);
    


    struct insertList* insList = initInsertList();

    instruction* instructSeeker = instructList->head->next;


    while (instructSeeker != NULL) {
        node* nodeSeeker = nodeList->head->next;

        while (nodeSeeker->next != NULL) {
            if (nodeSeeker->letter == instructSeeker->left
                && nodeSeeker->next->letter == instructSeeker->right) {

                pushInsert(insList, nodeSeeker->index, instructSeeker->ins);
            }

            nodeSeeker = nodeSeeker->next;
        }

        instructSeeker = instructSeeker->next;
    }




    insert* insSeeker = insList->head->next;

    while (insSeeker != NULL) {
        node* nodeSeeker = nodeList->head->next;
        printf("Node index: %d, node letter: %c\n", nodeSeeker->index, nodeSeeker->letter);
        printf("ins index: %d, ins letter: %c\n", insSeeker->index, insSeeker->ins);
        printf("\n");

        while (nodeSeeker != NULL) {
            break;
            if (nodeSeeker->index == insSeeker->index){
                node* newNode = malloc(sizeof(node));
                newNode->letter = insSeeker->ins;
                newNode->next = nodeSeeker->next;
                nodeSeeker->next = newNode;
                nodeSeeker->index = -1;
            }

            nodeSeeker = nodeSeeker->next;
        }

        insSeeker = insSeeker->next;
    }
}

int main() {

    FILE* fp = fopen("input2.txt", "r");

    struct nodeList* nodeList = initNodeList();

    char buff;
    while ( (buff = fgetc(fp)) != '\n'){
        pushNode(nodeList, buff);                         
    }
struct instructionList* instructList = initInstructionList();
    char lr[3];
    char ins;
    while (fscanf(fp, "%s %*s %c", lr, &ins) != EOF) {
        pushInstruction(instructList, lr[0], lr[1], ins);
    }

    runSim(nodeList, instructList);


    node* seek = nodeList->head->next;
    while(seek != NULL){
        printf("%c\n", seek->letter);
        seek = seek->next;
    }

    return 0;
}
