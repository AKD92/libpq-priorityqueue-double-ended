

/************************************************************************************
	Implementation of Double Ended Priority Queue ADT
	Utility functions
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "pq.h"
#include <string.h>
#include <stdlib.h>








/************************************************************************************/
/************************************************************************************/


int pq_expandSize(PriorityQueue *pq);

int pq_nodeCompare(const void *arg1, const void *arg2);




/************************************************************************************/
/************************************************************************************/


int pq_expandSize(PriorityQueue *pq) {
	
	void *pNewArray, *pOldArray;
	unsigned int newSize, oldSize;
	
	if (pq->expandFactor < 2)
		return -1;
	
	pNewArray = 0;
	oldSize = pq->arraySize;
	newSize = oldSize * pq->expandFactor;
	
	pOldArray = (void *) pq->pNodeArray;
	pNewArray = malloc(newSize * sizeof(PQnode));
	if (pNewArray == 0)
		return -1;
	
	memcpy(pNewArray, (const void *) pOldArray, sizeof(PQnode) * oldSize);
	
	pq->pNodeArray = (PQnode *) pNewArray;
	pq->arraySize = newSize;
	free((void*) pOldArray);
	
	return 0;
}



int pq_nodeCompare(const void *arg1, const void *arg2) {
	
	int iCompareVal;
	const PQnode *pNode1, *pNode2;
	
	pNode1 = (const PQnode *) arg1;
	pNode2 = (const PQnode *) arg2;
	
	iCompareVal = pNode1->fpCompareKey((const void *) pNode1->key, (const void *) pNode2->key);
	return iCompareVal;
}


