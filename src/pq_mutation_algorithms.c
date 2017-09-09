

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



int pq_updateKey(PriorityQueue *pq, const void *pOldKey, const void *pNewKey, void **pRealOldKey) {
    
    BiHeap heap;
    PQnode *pNode;
    int (*fpHeapAlgorithm) (BiHeap *heap, unsigned int index);
    unsigned int index;
    int isRoot;
    int hasLeftChild, hasRightChild;
    int cmpWithParent;
    int cmpWithLeftChild, cmpWithRightChild;
    PQnode *pParent;
    PQnode *pLeftChild, *pRightChild;
    
    if (pq == 0 || pOldKey == 0 || pNewKey == 0)
        return -1;
    if (pq_size(pq) == 0)
        return -1;
    
    for (index = 0; index < pq_size(pq); index += 1) {
        pNode = pq_array(pq) + index;
        if (pq->fpCompareKey(pNode->key, pOldKey) == 0) {
            break;
        }
    }
    
    if (index == pq_size(pq))
        return -1;
    if (pRealOldKey != 0)
        *pRealOldKey = pNode->key;
    
    pNode->key = (void *) pNewKey;
    isRoot = index == 0 ? 1 : 0;
    hasLeftChild = biheap_leftChildIndex(index) < pq_size(pq) ? 1 : 0;
    hasRightChild = biheap_rightChildIndex(index) < pq_size(pq) ? 1 : 0;
    pParent = isRoot == 0 ? pq_array(pq) + biheap_parentIndex(index) : 0;
    pLeftChild = hasLeftChild == 1 ? pq_array(pq) + biheap_leftChildIndex(index) : 0;
    pRightChild = hasRightChild == 1 ? pq_array(pq) + biheap_rightChildIndex(index) : 0;
    cmpWithParent = pParent == 0 ? 0 : pq->fpCompareKey(pNode->key, pParent->key);
    cmpWithLeftChild = hasLeftChild == 1 ? pq->fpCompareKey(pNode->key, pLeftChild->key) : 0;
    cmpWithRightChild = hasRightChild == 1 ? pq->fpCompareKey(pNode->key, pRightChild->key) : 0;
    
    if (pq_heapOrientation(pq) == PQ_HEAP_MIN) {
        if (isRoot == 0 && cmpWithParent < 0)
            fpHeapAlgorithm = biheap_swimLightElement;
        else if (cmpWithLeftChild > 0 || cmpWithRightChild > 0)
            fpHeapAlgorithm = biheap_sinkHeavyElement;
        else
            fpHeapAlgorithm = 0;
    }
    else if (pq_heapOrientation(pq) == PQ_HEAP_MAX) {
        if (isRoot == 0 && cmpWithParent > 0)
            fpHeapAlgorithm = biheap_swimHeavyElement;
        else if (cmpWithLeftChild < 0 || cmpWithRightChild < 0)
            fpHeapAlgorithm = biheap_sinkLightElement;
        else
            fpHeapAlgorithm = 0;
    }
    else
        fpHeapAlgorithm = 0;
    
    /* Restore Binary Heap Property */
    /* Apply Binary Heap Algorthms */
    biheap_init(&heap, (void *) pq_array(pq), pq_size(pq), sizeof(PQnode), pq_nodeCompare);
    fpHeapAlgorithm(&heap, index);
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


