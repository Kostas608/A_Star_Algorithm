
#ifndef GRAPH_H
#define GRAPH_H

#include "GraphNode.h"

typedef struct {
	
	int mNodeCount;
	int mMaxNodes;
	struct GraphNode** mNodes;
}Graph;

void initGraph(Graph* pGraph, int pSize) {
	
	pGraph->mNodeCount = 0;
	pGraph->mMaxNodes = pSize;
	pGraph->mNodes = malloc(pSize * sizeof *pGraph->mNodes);
}

bool addNode(Graph* pGraph, char* pData, int pX, int pY, int pIndex) {

	//if(pGraph->mNodes[pIndex] == NULL) {
		struct GraphNode* temp = malloc(sizeof *temp);
		initGraphNode(temp, pData, pX, pY);

		pGraph->mNodes[pIndex] = temp;
		pGraph->mNodeCount++;
		//printf("%d", pIndex);
		printf("Added node %s to graph\n", pData);
		return true;
	/*}
	else {
		printf("WARNING: Attempted to create node %s at index %d. Index already in use\n", pData, pIndex);
		return false;
	}*/
}

bool addArc(Graph* pGraph, char pFrom, char pTo, int pWeight) {
	
	int fromIndex = -1;
	int toIndex = -1;

	int i;
	for(i = 0; i < pGraph->mNodeCount; ++i) {
		if(*pGraph->mNodes[i]->mData == pFrom) {
			fromIndex = i;
		}
		else if(*pGraph->mNodes[i]->mData == pTo) {
			toIndex = i;
		}
	}

	if(fromIndex == -1 || toIndex == -1) {
		// Nodes not found
		printf("WARNING: Attempted to create arc from nodes %c, to %c. One or more nodes not found\n", pFrom, pTo);
		return false;
	}
	else {
		
		if(pGraph->mNodes[fromIndex]->mArcListRoot == NULL) {
			// Create new arc root
			createRootArc(pGraph->mNodes[fromIndex], pGraph->mNodes[toIndex], pWeight);
			printf("Created root arc at node %c, to node %c\n", pFrom, pTo);
			return true;
		}
		else {
			// Add new arc to list
			// Update pointer in existing arc
			createNewArc(pGraph->mNodes[fromIndex], pGraph->mNodes[toIndex], pWeight);
			printf("Added new arc to node %c, to node %c\n", pFrom, pTo);
			return true;
		}
	}
}

#endif

