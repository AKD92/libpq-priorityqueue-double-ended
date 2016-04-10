

/************************************************************************************
	Implementation of Double Ended Priority Queue ADT
	Mutation Algorithms
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "pq.h"
#include <binheap.h>
#include <stdlib.h>
#include <string.h>






int pq_expandSize(PriorityQueue *pq);

int pq_nodeCompare(const void *arg1, const void *arg2);






int pq_insert(PriorityQueue* pq, const void *key, const void *data) {
	
	BinHeap heap;
	PQnode *pNode;
	int opExpand;
	int (*fBinHeapSwimAlgorithm) (BinHeap *heap, unsigned int index);
	
	
	/* Expand internal array if the array is full */
	/* Expand operation can fail due to unavailability of additional memory */
	/* It can also fail if ExpandFactor if this PQ is less than 2 */
	if (pq_size(pq) == pq->arraySize) {
		opExpand = pq_expandSize(pq);
		if (opExpand != 0)
			return -1;
	}
	
	
	/* Detech which BinHeap Orientation this PQ is currently using */
	/* We insert into this PQ according to the Rules of current BinHeap Orientation */
	switch (pq->heapOrint) {
		case PQ_HEAP_MAX:
			fBinHeapSwimAlgorithm = binheap_swimHeavyElement;
			break;
		case PQ_HEAP_MIN:
			fBinHeapSwimAlgorithm = binheap_swimLightElement;
			break;
		default:
			fBinHeapSwimAlgorithm = 0;
			return -1;
	}
	
	
	/* Determine last PQnode as our new node where we insert data */
	pNode = pq->pNodeArray + pq->nodeCount;
	pNode->key = (void *) key;
	pNode->data = (void *) data;
	pNode->fpCompareKey = pq->fpCompareKey;
	pq->nodeCount = pq->nodeCount + 1;
	
	if (pq->nodeCount == 1)
		return 0;
	
	/* Maintain BinHeap Property */
	/* Apply BinHeap Algorthms */
	binheap_init(&heap, (void *) pq->pNodeArray, pq->nodeCount, sizeof(PQnode), pq_nodeCompare);
	fBinHeapSwimAlgorithm(&heap, pq->nodeCount - 1);
	binheap_destroy(&heap);
	
	return 0;
}



/************************************************************************************/
/************************************************************************************/


int pq_removeMax(PriorityQueue *pq, void **key, void **data) {
	
	BinHeap heap;
	PQnode *pNodeMax;
	
	if (pq_size(pq) == 0)
		return -1;
	
	
	/* Detect current BinHeap Orientation this PQ is using */
	/* If current BinHeap Orientation is MIN HEAP, transform it to MAX HEAP */
	if (pq->heapOrint == PQ_HEAP_MIN) {
		binheap_init(&heap, (void *) pq->pNodeArray, pq->nodeCount, sizeof(PQnode), pq_nodeCompare);
		binheap_buildMaxBinHeap(&heap);
		binheap_destroy(&heap);
		pq->heapOrint = PQ_HEAP_MAX;
	}
	
	
	/* Access data for transfering to the caller */
	pNodeMax = pq->pNodeArray + 0;
	if (key != 0) *key = pNodeMax->key;
	if (data != 0) *data = pNodeMax->data;
	pq->nodeCount = pq->nodeCount - 1;
	
	if (pq->nodeCount == 0)
		return 0;
	
	/* We need to maintain the HEAP Property */
	/* Apply HEAP algorithm, by creating a heap, call function and destroy heap */
	binheap_init(&heap, (void *) pq->pNodeArray, pq->nodeCount + 1, sizeof(PQnode), pq_nodeCompare);
	binheap_exchangeElement(0, heap.elemCount - 1, &heap);
	heap.elemCount = heap.elemCount - 1;
	binheap_sinkLightElement(&heap, 0);
	binheap_destroy(&heap);
	
	return 0;
}



int pq_peekMax(PriorityQueue *pq, void **key, void **data) {
	
	BinHeap heap;
	PQnode *pNodeMax;
	
	if (pq_size(pq) == 0)
		return -1;
	
	
	/* Detect current BinHeap Orientation this PQ is using */
	/* If current BinHeap Orientation is MIN HEAP, transform it to MAX HEAP */
	if (pq->heapOrint == PQ_HEAP_MIN) {
		binheap_init(&heap, (void *) pq->pNodeArray, pq->nodeCount, sizeof(PQnode), pq_nodeCompare);
		binheap_buildMaxBinHeap(&heap);
		binheap_destroy(&heap);
		pq->heapOrint = PQ_HEAP_MAX;
	}
	
	
	/* Access data for transfering to the caller */
	pNodeMax = pq->pNodeArray + 0;
	if (key != 0) *key = pNodeMax->key;
	if (data != 0) *data = pNodeMax->data;
	
	return 0;
}



/************************************************************************************/
/************************************************************************************/


int pq_removeMin(PriorityQueue *pq, void **key, void **data) {
	
	BinHeap heap;
	PQnode *pNodeMin;
	
	if (pq_size(pq) == 0)
		return -1;
	
	
	/* Detect current BinHeap Orientation this PQ is using */
	/* If current BinHeap Orientation is MAX HEAP, transform it to MIN HEAP */
	if (pq->heapOrint == PQ_HEAP_MAX) {
		binheap_init(&heap, (void *) pq->pNodeArray, pq->nodeCount, sizeof(PQnode), pq_nodeCompare);
		binheap_buildMinBinHeap(&heap);
		binheap_destroy(&heap);
		pq->heapOrint = PQ_HEAP_MIN;
	}
	
	
	/* Access data for transfering to the caller */
	pNodeMin = pq->pNodeArray + 0;
	if (key != 0) *key = pNodeMin->key;
	if (data != 0) *data = pNodeMin->data;
	pq->nodeCount = pq->nodeCount - 1;
	
	if (pq->nodeCount == 0)
	return 0;
	
	/* We need to maintain the HEAP Property */
	/* Apply HEAP algorithm, by creating a heap, call function and destroy heap */
	binheap_init(&heap, (void *) pq->pNodeArray, pq->nodeCount + 1, sizeof(PQnode), pq_nodeCompare);
	binheap_exchangeElement(0, heap.elemCount - 1, &heap);
	heap.elemCount = heap.elemCount - 1;
	binheap_sinkHeavyElement(&heap, 0);
	binheap_destroy(&heap);
	
	return 0;
}


int pq_peekMin(PriorityQueue *pq, void **key, void **data) {
	
	BinHeap heap;
	PQnode *pNodeMin;
	
	if (pq_size(pq) == 0)
		return -1;
	
	
	/* Detect current BinHeap Orientation this PQ is using */
	/* If current BinHeap Orientation is MAX HEAP, transform it to MIN HEAP */
	if (pq->heapOrint == PQ_HEAP_MAX) {
		binheap_init(&heap, (void *) pq->pNodeArray, pq->nodeCount, sizeof(PQnode), pq_nodeCompare);
		binheap_buildMinBinHeap(&heap);
		binheap_destroy(&heap);
		pq->heapOrint = PQ_HEAP_MIN;
	}
	
	
	/* Access data for transfering to the caller */
	pNodeMin = pq->pNodeArray + 0;
	if (key != 0) *key = pNodeMin->key;
	if (data != 0) *data = pNodeMin->data;
	
	return 0;
}


