

/************************************************************************************
	Program Interface of Double Ended Priority Queue ADT
	Based on Binary Heap Data Structure
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:             https://github.com/AKD92
*************************************************************************************/






#ifndef DOUBLE_ENDED_PQ_BINHEAP_H
#define DOUBLE_ENDED_PQ_BINHEAP_H






#define PQ_DEFAULT_EXPAND_FACTOR		20




/************************************************************************************/
/************************************************************************************/


enum pq_heaporient_t {
	
	PQ_HEAP_MIN = 0,
	PQ_HEAP_MAX,
	
};
typedef enum pq_heaporient_t HeapOrientation;



struct PQnode_ {
	
	void *key;							/* User supplied pointer to a Key */
	void *data;							/* User supplied pointer to a Value (Optional, Can be NULL) */
	
	int (*fpCompareKey)
			(const void *key1, const void *key2);
										/* User supplied comparing function to compare Keys */
};
typedef struct PQnode_ PQnode;



struct PQ_DE_ {
	
	PQnode *pNodeArray;					/* Array of PQnode objects, which will carry user keys & data */
										/* The operations of a PQ like removeMin(), removeMAX(), insert() */
										/* Will eventually manipulate this array using HEAP algorithms */
	
	HeapOrientation heapOrint;			/* Current state of Heap Orientation: PQ_HEAP_MIN or PQ_HEAP_MAX */
	
	unsigned int nodeCount;				/* Number of objects in the PQnode array (not array length) */
	unsigned int arraySize;				/* Length of PQnode array */
	unsigned int expandFactor;			/* Customizable factor integer by which */
										/* Internal array will be expanded (resized) */
	
	int     (*fpCompareKey)     (const void *key1, const void *key2);
	void    (*fpDestroyKey)     (void *keyElement);
	void    (*fpDestroyData)    (void *dataElement);
	
};
typedef struct PQ_DE_ PriorityQueue;




/************************************************************************************/
/************************************************************************************/



#define pq_array(pq) ((pq)->pNodeArray)

#define pq_size(pq) ((pq)->nodeCount)

#define pq_heapOrientation(pq) ((pq)->heapOrint)

#define pq_expandFactor(pq) ((pq)->expandFactor)



int pq_init(PriorityQueue *queue, HeapOrientation hOrientation,
				int (*fpCompareKey) (const void *key1, const void *key2),
				void (*fpDestroyKey) (void *key), void (*fpDestroyData) (void *data));

void pq_destroy(PriorityQueue *queue);



int pq_peekMin(PriorityQueue *queue, void **key, void **data);

int pq_peekMax(PriorityQueue *queue, void **key, void **data);



int pq_insert(PriorityQueue* pq, const void *key, const void *data);



int pq_removeMin(PriorityQueue *pq, void **key, void **data);

int pq_removeMax(PriorityQueue *pq, void **key, void **data);






#endif


