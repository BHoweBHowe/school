#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pq.h"

int main() {
    PQ_PTR pq = pq_create(10, 1);

    pq_insert(pq, 0, 5);
    pq_insert(pq, 1, 10);
    pq_insert(pq, 2, -3);
    pq_insert(pq, 3, 2);
    pq_insert(pq, 4, 20);
    pq_insert(pq, 5, -80);
    pq_insert(pq, 6, -40);
    pq_insert(pq, 7, 33);
    pq_insert(pq, 8, 120);
    pq_insert(pq, 9, 7);

    printf("size of queue: %d\n", pq_size(pq));

    double p;
    int id;

    pq_delete_top(pq, &id, &p);
    printf("first in queue: %d, %f\n", id, p);

    pq_delete_top(pq, &id, &p);
    printf("first in queue: %d, %f\n", id, p);

    pq_delete_top(pq, &id, &p);
    printf("first in queue: %d, %f\n", id, p);

    pq_free(pq);

    return 0;
}
