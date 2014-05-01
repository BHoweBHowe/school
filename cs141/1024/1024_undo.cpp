/* ------------------------------------------------
*
* Class: CS 141, Spring 2014.  Thur. 4pm lab.
* System: Linux Mint, g++
* Author: Brian Howe
*
* TODO: When the board fills up the game does not
* end. no moves can be made but input is still allowed.
* max val must be reached to end game. (or enter 'x')
* -------------------------------------------------
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

typedef struct board_struct {
    int **board;
    int num_on_board;
    int score;
    int high;
    board_struct *prev;
} BOARD;

int b_size; // board dimension
int max; // max val for board dimension
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
        || in == 'r' || in == 'x' || in == 'p' || in == 'u') {
        return 1;
    }
    return 0;
}


/*
    places a specified val in a specified location. (cheaters only)
*/
void place(BOARD *h, int i, int val) {
    int row = 0;

    while(i >= b_size) {
        i-=b_size;
        row++;
    }

    h->board[row][i] = val;

    if(val > h->high) {
        h->high = val;
    }
}


/*
    retrieves and checks user input.
*/
char get_input(BOARD *h) {
    char out;

    do{
        printf("%d. Your move: ", num_turns);
        scanf(" %c", &out);
        out = tolower(out);

        if(!valid_in(out)) {
            printf("Invalid input please enter w,a,s,d,r,p,u, or x.\n");
        }

        if(out == 'p') {
            int i, val;
            scanf("%d%d", &i, &val);

            place(h, i, val);
        }
        else if(out == 'u') {
            if(h->prev == NULL) {
                printf("*** You cannot undo at the beginning of the game. Retry.\n");
                out = 'i';
            }
        }
    } while(!valid_in(out));

    return out;
}


