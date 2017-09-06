

/************************************************************************************
    Implementation of Double Ended Priority Queue ADT Mutation Algorithms
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "pq.h"
#include <stdlib.h>
#include <string.h>
#include <biheap.h>








/************************************************************************************/
/************************************************************************************/


int pq_expandCapacity(PriorityQueue *pq);

int pq_nodeCompare(const void *arg1, const void *arg2);




/************************************************************************************/
/************************************************************************************/


int pq_insert(PriorityQueue *pq, const void *key, const void *data) {
    
    BiHeap heap;
    PQnode *pNode;
    int opExpand;
    int (*fpHeapSwimAlgorithm) (BiHeap *heap, unsigned int index);
    
    
    /* Check for invalid function arguments */
    if (pq == 0 || key == 0)
        return -1;
    
    
    /* Expand internal array if the array is full */
    /* Expand operation can fail due to unavailability of additional memory */
    /* It can also fail if ExpandFactor if this PQ is less than 2 */
    if (pq_size(pq) == pq_capacity(pq)) {
        opExpand = pq_expandCapacity(pq);
        if (opExpand != 0)
            return -1;
    }
    
    
    /* Select which Heap Orientation this PQ is currently configured to */
    /* We insert into this PQ according to the Rules of current Heap Orientation */
    switch (pq_heapOrientation(pq)) {
        case PQ_HEAP_MAX:
            fpHeapSwimAlgorithm = biheap_swimHeavyElement;
            break;
        case PQ_HEAP_MIN:
            fpHeapSwimAlgorithm = biheap_swimLightElement;
            break;
        default:
            fpHeapSwimAlgorithm = 0;
            return -1;
    }
    
    
    /* Determine last PQnode as our new node where we insert data */
    pNode = pq_array(pq) + pq_size(pq);
    pNode->key = (void *) key;
    pNode->data = (void *) data;
    pNode->fpCompareKey = pq->fpCompareKey;
    pq_size(pq) = pq_size(pq) + 1;
    
    if (pq_size(pq) == 1)
        return 0;
    
    /* Restore Binary Heap Property */
    /* Apply Binary Heap Algorthms */
    biheap_init(&heap, (void *) pq_array(pq), pq_size(pq), sizeof(PQnode), pq_nodeCompare);
    fpHeapSwimAlgorithm(&heap, pq_size(pq) - 1);
    biheap_destroy(&heap);
    
    return 0;
}



/************************************************************************************/
/************************************************************************************/


int pq_removeMax(PriorityQueue *pq, void **key, void **data) {
    
    BiHeap heap;
    PQnode *pNodeMax;
    
    
    /* Check for invalid function arguments */
    if (pq == 0)
        return -1;
    if (pq_size(pq) == 0)
        return -1;
    
    
    /* Detect which Heap Orientation this PQ is currently configured to */
    /* If current Heap Orientation is a MIN HEAP, transform it to a MAX HEAP */
    if (pq_heapOrientation(pq) == PQ_HEAP_MIN) {
        biheap_init(&heap, (void *) pq_array(pq), pq_size(pq), sizeof(PQnode), pq_nodeCompare);
        biheap_buildBinaryMaxHeap(&heap);
        biheap_destroy(&heap);
        pq_heapOrientation(pq) = PQ_HEAP_MAX;
    }
    
    
    /* Access data for transfering to the caller */
    pNodeMax = pq_array(pq) + 0;
    if (key != 0)
        *key = pNodeMax->key;
    if (data != 0)
        *data = pNodeMax->data;
    pq_size(pq) = pq_size(pq) - 1;
    
    if (pq_size(pq) == 0)
        return 0;
    
    /* Restore Binary Heap Property */
    /* Apply Binary Heap algorithm, by creating a heap, call function and destroy heap */
    biheap_init(&heap, (void *) pq_array(pq), pq_size(pq) + 1, sizeof(PQnode), pq_nodeCompare);
    biheap_swapElements(0, biheap_size(&heap) - 1, &heap);
    biheap_size(&heap) = biheap_size(&heap) - 1;
    biheap_sinkLightElement(&heap, 0);
    biheap_destroy(&heap);
    
    return 0;
}



