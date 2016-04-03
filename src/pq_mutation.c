

/************************************************************************************
	Implementation of Priority Queue ADT Mutation Algorithms
	Author:             Ashis Kumar Das
	Email:              akd.bracu@gmail.com
	GitHub:             https://github.com/AKD92
*************************************************************************************/






#include "pq.h"
#include <heap.h>
#include <stdlib.h>
#include <string.h>






int pq_expandSize(PriorityQueue *pq);

int pq_nodeCompare(const void *arg1, const void *arg2);






int pq_insert(PriorityQueue* pq, const void *key, const void *data) {
	
	Heap heap;
	PQnode *pNode;
	int (*fHeapSwimAlgorithm) (Heap *heap, unsigned int index);
	
	if (pq->nodeCount == pq->arraySize) {
		pq_expandSize(pq);
	}
	
	
	/* Detech which Heap Orientation this PQ is currently using */
	/* We insert into this PQ according to the Rules of current Heap Orientation */
	switch (pq->heapState) {
		case PQ_HEAP_MAX:
			fHeapSwimAlgorithm = heap_swimHeavyElement;
			break;
		case PQ_HEAP_MIN:
			fHeapSwimAlgorithm = heap_swimLightElement;
			break;
		default:
			fHeapSwimAlgorithm = 0;
			return -1;
	}
	
	
	/* Determine last PQnode as our new node where we insert data */
	pNode = pq->pNodeArray + pq->nodeCount;
	pNode->key = (void *) key;
	pNode->data = (void *) data;
	pNode->compareKey = pq->compareKey;
	pq->nodeCount = pq->nodeCount + 1;
	
	
	/* Maintain Heap Property */
	/* Apply Heap Algorthms */
	heap_init(&heap, (void *) pq->pNodeArray, pq->nodeCount, sizeof(PQnode), pq_nodeCompare);
	fHeapSwimAlgorithm(&heap, pq->nodeCount - 1);
	heap_destroy(&heap);
	
	return 0;
}



int pq_removeMax(PriorityQueue *pq, void **key, void **data) {
	
	Heap heap;
	PQnode *pNodeMax;
	
	if (pq->nodeCount == 0)
		return -1;
	
	
	/* Detect current Heap Orientation this PQ is using */
	/* If current Heap Orientation is MIN HEAP, transform it to MAX HEAP */
	if (pq->heapState == PQ_HEAP_MIN) {
		heap_init(&heap, (void *) pq->pNodeArray, pq->nodeCount, sizeof(PQnode), pq_nodeCompare);
		heap_buildMaxHeap(&heap);
		heap_destroy(&heap);
		pq->heapState = PQ_HEAP_MAX;
	}
	
	
	/* Access data to transfer to the caller */
	pNodeMax = pq->pNodeArray + 0;
	if (key != 0) *key = pNodeMax->key;
	if (data != 0) *data = pNodeMax->data;
	pq->nodeCount = pq->nodeCount - 1;
	
	
	/* We need to maintain the HEAP Property */
	/* Apply HEAP algorithm, by creating a heap, call function and destroy heap */
	heap_init(&heap, (void *) pq->pNodeArray, pq->nodeCount + 1, sizeof(PQnode), pq_nodeCompare);
	heap_exchangeElement(0, heap.elemCount - 1, &heap);
	heap.elemCount = heap.elemCount - 1;
	heap_sinkLightElement(&heap, 0);
	heap_destroy(&heap);
	
	return 0;
}



int pq_removeMin(PriorityQueue *pq, void **key, void **data) {
	
	Heap heap;
	PQnode *pNodeMin;
	
	if (pq->nodeCount == 0)
		return -1;
	
	
	/* Detect current Heap Orientation this PQ is using */
	/* If current Heap Orientation is MAX HEAP, transform it to MIN HEAP */
	if (pq->heapState == PQ_HEAP_MAX) {
		heap_init(&heap, (void *) pq->pNodeArray, pq->nodeCount, sizeof(PQnode), pq_nodeCompare);
		heap_buildMinHeap(&heap);
		heap_destroy(&heap);
		pq->heapState = PQ_HEAP_MIN;
	}
	
	
	/* Access data to transfer to the caller */
	pNodeMin = pq->pNodeArray + 0;
	if (key != 0) *key = pNodeMin->key;
	if (data != 0) *data = pNodeMin->data;
	pq->nodeCount = pq->nodeCount - 1;
	
	
	/* We need to maintain the HEAP Property */
	/* Apply HEAP algorithm, by creating a heap, call function and destroy heap */
	heap_init(&heap, (void *) pq->pNodeArray, pq->nodeCount + 1, sizeof(PQnode), pq_nodeCompare);
	heap_exchangeElement(0, heap.elemCount - 1, &heap);
	heap.elemCount = heap.elemCount - 1;
	heap_sinkHeavyElement(&heap, 0);
	heap_destroy(&heap);
	
	return 0;
}

