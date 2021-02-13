

/************************************************************************************
    Public Program Interface of Double Ended Priority Queue ADT
    Based on Binary Heap Data Structure (Array Based)
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/






#ifndef DOUBLE_ENDED_PQ_BIHEAP_H
#define DOUBLE_ENDED_PQ_BIHEAP_H






#define PQ_DEFAULT_CAPACITY             10
#define PQ_DEFAULT_EXPAND_FACTOR        2






/*********************************************************************************************/
/***********************************                      ************************************/
/***********************************    DATA STRUCTURES   ************************************/
/***********************************                      ************************************/
/*********************************************************************************************/




enum PQ_HeapOrient_t {
    
    PQ_HEAP_MIN = 0,
    PQ_HEAP_MAX = 1,
    
};


struct PQnode_ {
    
    void *priority;                         /* Pointer to the priority element */
    void *elem;                             /* Pointer to the element */
    
    int (*fpComparePriority)                /* User specifed function for comparing two priority elements */
            (const void *pr1, const void *pr2);
            
};
typedef struct PQnode_ PQnode;


struct PriorityQueue_DE_ {
    
    PQnode *pArrayNode;                     /* Array of PQnode objects, which will carry user keys & data */
                                            /* The operations of a PQ like removeMin(), removeMAX(), insert() */
                                            /* Will eventually manipulate this array using HEAP algorithms */
    
    enum PQ_HeapOrient_t heapOrint;         /* Current state of Heap Orientation: PQ_HEAP_MIN or PQ_HEAP_MAX */
    
    unsigned int nodeCount;                 /* Number of objects in the PQnode array (not array length) */
    unsigned int arrCapacity;               /* Length of PQnode array */
    unsigned int expandFactor;              /* Customizable integer factor by which */
                                            /* Internal array will be expanded (resized) */
    
    int     (*fpComparePriority)    (const void *key1, const void *key2);
    void    (*fpDestroyPriority)    (void *priority);
    void    (*fpDestroyElement)     (void *element);
    
};
typedef struct PriorityQueue_DE_ PriorityQueue;






/*********************************************************************************************/
/***********************************                      ************************************/
/***********************************   PUBLIC INTERFACES  ************************************/
/***********************************                      ************************************/
/*********************************************************************************************/



/*
 *  Returns the underlying array of PQnode of the current priority queue.
 *
 *  Parameter:
 *      pq       	:   Pointer to a priority queue
 *
 *  Returns:
 *      (PQnode *)		Pointer to the internal array of type PQnode *
*/
#define pq_array(pq)                         ((pq)->pArrayNode)





/*
 *  Returns the number of elements the priority queue is currently holding.
 *
 *  Parameter:
 *      pq       	:   Pointer to a priority queue
 *
 *  Returns:
 *      (unsigned int)	Number of current elements
*/
#define pq_size(pq)                          ((pq)->nodeCount)





/*
 *  Returns the capacity (total number of slots) of the specified priority queue.
 *
 *  Parameter:
 *      pq       	:   Pointer to a priority queue
 *
 *  Returns:
 *      (unsigned int)	Capacity of the specified priority queue
*/
#define pq_capacity(pq)                      ((pq)->arrCapacity)





/*
 *  Returns the heap orientation (min queue or max queue) of the 
 *	specified priority queue.
 *
 *  Parameter:
 *      pq       	:   Pointer to a priority queue
 *
 *  Returns:
 *      (enum PQ_HeapOrient_t)	Heap orientation of the specified priority queue
*/
#define pq_heap_orientation(pq)               ((pq)->heapOrint)





/*
 *  Sets or returns the expansion factor of the specified priority queue.
 *	When the priority queue is full, inserting a new elements
 *	on the priority queue will need to increase the capacity of
 *	the current underlying array.
 *	The new capacity will be = (current capacity) * (expansion factor)
 *	By default, the expansion factor is PQ_DEFAULT_EXPAND_FACTOR
 *	which doubles the capacity.
 *
 *  Parameter:
 *      pq       	:   Pointer to a priority queue
 *
 *  Returns:
 *      (unsigned int)	The expansion factor
*/
#define pq_expand_factor(pq)                  ((pq)->expandFactor)





