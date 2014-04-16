/* ------------------------------------------------ 
*
* Class: CS 141, Spring 2014.  Thur. 4pm lab.
* System: Linux Mint, g++
* Author: Brian Howe
*
* -------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

int **board;
int b_size; // board dimension
int num_on_board; // num of vals on board
int max; // max val for board dimension
int score; // total score
int high; // highest val reached
int num_turns;
int did_move; // if pieces actually moved


/*
    prints the game directions.
*/
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
    printf("'r' resets board. 'p <index> <value>' places value on board.\n");
    printf("'x' exits game.\n");
    printf("\n");
    printf("After a move, when two identical valued tiles come together they\n");
    printf("join to become a new single tile with the value of the sum of the\n");
    printf("two originals. This value gets added to the score.  On each move\n");
    printf("one new randomly chosen value of 2 or 4 is placed in a random open\n");
    printf("square.  User input of r restarts the game, and x exits the game.\n");
    printf("\n");
}


/*
    makes sure input is valid.
*/
int valid_in(char in) {
    if(in == 'w' || in == 'a' || in == 's' || in == 'd'
        || in == 'r' || in == 'x' || in == 'p') {
        return 1;
    }
    return 0;
}


/*
    places a specified val in a specified location. (cheaters only)
*/
void place(int i, int val) {
    int row = 0;

    while(i >= b_size) {
        i-=b_size;
        row++;
    }

    board[row][i] = val;

    if(val > high) {
        high = val;
    }
}


/*
    retrieves and checks user input.
*/
char get_input() {
    char out;

    do{
        printf("%d. Your move: ", num_turns);
        scanf(" %c", &out);
        out = tolower(out);

        if(!valid_in(out)) {
            printf("Invalid input please enter w,a,s,d,r,p, or x.\n");
        }

        if(out == 'p') {
            int i, val;
            scanf("%d%d", &i, &val);

            place(i, val);
        }
    } while(!valid_in(out));

    return out;
}


/*
    moves all pieces on the board up combining like numbers.
*/
void move_up() {
    int i, j;

    for(i = 1; i < b_size; i++) {
        for(j = 0; j < b_size; j++) {
            if(board[i][j] != -1) {
                int k;
                for(k = 1; k <= i; k++) {
                    if(board[i-k][j] == board[i-k+1][j]) {
                        board[i-k][j]*=2;
                        board[i-k+1][j] = -1;

                        if(board[i-k][j] > high) {
                            high = board[i-k][j];
                        }

                        score+=board[i-k][j];
                        did_move = 1;
                        break;
                    }
                    else if(board[i-k][j] == -1) {
                        board[i-k][j] = board[i-k+1][j];
                        board[i-k+1][j] = -1;
                        did_move = 1;
                    }
                    else {
                        break;
                    }
                }
            }
        }
    }
}


/*
    moves all vals down and combines accordingly.
*/
void move_down() {
    int i, j;

    for(i = b_size -2; i >= 0; i--) {
        for(j = 0; j < b_size; j++) {
            if(board[i][j] != -1) {
                int k;
                for(k = 1; i+k <= b_size-1; k++) {
                    if(board[i+k][j] == board[i+k-1][j]) {
                        board[i+k][j]*=2;
                        board[i+k-1][j] = -1;

                        if(board[i+k][j] > high) {
                            high = board[i+k][j];
                        }

                        score+=board[i+k][j];
                        did_move = 1;
                        break;
                    }
                    else if(board[i+k][j] == -1) {
                        board[i+k][j] = board[i+k-1][j];
                        board[i+k-1][j] = -1;
                        did_move = 1;
                    }
                    else {
                        break;
                    }
                }
            }
        }
    }
}


