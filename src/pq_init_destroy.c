

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




#define PQ_INITIAL_CAPACITY     10






/************************************************************************************/
/************************************************************************************/


int pq_init(PriorityQueue *pq, enum PQ_HeapOrient_t hOrientation,
                int (*fpCompareKey) (const void *key1, const void *key2),
                    void (*fpDestroyKey) (void *key), void (*fpDestroyData) (void *data))
{
    
    PQnode *pArray;
    
    
    /* Check for invalid function arguments */
    if (pq == 0 || fpCompareKey == 0)
        return -1;
    
    
    /* Request to allocate memory storage using malloc() */
    /* If the request is not granted, return -2 to signal this problem */
    pArray = 0;
    pArray = (PQnode *) malloc(PQ_INITIAL_CAPACITY * sizeof(PQnode));
    if (pArray == 0)
        return -2;
    
    
    /* Adjust all the fields of this Priority Queue */
    /* With proper values and set all function pointers */
    pq->nodeCount = 0;
    pq->pArrayNode = pArray;
    pq->heapOrint = hOrientation;
    pq->arrCapacity = PQ_INITIAL_CAPACITY;
    pq->expandFactor = PQ_DEFAULT_EXPAND_FACTOR;
    pq->fpCompareKey = fpCompareKey;
    pq->fpDestroyKey = fpDestroyKey;
    pq->fpDestroyData = fpDestroyData;
    
    return 0;
}



void pq_destroy(PriorityQueue *pq) {
    
    register PQnode *pNode;
    register unsigned int iNode;
    void *vfpDesKey, *vfpDesData;
    
    
    /* Check for invalid function arguments */
    if (pq == 0)
        return;
    
    vfpDesKey = (void *) pq->fpDestroyKey;
    vfpDesData = (void *) pq->fpDestroyData;
    
    if (vfpDesKey == 0 && vfpDesData == 0)
        goto CLEAN_UP;
    
    
    /* Iterate through each Key and Data object */
    /* In order to de-allocate them from memory */
    iNode = 0;
    while (iNode < pq_size(pq)) {
        pNode = pq_array(pq) + iNode;
        if (pq->fpDestroyKey != 0) {
            pq->fpDestroyKey(pNode->key);
        }
        if (pq->fpDestroyData != 0) {
            pq->fpDestroyData(pNode->data);
        }
        iNode = iNode + 1;
    }
    
    
    /* Release internal memory of this Priority Queue */
    CLEAN_UP:
    free((void *) pq_array(pq));
    memset((void *) pq, 0, sizeof(PriorityQueue));
    
    return;
}


