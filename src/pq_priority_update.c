

/************************************************************************************
    Implementation of Double Ended Priority Queue ADT Utility functions
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/







#include "pq.h"
#include "pq_internal.h"
#include <bh.h>








int pq_reassign_priority(
    PriorityQueue *pq,
    int (*fpCompareElement) (const void *arg1, const void *arg2),
    const void *elem,
    const void *priority,
    void **oldPriority
)
{
    
    BiHeap heap;
    int (*fpHeapAlgorithm) (BiHeap *heap, unsigned int index);
    unsigned int index;
    
    int isRoot;
    int hasLeftChild, hasRightChild;
    int cmpWithParent;
    int cmpWithLeftChild, cmpWithRightChild;
    
    PQnode *pNode, *pThis, *pParent;
    PQnode *pLeftChild, *pRightChild;
    
    
    /*  Check for invalid function arguments */
    if (pq == 0 || fpCompareElement == 0 || elem == 0 || priority == 0)
        return -1;
    if (pq_size(pq) == 0)
        return -1;
    
    
    /*  Search for the specified element (elem) in the priority queue */
    pThis = 0;
    for (index = 0; index < pq_size(pq); index += 1) {
        pNode = pq_array(pq) + index;
        if (fpCompareElement((const void *) pNode->elem, elem) == 0) {
            pThis = pNode;
            break;
        }
    }
    
    
    /*  If the element (elem) does not exist, exit with error code */
    if (pThis == 0)
        return -2;
    
    
    /*  The element (elem) has been found.
        We proceed to update the priority associated with this element.
    */
    if (oldPriority != 0)
        *oldPriority = pThis->priority;
    pThis->priority = (void *) priority;
    
    
    /*  Check if this node is the root, if it has left or right child */
    isRoot = index == 0 ? 1 : 0;
    hasLeftChild = bh_leftchild_index(index) < pq_size(pq) ? 1 : 0;
    hasRightChild = bh_rightchild_index(index) < pq_size(pq) ? 1 : 0;
    
    
    /*  Get the memory location of this node's parent, left and right child nodes
        if exists
    */
    pParent = isRoot == 1 ? 0 : pq_array(pq) + bh_parent_index(index);
    pLeftChild = hasLeftChild == 1 ? pq_array(pq) + bh_leftchild_index(index) : 0;
    pRightChild = hasRightChild == 1 ? pq_array(pq) + bh_rightchild_index(index) : 0;
    
    
    /*  Compare our new priority with the priority of its parent,
        left child and the right child.
    */
    cmpWithParent = pParent == 0 ? 0 : pq->fpComparePriority(pThis->priority, pParent->priority);
    cmpWithLeftChild = hasLeftChild == 1 ? pq->fpComparePriority(pThis->priority, pLeftChild->priority) : 0;
    cmpWithRightChild = hasRightChild == 1 ? pq->fpComparePriority(pThis->priority, pRightChild->priority) : 0;
    
    
    /*  Choose the appropriate heap operation in order to restore heap property.
        fpHeapAlgorithm function pointer will point to the appropriate heap operation.
        So it can be either:
            a). Swim Light Element      for min heap, move lower priority elements up on the heap
            b). Sink Heavy Element      for min heap, move higher priority elements down to the heap
            c). Swim Heavy Element      for max heap, move higher priority elements up on the heap
            d). Sink Light Element      for max heap, move lower priority elements down to the heap
    */
    fpHeapAlgorithm = 0;
    switch (pq_heap_orientation(pq)) {
        case PQ_HEAP_MIN:
            
            /*  This node is not root node, and priority of parent node is higher */
            if (isRoot == 0 && cmpWithParent < 0)
                fpHeapAlgorithm = bh_swim_light;
                
            /*  Any of the children has higher priority than priority of this node */
            else if (cmpWithLeftChild > 0 || cmpWithRightChild > 0)
                fpHeapAlgorithm = bh_sink_heavy;
            break;
        case PQ_HEAP_MAX:
            
            /*  This node is not root node, and priority of parent node is lower */
            if (isRoot == 0 && cmpWithParent > 0)
                fpHeapAlgorithm = bh_swim_heavy;
                
            /*  Any of the children has lower priority than priority of this node */
            else if (cmpWithLeftChild < 0 || cmpWithRightChild < 0)
                fpHeapAlgorithm = bh_sink_light;
        break;
        default:    ;
    }
    
    
    if (fpHeapAlgorithm == 0)
        return 0;
    
    
    /*  Restore binary heap property.
        Run the chosen algorithm / operation.
    */
    bh_init(&heap, (void *) pq_array(pq), pq_size(pq), sizeof(PQnode), pq_compare_node);
    fpHeapAlgorithm(&heap, index);
    bh_destroy(&heap);
    return 0;
}


