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

void print_heading(int num, char *s) {
    printf("Author: Brina Howe\n");
    printf("Lab: Thur 4pm\n");
    printf("Program: #%d, %s\n\n", num, s);
}

int main() {
    print_heading(2, "a game that guess your number correctly.");

    return 0;
}
