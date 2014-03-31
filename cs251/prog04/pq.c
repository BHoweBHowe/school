/*
* AUTH: Brian Howe
*
* DESC: a set of function that control and maintain a priority queue binary heap
*
* TODO: fix prioritze
*/

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


/**
* Function: pq_create
* Parameters: capacity - self-explanatory
*             min_heap - if 1 (really non-zero), then it is a min-heap
*                        if 0, then a max-heap
*
* Returns:  Pointer to empty priority queue with given capacity and
*           min/max behavior as specified.
*
*/
PQ_PTR pq_create(int capacity, int min_heap) {
    PQ_PTR pq = malloc(sizeof(struct pq_struct));
    pq->capacity = capacity;
    pq->min_heap = min_heap;
    pq->size = 0;
    pq->ids = malloc(sizeof(NODE*) * capacity);
    pq->heap = malloc(sizeof(NODE*) * capacity);

    int i;
    for(i = 0; i <= pq->capacity; i++) {
        pq->ids[i] = NULL; // will have extra at end
        pq->heap[i] = NULL; // will have extra at begining
    }

    return pq;
}


/**
* Function: pq_free
* Parameters: PQ_PTR pq
* Returns: --
* Desc: deallocates all memory associated with passed priority
*       queue.
*
*/
void pq_free(PQ_PTR pq) {
    int i;
    for(i = 0; i <= pq->size; i++) {
        free(pq->heap[i]);
    }
    free(pq->ids);
    free(pq->heap);
    free(pq);
}


// checks if id is with in range
int valid_id(PQ_PTR pq, int id) {
    if(id >= pq->capacity || id < 0) {
        return 0;
    }
    return 1;
}


// if the node has children the index with the highest
// priority is returned
int has_children(PQ_PTR pq, int k, int i) {
    NODE **heap = pq->heap;
    NODE *l = heap[i*2];

    if((i*2) > pq->size || l == NULL) {
        return -1;
    }

    NODE *r = heap[(i*2)+1];

    if((i*2)+1 <= pq->size && r != NULL) {
        if((l->priority)*k < (r->priority)*k) {
            return r->i;
        }
    }
    return l->i;
}


// swaps 2 nodes positions in the heap
void swap_node(NODE **heap, int i, int dest) {
    // update indecies
    heap[i]->i = heap[dest]->i;
    heap[dest]->i = i;
    // swap nodes
    NODE *tmp = heap[dest];
    heap[dest] = heap[i];
    heap[i] = tmp;
}


// keeps highest priority (relative to min_heap) at top
void prioritize(PQ_PTR pq, int i) {
    NODE **heap = pq->heap;
    int k = 1; // modifier
    if(pq->min_heap == 1) {
        k = -1; // makes largest pri smallest
    }

    // if the priority of i is greater than its parent switch them
    if(i != 1 && (heap[i]->priority)*k > (heap[i/2]->priority)*k) {
        swap_node(heap, i, i/2);
        prioritize(pq, i/2);
    }
    else {
        int h = has_children(pq, k, i);

        if(h != -1) {
            if((heap[i]->priority)*k < (heap[h]->priority)*k) {
                swap_node(heap, i, h);
                prioritize(pq, h);
            }
        }
    }
}


/**
* Function: pq_insert
* Parameters: priority queue pq
*             id of entry to insert
*             priority of entry to insert
* Returns: 1 on success; 0 on failure.
*          fails if id is out of range or
*            there is already an entry for id
*          succeeds otherwise.
*
* Desc: self-explanatory
*
* Runtime:  O(log n)
*
*/
int pq_insert(PQ_PTR pq, int id, double priority) {
    if(!valid_id(pq, id) || pq->ids[id] != NULL) {
        return 0;
    }

    NODE *n = malloc(sizeof(NODE));
    n->id = id;
    n->priority = priority;

    pq->size++;
    n->i = pq->size;

    pq->ids[id] = n;
    pq->heap[pq->size] = n;

    prioritize(pq, n->i);
}


