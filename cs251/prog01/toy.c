#include "sset.h"
#include <stdlib.h>
#include <stdio.h>

int main(){
    SSET *s1, *s2, *s3, *s4;
    int n, *c;

    int a[] = {2, 8, 1, 3, 1, 8, 0, 4};
    int b[] = {5, 4, 3, 2, 1, 0, 9, 8, 7, 6};
    int d[] = {30, 4, 13, 2, 6, 47, 345, 5};

    printf("Sorting...\n\n");

    s1 = sset_from_array(a, 8);
    s2 = sset_from_array(b, 10);
    s4 = sset_from_array(d, 8);

    printf("sset_intersection\n");

    sset_display(s2);
    sset_display(s4);
    s3 = sset_intersection(s2, s4);
    sset_display(s3);

    printf("comparing...\n\n");

    if(sset_contains(s1, 3)) {
        sset_display(s1);
        c = sset_toarray(s2);
        n = 10;
    }
    else {
        sset_display(s2);
        c = sset_toarray(s1);
        n = 6;
    }

    printf("freeing...\n\n");

    sset_free(s2);

    printf("sset_from_array\n");

    s3 = sset_from_array(c, n);
    sset_display(s3);
    sset_display(s1);

    printf("sset_diff\n");

    s2 = sset_diff(s1, s3);
    sset_display(s2);

    printf("sset_cmp\n");

    s3 = s2;
    s2 = s1;
    s1 = s3;

    int x = sset_cmp(s1, s2);

    if(x == 1) {
        printf("s1:");
        sset_display(s1);
        printf("is larger.\n");
    }
    else if(x == -1) {
        printf("s2:");
        sset_display(s2);
        printf("is larger.\n");
    }
    else {
        printf("The sets are equal.\n");
    }

    return 0;
}

