#include <stdio.h>
#include <stdlib.h>
#include "gw.h"

typedef struct disct_struct DISCT;
typedef struct person_struct PERSON;

struct gw_struct {
    int pop;
    int rows;
    int cols;
    int size;
    DISCT **grid;
    PERSON *people;
    PERSON *dead;
};


struct disct_struct {
    int pop;
    PERSON *first;
};


struct person_struct {
    int id;
    int isAlive;
    int r;
    int c;
    PERSON *next;
    PERSON *prev;
};

//removes person from their current district
void detatch(DISCT *d, PERSON *p) {
    if(p->next == NULL && p->prev == NULL) { //if only person in the district
        d->first = NULL;
    }
    if(p->next != NULL) {
        p->next->prev = p->prev;
    }
    if(p->prev != NULL) {
        p->prev->next = p->next;
    }

    p->next = NULL;
    p->prev = NULL;

    d->pop--;
}

// adds person to a district
void add(DISCT *d, PERSON *p) {
    if(d->first == NULL) {
        p->next = NULL;
    }
    else {
        p->next = d->first;
    }
    p->prev = NULL;
    d->first = p;
}

//creates the grid world
GW gw_build(int nrows, int ncols, int pop, int rnd) {
    GW g = malloc(sizeof(GW));
    int i, j, id, k;

    g->pop = pop;
    g->size = pop * 2;
    g->rows = nrows;
    g->cols = ncols;
    g->grid = malloc(sizeof(DISCT*) * nrows);
    g->people = malloc(sizeof(PERSON) * g->size);
    g->dead = NULL;

    id = 0;

    for(i = 0; i < nrows; i++) { //for each row
        g->grid[i] = malloc(sizeof(DISCT) * ncols);

        for(j = 0; j < ncols; j++) { //for each column
            DISCT *d = &(g->grid[i][j]);

            d->first = NULL;

            if(rnd == 1) { //population is dispersed randomly
		// incomplete
            }
            else { //all people are placed in district 0,0
                if(i == 0 && j == 0) {
                    d->pop = pop;
                    printf("d->pop = %d\n", d->pop);
                }
                else {
                    d->pop = 0;
                }
            }

            for(k = 0; k < d->pop; k++) { //creates all poeple and places them
                                          //    in a district
                PERSON *p = &(g->people[id]);

                p->id = id;
                p->isAlive = 1;
                p->r = i;
                p->c = j;
                add(d, p);
                id++;
               // printf("%d %d %d\n", p->id, p->r, p->c);
            }
        }
    }

    return g;
}

//returns the members of a district in an array
int *gw_members(GW g, int i, int j, int *n) {
    DISCT *d = &(g->grid[i][j]);
    PERSON *p = d->first;
    int *a = malloc(sizeof(int) * d->pop);

    int k = 0;
    while(p->next != NULL) {
        a[k] = p->id;
        p = p->next;
        k++;
    }

    *n = d->pop;

    return a;
}

//returns the population of a district
int gw_district_pop(GW g, int i, int j) {
    return g->grid[i][j].pop;
}

//returns the population of the entire grid
int gw_total_pop(GW g) {
    return g->pop;
}

//moves person of id x to to district i, j
int gw_move(GW g, int x, int i,  int j) {
    if(x >= g->pop) {
        return 0;
    }

    PERSON *p = &(g->people[x]);
    DISCT *from = &(g->grid[p->r][p->c]);
    DISCT *to = &(g->grid[i][j]);

    if(p->isAlive == 0) {
        return 0;
    }

    detatch(from, p); //remove from current district

    p->r = i;
    p->c = j;
    add(to, p); // add to new district
    to->pop++; // increase population of new district

    return 1;
}

//finds the district of a person
int gw_find(GW g, int x, int *r, int *c) {
    PERSON *p = &(g->people[x]);

    if(p->isAlive == 0) {
        return 0;
    }

    *r = p->r;
    *c = p->c;

    return 1;
}

//kill the person with id x
int gw_kill(GW g, int x) {
    PERSON *p = &(g->people[x]);

    if(p->isAlive == 0) {
        return 0;
    }

    detatch(&(g->grid[p->r][p->c]), p);

    if(g->dead == NULL) {
        p->next = NULL;
    }
    else {
        p->next = g->dead;
    }

    p->prev = NULL;
    g->dead = p;

    p->isAlive = 0;
    g->pop--;

    return 1;
}

//creates a new person and places them in district i,j
int gw_create(GW g, int i, int j) {
    if(i > g->rows || j > g->cols) {
        return -1;
    }

    PERSON *p;
    int id = g->pop + 1;

    if(g->dead != NULL) {
        p = g->dead;
        g->dead = p->next;
    }
    else {
        p = &(g->people[id]);

        if((g->pop + 1) > g->size) {
            g->size = g->size * 2;
            PERSON *tPeople = malloc(sizeof(PERSON) * g->size);

            for(id = 0; i < g->pop; i++) {
                tPeople[id] = g->people[id];
            }

            g->people = tPeople;
        }
        p->id = id;
    }

    p->isAlive = 1;
    p->r = i;
    p->c = j;

    add(&(g->grid[i][j]), p);

    return id;
}
