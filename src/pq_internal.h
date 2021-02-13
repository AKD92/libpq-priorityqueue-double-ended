

/************************************************************************************
    Internal Program Interface of Double Ended Priority Queue ADT
    Based on Binary Heap Data Structure (Array Based)
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/






#ifndef PQ_INTERNAL_H_INCLUDED
#define PQ_INTERNAL_H_INCLUDED




#include "pq.h"





/*
 *  Expand the capacity of the underlying array of the specified priority queue.
 *  The capacity needs to be expanded when the underlying array is full and
 *  any new element can not be inserted into the priority queue until and unless
 *  the array is resized (expanded to higher capacity).
 *  It is basically an array-resize function.
 *  
 *  Parameters:
 *      pq          :   The priority queue which is being expanded
 *
 *  Returns:
 *      (int)           0 if the capacity is expanded (increased) succesfully
 *                      -1 if the expansion factor is set less than 2
 *                      -2 if the memory could not be allocated
*/
int pq_expand_capacity(PriorityQueue *pq);





/*
 *  Compare two elements of type PQnode.
 *  
 *  Parameters:
 *      arg1        :   First argument for a PQnode element
 *      arg2        :   Second argument for another PQnode element
 *
 *  Returns:
 *      (int)           1 if the first PQnode element (arg1) is greater than the second one (arg2)
 *                      0 if the specified PQnode elements are same (equal to each other)
 *                      -1 if the first PQnode element (arg1) is less than the second one (arg2)
*/
int pq_compare_node(const void *arg1, const void *arg2);





#endif

