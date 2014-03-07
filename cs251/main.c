#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gw.h"

void printargv(int argc, char **argv) {
    int i;
    for(i = 0; i < argc; i++) {
        printf("%d. %s\n", i, argv[i]);
    }
    printf("\n");
}

void print_array(int *m, int n) {
    int i;
    printf("\n[");
    for(i = 0; i < n; i++) {
        printf("%d ", m[i]);
    }
    printf("\b]\n");
}

void init_array(int *a, int n, int x) {
    int i;
    for(i = 0; i < n; i++) {
        a[i] = x;
    }
}

int main(int argc, char **argv) {
    int pop, rows, cols, rnd;
    pop = 10;
    rows = 5;
    cols = 5;
    rnd = 0;

    if(argc > 1) {
        int i;
        for(i = 1; i < argc; i++) {
            printf("%d. %s\n", i, argv[i]);
            if(argv[i][0] == '-') {
                if('N' == argv[i][1]) {
                    pop = atoi(argv[i+1]);
                }
                else if('R' == argv[i][1]) {
                    rows = atoi(argv[i+1]);
                }
                else if('C', argv[i][1]) {
                    cols = atoi(argv[i+1]);
                }
                else if(strcmp("-rand", argv[i]) == 0) {
                    printf("\n-rand\n");
                }
                printf("%d. done\n", i);
            }
        }
    }

    printf("pop = %d\n", pop);
    printf("rows = %d\n", rows);
    printf("cols = %d\n", cols);
    printf("rand = %d\n\n", rnd);

    GW world = world = gw_build(rows, cols, pop, rnd);

    int opp;

    while(1) {
        printf("1. members of a district\n");
        printf("2. population of district\n");
        printf("3. population of entire grid\n");
        printf("4. move a person\n");
        printf("5. find a person\n");
        printf("6. kill a person\n");
        printf("7. create a person\n");
        printf("8. quit\n\n");

        printf("Enter a command: ");
        scanf("%d", &opp);

        switch (opp) {
            case 1: { //members
                int *a; int n, r, c;
                printf("row: ");
                scanf("%d", &r);
                printf("col: ");
                scanf("%d", &c);
                a  = gw_members(world, r, c, &n);
                if(n < 1) {
                    printf("District %d,%d has no members.\n", r, c);
                }
                else {
                    print_array(a, n);
                }
                break;
            }
            case 2: { // district pop
                int n, r, c;
                printf("row: ");
                scanf("%d", &r);
                printf("col: ");
                scanf("%d", &c);
                n = gw_district_pop(world, r, c);
                if(n == -1) {
                    printf("No such district in grid.\n");
                }
                else {
                    printf("The population of %d,%d is %d.\n", r, c, n);
                }
                break;
            }
            case 3: { // world pop
                int n;
                n = gw_total_pop(world);
                printf("The population of the world is %d\n", n);
                break;
            }
            case 4: { // move
                int id, r, c;
                printf("Persons id: ");
                scanf("%d", &id);
                printf("row: ");
                scanf("%d", &r);
                printf("col: ");
                scanf("%d", &c);
                if(gw_move(world, id, r, c)) {
                    printf("Move succeeded.\n");
                }
                else {
                    printf("Move failed.\n");
                }
                break;
            }
            case 5: { // find
                int r, c, id;
                printf("Persons id: ");
                scanf("%d", &id);
                if(gw_find(world, id, &r, &c)) {
                    printf("Person %d is in district %d,%d.\n", id, r, c);
                }
                else {
                    printf("Person %d does not exist\n", id);
                }
                break;
            }
            case 6: { // kill
                int id;
                printf("Persons id: ");
                scanf("%d", &id);
                if(gw_kill(world, id)) {
                    printf("Person %d has been killed.\n", id);
                }
                else {
                    printf("Person %d does not exist or is already dead.\n", id);
                }
                break;
            }
            case 7: { // create
                int r, c;
                printf("row: ");
                scanf("%d", &r);
                printf("col: ");
                scanf("%d", &c);
                if(gw_create(world, r, c) != -1) {
                    printf("Person succesfully created at %d,%d.\n", r, c);
                }
                else {
                    printf("Failed to create person");
                }
                break;
            }
            case 8: { // quit
                gw_free(world);
                printf("Exiting...\n");
                return 0;
            }
            default: {
                printf("\nCommand not valid.\n");
                pause();
            }
        }
        printf("\n--------------------------------------------------------\n\n");
    }

    return 0;
}
