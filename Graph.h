#pragma once

#include "GraphNode.h"

struct Graph {
	
	int mNodeCount;
	int mMaxNodes;
	struct GraphNode* mNodes[10];
};

void initGraph(struct Graph* pGraph, int pSize) {
	
	pGraph->mNodeCount = 0;
	pGraph->mMaxNodes = pSize;
}

bool addNode(struct Graph* pGraph, char* pData, int pIndex) {

	struct GraphNode* temp = malloc(sizeof *temp);
	initGraphNode(temp, pData);

	pGraph->mNodes[pIndex] = temp;
	pGraph->mNodeCount++;

	//printf("%c", pGraph->mNodes[pIndex]->mData[0]);
}

bool addArc(struct Graph* pGraph, char* pFrom, char* pTo, int pWeight) {
	
	int fromIndex = -1;
	int toIndex = -1;

	int i;
	for(i = 0; i < pGraph->mNodeCount; ++i) {
		if(pGraph->mNodes[i]->mData == pFrom) {
			fromIndex = i;
		}
		else if(pGraph->mNodes[i]->mData == pTo) {
			toIndex = i;
		}
	}

	if(fromIndex == -1 || toIndex == -1) {
		// Nodes not found
		return false;
	}
	else {
		
		if(pGraph->mNodes[fromIndex]->mArcListRoot == NULL) {
			// Create new arc root
		}
		else {
			// Add new arc to list
			// Update pointer in existing arc
		}
	}
}

