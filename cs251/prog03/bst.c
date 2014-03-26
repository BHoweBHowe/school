/*
 AUTH: Brian Howe

 DESC: a set of functions for binary search trees(bst)

 TODO:
*/

#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

struct bst_node {
    int val;
    int min; // smallest number in subtree
    int max; // largest number in subtree
    int size; // number of nodes in subtree including self.
    struct bst_node *left;
    struct bst_node *right;

};
typedef struct bst_node NODE;


struct bst {
    NODE *root;
};

BST_PTR bst_create(){
  BST_PTR t = malloc(sizeof(struct bst));
  t->root = NULL;
  return t;
}


// frees a node
static void free_r(NODE *r){
    if(r==NULL) return;
    free_r(r->left);
    free_r(r->right);
    free(r);
}


// frees a bst
void bst_free(BST_PTR t){
    free_r(t->root);
    free(t);
}


// inserts a node into a bst
static NODE * insert(NODE *r, int x){
    NODE *leaf;
    if(r == NULL){
      leaf = malloc(sizeof(NODE));
      leaf->left = NULL;
      leaf->right = NULL;
      leaf->val = x;
      leaf->size = 1;
      leaf->max = leaf->min = x; // tree has 1 elem so it is min and max
      return leaf;
    }

    if(r->val == x)
        return r;
    if(x < r->val){
        r->left = insert(r->left, x);
        r->size++;
        if(r->min > x) {
            r->min = x;
        }
        return r;
    }
    else {
        r->right = insert(r->right, x);
        r->size++;
        if(r->max < x) {
            r->max = x;
        }
        return r;
    }
}


void bst_insert(BST_PTR t, int x) {
    t->root = insert(t->root, x);
}


// checks if the value x is in the bst
int bst_contains(BST_PTR t, int x){
    NODE *p = t->root;

    while(p != NULL){

        if(p->val == x)
            return 1;
        if(x < p->val){
            p = p->left;
        }
        else
            p = p->right;
    }
    return 0;
}


int min_h(NODE *r){
  return r->min;
}


int max_h(NODE *r){
  return r->max;
}



static NODE *remove_r(NODE *r, int x, int *success){
NODE   *tmp;
int sanity;

  if(r==NULL){
    *success = 0;
    return NULL;
  }
  if(r->val == x){
    *success = 1;

    if(r->left == NULL){
        tmp = r->right;
        free(r);
        return tmp;
    }
    if(r->right == NULL){
        tmp = r->left;
        free(r);
        return tmp;
    }
    // if we get here, r has two children
    r->val = min_h(r->right);
    r->right = remove_r(r->right, r->val, &sanity);
    if(!sanity)
        printf("ERROR:  remove() failed to delete promoted value?\n");
    return r;
  }
  if(x < r->val){
    r->left = remove_r(r->left, x, success);
    if(r->left != NULL) { // updates min tree vals
        r->min = r->left->min;
    }
    else {
        r->min = r->val;
    }
  }
  else {
    r->right = remove_r(r->right, x, success);
    if(r->right != NULL) { // updates max tree vals
        r->max = r->right->max;
    }
    else {
        r->max = r->val;
    }
  }
  r->size--;
  return r;
}


// remove node with val x from tree
int bst_remove(BST_PTR t, int x){
    int success;
    t->root = remove_r(t->root, x, &success);
    return success;
}

// returns nuber of nodes in tree of root r.
int size(NODE *r){
    return r->size;
}


// returns the number of nodes in a tree
int bst_size(BST_PTR t){
    return size(t->root);
}


// returns the height of the tree
static int height(NODE *r){
    int l_h, r_h;

    if(r==NULL) return -1;
    l_h = height(r->left);
    r_h = height(r->right);
    return 1 + (l_h > r_h ? l_h : r_h);

}
int bst_height(BST_PTR t){
    return height(t->root);

}


// return lowest number in tree
int bst_min(BST_PTR t){
    return min_h(t->root);
}


// return largest number in tree
int bst_max(BST_PTR t){
    return max_h(t->root);
}


// prints '-' m times
static void indent(int m){
    int i;
    for(i=0; i<m; i++)
        printf("-");
}


// prints tree nodes in order
static void inorder(NODE *r){
  if(r==NULL) return;
  inorder(r->left);
  printf("[%d] (size=%d, min=%d, max=%d)\n", r->val, r->size, r->min, r->max);
  inorder(r->right);

}
void bst_inorder(BST_PTR t){

  printf("========BEGIN INORDER============\n");
  inorder(t->root);
  printf("=========END INORDER============\n");

}


// prints tree in preorder
static void preorder(NODE *r, int margin){
  if(r==NULL) {
    indent(margin);
    printf("NULL \n");
  } else {
    indent(margin);
    printf("%d (size=%d, min=%d, max=%d))\n", r->val, r->size, r->min, r->max);
    preorder(r->left, margin+3);
    preorder(r->right, margin+3);
  }
}
void bst_preorder(BST_PTR t){

  printf("========BEGIN PREORDER============\n");
  preorder(t->root, 0);
  printf("=========END PREORDER============\n");

}



/* TODO
 * Complete the (recursive) helper function for the post-order traversal.
 * Remember: the indentation needs to be proportional to the height of the node!
 */
