


Name: Brian Howe

Answer each of the questions below to the best of your
ability.  If you didn't complete the part of the assignment
relevant to a particular question, just say so.
-----------------------------------------------

Briefly describe how you modified the basic heap organization (as
presented in class ans in section 5.9 of Aho/Ullman) to support
the specifications for this assignment -- in particular how was
the idea of an ID incorporated.  

  Each node in the heap had 3 values. ID, and prioirty because these
  were required and index for easy look up and deletion. Next, in addition
  to the heap itself in pq_struct i also added an array that kept track of
  the nodes by there ID number. This allowed for quick look ups.

-----------------------------------------------
How did your modifications above affect your implementation of
pq_insert (vs. the standard implementation of insert)?

  The insertion was based on the priority instead of the ID. Also
  some extra bookkeeping steps were needed.

-----------------------------------------------
How did your modifications above affect your implementation of
pq_delete_top (vs. the standard implementation of delete_max)?
  
-----------------------------------------------
Explain how your implementation of bst_change_priority worked,
why it is correct and why it achieves the runtime requirement.

  I used a modifier called "k", if min_heap was true k = -1 else k = 1.
  this allowed me to write one function that would work for both heaps
  because if you multiply all the priorities by -1 then the least is then
  the greatest. Then it compared which priority was larger and swapped the
  larger one higher in the queue.

-----------------------------------------------
How did your implementation enable O(1) runtime for pq_get_priority?

  I used another array that kept track of the nodes by thier ID number. this
  allowed a constant look up for any node. Then the return of that nodes priority
  which is also constant time.