/*
 *  Initializes the given priority queue.
 *  The capacity and the expansion factor will be set to default values.
 *
 *  Parameter:
 *      pq       	        :   Pointer to a priority queue to initialize
 *		hOrientation        :	Orientation of the binary heap (min queue or max queue)
 *		fpComparePriority   :	Pointer to the function which will compare the priority elements
 *						        of the priority queue
 *                              (can not be NULL)
 *		fpDestroyPriority   :	Pointer to the function which will destroy the priority elements
 *						        of the priority queue
 *                              (can be NULL)
 *		fpDestroyElement    :	Pointer to the function which will destroy the elements
 *						        (can be NULL)
 *
 *  Returns:
 *      (int)			0 if the priority queue is initialized successfully
 *						-1 if any of the supplied parameters is NULL
 *                      -2 if failed to allocate memory
*/
int pq_init(
    PriorityQueue *pq,
    enum PQ_HeapOrient_t hOrientation,
    int (*fpComparePriority) (const void *pr1, const void *pr2),
    void (*fpDestroyPriority) (void *priority),
    void (*fpDestroyElement) (void *element)
);





/*
 *  Initializes the given priority queue.
 *
 *  Parameter:
 *      pq       	        :   Pointer to a priority queue to initialize
 *		hOrientation        :	Orientation of the binary heap (min queue or max queue)
 *      capacity            :   Total number of elements this priority queue is able to hold
 *      expandFactor        :   Expansion factor which will define how the capacity of this
 *                              priority queue will be expanded when it is holding elements
 *                              in full capacity.
 *                              New Capacity = Old Capacity x Expansion Factor
 *		fpComparePriority   :	Pointer to the function which will compare the priority elements
 *						        of the priority queue
 *                              (can not be NULL)
 *		fpDestroyPriority   :	Pointer to the function which will destroy the priority elements
 *						        of the priority queue
 *                              (can be NULL)
 *		fpDestroyElement    :	Pointer to the function which will destroy the elements
 *						        (can be NULL)
 *
 *  Returns:
 *      (int)			0 if the priority queue is initialized successfully
 *						-1 if any of the supplied parameters is NULL
 *                      -2 if failed to allocate memory
*/
int pq_init_ex(
    PriorityQueue *pq,
    enum PQ_HeapOrient_t hOrientation,
    unsigned int capacity,
    unsigned int expandFactor,
    int (*fpComparePriority) (const void *pr1, const void *pr2),
    void (*fpDestroyPriority) (void *priority),
    void (*fpDestroyElement) (void *element)
);





/*
 *  Destroys the given priority queue.
 *	Releases all the resources occupied by the queue.
 *	if fpDestroyPriority or fpDestroyElement functions are provided,
 *	then those functions are called for each priority element and each element
 *	to destroy all the containing elements along with their priority elements.
 *
 *  Parameter:
 *      pq       	:   Pointer to a priority queue to destroy
 *
 *  Returns:
 *      (void)
*/
void pq_destroy(PriorityQueue *pq);





/*
 *  Insets an element with a priority associated into the specified priority queue.
 *  Both the priority and the elem can point to the same element/object in memory
 *  at the same time and can not be NULL.
 *
 *  Parameter:
 *      pq       	:   Pointer to a priority queue
 *		elem		:	Pointer to the element which is being inserted with the priority
 *                      (can not be NULL)
 *		priority	:	Pointer to the priority element which is the priority of elem element
 *                      (can not be NULL)
 *
 *  Returns:
 *      (int)			0 if the elem is successfully inserted
 *						-1 if the supplied parameters are invalid
 *                      -2 if the system could not expand the priority queue (if needed)
*/
int pq_insert_with_priority(PriorityQueue *pq, const void *elem, const void *priority);





/*
 *  Retrives but does not remove the element with minimum priority from the priority queue.
 *	The element with minimum priority will be determined by the compare
 *	function (fpComparePriority) provided with the priority queue.
 *  If the heap orientation of the specified priority queue is PQ_HEAP_MIN
 *  then this operation will commit in O(1) time.
 *  Otherwise, in case if the heap orientation is PQ_HEAP_MAX,
 *  then it will be transformed into a PQ_HEAP_MIN type before obtaining
 *  the element with minimum priority and this operation will commit in O(nlogn) time.
 *
 *  Parameter:
 *      pq       	:   Pointer to a priority queue
 *		priority	:	Pointer to a pointer which will receive the priority
 *						(can not be NULL)
 *		elem		:	Pointer to a pointer which will receive the minimum element
 *						(can not be NULL)
 *
 *  Returns:
 *      (int)			0 if the minimum key is retrived
 *						-1 otherwise (the queue is empty or pq is NULL)
*/
int pq_peek_minimum(PriorityQueue *pq, void **priority, void **elem);