static void postorder(NODE *r, int margin){
  if(r!=NULL) {
    postorder(r->left, margin+3);
    postorder(r->right, margin+3);
    indent(margin);
    printf("%d (size=%d, min=%d, max=%d)\n", r->val, r->size, r->min, r->max);
  }
  else {
    indent(margin);
    printf("NULL \n");
  }
}
// indentation is proportional to depth of node being printed
//   depth is #hops from root.
void bst_postorder(BST_PTR t){

  printf("========BEGIN POSTORDER============\n");
  postorder(t->root, 0);
  printf("=========END POSTORDER============\n");

}


/* TODO:
 * Write the (recursive) helper function from_arr, used by
 * bst_from_sorted_arr(...). The function must return a sub-tree that is
 * perfectly balanced, given a sorted array of elements a.
 */
static NODE * from_arr(int *a, int n){
    NODE *r = malloc(sizeof(NODE));

    if(n==1) {
        r->val = a[0];
        r->right = NULL;
        r->left = NULL;
        r->max = r->min = a[0];
        r->size = n;
        return r;
    }

    if(n==2) {
        r->val = a[1];
        r->right = NULL;
        r->left = from_arr(a, 1);
        r->max = a[1];
        r->min = a[0];
        r->size = n;
        return r;
    }

    int mid = n/2;

    r->val = a[mid];
    r->max = a[n-1];
    r->min = a[0];
    r->right = from_arr(&a[mid+1], n-(mid+1));
    r->left = from_arr(a, mid);
    r->size = n;
    return r;
}

BST_PTR bst_from_sorted_arr(int *a, int n){

  BST_PTR t = bst_create();

  t->root = from_arr(a, n);

  return t;
}


/* allocates an integer array, populates it with the elements
 of t (in-order) and returns the array as an int pointer */
void to_array_r(NODE *n, int *arr) {
    NODE *r = n->right;
    NODE *l = n->left;

    if(l == NULL) { // lowest value in tree
        arr[0] = n->val;
        if(r != NULL) {
            to_array_r(r, &arr[1]);
        }
        return;
    }

    arr[l->size] = n->val; // num elem in left leaf is mun elem before n in array.
    to_array_r(l, arr);

    if(r != NULL) {
        to_array_r(r, &arr[n->size - r->size]);
    }
}
int * bst_to_array(BST_PTR t) {
    int *arr = malloc(sizeof(int) * size(t->root));
    to_array_r(t->root, arr);
    return arr;
}


/* returns the ith smallest element in t. i ranges from 1..n where n is
 the number of elements in the tree. If i is outside this range, an error
 message is printed to stderr and the return value is arbitrary (you may return
 whatever you like, but it has no meaning. Runtime: O(h) where h is the tree height*/
int get_ith_r(NODE *n, int i) {
    int size = n->size;
    if(i < 1 || n == NULL) {
        fprintf(stderr, "Element i out of bounds\n");
        return 1;
    }
    NODE *l = n->left;
    NODE *r = n->right;

    if(l == NULL) { // lowest val in tree
        if(i == 1) {
            return n->val;
        }
        return get_ith_r(r, i-1);
    }
    if(l->size < i) { // all left are less than i
        if((size - l->size) == i) { // i is the root node
            return n->val;
        }
        return get_ith_r(r, (i-1) - l->size);
    }
    return get_ith_r(l, i); // continue left
}
int bst_get_ith(BST_PTR t, int i) {
    return get_ith_r(t->root, i);
}


/* returns the value in the tree closest to x -- in other words, some y
 in the three where |x-y| is minimum. If the tree is empty, a message
 is sent to stderr and the return value is of your choosing.
 Runtime: O(h) where h is the tree height.*/
int get_nearest_r(NODE *n, int x) {
    if(n == NULL) { // tree empty
        fprintf(stderr, "Tree empty\n");
        return -1;
    }
    if(x == n->val) {
        return x;
    }
    if(x >= n->max) { // x is larger than all vals in tree
        return n->max;
    }
    if(x <= n->min) { // x is smaller than all vals in tree
        return n->min;
    }

    // if it gets here the tree has atleast 1 child
    int tmp = 0;
    if(x > n->val && n->right != NULL) { // x is between n->val +1 and right->max
        tmp = get_nearest_r(n->right, x);
    }
    else { // x is between n->val -1 and left->min
        tmp = get_nearest_r(n->left, x);
    }

    if(abs(n->val - x) < abs(tmp - x)) { // x is closer to n->val
        return n->val;
    }
    return tmp; // x is closer to tmp
}
int bst_get_nearest(BST_PTR t, int x){
    return get_nearest_r(t->root, x);
}


/* returns the number of elements in t which are greater than or equal to x.
 Runtime: O(h) where h is the tree height*/
int num_geq_r(NODE *n, int x) {
    if(n == NULL) {
        return 0;
    }
    if(x <= n->val) {
        if(n->right == NULL) {
            return 1 + num_geq_r(n->left, x);
        }
        return (n->right->size + 1) + num_geq_r(n->left, x); // all elem to the right are
    }                                                           // greater or equal to x
    return num_geq_r(n->right, x);
}
int bst_num_geq(BST_PTR t, int x) {
    return num_geq_r(t->root, x);
}


/* returns the number of elements in t which are less than or equal to x.
 Runtime: O(h) where h is the tree height*/
int num_leq_r(NODE *n, int x) {
    if(n == NULL) {
        return 0;
    }
    if(x >= n->val) {
        if(n->left == NULL) {
            return 1 + num_leq_r(n->right, x);
        }
        return (n->left->size + 1) + num_leq_r(n->right, x); // all elem to the left are
    }                                                           // less or equal to x
    return num_leq_r(n->left, x);
}
int bst_num_leq(BST_PTR t, int x) {
    return num_leq_r(t->root, x);
}