int pq_peekMax(PriorityQueue *pq, void **key, void **data) {
    
    BiHeap heap;
    PQnode *pNodeMax;
    
    
    /* Check for invalid function arguments */
    if (pq == 0)
        return -1;
    if (pq_size(pq) == 0)
        return -1;
    
    
    /* Detect which Heap Orientation this PQ is currently configured to */
    /* If current Heap Orientation is a MIN HEAP, transform it to a MAX HEAP */
    if (pq_heapOrientation(pq) == PQ_HEAP_MIN) {
        biheap_init(&heap, (void *) pq_array(pq), pq_size(pq), sizeof(PQnode), pq_nodeCompare);
        biheap_buildBinaryMaxHeap(&heap);
        biheap_destroy(&heap);
        pq_heapOrientation(pq) = PQ_HEAP_MAX;
    }
    
    
    /* Access data for transfering to the caller */
    pNodeMax = pq_array(pq) + 0;
    if (key != 0)
        *key = pNodeMax->key;
    if (data != 0)
        *data = pNodeMax->data;
    
    return 0;
}



/************************************************************************************/
/************************************************************************************/


int pq_removeMin(PriorityQueue *pq, void **key, void **data) {
    
    BiHeap heap;
    PQnode *pNodeMin;
    
    
    /* Check for invalid function arguments */
    if (pq == 0)
        return -1;
    if (pq_size(pq) == 0)
        return -1;
    
    
    /* Detect which Heap Orientation this PQ is currently configured to */
    /* If current Heap Orientation is a MAX HEAP, transform it to a MIN HEAP */
    if (pq_heapOrientation(pq) == PQ_HEAP_MAX) {
        biheap_init(&heap, (void *) pq_array(pq), pq_size(pq), sizeof(PQnode), pq_nodeCompare);
        biheap_buildBinaryMinHeap(&heap);
        biheap_destroy(&heap);
        pq_heapOrientation(pq) = PQ_HEAP_MIN;
    }
    
    
    /* Access data for transfering to the caller */
    pNodeMin = pq_array(pq) + 0;
    if (key != 0)
        *key = pNodeMin->key;
    if (data != 0)
        *data = pNodeMin->data;
    pq_size(pq) = pq_size(pq) - 1;
    
    if (pq_size(pq) == 0)
        return 0;
    
    /* Restore Binary Heap Property */
    /* Apply Binary Heap algorithm, by creating a heap, call function and destroy heap */
    biheap_init(&heap, (void *) pq_array(pq), pq_size(pq) + 1, sizeof(PQnode), pq_nodeCompare);
    biheap_swapElements(0, biheap_size(&heap) - 1, &heap);
    biheap_size(&heap) = biheap_size(&heap) - 1;
    biheap_sinkHeavyElement(&heap, 0);
    biheap_destroy(&heap);
    
    return 0;
}


int pq_peekMin(PriorityQueue *pq, void **key, void **data) {
    
    BiHeap heap;
    PQnode *pNodeMin;
    
    
    /* Check for invalid function arguments */
    if (pq == 0)
        return -1;
    if (pq_size(pq) == 0)
        return -1;
    
    
    /* Detect which Heap Orientation this PQ is currently configured to */
    /* If current Heap Orientation is a MAX HEAP, transform it to a MIN HEAP */
    if (pq_heapOrientation(pq) == PQ_HEAP_MAX) {
        biheap_init(&heap, (void *) pq_array(pq), pq_size(pq), sizeof(PQnode), pq_nodeCompare);
        biheap_buildBinaryMinHeap(&heap);
        biheap_destroy(&heap);
        pq_heapOrientation(pq) = PQ_HEAP_MIN;
    }
    
    
    /* Access data for transfering to the caller */
    pNodeMin = pq_array(pq) + 0;
    if (key != 0)
        *key = pNodeMin->key;
    if (data != 0)
        *data = pNodeMin->data;
    
    return 0;
}