/*
 *  Retrives but does not remove the element with maximum priority from the priority queue.
 *	The element with maximum priority will be determined by the compare
 *	function (fpComparePriority) provided with the priority queue.
 *  If the heap orientation of the specified priority queue is PQ_HEAP_MAX
 *  then this operation will commit in O(1) time.
 *  Otherwise, in case if the heap orientation is PQ_HEAP_MIN,
 *  then it will be transformed into a PQ_HEAP_MAX type before obtaining
 *  the element with maximum priority and this operation will commit in O(nlogn) time.
 *
 *  Parameter:
 *      pq       	:   Pointer to a priority queue
 *		priority	:	Pointer to a pointer which will receive the priority
 *						(can not be NULL)
 *		elem		:	Pointer to a pointer which will receive the maximum element
 *						(can not be NULL)
 *
 *  Returns:
 *      (int)			0 if the maximum key is retrived
 *						-1 otherwise (the queue is empty or pq is NULL)
*/
int pq_peek_maximum(PriorityQueue *pq, void **priority, void **elem);





/*
 *  Retrives and removes the element with minimum priority from the priority queue.
 *	The element with minimum priority will be determined by the compare
 *	function (fpComparePriority) provided with the priority queue.
 *  If the heap orientation of the specified priority queue is PQ_HEAP_MIN
 *  then this operation will commit in O(1) time.
 *  Otherwise, in case if the heap orientation is PQ_HEAP_MAX,
 *  then it will be transformed into a PQ_HEAP_MIN type before obtaining
 *  the element with minimum priority and this operation will commit in O(nlogn) time.
 *
 *  Parameter:
 *      pq       	:   Pointer to a priority queue
 *		priority	:	Pointer to a pointer which will receive the priority
 *						(can not be NULL)
 *		elem		:	Pointer to a pointer which will receive the minimum element
 *						(can not be NULL)
 *
 *  Returns:
 *      (int)			0 if the minimum key is retrived and removed
 *						-1 otherwise (the queue is empty or pq is NULL)
*/
int pq_pull_minimum(PriorityQueue *pq, void **priority, void **elem);





/*
 *  Retrives and removes the element with maximum priority from the priority queue.
 *	The element with maximum priority will be determined by the compare
 *	function (fpComparePriority) provided with the priority queue.
 *  If the heap orientation of the specified priority queue is PQ_HEAP_MAX
 *  then this operation will commit in O(1) time.
 *  Otherwise, in case if the heap orientation is PQ_HEAP_MIN,
 *  then it will be transformed into a PQ_HEAP_MAX type before obtaining
 *  the element with maximum priority and this operation will commit in O(nlogn) time.
 *
 *  Parameter:
 *      pq       	:   Pointer to a priority queue
 *		priority	:	Pointer to a pointer which will receive the priority
 *						(can not be NULL)
 *		elem		:	Pointer to a pointer which will receive the maximum element
 *						(can not be NULL)
 *
 *  Returns:
 *      (int)			0 if the maximum key is retrived and removed
 *						-1 otherwise (the queue is empty or pq is NULL)
*/
int pq_pull_maximum(PriorityQueue *pq, void **priority, void **elem);





/*
 *  Reassign (change) the priority associated to an existing element in the priority queue.
 *  This is an O(n) time operation, where n is the number of elements this queue is holding.
 *
 *  Parameter:
 *      pq              :   Pointer to a priority queue
 *      fpCompareElement:   Pointer to a function which will be used to identify
 *                          the location of the element (elem) by comparing this element (elem)
 *                          with the elements exist in this priority queue.
 *                          At least the equality comparison is required from this
 *                          comparison function, such that it will return 0 when
 *                          two elements are considered equal.
 *                          It is fine if this comparison function implements 'total order'.
 *      elem            :   Pointer to an element which must exists into the specified
 *                          priority queue. It is vital that it must exists because
 *                          the priority associated with it is being changed.
 *      priority        :   Pointer to a priority element which is being assigned as the new
 *                          priority of the (elem) element.
 *                          Just like the requirements of the 'insert' function, this
 *                          priority element and the elem element can be same. In other
 *                          words, they can point to the same element/object in memory
 *                          at the same time.
 *      oldPriority     :   Pointer to a pointer which will receive the memory location of
 *                          the old priority element which is being replaced by the new
 *                          priority element.
 *                          (can be NULL)
 *
 *  Returns:
 *      (int)			0 if the priority is successfully reassigned
 *						-1 otherwise
*/
int pq_reassign_priority(
    PriorityQueue *pq,
    int (*fpCompareElement) (const void *arg1, const void *arg2),
    const void *elem,
    const void *priority,
    void **oldPriority
);





#endif


