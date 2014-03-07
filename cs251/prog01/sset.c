/*
* Brian Howe
* cs251, project1
*/

#include "sset.h"
#include "stdlib.h"
#include "stdio.h"

#define DEBUG

struct sset_struct{
 int val;
 struct sset_struct *next;
};


/**
* DONE
* Returns an empty set
*/
SSET *sset_create(){
 return NULL;
}

SSET *sset_singleton(int x) {
SSET *p;

 p = malloc(sizeof(SSET));
 p->val = x;
 p->next = NULL;
 return p;
}

/**
* Used by qsort
*/
static int int_cmp(const void *a, const void *b) {

 int *pa = (int *)a;
 int *pb = (int *)b;

 return (*pa - *pb);
}

/**
* TODO
* Requirement:  linear time
* Recommendation:  recursion
*/
static SSET *from_sorted_array(int *a, int n) {
    SSET *s = sset_singleton(a[0]);
    if(a[0] == a[n-1]) {
        return s;
    }
    else {
        s->next = from_sorted_array(&a[1],n-1);
        return s;
    }
}

static void print_arr(int *a, int n) {
int i;
 printf("[ ");
 for(i=0; i<n; i++)
    printf("%i ", a[i]);
 printf("]\n");
}

SSET *sset_from_array(int *a, int n) {
int *b, *c;
int i, j, x;
SSET *s;

 b = malloc(n*sizeof(int));
 c = malloc(n*sizeof(int));
 
 for(i=0; i<n; i++)
   b[i] = a[i];
 qsort(b, n, sizeof(int), int_cmp);

 i=0; j=0;

 // copy elements w/o duplicats from b[] to c[] (retaining
 //   sorted order
 while(i < n) {
   x = b[i];
   c[j] = x;
   i++; j++;

   while(i < n && b[i] == x)
i++;
 }
#ifdef DEBUG
 printf("---start debug---\n");
 printf("sset_from_array:\n");
 printf("       a: ");
 print_arr(a, n);
 printf("       b: ");
 print_arr(b, n);
 printf("       c: ");
 print_arr(c, j);
 printf("---end debug---\n");
#endif

 s = from_sorted_array(c, j);

 free(b);
 free(c);
 return s;
}
 
 
/**
* TODO
* Requirements:  linear time
*                recursive
*/
void sset_free(SSET *s) {
    if(s->next != NULL) {
        sset_free(s->next);
        s->next = NULL;
    }
    free(s);
}

/**
* DONE
*/
int sset_isempty(SSET *s) {
return s==NULL;
}

/**
* DONE
*/
int sset_size(SSET *s) {
 if(s == NULL) return 0;
 return 1 + sset_size(s->next);
}

/**
* DONE
*/
void sset_display(SSET *s) {
 printf("  { ");
 while(s != NULL) {
printf("%i ", s->val);
s = s->next;
 }
 printf("}\n");
}


/**
* TODO
*   Returns 0 or 1 accordingly
*   Requirement:  linear time
*   Recommendation:  recursion
*/
int sset_contains(SSET *s, int x) {
    if(s->val == x) {
        return 1;
    }
    else
    {
        if(s->next != NULL) {
            return sset_contains(s->next, x);
        }
        else {
            return 0;
        }
    }
}

/**
* DONE
*/
SSET *sset_clone(SSET *s) {
 SSET *p;
 if(s == NULL)
return NULL;
 p = malloc(sizeof(struct sset_struct));
 p->val = s->val;
 p->next = sset_clone(s->next);
 return p;
}

/**
* DONE
*/
SSET *sset_union(SSET *a, SSET *b) {
SSET *p;

 if(a == NULL)
return sset_clone(b);
 if(b == NULL)
return sset_clone(a);
 p = malloc(sizeof(SSET));
 if(a->val < b->val){
p->val = a->val;
p->next = sset_union(a->next, b);
 }
 else if(a->val > b->val){
p->val = b->val;
p->next = sset_union(a, b->next);
 }
 else {
p->val = a->val;
p->next = sset_union(a->next, b->next);
 }
 return p;
}

/**
* TODO
* Requirements:  linear time
*                recursive
*/
SSET *sset_intersection(SSET *a, SSET *b) {
    SSET *p;

    if(a == NULL || b == NULL) {
        return NULL;
    }
    p = malloc(sizeof(SSET));
    if(a->val > b->val) {
        p = sset_intersection(a, b->next);
    }
    else if(b->val > a->val) {
        p = sset_intersection(a->next, b);
    }
    else {
        p->val = a->val;
        p->next = sset_intersection(a->next, b->next);
    }

    return p;
}

/**
* TODO
* Requirements:  linear time
*                recursive
*
*  A - B = {x in A s.t. x NOT-IN B}
*
* Example:  {3, 7, 11, 14} - {3, 5, 11, 20} = {7, 11}
*/
SSET *sset_diff(SSET *a, SSET *b) {
    SSET *p;

    if(a == NULL) {
        return sset_clone(b);
    }
    if(b == NULL) {
        return sset_clone(a);
    }
    p = malloc(sizeof(SSET));
    if(a->val < b->val) {
        p->val = a->val;
        p->next = sset_diff(a->next, b->next);
    }
    else if(b->val < a->val) {
        p->val = b->val;
        p->next = sset_diff(a, b->next);
    }
    else {
        p = sset_diff(a->next, b->next);
    }

    return p;
}

/**
* TODO
* allocates and returns an array containing the elements of *a
*   in sorted order.
* Requirement:  linear time
*/
int *sset_toarray(SSET *a) {
    int i, n;
    n = sset_size(a);

    int *b = malloc(n * sizeof(int));

    for(i = 0; i < n; i++) {
        b[i] = a->val;
        a = a->next;
    }
    return b;
}

/**
* TODO
* Requirements:  linear time
*                recursive
*
* Compares sets a and b lexicographically (essentially like alphabetical).
*
*    If "a < b", a negative number is returned.
*    if "a > b", a positive number is returned.
*    if a and b are identical, zero is returned.
*
*    Lex rules:
*       The empty set precedes all other sets
*       For non-empty A={a0, ...}, B={b0, ...}, compare a0 and b0
*
*           - if a0 != b0 set with smallest first elem "wins"
*           - otherwise, compare A-{a0} with B-{b0}
*
*     Example:
*              A = {2, 3, 5, 8, 10, 11}
*              B = {2, 3, 5, 7, 1000, 2000, 30000}
*
*             we have ties on frst 3 elements; then 7<8 so B < A.
*
*     Example:
*              A = {2, 3, 5}
*              B = {2, 3, 5, 7, 1000 }
*
*             Again, ties on first three elements; then we are comparing {} with
*             {7, 1000} so A < B
*
*  Note:  in the future you will tweak this function so it can be passed to
*    qsort so we can sort arrays of SSETs.
*
*/
int sset_cmp(SSET *a, SSET *b){
    if(a == NULL && b == NULL) {
        return 0;
    }
    else if(a == NULL && b != NULL) {
        return -1;
    }
    else if(a != NULL && b == NULL) {
        return 1;
    }
    if(a->val > b->val) {
        return 1;
    }
    else if(b->val > a->val) {
        return -1;
    }
    else {
        return sset_cmp(a->next, b->next);
    }
}


