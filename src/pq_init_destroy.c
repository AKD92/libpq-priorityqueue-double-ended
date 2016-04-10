

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




#define PQ_INIT_SIZE		10






/************************************************************************************/
/************************************************************************************/


int pq_init(PriorityQueue *pq, HeapOrientation hOrientation,
				int (*fpCompareKey) (const void *key1, const void *key2),
				void (*fpDestroyKey) (void *key), void (*fpDestroyData) (void *data))
{
	
	PQnode *array;
	
	if (pq == 0 || fpCompareKey == 0)
		return -1;
	
	array = 0;
	array = (PQnode *) malloc(sizeof(PQnode) * PQ_INIT_SIZE);
	if (array == 0)
		return -2;
	
	pq->pNodeArray = array;
	pq->nodeCount = 0;
	pq->heapOrint = hOrientation;
	pq->arraySize = PQ_INIT_SIZE;
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
	
	vfpDesKey = (void *) pq->fpDestroyKey;
	vfpDesData = (void *) pq->fpDestroyData;
	
	if (vfpDesKey == 0 && vfpDesData == 0)
		goto CLEAN_UP;
	
	iNode = 0;
	while (iNode < pq_size(pq)) {
		
		pNode = pq->pNodeArray + iNode;
		if (pq->fpDestroyKey != 0) {
			pq->fpDestroyKey(pNode->key);
		}
		if (pq->fpDestroyData != 0) {
			pq->fpDestroyData(pNode->data);
		}
		iNode = iNode + 1;
	}
	
	CLEAN_UP:
	free((void *) pq->pNodeArray);
	memset((void *) pq, 0, sizeof(PriorityQueue));
	return;
}


