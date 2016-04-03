

/************************************************************************************
	Implementation of Priority Queue ADT Initialization & Destruction functions
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "pq.h"
#include <stdlib.h>
#include <string.h>



#define PQ_INIT_SIZE					20






int pq_init(PriorityQueue *pq,
				int (*compareKey) (const void *key1, const void *key2),
				void (*destroyKey) (void *key), void (*destroyData) (void *data))
{
	
	PQnode *array;
	
	array = 0;
	array = (PQnode *) malloc(sizeof(PQnode) * PQ_INIT_SIZE);
	if (array == 0)
		return -1;
	
	pq->pNodeArray = array;
	pq->nodeCount = 0;
	pq->heapState = PQ_HEAP_MIN;
	pq->arraySize = PQ_INIT_SIZE;
	pq->compareKey = compareKey;
	pq->destroyKey = destroyKey;
	pq->destroyData = destroyData;
	
	return 0;
}



void pq_destroy(PriorityQueue *pq) {
	
	register PQnode *pNode;
	register unsigned int iIndex;
	
	iIndex = 0;
	while (iIndex < pq->nodeCount) {
		
		pNode = pq->pNodeArray + iIndex;
		if (pq->destroyKey != 0) {
			pq->destroyKey(pNode->key);
		}
		if (pq->destroyData != 0) {
			pq->destroyData(pNode->data);
		}
		iIndex = iIndex + 1;
	}
	
	free((void *) pq->pNodeArray);
	memset((void *) pq, 0, sizeof(PriorityQueue));
	return;
}

