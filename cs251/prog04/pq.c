#include <stdio.h>
#include <stdlib.h>
#include "pq.h"

typedef struct pq_node {
    int id;
    double priority;
    int i; // index in heap
} NODE;

struct pq_struct {
    int capacity;
    int min_heap;
    int size;
    NODE **heap;
    NODE **ids;
};


PQ_PTR pq_create(int capacity, int min_heap) {
    PQ_PTR pq = malloc(sizeof(struct pq_struct));
    pq->capacity = capacity;
    pq->min_heap = min_heap;
    pq->size = 0;
    pq->ids = malloc(sizeof(NODE*) * capacity);
    pq->heap = malloc(sizeof(NODE*) * capacity);

    int i;
    for(i = 0; i < pq->capacity; i++) {
        pq->ids[i] = NULL;
        pq->heap[i] = NULL;
    }

    return pq;
}


void pq_free(PQ_PTR pq) {
    int i;
    for(i = 0; i < pq->size; i++) {
        free(pq->heap[i]);
    }
    free(pq->ids);
    free(pq->heap);
    free(pq);
}


int valid_id(PQ_PTR pq, int id) {
    if(id >= pq->capacity || id < 0) {
        return 0;
    }
    return 1;
}


void prioritize(PQ_PTR pq, int i) {
    NODE **heap = pq->heap;
    int k = 1; // modifier
    if(pq->min_heap == 1) {
        k = -1; // makes largest pri smallest
    }

    if(i == pq->size-1) {
        return;
    }

    // if the priority of i is greater than its parent switch them
    if((heap[i]->priority)*k > (heap[i/2]->priority)*k) {
        // update indecies
        heap[i]->i = i/2;
        heap[i/2]->i = 1;
        // swap nodes
        NODE *tmp = heap[i/2];
        heap[i/2] = heap[i];
        heap[i] = tmp;

        prioritize(pq, i/2);
    }
    // if i has children
    else if(i*2 < pq->size) {
        NODE *l = heap[i*2];
        int h;
        if((i*2)+1 < pq->size) {
            NODE *r = heap[(i*2)+1];
            if((l->priority)*k > (r->priority)*k) {
                h = l->i;
            }
            else {
                h = r->i;
            }
        }
        else {
            h = l->i;
        }

        // if the childs priority is higher
        if((heap[h]->priority)*k > (heap[i]->priority)*k) {
            // update indecies
            heap[i]->i = heap[h]->i;
            heap[h]->i = i;
            // swap nodes
            NODE *tmp = heap[i];
            heap[i] = heap[h];
            heap[h] = tmp;

            prioritize(pq, h);
        }
    }

    prioritize(pq, i++);
}


int pq_insert(PQ_PTR pq, int id, double priority) {
    // if id is within capacity and is not yet in use
    if(id >= pq->capacity || id < 0 || pq->ids[id] != NULL) {
        return 0;
    }

    NODE *n = malloc(sizeof(NODE));
    n->id = id;
    n->priority = priority;
    n->i = pq->size;

    pq->ids[id] = n;
    pq->heap[pq->size] = n;

    pq->size++;

    prioritize(pq, n->i);
}


int pq_change_priority(PQ_PTR pq, int id, double new_priority) {
    if(!valid_id(pq, id) || pq->ids[id] == NULL) {
        return 0;
    }

    NODE *n = pq->ids[id];
    n->priority = new_priority;
    prioritize(pq, n->i);
    return 1;
}


int pq_remove_by_id(PQ_PTR pq, int id) {
    if(!valid_id(pq, id) || pq->ids[id] == NULL) {
        return 0;
    }

    NODE *n = pq->ids[id];
    pq->ids[id] = NULL;
    pq->size--;

    if(n->i < pq->size) { // there is a node lower in the heap
        pq->heap[n->i] = pq->heap[pq->size];
        pq->heap[n->i]->i = n->i; // update index
        pq->heap[pq->size] = NULL;

        prioritize(pq, n->i);
    }

    free(n);
    return 1;
}


int pq_get_priority(PQ_PTR pq, int id, double *priority) {
    if(!valid_id(pq, id) || pq->ids[id] == NULL) {
        return 0;
    }
    *priority = pq->ids[id]->priority;
    return 1;
}


int pq_delete_top(PQ_PTR pq, int *id, double *priority) {
    if(pq->heap[0] == NULL) {
        return 0;
    }

    NODE *n = pq->heap[0];
    *id = n->id;
    *priority = n->priority;

    pq_remove_by_id(pq, n->id);
    return 1;
}


int pq_capacity(PQ_PTR pq) {
    return pq->capacity;
}


int pq_size(PQ_PTR pq) {
    return pq->size;
}


int pq_contains(PQ_PTR pq, int id) {
    double p;
    return pq_get_priority(pq, id, &p);
}

