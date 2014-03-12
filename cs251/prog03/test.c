/*
 AUTH:  Brian Howe

 DESC: tests the functions of the binary search tree(bst) datatype.

 TODO: more test cases.
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"


// prints array of numbers
void print_arr(int *a, int n) {
    int i;
    printf("bst_to_array = {");
    for(i = 0; i < n; i++) {
        printf("%d,", a[i]);
    }
    printf("\b}\n");
}


int main(){
    int i;

    /* PART 1 */

    int a[] = {8, 2, 6, 9, 11, 3, 7};

    BST_PTR t = bst_create();

    for(i=0; i<7; i++)
        bst_insert(t, a[i]);

    assert(bst_size(t) == 7);

    // test bst_to_array
    int *b = bst_to_array(t);
    print_arr(b, 7);
    free(b);

    // test min, max, size
    printf("Tree info {size = %d, min = %d, max = %d}\n",
                                                bst_size(t),
                                                bst_min(t),
                                                bst_max(t));
    printf("2nd smallest element is: %d\n", bst_get_ith(t,2));

    bst_inorder(t);
    // test bst_num_leq and bst_num_geq
    printf("num elements less or equal to 10: %d\n", bst_num_leq(t, 10));
    printf("num elements greater or equal to 6: %d\n", bst_num_geq(t, 6));
    //test bst_get_nearest
    printf("element closest to 4: %d\n", bst_get_nearest(t, 4));

    bst_postorder(t);

    bst_free(t);

    /* Second bst */

    int sorted_a[] = {2,6,10,15,17,22,30};

    t = bst_from_sorted_arr(sorted_a, 7);

    // test bst_get_ith
    printf("3rd smallest element is: %d\n", bst_get_ith(t,3));

    bst_inorder(t);

    // test bst_num_geq
    printf("num elements greater or equal to 16: %d\n", bst_num_geq(t, 16));
    // test bst_num_leq
    printf("num elements less or equal to 9: %d\n", bst_num_leq(t, 9));
    // test bst_get_nearest
    printf("num closest to 20: %d\n", bst_get_nearest(t, 20));
    // test remove
    bst_remove(t, 22);
    // test bst_get_nearest
    printf("num closest to 20: %d\n", bst_get_nearest(t, 20));

    bst_inorder(t);

    bst_free(t);
}
