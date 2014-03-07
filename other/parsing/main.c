/*
* This is a basic argument parsing template
* By: Brian Howe
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_help() {
    printf("\n-----HELP-----\n");
    printf("-a   print 'a'\n");
    printf("-b   print 'b'\n");
    printf("-c   print 'c'\n");
    printf("-d   print 'd'\n");
    printf("-h   print this help\n");
}


int main(int argc, char *argv[]) {
    int opt = 0;

    while((opt = getopt(argc, argv, "abcdh")) != -1) {
        switch(opt) {
            case 'a':
                printf("You picked 'a'\n");
                break;
            case 'b':
                printf("You picked 'b'\n");
                break;
            case 'c':
                printf("You picked 'c'\n");
                break;
            case 'd':
                printf("You picked 'd'\n");
                break;
            case 'h':
                print_help();
                break;
        }
    }
    
    if(argc == 1) {
        print_help();
    }
    
    printf("\nExiting...\n\n");
    return 0;
}
