// Note:  struct sset_struct is "hidden" in
//   sset.c
typedef struct sset_struct SSET;

/**
* Returns an empty set
* DONE
*/
extern SSET *sset_create();

/**
* Returns a set containing just x.
* DONE
*/
extern SSET *sset_singleton(int x);


/**
* takes an array of integers in arbitrary order (and
*   maybe containing duplicates) and returns an SSET
*   of the set
*   sets *a and *b;
* sets a and b are unchanged.
* TODO:  function complete but you have to write
*        helper function from_sorted_array()
*/
extern SSET *sset_from_array(int *a, int n);

/**
* DONE
*/
extern int sset_isempty(SSET *s);

/**
* DONE
*/
extern int sset_size(SSET *s);

/**
* DONE
*/
extern void sset_display(SSET *s);

/*
* TODO
*/
extern int sset_contains(SSET *s, int x);

/*
* TODO
*/
extern void sset_free(SSET *s);

/**
* returns a sorted set representing the UNION of
*   sets *a and *b;
* sets a and b are unchanged.
* DONE
*/
extern SSET *sset_union(SSET *a, SSET *b);

/**
* TODO
* returns a sorted set representing the INTERSECTION of
*   sets a and b;
* sets a and b are unchanged.
*/
extern SSET *sset_intersection(SSET *a, SSET *b);

/**
* TODO
* returns a sorted set representing the set DIFFERENCE of
*   a - b  (the set of elements in *a which are NOT in *b)
* sets a and b are unchanged.
*
* Example:  {3, 7, 11, 14} - {3, 5, 11, 20} = {7, 11}
*
*/
extern SSET *sset_diff(SSET *a, SSET *b);

/**
* TODO
* allocates and returns an array containing the elements of *a
*   in sorted order.
*/
extern int *sset_toarray(SSET *a);


/**
* TODO
* Compares sets a and b "lexicographically" and returns
*   a negative number if "a < b";
*   a positive number if "a > b"
*   zero if they are identical
*
*/
extern int sset_cmp(SSET *a, SSET *b);

