
#ifndef GRAPHNODE_H
#define GRAPHNODE_H

typedef struct ArcListNode ArcListNode;

#include "ArcList.h"

typedef short bool;
#define true 1
#define false 0

struct GraphNode {

	char* mData;
	bool mMarked;
	int xPos;
	int yPos;
	GraphNode* mPrevious;
	ArcListNode* mArcListRoot;
};

void initGraphNode(GraphNode* pNode, char* pData, int pX, int pY) {

	pNode->mData = pData;
	pNode->mMarked = false;
	pNode->mPrevious = NULL;
	pNode->mArcListRoot = NULL;
	pNode->xPos = pX;
	pNode->yPos = pY;
}

void createNewArc(GraphNode* pFrom, GraphNode* pTo, int pWeight) {
	
	ArcListNode* arcListIter = pFrom->mArcListRoot;
	
	while(arcListIter->mNext != NULL) {
		arcListIter = arcListIter->mNext;
	}

	ArcListNode* tempNode = malloc(sizeof *tempNode);
	GraphArc* tempArc = malloc(sizeof *tempArc);
	
	tempArc->mNode = pTo;
	tempArc->mWeight = pWeight;

	tempNode->mArc = tempArc;
	tempNode->mNext = NULL;
	
	arcListIter->mNext = tempNode;
}

void createRootArc(GraphNode* pFrom, GraphNode* pTo, int pWeight) {
	
	ArcListNode* tempNode = malloc(sizeof *tempNode);
	GraphArc* tempArc = malloc(sizeof *tempArc);
	
	tempArc->mNode = pTo;
	tempArc->mWeight = pWeight;

	tempNode->mArc = tempArc;
	tempNode->mNext = NULL;
	
	pFrom->mArcListRoot = tempNode;
}

#endif
