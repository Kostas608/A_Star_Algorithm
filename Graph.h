
#ifndef GRAPH_H
#define GRAPH_H

#include "GraphNode.h"

typedef struct {
	
	int mNodeCount;
	int mMaxNodes;
	GraphNode** mNodes;
}Graph;

void initGraph(Graph* pGraph, int pSize) {
	
	pGraph->mNodeCount = 0;
	pGraph->mMaxNodes = pSize;
	pGraph->mNodes = malloc(pSize * sizeof *pGraph->mNodes);
}

bool addNode(Graph* pGraph, char* pData, int pX, int pY, int pIndex) {

	if(pGraph->mNodes[pIndex] == NULL) {
		GraphNode* temp = malloc(sizeof *temp);
		initGraphNode(temp, pData, pX, pY);

		pGraph->mNodes[pIndex] = temp;
		pGraph->mNodeCount++;
		printf("Added node %s to graph\n", pData);
		return true;
	}
	else {
		printf("WARNING: Attempted to create node %s at index %d. Index already in use\n", pData, pIndex);
		return false;
	}
}

bool addArc(Graph* pGraph, char* pFrom, char* pTo, int pWeight) {
	
	int fromIndex = -1;
	int toIndex = -1;

	int i;
	for(i = 0; i < pGraph->mNodeCount; ++i) {
		if(strcmp( pGraph->mNodes[i]->mData, pFrom ) == 0) {
			fromIndex = i;
		}
		else if(strcmp( pGraph->mNodes[i]->mData, pTo ) == 0) {
			toIndex = i;
		}
	}

	if(fromIndex == -1 || toIndex == -1) {
		// Nodes not found
		printf("WARNING: Attempted to create arc from nodes %s, to %s. One or more nodes not found\n", pFrom, pTo);
		return false;
	}
	else {
		
		if(pGraph->mNodes[fromIndex]->mArcListRoot == NULL) {
			// Create new arc root
			createRootArc(pGraph->mNodes[fromIndex], pGraph->mNodes[toIndex], pWeight);
			printf("Created root arc at node %s, to node %s\n", pFrom, pTo);
			return true;
		}
		else {
			// Add new arc to list
			// Update pointer in existing arc
			createNewArc(pGraph->mNodes[fromIndex], pGraph->mNodes[toIndex], pWeight);
			printf("Added new arc to node %s, to node %s\n", pFrom, pTo);
			return true;
		}
	}
}


void resetGraph(Graph* pGraph) {

	int i;
	for(i = 0; i < pGraph->mNodeCount; i++) {
		pGraph->mNodes[i]->mPrevious = NULL;
		pGraph->mNodes[i]->mCost = 0;
		pGraph->mNodes[i]->mCostToEnd = 0;
	}
}


#endif

