#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

int *board;
int b_size;
int num_on_board;
int max;
int num_turns;

void instructions() {
    printf("Brian Howe\n");
    printf("UIC CS 141, Spring 2014\n");
    printf("Welcome to 1024 and More.\n");
    printf("This program is based off of Gabriele Cirulli's game online at\n");
    printf("bit.ly/great2048\n");
    printf("\n");
    printf("For each move enter a direction as a letter key, as follows:\n");
    printf("  W\n");
    printf("A S D\n");
    printf("where A=left,W=up, D=right and S=down.\n");
    printf("\n");
    printf("After a move, when two identical valued tiles come together they\n");
    printf("join to become a new single tile with the value of the sum of the\n");
    printf("two originals. This value gets added to the score.  On each move\n");
    printf("one new randomly chosen value of 2 or 4 is placed in a random open\n");
    printf("square.  User input of r restarts the game, and x exits the game.\n");
    printf("\n");
}

int valid_dir(char dir) {
    if(dir == 'w' || dir == 'a' || dir == 's' || dir == 'd') {
        return 1;
    }
    return 0;
}

void move_up() {
    int i;
    int next;
    for(i = 0; i < b_size*b_size; i++) {
        next = i - 10;
        if(next >= 0) {
            if(
        }
    }
}

void make_move() {
    char dir;
    int i, j, vert;

    num_turns++;

    do {
        printf("%d. Your move: ", num_turns);
        scanf(" %c", &dir);
        dir = tolower(dir);

        if(!valid_dir(dir)) {
            printf("Input must be 'W', 'A', 'S', or 'D'\n");
        }
    } while(!valid_dir(dir));

    if(dir == 'w') {
        move_up();
    }
    else if(dir == 'a') {
        move_left();
    }
    else if(dir == 's') {
        move_down();
    }
    else if(dir == 'd') {
        move_right();
    }

    for(i = 0; i < b_size; i++) {
        move_nums(0, jump[j]);
    }
}

void plc_rnd() {
    int i;

    do{
        i = rand() % (b_size * b_size);
    } while(board[i] != -1);

    board[i] = 2;
    num_on_board++;
}

void init_board() {
    board = (int*)malloc(sizeof(int) * b_size * b_size);

    int i;
    for(i = 0; i < b_size * b_size; i++) {
        board[i] = -1;
    }

    max = 2;
    num_on_board = 0;
    num_turns = 0;

    plc_rnd();
    plc_rnd();
}

void print_board() {
    int i;
    for(i = 1; i <= b_size * b_size; i++) {
        if(board[i-1] == -1) {
            printf(" %3c", '.');
        }
        else {
            printf(" %3d", board[i-1]);
        }

        if(i % b_size == 0) {
            printf("\n\n");
        }
    }

    printf("\n\n");
}

int main() {
    srand(time(NULL));

    instructions();

    do {
        printf("Enter the size board you want, between 4 and 12: ");
        scanf("%d", &b_size);
    } while(b_size < 4 || b_size > 12);
    printf("Game ends when you reach 2048.\n\n");

    init_board();

    do {
        print_board();

        make_move();

        system("clear");
    } while(max != 1024);

    return 0;
}
