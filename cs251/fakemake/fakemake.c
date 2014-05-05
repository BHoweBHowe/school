/*
    fakemake

    AUTH: Brian Howe
    DATE: 5/1/2014
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hmap.h"

#define BUFF    256
#define LIMIT   64 // assuming there wont be more than 64 files


typedef struct dNode_struct { //
    char   name[BUFF]; // name of file
    struct dNode_struct *next; // next dependency
} DNODE;

typedef struct fNode_struct {
    char  name[BUFF]; // name of file
    int   time_stamp; // last touched
    DNODE *head; // linked list of dependencies
} FNODE;


/*
    initilizes a node and adds it to the hashtable
*/
void add_node(HMAP_PTR graph, char *key) {
    FNODE *t = malloc(sizeof(FNODE));

    strcpy(t->name, key);
    t->time_stamp = 0;
    t->head       = NULL;

    hmap_set(graph, key, t);
}


/*
    places all keys into hash table, keeps track of keys and dependencies

    return: pointer to initialized graph.
*/
HMAP_PTR build_graph(FILE *f, char keys[][BUFF], int *n) {
    HMAP_PTR graph      = hmap_create(0, 0);
    HMAP_PTR undeclared = hmap_create(0, 0);
    char     *word      = malloc(sizeof(char) * BUFF);
    char     *prev_word = malloc(sizeof(char) * BUFF);
    char     *line      = malloc(sizeof(char) * BUFF);

    int i = 0; // num unique files added to graph
    int k = 0; // num unique dependencies not yet in graph

    // parses file
    while(fgets(line, BUFF, f)) {
        word = strtok(line, " \n");

        while(word) {

            if(!hmap_contains(graph, word) && strcmp(word, ":") != 0) {
                add_node(graph, word);
                strcpy(keys[i], word);
                i++;
                (*n)++;

                if(hmap_contains(undeclared, word)) {
                    k--;
                    hmap_remove(undeclared, word);
                }
            }
            // has dependencies
            else if(strcmp(word, ":") == 0) {
                FNODE *prev = hmap_get(graph, prev_word);
                word = strtok(NULL, " ");

                while(prev_word[0] != '\n') {
                    DNODE *d = malloc(sizeof(DNODE));

                    if(word[strlen(word)-1] == '\n') {
                        word[strlen(word)-1] = '\0';
                        prev_word[0] = '\n';
                    }

                    strcpy(d->name, word);
                    d->next = prev->head;
                    prev->head = d;

                    if(!hmap_contains(graph, word)) {
                        int *temp;
                        hmap_set(undeclared, word, temp);
                        k++;
                    }

                    if(prev_word[0] != '\n') {
                        word = strtok(NULL, " ");
                    }
                }
            }

            strcpy(prev_word, word); // keeps track of previous file
            word = strtok(NULL, " \n");
        }
    }

    if(k > 0) {
        fprintf(stderr, "A dependency was not found. exiting...\n");
        *n = -1;
    }

    free(word);
    free(prev_word);
    free(line);
    hmap_free(undeclared, 0);

    return graph;
}


/*
    updates a files time stamp if the file has no dependencies
*/
void touch(HMAP_PTR graph, char* file, int *clock) {
    if(hmap_contains(graph, file)) {
        FNODE *f = hmap_get(graph, file);
        if(f->head == NULL) {
            f->time_stamp = *clock;
            (*clock)++;
            printf("  File '%s' has been modified\n", file);
        }
        else {
            fprintf(stderr, "  File '%s' cannot be modified due to dependencies\n", file);
        }
    }
    else {
        printf("  File '%s' not found\n", file);
    }
}


/*
    prints the time stamp of the specified file
*/
void timestamp(HMAP_PTR graph, char *file) {
    if(hmap_contains(graph, file)) {
        FNODE *f = hmap_get(graph, file);
        printf("  %d\n", f->time_stamp);
    }
    else {
        printf("  File '%s' not found\n", file);
    }
}


/*
    prints time stamp of all files
*/
void timestamps(HMAP_PTR graph, char keys[][BUFF], int n) {
    int i;
    for(i = 0; i < n; i++) {
        printf("  %s ", keys[i]);
        timestamp(graph, keys[i]);
    }
}


/*
    if the file has dependencies that have a higher time stamp
    the file is made. if a dependecy has its own dependencies
    make is called on it.
*/
void make(HMAP_PTR graph, char *file, int *clock) {
    if(hmap_contains(graph, file)) {
        FNODE *main = hmap_get(graph, file);
        DNODE *d    = main->head;
        int   high  = main->time_stamp;

        if(d != NULL) {
            FNODE *dep = NULL;

            while(d != NULL) {
                dep = hmap_get(graph, d->name);

                make(graph, dep->name, clock);
                d = d->next;

                if(dep->time_stamp > high) {
                    high = dep->time_stamp;
                }
            }
            if(high > main->time_stamp || main->time_stamp == 0) {
                main->time_stamp = *clock;
                (*clock)++;
                printf("  making %s...done\n", file);
            }
            else {
                printf("  %s is up to date\n", file);
            }
        }
    }
    else {
        printf("  File '%s' not found\n", file);
    }
}


/*
    deallocates all nodes and dependencies aswell as the hashtable.
*/
void free_graph(HMAP_PTR graph, char keys[][BUFF], int n) {
    int i;
    FNODE *f = NULL;
    DNODE *d = NULL;

    for(i = 0; i < n; i++) {
        f = hmap_get(graph, keys[i]);

        while(f->head != NULL) {
            d = f->head->next;
            free(f->head);
            f->head = d;
        }
        free(f);
    }

    hmap_free(graph, 0);
}


int main(int argc, char *argv[]) {
    if(argc < 2) { // no file name entered
        fprintf(stderr, "target file not specified. exiting...\n");
        return -1;
    }

    int  clock = 1;
    char input[BUFF];
    char keys[LIMIT][BUFF]; // all file names in graph
    int  num_keys = 0;
    FILE *m_file = NULL;

    m_file = fopen(argv[1], "r");
    if(m_file == NULL) { // file not found
        fprintf(stderr, "could not open file. exiting...\n");
        return -1;
    }

    HMAP_PTR graph = build_graph(m_file, keys, &num_keys);

    fclose(m_file);

    if(num_keys == -1) {
        return -1; // file had undeclared dependency. exit program.
    }

    do {
        printf("> ");
        scanf(" %256s", input);

        if(strcmp(input, "time") == 0) {
            printf("%d\n", clock);
        }
        else if(strcmp(input, "touch") == 0) {
            char file[BUFF];

            scanf(" %256s", file);
            touch(graph, file, &clock);
        }
        else if(strcmp(input, "timestamp") == 0) {
            char file[BUFF];

            scanf(" %256s", file);
            timestamp(graph, file);
        }
        else if(strcmp(input, "timestamps") == 0) {
            timestamps(graph, keys, num_keys);
        }
        else if(strcmp(input, "make") == 0) {
            char file[BUFF];

            scanf(" %256s", file);
            make(graph, file, &clock);
        }
        else if(strcmp(input, "quit") == 0) {
            free_graph(graph, keys, num_keys);
        }
        else {
            printf("invalid input. try again.\n");
        }
    } while(strcmp(input, "quit") != 0);

    return 0;
}
