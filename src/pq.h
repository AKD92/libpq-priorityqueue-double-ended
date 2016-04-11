

/************************************************************************************
    Program Interface of Double Ended Priority Queue ADT
    Based on Binary Heap Data Structure (Array Based)
    Author:             Ashis Kumar Das
    Email:              akd.bracu@gmail.com
    GitHub:             https://github.com/AKD92
*************************************************************************************/






#ifndef DOUBLE_ENDED_PQ_BINHEAP_H
#define DOUBLE_ENDED_PQ_BINHEAP_H






#define PQ_DEFAULT_EXPAND_FACTOR        2






/*********************************************************************************************/
/***********************************                      ************************************/
/***********************************    DATA STRUCTURES   ************************************/
/***********************************                      ************************************/
/*********************************************************************************************/




enum PQ_HeapOrient_t {
    
    PQ_HEAP_MIN = 0,
    PQ_HEAP_MAX,
    
};


struct PQnode_ {
    
    void *key;                              /* Pointer to a Key */
    void *data;                             /* Pointer to a Value (Optional, can be NULL) */
    
    int (*fpCompareKey)                     /* User specifed function for comparing Keys */
            (const void *key1, const void *key2);
            
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
    
    int     (*fpCompareKey)     (const void *key1, const void *key2);
    void    (*fpDestroyKey)     (void *keyElement);
    void    (*fpDestroyData)    (void *dataElement);
    
};
typedef struct PriorityQueue_DE_ PriorityQueue;






/*********************************************************************************************/
/***********************************                      ************************************/
/***********************************   PUBLIC INTERFACES  ************************************/
/***********************************                      ************************************/
/*********************************************************************************************/




#define pq_array(pq)                         ((pq)->pArrayNode)

#define pq_size(pq)                          ((pq)->nodeCount)

#define pq_capacity(pq)                      ((pq)->arrCapacity)

#define pq_heapOrientation(pq)               ((pq)->heapOrint)

#define pq_expandFactor(pq)                  ((pq)->expandFactor)




int pq_init(PriorityQueue *pq, enum PQ_HeapOrient_t hOrientation,
                int (*fpCompareKey) (const void *key1, const void *key2),
                    void (*fpDestroyKey) (void *key), void (*fpDestroyData) (void *data));

void pq_destroy(PriorityQueue *pq);




int pq_peekMin(PriorityQueue *pq, void **key, void **data);

int pq_peekMax(PriorityQueue *pq, void **key, void **data);



int pq_insert(PriorityQueue *pq, const void *key, const void *data);



int pq_removeMin(PriorityQueue *pq, void **key, void **data);

int pq_removeMax(PriorityQueue *pq, void **key, void **data);






#endif


