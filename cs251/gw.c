#include <stdio.h>
#include <stdlib.h>
#include "gw.h"

typedef struct disct_struct DIST;
typedef struct person_struct PERSON;

struct gw_struct {
    int pop;
    int rows;
    int cols;
    int size;
    DIST **grid;
    PERSON *people;
    DIST *dead;
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
void detatch(DIST *d, PERSON *p) {
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

    d->pop--; // decrease district pop
}


int in_grid(GW g, int r, int c) {
    if(r < 0 || r > g->rows || c < 0 || c > g->cols){
        return 0;
    }
    else {
        return 1;
    }
}

// adds person to a district
void add(DIST *d, PERSON *p) {
    if(d->first == NULL) {
        p->next = NULL;
    }
    else {
        p->next = d->first;
        d->first->prev = p;
    }
    p->prev = NULL;
    d->first = p;
}

//creates the grid world
GW gw_build(int nrows, int ncols, int pop, int rnd) {
    GW g = malloc(sizeof(GW));
    int i, j, id, k;

    g->pop = pop;
    g->size = (pop * 2);
    g->rows = nrows;
    g->cols = ncols;
    g->grid = malloc(sizeof(DIST*) * nrows);
    g->people = malloc(sizeof(PERSON) * g->size);
    g->dead = malloc(sizeof(DIST));

    id = 0;

    for(i = 0; i < nrows; i++) { //for each row
        g->grid[i] = malloc(sizeof(DIST) * ncols);

        for(j = 0; j < ncols; j++) { //for each column
            DIST *d = &(g->grid[i][j]);

            d->first = NULL;

            if(rnd == 1) { //population is dispersed randomly

            }
            else { //all people are placed in district 0,0
                if(i == 0 && j == 0) {
                    d->pop = pop;
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
            }
        }
    }

    return g;
}


void print_people(GW g) {
    printf("\nAll people in world [");
    int i;
    for(i = 0; i < g->pop; i++) {
        printf("%d ", g->people[i].id);
    }
    printf("\b]\n");
}

//returns the members of a district in an array
int *gw_members(GW g, int i, int j, int *n) {
    if(i >= g->rows || j >= g->cols){
        return NULL;        
    }

    DIST *d = &(g->grid[i][j]);

    if(d->pop == 0) {
        *n = 0;
        return NULL;
    }

    PERSON *p = d->first;

    int *a = malloc(sizeof(int) * d->pop);


    int k;
    for(k = 0; k < d->pop; k++) {
        if(p != NULL) {
            a[k] = p->id;
            p = p->next;
        }
    }

    *n = d->pop;

    print_people(g);

    return a;
}

//returns the population of a district
int gw_district_pop(GW g, int i, int j) {
    if(in_grid(g, i, j)) {
        return g->grid[i][j].pop;
    }
    else {
        return -1;
    }
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
    DIST *from = &(g->grid[p->r][p->c]);
    DIST *to = &(g->grid[i][j]);

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
    if(x >= g->pop) {
        return 0;
    }

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
    DIST *d = &(g->grid[p->r][p->c]);

    if(p->isAlive == 0) {
        return 0;
    }

    detatch(d, p);

    add(g->dead, p);
    g->dead->pop++;

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
    DIST *d = &(g->grid[i][j]);

    int id = g->pop;

    if(g->dead->pop != 0) {
        p = g->dead->first;
        g->dead->first = p->next;
    }
    else {
        if(id >= g->size) {
            g->size = g->size * 2;
            PERSON *tPeople = malloc(sizeof(PERSON) * g->size);

            for(id = 0; id < g->pop; id++) {
                tPeople[id] = g->people[id];
            }

            g->people = tPeople;
            free(tPeople);
        }

        p = &(g->people[id]);
        p->id = id;
    }

    p->isAlive = 1;
    p->r = i;
    p->c = j;

    add(d, p);
    d->pop++;
    g->pop++;

    return id;
}

void gw_free(GW g) {
    int i;
    for(i = 0; i < g->rows; i++) {
        free(g->grid[i]);
    }
    free(g->people);
}
