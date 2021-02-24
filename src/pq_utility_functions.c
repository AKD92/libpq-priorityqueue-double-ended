

/************************************************************************************
    Implementation of Double Ended Priority Queue ADT Utility functions
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/







#include "pq.h"
#include "pq_internal.h"
#include <string.h>
#include <stdlib.h>









int pq_expand_capacity(PriorityQueue *pq) {
    
    void *array_new, *array_old;
    unsigned int new_capacity, old_capacity;
    
    
    if (pq == 0)
        return -2;
    
    
    /* Calculate the size (not in bytes) of new expanded memory region */
    /* New size is the size of old memory region multiplied by Expand Factor */
    old_capacity = pq_capacity(pq);
    new_capacity = old_capacity * PQ_DEFAULT_EXPANSION_FACTOR;
    
    
    /* Request for an expanded memory region using malloc() */
    array_old = (void *) pq_array(pq);
    array_new = (void *) malloc(new_capacity * sizeof(PQnode));
    
    
    /* If the request for allocating new memory region */
    /* Is not granted, return -2 to signal this problem */
    if (array_new == 0)
        return -1;
    
    
    /* Copy data from old memory region to new expanded memory region */
    memcpy((void *) array_new, (const void *) array_old, old_capacity * sizeof(PQnode));
    
    
    /* Adjust this Priority Queue to use new memory region */
    pq_array(pq) = (PQnode *) array_new;
    pq_capacity(pq) = new_capacity;
    
    
    /* Release old memory region */
    free((void*) array_old);
    
    return 0;
}




int pq_compare_node(const void *arg1, const void *arg2) {
    
    int iCompareVal;
    PQnode *pNode1, *pNode2;
    
    pNode1 = (PQnode *) arg1;
    pNode2 = (PQnode *) arg2;
    
    iCompareVal = pNode1->fpComparePriority((const void *) pNode1->priority, (const void *) pNode2->priority);
    return iCompareVal;
}


