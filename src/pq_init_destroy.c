

/************************************************************************************
    Implementation of Double Ended Priority Queue ADT
    Initialization & Destruction functions
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "pq.h"
#include <stdlib.h>
#include <string.h>









int pq_init(
    PriorityQueue *pq,
    enum PQ_HeapOrient_t hOrientation,
    int (*fpComparePriority) (const void *pr1, const void *pr2),
    void (*fpDestroyPriority) (void *priority),
    void (*fpDestroyElement) (void *element)
)
{
    
    int retval;
    unsigned int capacity, expandFactor;
    
    /*  This initialization function will initialize this queue
        with the default capacity and default expand factor
    */
    capacity = PQ_DEFAULT_CAPACITY;
    expandFactor = PQ_DEFAULT_EXPAND_FACTOR;
    
    /*  Initialize the priority queue */
    retval = pq_init_ex(pq, hOrientation, capacity, expandFactor, fpComparePriority, fpDestroyPriority, fpDestroyElement);
    return retval;
}





int pq_init_ex(
    PriorityQueue *pq,
    enum PQ_HeapOrient_t hOrientation,
    unsigned int capacity,
    unsigned int expandFactor,
    int (*fpComparePriority) (const void *pr1, const void *pr2),
    void (*fpDestroyPriority) (void *priority),
    void (*fpDestroyElement) (void *element)
)
{
    
    PQnode *pArray;
    
    
    /* Check for invalid function arguments */
    if (pq == 0 || fpComparePriority == 0 || capacity == 0 || expandFactor < 2)
        return -1;
    
    
    /* Request to allocate memory storage using malloc() */
    /* If the request is not granted, return -2 to signal this problem */
    pArray = 0;
    pArray = (PQnode *) malloc(capacity * sizeof(PQnode));
    if (pArray == 0)
        return -2;
    
    
    /* Adjust all the fields of this Priority Queue */
    /* With proper values and set all function pointers */
    memset((void *) pq, 0, sizeof(PriorityQueue));
    pq->nodeCount = 0;
    pq->pArrayNode = pArray;
    pq->heapOrint = hOrientation;
    pq->arrCapacity = capacity;
    pq->expandFactor = expandFactor;
    pq->fpComparePriority = fpComparePriority;
    pq->fpDestroyPriority = fpDestroyPriority;
    pq->fpDestroyElement = fpDestroyElement;
    
    return 0;
}





void pq_destroy(PriorityQueue *pq) {
    
    register PQnode *pNode;
    register unsigned int index;
    
    
    /* Check for invalid function arguments */
    if (pq == 0)
        return;
    
    if (pq->fpDestroyPriority == 0 && pq->fpDestroyElement == 0)
        goto DESTROY_END;
    
    
    /* Iterate through each Key and Data object */
    /* In order to de-allocate them from memory */
    index = 0;
    while (index < pq_size(pq)) {
        pNode = pq_array(pq) + index;
        if (pq->fpDestroyPriority != 0) {
            pq->fpDestroyPriority(pNode->priority);
        }
        if (pq->fpDestroyElement != 0) {
            pq->fpDestroyElement(pNode->elem);
        }
        index += 1;
    }
    
    
    /* Release internal memory of this Priority Queue */
    DESTROY_END:
    free((void *) pq_array(pq));
    
    return;
}


