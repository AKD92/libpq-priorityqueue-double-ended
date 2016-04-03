

/************************************************************************************
	Implementation of Priority Queue ADT Utility functions
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "pq.h"
#include <string.h>
#include <stdlib.h>


#define PQ_RESIZE_FACTOR				2









int pq_expandSize(PriorityQueue *pq);

int pq_nodeCompare(const void *arg1, const void *arg2);







int pq_expandSize(PriorityQueue *pq) {
	
	unsigned int newSize, oldSize;
	void *newNodeArray, *oldNodeArray;
	
	oldSize = pq->arraySize;
	newSize = oldSize * PQ_RESIZE_FACTOR;
	
	oldNodeArray = (void *) pq->pNodeArray;
	newNodeArray = malloc(newSize * sizeof(PQnode));
	if (newNodeArray == 0)
		return -1;
	
	memcpy(newNodeArray, (const void *) oldNodeArray, sizeof(PQnode) * oldSize);
	
	pq->pNodeArray = (PQnode *) newNodeArray;
	pq->arraySize = newSize;
	free((void*) oldNodeArray);
	
	return 0;
}



int pq_nodeCompare(const void *arg1, const void *arg2) {
	
	int cmpresult;
	const PQnode *node1, *node2;
	
	node1 = (const PQnode *) arg1;
	node2 = (const PQnode *) arg2;
	
	cmpresult = node1->compareKey((const void *) node1->key, (const void *) node2->key);
	return cmpresult;
}

