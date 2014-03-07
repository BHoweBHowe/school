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
void scan_board(FILE* bFile, char *board, int cars[26][3]) {
    char temp = '\0';
    int k, i;

    i = k = 0;
    while(!feof(bFile)) { // while not end of file
        fscanf(bFile, "%c", &temp);
        board[i] = temp;

        if(temp != 'X' && (temp >= 'A' && temp <= 'Z')) { // if it represents a car
            int *carInfo = cars[temp - 'A'];

            if(carInfo[0] < 1 || carInfo[0] > 4) {
                carInfo[0] = 1;
            }
            else {
                carInfo[0]++;
            }

            if(carInfo[0] == 1) {
                carInfo[1] = i; // location of last index of car
            }

            if(i > 0 && board[i-1] == temp) {
                carInfo[2] = 0; // horizontal
            }
            else {
                carInfo[2] = 1; // vertical
            }
        }
        i++;
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
int path_clear(char car, char dir, int amount, int cars[26][3], char *board){
    int k = 1; // change in index
    int *carInfo = cars[car - 'A'];

    if(dir == 'U' || dir == 'L') { // if up or left
        k = -k; // move backwards
    }
    if(dir == 'D' || dir == 'U') { // if up or down
        k = k * 9; // jump a row
    }

    int i, j;
    char next;
    for(i = 1; i < (amount+1); i++) { // amount + 1 because i starts at 1 not 0.
        j = carInfo[1] + (k * i);
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


// checks if the users inout is a possible move
int valid_move(char car, char dir, int amount, int cars[26][3], char *board) {
    int *carInfo = cars[car - 'A'];

    if(carInfo[0] < 2 || carInfo[0] > 4) {
        printf("Car not found.\n");
        return 0;
    }

    // proper direction and orientation ex. vertical can only be 'U' and 'D'
    if(carInfo[2] == 1 && (dir == 'U' || dir == 'D')) {
        if(path_clear(car, dir, amount, cars, board)) {
            return 1; // valid move
        }
        else {
            printf("Vehicle %c can not move %d spaces in that direction.\n", car, amount);
            return 0; // path is blocked
        }
    }
    else if(carInfo[2] == 0 && (dir == 'L' || dir == 'R')) {
        if(path_clear(car, dir, amount, cars, board)) {
            return 1; // valid move
        }
        else {
            printf("Vehicle %c can not move %d spaces in that direction.\n", car, amount);
            return 0; // path is blocked
        }
    }
    else {
        printf("Vehicle %c can not move that direction.\n", car);
        return 0; // invalid move
    }
}


// makes the move specified by the input
int make_move(char car, char dir, int amount, int cars[26][3], char *board) {
    int k = 1; // change in index
    int *carInfo = cars[car - 'A'];

    if(dir == 'U' || dir == 'L') { // if down or left
        k = -k; // move backwards
    }
    if(dir == 'D' || dir == 'U') { // if up or down
        k = k * 9; // jump a row
    }

    int i, j;
    char *next;
    for(i = 1; i < amount+1; i++) {
        j = carInfo[1] + (k * i);
        next = &board[j];
        if(*next == car) {
            next = &board[j+k]; // skip the space because it is part of the car
            amount++;
        }
        else if(*next == '.') {
            *next = car;
            board[j - (k*carInfo[0])] = '.';
        }
        else if(*next == '>' && car == 'R') {
            *next = car;
            board[j - (k*carInfo[0])] = '.';
            return 1;
        }
        if(i == amount) {
            carInfo[1] = j; // sets new location of car
        }
    }

    return 0;
}


int main() {
    FILE* bFile;
    char *board = malloc(sizeof(char) * 128);
    int cars[26][3];
    char car = '\0'; // car to move
    char dir = '\0'; // direction of move
    int amount = -1; // number of spaces to move
    int temp = 0;

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
                return 0;
            }

            temp = valid_move(car, dir, amount, cars, board);

            if(! temp) {
                printf("Move not valid. try again.\n");
            }

        }while(! temp);

        if(make_move(car, dir, amount, cars, board)) {
            print_board(board);
            printf("\nCongradulations!! You Win!!!\n\n");
            printf("Thanks for playing! Exiting...\n");
            free(board);
            return 0;
        }
    }
}
