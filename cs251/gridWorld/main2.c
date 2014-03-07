/*
* GridWorld
* By: Brian Howe
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include "gw.h"

static const char *optString = "N:R:C:h?";

static const struct option build_args[] = {
    { "Num-Rows", required_argument, NULL, 'R' },
    { "Init-Population", required_argument, NULL, 'N' },
    { "Num-Cols", required_argument, NULL, 'C' },
    { "rand", no_argument, NULL, 0 },
    { "help", no_argument, NULL, 'h' },
    { NULL, no_argument, NULL, 0 }
};

static const struct option commands[] = {
    { "members", required_argument, NULL, 0 },
    { "population", no_argument, NULL, 0 },
    { "population", required_argument, NULL, 0 },
    { "move", required_argument, NULL, 0 },
    { "find", required_argument, NULL, 0 },
    { "kill", required_argument, NULL, 0},
    { "create", required_argument, NULL, 0},
    { "help", no_argument, NULL, 'h' },
    { "quit", no_argument, NULL, 'q' },
    { NULL, no_argument, NULL, 0 }
};


void print_help() {
    printf("\n-----HELP-----\n\n");
    printf("./gwsim -N [int] -R [int] -C [int] --rand\n\n");
    printf("-N      sets initial population of world to [int]\n");
    printf("-R      creates a grid with [int] rows\n");
    printf("-C      creates a grid with [int] columns\n");
    printf("--rand  randomly disperses the grid's population to all districts(else all assigned to 0,0\n");
    printf("-h      print this help\n");
}


void print_commands() {
    printf("command help\n");
}


int main(int argc, char *argv[]) {
    int opt = 0;
    int longIndex = 0;
    int rows = 5;
    int cols = 5;
    int pop = 10;
    int rand = 0;

    opt = getopt_long(argc, argv, optString, build_args, &longIndex);
    while(opt != -1) {
        switch(opt) {
            case 'R':
                printf("%c\n", (char)opt);
                rows = atoi(optarg);
                break;
            case 'C':
                printf("%c\n", (char)opt);
                cols = atoi(optarg);
                break;
            case 'N':
                printf("%c\n", (char)opt);
                pop = atoi(optarg);
                break;
            case 'h':
            case '?':
                print_help();
                break;
            case 0:
                if(strcmp("rand", build_args[longIndex].name) == 0) {
                    printf("random\n");
                    rand = 1;
                }
                break;
            default:
                break;
        }

        opt = getopt_long(argc, argv, optString, build_args, &longIndex);
    }

    char *command = malloc(sizeof(char) * 256);
    int a1 = 0;
    int a2 = 0;
    int a3 = 0;

    GW world = malloc(sizeof(GW));
    world =  gw_build(rows, cols, pop, rand);

    print_commands();

    while(1) {
        printf("Enter a command: ");
        scanf("%s %d %d %d", command, &a1, &a2, &a3);

        if(strcmp("q", command) == 0) {
            printf("\n\nExiting...\n");
            return 0;
        }
        else if(strcmp("kill", command) == 0) {
            printf("hey\n");
            printf("%d\n", a1);
        }
    }
}
