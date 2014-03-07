/*
* The Traffic game. Move the cars and try to get the R car to the exit (>).
*
* Class: CS 141, Spring 2014, Thur 4pm lab.
* System: LinuxMint 16 x64, gcc
* Author: Brian Howe
*
* ToDo:
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void print_heading(int num, char *s) {
    printf("Author: Brian Howe\n");
    printf("Lab: Thur 4pm\n");
    printf("Program: #%d, %s\n\n", num, s);
}


// scans the board in from the file
void scan_board(FILE* bFile, char *board, char *cars) {
    char temp = '\0';
    int k, i;

    i = k = 0;
    while(!feof(bFile)) { // while not end of file
        fscanf(bFile, "%c", &temp);
        board[i] = temp;
        i++;

        if(temp >= 'A' && temp <= 'Z') { // if it represents a car
            cars[k] = temp;
            k++;
        }
    }
}


// prints the board
void print_board(char *board) {
    int i;

    printf("\n");
    for(i = 0; i < strlen(board); i++) {
        printf(" %c", board[i]);
    }
}


// checks to see if the car can move the requested amount of spaces
int path_clear(char car, char dir, int amount, int loc, char *board){
    int k = 1; // change in index

    if(dir == 'U' || dir == 'L') { // if up or left
        k = -k; // move backwards
    }
    if(dir == 'D' || dir == 'U') { // if up or down
        k = k * 9; // jump a row
    }

    int i, j;
    char next;
    for(i = 1; i < (amount+1); i++) { // amount + 1 because i starts at 1 not 0.
        j = loc + (k * i);
        next = board[j];
        if(next == car) {
            next = board[j+k]; // skip the space because it is part of the car
            amount++;
        }
        else if(next != '.' && next != '>') {
            return 0;
        }
    }

    return 1;
}


// retrieves the users input from the terminal
void get_input(char *car, char *dir, int *amount) {

    printf("Your move -> ");
    scanf(" %c", car);
    *car = toupper(*car);
    if(*car != 'X') { //if not x (for exit) get next charater and integer
        scanf(" %c%d", dir, amount);
        *dir = toupper(*dir); // makes dir uppercase
    }
}


// returns the index of the first instance of car. the index is negative
// if the car is horizontal and positive if the car is vertical
int get_orientation(char car, char *board) {
    int i;

    for(i = 0; i < strlen(board); i++) {
        if(board[i] == car && (board[i+9] == car || board[i-9] == car)) {
            return i; //vertical
        }
        else if(board[i] == car && (board[i-1] == car || board[i+1] == car)) {
            return -i; //horizontal
        }
    }

    return 0; // should not reach this (error)
}


// checks if the users inout is a possible move
int valid_move(char car, char dir, int amount, char *cars, char *board) {
    int i = 0;
    for(i = 0; i < strlen(cars); i++) { // checks if car is on the board
        if(cars[i] == '\0') {
            return 0;
        }
        if(cars[i] == car) {
            i = strlen(cars);
        }
    }

    int loc = get_orientation(car, board); //index of car on board (neg if horizontal)

    // proper direction and orientation ex. vertical can only be 'U' and 'D'
    if(loc > 0 && (dir == 'U' || dir == 'D')) {
        if(path_clear(car, dir, amount, loc, board)) {
            return loc; // valid move
        }
        else {
            return 0; // path is blocked
        }
    }
    else if(loc < 0 && (dir == 'L' || dir == 'R')) {
        if(path_clear(car, dir, amount, -loc, board)) {
            return loc; // valid move
        }
        else {
            return 0; // path is blocked
        }
    }
    else {
        return 0; // invalid move
    }
}


int get_carLen(char car, char *cars) {
    int i;
    int carLen = 0;

    for(i = 0; i < strlen(cars); i++) {
        if(cars[i] == car) {
            carLen++;
        }
    }
    return carLen;
}

// makes the move specified by the input
int make_move(char car, char dir, int amount, int loc, char *cars, char *board) {
    int k = 1; // change in index
    int carLen = 0;

    if(dir == 'U' || dir == 'L') { // if down or left
        k = -k; // move backwards
    }
    if(dir == 'D' || dir == 'U') { // if up or down
        k = k * 9; // jump a row
    }

    carLen = get_carLen(car, cars);

    if(loc < 0){
        loc = -loc;
    }

    int i, j;
    char *next;
    for(i = 1; i < amount+1; i++) {
        j = loc + (k * i);
        next = &board[j];
        if(*next == car) {
            next = &board[j+k]; // skip the space because it is part of the car
            amount++;
        }
        else if(*next == '.') {
            *next = car;
            board[j - (k*carLen)] = '.';
        }
        else if(*next == '>' && car == 'R') {
            *next = car;
            board[j - (k*carLen)] = '.';
            return 1;
        }
    }

    return 0;
}


int main() {
    FILE* bFile;
    char *board = malloc(256 * sizeof(char)); // the board
    char *cars = malloc(64 * sizeof(char)); // all car identifiers
    char car = '\0'; // car to move
    char dir = '\0'; // direction of move
    int amount = -1; // number of spaces to move
    int loc = -1;

    print_heading(3, "The Traffic Game");

    bFile = fopen("board.txt", "r");
    if(bFile == NULL) {
        printf("Could not open file board.txt.\n");
        return -1;
    }

    scan_board(bFile, board, cars);

    fclose(bFile);

    printf("Welcome to the traffic game!\n\n");
    printf("Move the vehicles so that the Red car (RR) can\n");
    printf("exit the board to the right. Each move should be\n");
    printf("of the form:    CDN    where C is the vehicle to\n");
    printf("be moved,  D ids the direction (u for up, d for down,\n");
    printf("l for left or r for right), and N is the number of\n");
    printf("squares to move it. For example GR2 means move the\n");
    printf("G vehicle to the right 2 squares. Lower-case input\n");
    printf("such as   gr2   is also accepted.   Entre x to exit the\n");
    printf("program.\n");

    while(1) {
        print_board(board);

        do {
            get_input(&car, &dir, &amount);

            // printf("\n%c%c%d\n", car, dir, amount); //for testing

            if(car == 'X') {
                printf("Thanks for playing! Exiting...\n");
                free(board);
                free(cars);
                return 0;
            }

            loc = valid_move(car, dir, amount, cars, board);

            if(! loc) {
                printf("Move not valid. try again.\n");
            }

        }while(! loc);

        if(make_move(car, dir, amount, loc, cars, board)) {
            print_board(board);
            printf("\nCongradulations!! You Win!!!\n\n");
            printf("Thanks for playing! Exiting...\n");
            free(board);
            free(cars);
            return 0;
        }
    }
}
