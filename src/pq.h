

/************************************************************************************
	Program Interface of Priority Queue ADT (Based on Heap Data Structure)
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:             https://github.com/AKD92
*************************************************************************************/






#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H







#define PQ_HEAP_MIN			1
#define PQ_HEAP_MAX			2





struct PQnode_ {
	
	void *key;							/* User supplied pointer to a Key */
	void *data;							/* User supplied pointer to a Value (Optional, Can be NULL) */
	
	int (*compareKey)
			(const void *key1, const void *key2);
										/* User supplied comparing function to compare Keys */
};
typedef struct PQnode_ PQnode;



struct PQ_ {
	
	PQnode *pNodeArray;					/* Array of PQnode objects, which will carry user keys & data */
										/* The operations of a PQ like removeMin(), removeMAX(), insert() */
										/* Will eventually manipulate this array using HEAP algorithms */
	
	unsigned int heapState;				/* Current state of Heap Orientation: PQ_HEAP_MIN or PQ_HEAP_MAX */
	
	unsigned int nodeCount;				/* Number of objects in the PQnode array (not array length) */
	unsigned int arraySize;				/* Length of PQnode array */
	
	int		(*compareKey) 	(const void *key1, const void *key2);
	void 	(*destroyKey)	(void *keyElement);
	void 	(*destroyData) 	(void *dataElement);
	
};
typedef struct PQ_ PriorityQueue;





#define pq_size(pq) ((pq)->nodeCount)



int pq_init(PriorityQueue *queue,
				int (*compareKey) (const void *key1, const void *key2),
				void (*destroyKey) (void *key), void (*destroyData) (void *data));

void pq_destroy(PriorityQueue *queue);



int pq_peek(PriorityQueue *queue, void **key, void **data);

int pq_insert(PriorityQueue* pq, const void *key, const void *data);

int pq_removeMin(PriorityQueue *pq, void **key, void **data);

int pq_removeMax(PriorityQueue *pq, void **key, void **data);






#endif