/*
    moves all vals right and combines accordingly.
*/
void move_right() {
    int i, j;

    for(i = 0; i < b_size; i++) {
        for(j = b_size -2; j >= 0; j--) {
            if(board[i][j] != -1) {
                int k;
                for(k = 1; j+k <= b_size-1; k++) {
                    if(board[i][j+k] == board[i][j+k-1]) {
                        board[i][j+k]*=2;
                        board[i][j+k-1] = -1;

                        if(board[i][j+k] > high) {
                            high = board[i][j+k];
                        }

                        score+=board[i][j+k];
                        did_move = 1;
                        break;
                    }
                    else if(board[i][j+k] == -1) {
                        board[i][j+k] = board[i][j+k-1];
                        board[i][j+k-1] = -1;
                        did_move = 1;
                    }
                    else {
                        break;
                    }
                }
            }
        }
    }
}


/*
    moves all vals left and combines accordingly.
*/
void move_left() {
    int i, j;

    for(i = 0; i < b_size; i++) {
        for(j = 1; j < b_size; j++) {
            if(board[i][j] != -1) {
                int k;
                for(k = 1; k <= j; k++) {
                    if(board[i][j-k] == board[i][j-k+1]) {
                        board[i][j-k]*=2;
                        board[i][j-k+1] = -1;

                        if(board[i][j-k] > high) {
                            high = board[i][j-k];
                        }

                        score+=board[i][j-k];
                        did_move = 1;
                        break;
                    }
                    else if(board[i][j-k] == -1) {
                        board[i][j-k] = board[i][j-k+1];
                        board[i][j-k+1] = -1;
                        did_move = 1;
                    }
                    else {
                        break;
                    }
                }
            }
        }
    }
}



/*
    determines what direction to move the peices.
*/
void make_move(char dir) {
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
}


/*
    picks a random row and column to place a new number.
*/
void plc_rnd() {
    int i, j;

    do{
        i = rand() % b_size;
        j = rand() % b_size;
    } while(board[i][j] != -1);

    if(num_on_board > 1) {
        int x = rand() % 2;
        if(x == 0) {
            board[i][j] = 2;
        }
        else {
            board[i][j] = 4;
        }
    }
    else {
        board[i][j] = 2;
    }

    num_on_board++;
}


/*
    set the val of max according to board size.
*/
void set_max() {
    max = 1024;

    int i;
    for(i = 4; i < b_size; i++) {
        max*=2;
    }
}


/*
    sets all global vals and initializes the board and max to
    the correct vals.
*/
void init_board() {
    board = (int**)malloc(sizeof(int*) * b_size);
    num_on_board = 0;
    num_turns = 0;
    did_move = 0;
    score = 0;
    high = 2;

    set_max();

    int i, j;
    for(i = 0; i < b_size; i++) {
        board[i] = (int*)malloc(sizeof(int) * b_size);

        for(j = 0; j < b_size; j++) {
            board[i][j] = -1;
        }
    }

    plc_rnd();
    plc_rnd();
}


/*
    prints out the content of the board
*/
void print_board() {
    int i, j;

    printf("Score: %d\n", score);
    for(i = 0; i < b_size; i++) {
        for(j = 0; j < b_size; j++) {
            if(board[i][j] == -1) {
                printf(" %3c", '.');
            }
            else {
                printf(" %3d", board[i][j]);
            }
        }
        printf("\n\n");
    }

    printf("\n\n");
}


/*
    frees the board
*/
void quit() {
    int i;
    for(i = 0; i < b_size; i++) {
        free(board[i]);
    }
    free(board);
}


int main() {
    srand(time(NULL));

    instructions();

    do {
        printf("Enter the size board you want, between 4 and 12: ");
        scanf("%d", &b_size);
    } while(b_size < 4 || b_size > 12);

    init_board();
    printf("Game ends when you reach %d.\n\n", max);

    int in;
    do {
        print_board();

        did_move = 0;
        num_turns++;
        in = get_input();

        if(in == 'x') {
            quit();
            return 0;
        }
        else if(in == 'r') {
            init_board();
        }
        else {
            make_move(in);
        }

        if(did_move == 1) {
            plc_rnd();
        }

        system("clear");
    } while(max > high);

    print_board();
    printf("*** You Win ***\n");
    quit();

    return 0;
}
