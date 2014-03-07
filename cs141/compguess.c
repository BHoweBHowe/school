/* ----------------------------------------------
 * brief description
 *
 * Class: cs 141, Spring 2014, Thur 4pm lab.
 * System: CentOS 6.5 x86, g++
 * Author: Brian Howe
 *
 * ToDo: What was im supposed to accomplish
 */

#include <stdio.h>
#include <stdlib.h>

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })

void printHeading(int num, char *s) {
    printf("Author: Brina Howe\n");
    printf("Lab: Thur 4pm\n");
    printf("Program: #%d, %s\n\n", num, s);
}

int most_common(int *a, int j, int k) {
    int com = 0;
    int i;

    for(i = 0; i < 10; i++) {
        if(a[i] > a[com] && (i != j || i != k)) {
             com = i;
        }
        printf("com=%d, i=%d, a[com]=%d, a[i]=%d\n", com, i, a[com], a[i]);
    }

    return com;
}

void guess() {
    int g1, g2, g3, ip, op, x, sum;
    int a[10];

    int i;
    for(i = 0; i < 10; i++) {
        a[i] = 0;
    }

    g1 = 0;
    g2 = 1;
    g3 = 2;
    ip = 0;
    op = 0;
    x = 0;

    while(x < 10) {
        printf("%d. The computers guessed: %d%d%d\n", x+1, g1, g2, g3);
        printf("        Amount in position: ");
        scanf("%d", &ip);
        printf("        Amount out of position: ");
        scanf("%d", &op);

        sum = ip + op;

        if(ip == 3) {
            printf("The computer guessed your number! It was %d%d%d!\n",
                g1, g2, g3);
            x = 10;
        }
        else if(sum == 3) {
            sum = g1;
            g1 = g3;
            g3 = g2;
            g2 = sum;
            x++;
        }
        else if(sum == 0 && x < 3) {
            if(max(g1, max(g2, g3)) < 7) {
                g1+=3;
                g2+=3;
                g3+=3;
            }
            else {
                g1 = 7;
                g2 = 8;
                g3 = 9;
            }
            x++;
        }
        else {
            a[g1] = sum;
            a[g2] = sum;
            a[g3] = sum;

            if(x < 8) {
                do {
                    g1 = most_common(a, -1, -1);
                    g2 = most_common(a, -1, g1);
                    g3 = most_common(a, g1, g2);
                }while(g1 == g2 || g1 == g3 || g3 == g2);
            }
            else {
                g1 = g1+1;
                g2 = g2+1;
                g3 = g3+1;
            }
            x++;
        }
    }

    if(x == 10) {
        printf("*** Congradulations! The computer couldn't guess your number! ***\n");
    }
}

int main() {
    char magicNum[3];

    printHeading(2, "a game that trys to guess your number correctly.");

    printf("Please enter a 3 digit number: ");
    scanf("%s", magicNum);
    printf("The number you entered was %s. Please remeber it and be honest.\n\n",
        magicNum);

    guess();

    printf("Game Over. Exiting...\n");

    return 0;
}
