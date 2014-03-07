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

void print_array(int n, int *m) {
    int i;
    printf("[");
    for(i = 0; i < n; i++) {
        printf("%d ", m[i]);
    }
    printf("\b]\n");
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

    printf("The population of the world is %d\n", gw_total_pop(world));
    printf("The population of district 0,0 is %d\n", gw_district_pop(world, 0, 0));

    int n;
    int *mem = gw_members(world, 0, 0, &n);

    print_array(n, mem);

    if(gw_move(world, 3, 1, 1)) {
        printf("the population of 0,0 is now %d\n", gw_district_pop(world, 0, 0));
        printf("the population of 1,1 is now %d\n", gw_district_pop(world, 1, 1));
    }
    else {
        printf("move failed\n");
    }

    mem = gw_members(world, 0, 0, &n);
    print_array(n, mem);
    mem = gw_members(world, 1, 1, &n);
    print_array(n, mem);

    int i, j;
    gw_find(world, 5, &i, &j);
    printf("person 5 is in district %d,%d\n", i, j);

    return 0;
}
