#include <stdio.h>
#include <stdlib.h>

typedef struct dNode_struct dNode;
typedef struct dQueue_struct dQueue;

struct dNode_struct {
    int val;
    dNode *previous;
    dNode *next;
};

struct dQueue_struct {
    dNode *front;
    dNode *back;
};

void addBack(dQueue q, int x) {
    dNode n = {x, q.back, NULL};
    q.back->next = &n;
    q.back = &n;
}

void printQueue(dQueue q) {
    dNode* n = q.front;

    printf("[");
    while(n->next != NULL) {
        printf("%d, ", (*n).val);
        *n = *n->next;
    }
    printf("%d]", (*n).val);
}

int main() {
    printf("hey");
    dQueue data;

    printf("hey");

    int i;
    for(i = 0; i < 10; i++) {
        addBack(data, i);
    }

    printf("hey");

    printQueue(data);

    return 0;
}
