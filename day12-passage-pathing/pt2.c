#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TOTAL_SIZE 50
#define SPLIT 30


int solutionCount = 0;
int smallMaxed = 0;

struct node {
    int vertex;
    struct node* next;
};

struct Graph {
    int numVertices;
    struct node** adjLists;
};

struct node* createNode(int v) {
    struct node* newNode = malloc(sizeof(struct node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

struct Graph* createGraph(int vertices) {
    struct Graph* graph = malloc(sizeof(struct Graph));
    graph->numVertices = vertices;

    graph->adjLists = malloc(vertices * sizeof(struct node*));

    for (int i = 0; i < vertices; i++) {
        graph->adjLists[i] = NULL;
    }

    return graph;
}


void addEdge(struct Graph* graph, int s, int d) {
    /* insert newnode with value d at head of index s */
    struct node* newNode = createNode(d);
    newNode->next = graph->adjLists[s];
    graph->adjLists[s] = newNode;

    /* insert newnode with value s at head of index d */
    newNode = createNode(s);
    newNode->next = graph->adjLists[d];
    graph->adjLists[d] = newNode;
}

void printGraph(struct Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        struct node* temp = graph->adjLists[v];
        if (temp == NULL) continue;
        printf("\n Vertex %d\n: ", v);
        while (temp) {
            printf("%d -> ", temp->vertex);
            temp = temp->next;
        }
        printf("\n\n");
    }
}

struct pathsData {
    int s;      /* start vertex */
    int t;      /* end vertex */
    struct Graph g;    /* graph for finding paths in */
};


void constructCandidates(int a[], int k, struct pathsData *g, int c[], int *nc) {
    int i;              /* counter */
    int inSol[100];     /* bool array for representing  whether the ith index
                           is in the solution vector */
    struct node *p;     /* temp pointer for interating grhough adjList */
    int last;           /* last element of solution vector */

    /* Start by setting all flags to false */
    for (i = 0; i <= g->g.numVertices; i++) {
        inSol[i] = 0;
    }

    /* Set flag to true for soluction vector values */
    for (i = 0; i < k; i++) {
        if (a[i] < SPLIT) /* values > number are used for uppercase caves */
            inSol[a[i]]++;
    }

    int smallMaxed = 0;
    for (i = 0; i < g->g.numVertices; i++){
        if (inSol[i] >= 2) smallMaxed = 1;
    }


    if (k == 1) {
        c[0] = g->s;        /* forces start at s */
        *nc = 1;            /* number of candidates is 1 */
    } else {
        *nc = 0;
        last = a[k-1];
        p = g->g.adjLists[last];
        while (p != NULL) {
            if (inSol[ p->vertex ] == 0) {
                c[*nc] = p->vertex;         /* add vertex to candidates list */
                *nc = *nc + 1;              
            }
            else if (inSol[ p->vertex ] == 1 && smallMaxed == 0
                && p->vertex != g->s
                && p->vertex != g->t){
                c[*nc] = p->vertex;         /* add vertex to candidates list */
                *nc = *nc + 1;              
            }
            p = p->next;
        }
    }
}

int isSolution(int a[], int k, struct pathsData* g) {
   return (a[k] == g->t);
}

void processSolution(int a[], int k, struct pathsData *input){
    int i;

    solutionCount++;

    printf("{");
    for (i = 1; i <= k; i++) {
        printf(" %d", a[i]);
    }
    printf(" }\n");
    
}

void backtrack(int a[], int k, struct pathsData* g) {
    /* a[] is the soution vector a = (a1, a2, ... ak)
     * k denotes the final element of a 
     */

    int c[100];     /* candidates for next position */
    int nc;         /* next position candidate count */
    int i;          /* counter */


    if (isSolution(a, k, g)) {
        processSolution(a, k, g);
    } else {
        k = k+1;
        constructCandidates(a, k, g, c, &nc);

        for (i = 0; i < nc; i++) {      /* go through candidate list */
            a[k] = c[i];                /* create partial solution for each */
            backtrack(a, k, g);         /* backtrack new partial solution */
        }
    }
}

int stringIsUpper(char s[]){
    char c;

    for (int i = 0; s[i] != '\0'; i++){
        c = s[i];
        if (isupper(c)) return 1;
    }
    
    return 0;
}

int main() {

    char caves[TOTAL_SIZE][10];
    FILE* fp = fopen("input.txt", "r");
    struct Graph* graph = createGraph(TOTAL_SIZE);

    char buff[10];

    int caveIndex = 1;

    int start;
    int end;

    while ( fscanf(fp, "%s", buff) != EOF) {
        char* token;
        char* rest = buff;
        int add;

        while ((token = strtok_r(rest, "-", &rest))){
            add = 1;
            int i;
            for (i = 0; i < TOTAL_SIZE; i++){
                if (strcmp(caves[i], token) == 0) {
                    add = 0;
                }
            }
            if (add == 1) {
                if (strcmp(token, "start") == 0) start = caveIndex;
                if (strcmp(token, "end") == 0) end = caveIndex;
                strcpy(caves[caveIndex + (SPLIT*stringIsUpper(token))], token);
                caveIndex++;
            }
        }
    }

    rewind(fp);

    while ( fscanf(fp, "%s", buff) != EOF) {
        char* sString;
        char* tString;
        char* rest = buff;

        int s;
        int t;

        while ((sString = strtok_r(rest, "-", &rest))){
            tString = strtok_r(rest, "-", &rest);

            for (int i = 0; i < TOTAL_SIZE; i++){
                if (strcmp(caves[i], sString) == 0) {
                    s = i;
                }
                if (strcmp(caves[i], tString) == 0) {
                    t = i;
                }
            }

            addEdge(graph, s, t);
        }
    }

    printGraph(graph);

    int a[101];
    struct pathsData data = {start, end, *graph};

    backtrack(a, 0, &data);

    printf("Solution count: %d\n", solutionCount);

    return 0;
}
