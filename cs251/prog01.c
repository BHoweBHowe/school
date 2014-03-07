/* ----------------------------------------------
 * brief description
 *
 * Class: cs 251, Spring 2014, Thur 10am lab.
 * System: CentOS 6.5 x86, g++
 * Author: Brian Howe
 *
 * ToDo: What was im supposed to accomplish
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int val;
    int *previous;
    int *next;
} dNode;

typedef struct {
    int *front;
    int *back;
} dQueue;

void addBack(dQueue q, int x) {
    dNode *n = {&x, (int*) q->back, NULL};
    q->back = (int*) n;
}

void printQ(dQueue q) {
    dNode* n = (dNode*) q->front;

    while(n->next != NULL) {
        printf("%d, ", n->val);
        *n = (dNode*) n->next;
    }
    *n = (dNode*) n->next;
    printf("%d]", n->val);
}

int main() {
    dQueue data = {NULL, NULL};

    int i;
    for(i = 0; i < 10; i++) {
        addBack(data, i);
    }

    printQ(data);

    return 0;
}
