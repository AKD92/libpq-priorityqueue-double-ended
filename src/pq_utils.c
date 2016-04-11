

/************************************************************************************
	Implementation of Double Ended Priority Queue ADT Utility functions
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "pq.h"
#include <string.h>
#include <stdlib.h>








/************************************************************************************/
/************************************************************************************/


int pq_expandCapacity(PriorityQueue *pq);

int pq_nodeCompare(const void *arg1, const void *arg2);




/************************************************************************************/
/************************************************************************************/


int pq_expandCapacity(PriorityQueue *pq) {
	
	void *pArrayNew, *pArrayOld;
	unsigned int iCapacityNew, iCapacityOld;
	
	
	/* Expand Factor less than 2 does not make sense */
	if (pq_expandFactor(pq) < 2)
		return -1;
	
	
	/* Calculate the size (not in bytes) of new expanded memory region */
	/* New size is the size of old memory region multiplied by Expand Factor */
	iCapacityOld = pq_capacity(pq);
	iCapacityNew = iCapacityOld * pq_expandFactor(pq);
	
	
	/* Request for expanded memory region using malloc() */
	pArrayNew = 0;
	pArrayOld = (void *) pq_array(pq);
	pArrayNew = (void *) malloc(iCapacityNew * sizeof(PQnode));
	
	
	/* If the request for allocating new memory region */
	/* Is not granted, return -2 to signal this problem */
	if (pArrayNew == 0)
		return -2;
	
	
	/* Copy data from old memory region to new expanded memory region */
	memcpy(pArrayNew, (const void *) pArrayOld, iCapacityOld * sizeof(PQnode));
	
	
	/* Adjust this Priority Queue to use new memory region */
	pq_array(pq) = (PQnode *) pArrayNew;
	pq_capacity(pq) = iCapacityNew;
	
	
	/* De-allocate old memory region */
	free((void*) pArrayOld);
	
	return 0;
}



int pq_nodeCompare(const void *arg1, const void *arg2) {
	
	int iCompareVal;
	PQnode *pNode1, *pNode2;
	
	pNode1 = (PQnode *) arg1;
	pNode2 = (PQnode *) arg2;
	
	iCompareVal = pNode1->fpCompareKey((const void *) pNode1->key, (const void *) pNode2->key);
	return iCompareVal;
}


