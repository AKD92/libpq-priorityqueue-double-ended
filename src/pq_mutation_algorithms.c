

/************************************************************************************
    Implementation of Double Ended Priority Queue ADT Mutation Algorithms
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/







#include "pq.h"
#include "pq_internal.h"
#include <stdlib.h>
#include <string.h>
#include <bh.h>









int pq_insert_with_priority(PriorityQueue *pq, const void *elem, const void *priority) {
    
    BiHeap heap;
    PQnode *pNode;
    int opExpand;
    int (*fpHeapSwimAlgorithm) (BiHeap *heap, unsigned int index);
    
    
    /* Check for invalid function arguments */
    if (pq == 0 || priority == 0 || elem == 0)
        return -1;
    
    
    /* Expand internal array if the array is full */
    /* Expand operation can fail due to unavailability of additional memory */
    if (pq_size(pq) == pq_capacity(pq)) {
        opExpand = pq_expand_capacity(pq);
        if (opExpand != 0)
            return -2;
    }
    
    
    /* Select which Heap Orientation this PQ is currently configured to */
    /* We insert into this PQ according to the rules of current Heap Orientation */
    switch (pq_heap_orientation(pq)) {
        case PQ_HEAP_MAX:
            fpHeapSwimAlgorithm = bh_swim_heavy;
            break;
        case PQ_HEAP_MIN:
            fpHeapSwimAlgorithm = bh_swim_light;
            break;
        default:
            fpHeapSwimAlgorithm = 0;
            return -1;
    }
    
    
    /* Determine last PQnode as our new node where we insert data */
    pNode = pq_array(pq) + pq_size(pq);
    pNode->priority = (void *) priority;
    pNode->elem = (void *) elem;
    pNode->fpComparePriority = pq->fpComparePriority;
    pq_size(pq) = pq_size(pq) + 1;
    
    if (pq_size(pq) == 1)
        return 0;
    
    /*  Restore binary heap property.
        Run the chosen algorithm / operation.
    */
    bh_init(&heap, (void *) pq_array(pq), pq_size(pq), sizeof(PQnode), pq_compare_node);
    fpHeapSwimAlgorithm(&heap, pq_size(pq) - 1);
    bh_destroy(&heap);
    
    return 0;
}





int pq_pull_minimum(PriorityQueue *pq, void **priority, void **elem) {
    
    BiHeap heap;
    PQnode *pNodeMin;
    
    
    /* Check for invalid function arguments */
    if (pq == 0 || priority == 0 || elem == 0)
        return -1;
    if (pq_size(pq) == 0)
        return -1;
    
    
    /* Detect which Heap Orientation this PQ is currently configured to */
    /* If current Heap Orientation is a MAX HEAP, transform it to a MIN HEAP */
    if (pq_heap_orientation(pq) == PQ_HEAP_MAX) {
        bh_init(&heap, (void *) pq_array(pq), pq_size(pq), sizeof(PQnode), pq_compare_node);
        bh_build_minheap(&heap);
        bh_destroy(&heap);
        pq_heap_orientation(pq) = PQ_HEAP_MIN;
    }
    
    
    /* Access data for transfering to the caller */
    pNodeMin = pq_array(pq) + 0;
    *priority = pNodeMin->priority;
    *elem = pNodeMin->elem;
    pq_size(pq) = pq_size(pq) - 1;
    
    if (pq_size(pq) == 0)
        return 0;
    
    /*  Restore binary heap property.
        Run the chosen algorithm / operation.
    */
    bh_init(&heap, (void *) pq_array(pq), pq_size(pq) + 1, sizeof(PQnode), pq_compare_node);
    bh_swap(0, bh_size(&heap) - 1, &heap);
    bh_size(&heap) = bh_size(&heap) - 1;
    bh_sink_heavy(&heap, 0);
    bh_destroy(&heap);
    
    return 0;
}





int pq_peek_minimum(PriorityQueue *pq, void **priority, void **elem) {
    
    BiHeap heap;
    PQnode *pNodeMin;
    
    
    /* Check for invalid function arguments */
    if (pq == 0 || priority == 0 || elem == 0)
        return -1;
    if (pq_size(pq) == 0)
        return -1;
    
    
    /* Detect which Heap Orientation this PQ is currently configured to */
    /* If current Heap Orientation is a MAX HEAP, transform it to a MIN HEAP */
    if (pq_heap_orientation(pq) == PQ_HEAP_MAX) {
        bh_init(&heap, (void *) pq_array(pq), pq_size(pq), sizeof(PQnode), pq_compare_node);
        bh_build_minheap(&heap);
        bh_destroy(&heap);
        pq_heap_orientation(pq) = PQ_HEAP_MIN;
    }
    
    
    /* Access data for transfering to the caller */
    pNodeMin = pq_array(pq) + 0;
    *priority = pNodeMin->priority;
    *elem = pNodeMin->elem;
    
    return 0;
}





int pq_pull_maximum(PriorityQueue *pq, void **priority, void **elem) {
    
    BiHeap heap;
    PQnode *pNodeMax;
    
    
    /* Check for invalid function arguments */
    if (pq == 0 || priority == 0 || elem == 0)
        return -1;
    if (pq_size(pq) == 0)
        return -1;
    
    
    /* Detect which Heap Orientation this PQ is currently configured to */
    /* If current Heap Orientation is a MIN HEAP, transform it to a MAX HEAP */
    if (pq_heap_orientation(pq) == PQ_HEAP_MIN) {
        bh_init(&heap, (void *) pq_array(pq), pq_size(pq), sizeof(PQnode), pq_compare_node);
        bh_build_maxheap(&heap);
        bh_destroy(&heap);
        pq_heap_orientation(pq) = PQ_HEAP_MAX;
    }
    
    
    /* Access data for transfering to the caller */
    pNodeMax = pq_array(pq) + 0;
    *priority = pNodeMax->priority;
    *elem = pNodeMax->elem;
    pq_size(pq) = pq_size(pq) - 1;
    
    if (pq_size(pq) == 0)
        return 0;
    
    /*  Restore binary heap property.
        Run the chosen algorithm / operation.
    */
    bh_init(&heap, (void *) pq_array(pq), pq_size(pq) + 1, sizeof(PQnode), pq_compare_node);
    bh_swap(0, bh_size(&heap) - 1, &heap);
    bh_size(&heap) = bh_size(&heap) - 1;
    bh_sink_light(&heap, 0);
    bh_destroy(&heap);
    
    return 0;
}





int pq_peek_maximum(PriorityQueue *pq, void **priority, void **elem) {
    
    BiHeap heap;
    PQnode *pNodeMax;
    
    
    /* Check for invalid function arguments */
    if (pq == 0 || priority == 0 || elem == 0)
        return -1;
    if (pq_size(pq) == 0)
        return -1;
    
    
    /* Detect which Heap Orientation this PQ is currently configured to */
    /* If current Heap Orientation is a MIN HEAP, transform it to a MAX HEAP */
    if (pq_heap_orientation(pq) == PQ_HEAP_MIN) {
        bh_init(&heap, (void *) pq_array(pq), pq_size(pq), sizeof(PQnode), pq_compare_node);
        bh_build_maxheap(&heap);
        bh_destroy(&heap);
        pq_heap_orientation(pq) = PQ_HEAP_MAX;
    }
    
    
    /* Access data for transfering to the caller */
    pNodeMax = pq_array(pq) + 0;
    *priority = pNodeMax->priority;
    *elem = pNodeMax->elem;
    
    return 0;
}

