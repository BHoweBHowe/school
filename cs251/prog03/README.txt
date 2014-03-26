Name: Brian Howe

-----------------------------------------------

Describe what augmentations to the bst data structures you made to complete the
project -- i.e., what typedefs did you change and why?

  The only changes to the structs that i made was the addition of three ints to the bst_node struct.
int min which keeps track of the lowest value in that nodes sub-tree. int max which keeps track of the largest
value in that nodes sub-tree. and int size which keeps track of the number of nodes in the sub-tree.


-----------------------------------------------
Which functions did you need to modify as a result of the augmentations from the previous
question? 

  Since i added these new variables to the node struct i had to change the insert_r and remove_r functions.

-----------------------------------------------
For each function from the previous question, how did you ensure that the (assymptotic) runtime
remained the same?

  insert_r was able to keep its oringinal runtime because all that needed to be added was an increment for the
tree size and a comparison to see which number was larger or smaller followed by an assignment to min or max.

  remove_r was a little trickier. The size of the tree needed to be decreased by one which was simple but keeping
the min and max up to date was harder. this was accomplished by two if else statments and an assignment statment.

  All changes to both functions were of constant time so the assymptotic runtime was not effected.


-----------------------------------------------
For each of the assigned functions, tell us how far you got using the choices 0-5 and
answer the given questions. 


0:  didn't get started
1:  started, but far from working
2:  have implementation but only works for simple cases
3:  finished and I think it works most of the time but not sure the runtime req is met.
4:  finished and I think it works most of the time and I'm sure my design leads to
       the correct runtime (even if I still have a few bugs).
5:  finished and confident on correctness and runtime requirements


bst_to_array level of completion:  ______5____ 


-----------------------------------------------
bst_get_ith level of completion:  _______5___ 

    How did you ensure O(h) runtime?

    ANSWER: runtime was ensured by checking the size of the tree to the left and comparing it to i.  if the size
    was greater then the function went left if it was less than i then the function went right. this ensured that only
    one node on each level of the tree was visited keeping the runtime O(h).

-----------------------------------------------
bst_get_nearest level of completion:  ______5____ 

    How did you ensure O(h) runtime?

    ANSWER: runtime was ensured by checking if the value passed in was equal to the value of the node. if not the search went left
    if it was less than the node value or right if it was greater than the node value. This means that each level in the
    tree was only visited once making the runtime O(h).
 
-----------------------------------------------
bst_num_geq level of completion:  ______5____ 

    How did you ensure O(h) runtime?

    ANSWER: If the value passed in is greater than the value of the node then the search moves to the right child.
    if the value is less than the value of the node then we know that all nodes to the right are also greater
    so the search moves left. by visiting only one child of the node it ensures that the runtime will be O(h).

-----------------------------------------------
bst_num_leq level of completion:  ______5_____

    How did you ensure O(h) runtime?

    ANSWER: iF the value passed in is less than the value of the node then the search moves to the left child.
    if the value is greater than the value of the node then we know that all nodes to the left are also less than
    the value so the search moves right. by visting only one child of the node it ensures that the run time will
    be O(h).

-----------------------------------------------
EXTRA CREDIT FUNCTIONS:

bst_min level of completion:  ________5____

    How did you ensure O(1) runtime?

    ANSWER: the function just accesses and returns the value in t->r->min making the runtime O(1).

-----------------------------------------------
bst_max level of completion:  ________5___

    How did you ensure O(1) runtime?

    ANSWER: the function just accesses and returns the value in t->r->max making the runtime constant.

----------------------------------------------

Write a few sentences describing how you tested your solutions.  Are there
any tests that in retrospect you wish you'd done?

i tested my solutions by modifying the inorder function to also print out all the info of the node(size, min, max). This
helped me make sure that all the book keeping was being done correctly espeacially after removing a node.
next i test arrays of varying sizes, and some with negative numbers, to make sure that my solutions worked in
these different scenarios. i wish i would have tested the solutions on significantly larger trees to make sure they hold
up, but im confident that they are correct.