/**
* Function: pq_change_priority
* Parameters: priority queue ptr pq
*             element id
*             new_priority
* Returns: 1 on success; 0 on failure
* Desc: If there is an entry for the given id, its associated
*       priority is changed to new_priority and the data
*       structure is modified accordingly.
*       Otherwise, it is a failure (id not in pq or out of range)
* Runtime:  O(log n)
*
*/
int pq_change_priority(PQ_PTR pq, int id, double new_priority) {
    if(!valid_id(pq, id) || pq->ids[id] == NULL) {
        return 0;
    }

    NODE *n = pq->ids[id];
    n->priority = new_priority;
    prioritize(pq, n->i);
    return 1;
}


/**
* Function: pq_remove_by_id
* Parameters: priority queue pq,
*             element id
* Returns: 1 on success; 0 on failure
* Desc: if there is an entry associated with the given id, it is
*       removed from the priority queue.
*       Otherwise the data structure is unchanged and 0 is returned.
* Runtime:  O(log n)
*
*/
int pq_remove_by_id(PQ_PTR pq, int id) {
    if(!valid_id(pq, id) || pq->ids[id] == NULL) {
        return 0;
    }

    NODE *n = pq->ids[id];
    pq->ids[id] = NULL;

    if(n->i < pq->size) { // there is a node lower in the heap
        pq->heap[n->i] = pq->heap[pq->size];
        pq->heap[n->i]->i = n->i; // update index
        pq->heap[pq->size] = NULL;

        prioritize(pq, n->i);
    }

    pq->size--;
    free(n);
    return 1;
}


/**
* Function: pq_get_priority
* Parameters: priority queue pq
*             elment id
*             double pointer priority ("out" param)
* Returns: 1 on success; 0 on failure
* Desc: if there is an entry for given id, *priority is assigned
*       the associated priority and 1 is returned.
*       Otherwise 0 is returned and *priority has no meaning.
* Runtime:  O(1)
*
*/
int pq_get_priority(PQ_PTR pq, int id, double *priority) {
    if(!valid_id(pq, id) || pq->ids[id] == NULL) {
        return 0;
    }
    *priority = pq->ids[id]->priority;
    return 1;
}


/**
* Function: pq_delete_top
* Parameters: priority queue pq
*             int pointers id and priority ("out" parameters)
* Returns: 1 on success; 0 on failure (empty priority queue)
* Desc: if queue is non-empty the "top" element is deleted and
*       its id and priority are stored in *id and *priority;
*       The "top" element will be either min or max (wrt priority)
*       depending on how the priority queue was configured.
*
*       If queue is empty, 0 is returned.
*
* Runtime:  O(log n)
*
*
*/
int pq_delete_top(PQ_PTR pq, int *id, double *priority) {
    if(pq->heap[1] == NULL) {
        return 0;
    }

    NODE *n = pq->heap[1];
    *id = n->id;
    *priority = n->priority;

    pq_remove_by_id(pq, n->id);
    return 1;
}


/**
* Function:  pq_capacity
* Parameters: priority queue pq
* Returns: capacity of priority queue (as set on creation)
* Desc: see returns
*
* Runtime:   O(1)
*
*/
int pq_capacity(PQ_PTR pq) {
    return pq->capacity;
}


/**
* Function: pq_size
* Parameters: priority queue pq
* Returns: number of elements currently in queue
* Desc: see above
*
* Runtime:  O(1)
*/
int pq_size(PQ_PTR pq) {
    return pq->size;
}


/**
* Function: pq_contains
* Parameters: priority queue pq
*             element id
* Returns: 1 if there is an entry in the queue for given id
*          0 otherwise
* Desc: see above
*
* Runtime:  O(1)
*
* Note:  same return value as pq_get_priority
*
*/
int pq_contains(PQ_PTR pq, int id) {
    double p;
    return pq_get_priority(pq, id, &p);
}