/*
    moves all pieces on the board up combining like numbers.
*/
void move_up(BOARD *h) {
    int i, j;

    for(i = 1; i < b_size; i++) {
        for(j = 0; j < b_size; j++) {
            if(h->board[i][j] != -1) {
                int k;
                for(k = 1; k <= i; k++) {
                    if(h->board[i-k][j] == h->board[i-k+1][j]) {
                        h->board[i-k][j]*=2;
                        h->board[i-k+1][j] = -1;

                        if(h->board[i-k][j] > h->high) {
                            h->high = h->board[i-k][j];
                        }

                        h->score+=h->board[i-k][j];
                        did_move = 1;
                        break;
                    }
                    else if(h->board[i-k][j] == -1) {
                        h->board[i-k][j] = h->board[i-k+1][j];
                        h->board[i-k+1][j] = -1;
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
void move_down(BOARD *h) {
    int i, j;

    for(i = b_size -2; i >= 0; i--) {
        for(j = 0; j < b_size; j++) {
            if(h->board[i][j] != -1) {
                int k;
                for(k = 1; i+k <= b_size-1; k++) {
                    if(h->board[i+k][j] == h->board[i+k-1][j]) {
                        h->board[i+k][j]*=2;
                        h->board[i+k-1][j] = -1;

                        if(h->board[i+k][j] > h->high) {
                            h->high = h->board[i+k][j];
                        }

                        h->score+=h->board[i+k][j];
                        did_move = 1;
                        break;
                    }
                    else if(h->board[i+k][j] == -1) {
                        h->board[i+k][j] = h->board[i+k-1][j];
                        h->board[i+k-1][j] = -1;
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
void move_right(BOARD *h) {
    int i, j;

    for(i = 0; i < b_size; i++) {
        for(j = b_size -2; j >= 0; j--) {
            if(h->board[i][j] != -1) {
                int k;
                for(k = 1; j+k <= b_size-1; k++) {
                    if(h->board[i][j+k] == h->board[i][j+k-1]) {
                        h->board[i][j+k]*=2;
                        h->board[i][j+k-1] = -1;

                        if(h->board[i][j+k] > h->high) {
                            h->high = h->board[i][j+k];
                        }

                        h->score+=h->board[i][j+k];
                        did_move = 1;
                        break;
                    }
                    else if(h->board[i][j+k] == -1) {
                        h->board[i][j+k] = h->board[i][j+k-1];
                        h->board[i][j+k-1] = -1;
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
void move_left(BOARD *h) {
    int i, j;

    for(i = 0; i < b_size; i++) {
        for(j = 1; j < b_size; j++) {
            if(h->board[i][j] != -1) {
                int k;
                for(k = 1; k <= j; k++) {
                    if(h->board[i][j-k] == h->board[i][j-k+1]) {
                        h->board[i][j-k]*=2;
                        h->board[i][j-k+1] = -1;

                        if(h->board[i][j-k] > h->high) {
                            h->high = h->board[i][j-k];
                        }

                        h->score+=h->board[i][j-k];
                        did_move = 1;
                        break;
                    }
                    else if(h->board[i][j-k] == -1) {
                        h->board[i][j-k] = h->board[i][j-k+1];
                        h->board[i][j-k+1] = -1;
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
    creates a new copy of the board to be modified
*/
BOARD *new_board(BOARD *h) {
    BOARD *n = (BOARD*)malloc(sizeof(BOARD));

    n->board = (int**)malloc(sizeof(int*) * b_size);

    int i, j;
    for(i = 0; i < b_size; i++) {
        n->board[i] = (int*)malloc(sizeof(int) * b_size);

        for(j = 0; j < b_size; j++) {
            n->board[i][j] = h->board[i][j];
        }
    }

    n->num_on_board = h->num_on_board;
    n->score = h->score;
    n->high = h->high;
    n->prev = h;

    return n;
}


/*
    determines what direction to move the peices.
*/
BOARD *make_move(BOARD *h, char dir) {
    BOARD *n = new_board(h);

    if(dir == 'w') {
        move_up(n);
    }
    else if(dir == 'a') {
        move_left(n);
    }
    else if(dir == 's') {
        move_down(n);
    }
    else if(dir == 'd') {
        move_right(n);
    }

    if(did_move) {
        h = n;
    }

    return h;
}


/*
    picks a random row and column to place a new number.
*/
void plc_rnd(BOARD *h) {
    int i, j;

    do{
        i = rand() % b_size;
        j = rand() % b_size;
    } while(h->board[i][j] != -1);

    if(h->num_on_board > 1) {
        int x = rand() % 2;
        if(x == 0) {
            h->board[i][j] = 2;
        }
        else {
            h->board[i][j] = 4;
        }
    }
    else {
        h->board[i][j] = 2;
    }

    h->num_on_board++;
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
BOARD *init_board(BOARD *h) {
    h = (BOARD*)malloc(sizeof(BOARD));
    h->board = (int**)malloc(sizeof(int*) * b_size);
    h->num_on_board = 0;
    num_turns = 0;
    did_move = 0;
    h->score = 0;
    h->high = 2;
    h->prev = NULL;

    set_max();

    int i, j;
    for(i = 0; i < b_size; i++) {
        h->board[i] = (int*)malloc(sizeof(int) * b_size);

        for(j = 0; j < b_size; j++) {
            h->board[i][j] = -1;
        }
    }

    plc_rnd(h);
    plc_rnd(h);

    return h;
}


/*
    prints out the content of the board
*/
void print_board(BOARD *h) {
    int i, j;

    printf("Score: %d\n", h->score);
    for(i = 0; i < b_size; i++) {
        for(j = 0; j < b_size; j++) {
            if(h->board[i][j] == -1) {
                printf(" %3c", '.');
            }
            else {
                printf(" %3d", h->board[i][j]);
            }
        }
        printf("\n\n");
    }

    printf("\n\n");
}


/*
    goes to the previous board if prev is not NULL
*/
BOARD *undo(BOARD *h) {
    if(h->prev == NULL) {
        return h;
    }

    int i;
    for(i = 0; i < b_size; i++) {
        free(h->board[i]);
    }
    free(h->board);

    return h->prev;
}


/*
    frees the board
*/
void free_all(BOARD *h) {
    int i;

    while(h != NULL) {
        for(i = 0; i < b_size; i++) {
            free(h->board[i]);
        }
        free(h->board);
        h = h->prev;
    }
}


int main() {
    srand(time(NULL));

    BOARD *head = NULL;

    instructions();

    do {
        printf("Enter the size board you want, between 4 and 12: ");
        scanf("%d", &b_size);
    } while(b_size < 4 || b_size > 12);

    head = init_board(head);
    printf("Game ends when you reach %d.\n\n", max);

    int in;
    do {
        print_board(head);

        did_move = 0;
        num_turns++;
        in = get_input(head);

        if(in == 'x') {
            free_all(head);
            return 0;
        }
        else if(in == 'r') {
            free_all(head);
            head = init_board(head);
        }
        else if(in == 'u'){
            head = undo(head);
        }
        else {
            head = make_move(head, in);
        }

        if(did_move == 1) {
            plc_rnd(head);
        }

        system("clear");
    } while(max > head->high);

    print_board(head);
    printf("*** You Win ***\n");
    free_all(head);

    return 0;
}
