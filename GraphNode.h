
#ifndef GRAPHNODE_H
#define GRAPHNODE_H

#include "ArcList.h"

typedef short bool;
#define true 1
#define false 0

struct GraphNode {

	char* mData;
	bool mMarked;
	int xPos;
	int yPos;
	struct GraphNode* mPrevious;
	struct ArcListNode* mArcListRoot;
};

void initGraphNode(struct GraphNode* pNode, char* pData, int pX, int pY) {

	pNode->mData = pData;
	pNode->mMarked = false;
	pNode->mPrevious = NULL;
	pNode->mArcListRoot = NULL;
	pNode->xPos = pX;
	pNode->yPos = pY;
}

void createNewArc(struct GraphNode* pFrom, struct GraphNode* pTo, int pWeight) {
	
	struct ArcListNode* arcListIter = pFrom->mArcListRoot;
	
	while(arcListIter->mNext != NULL) {
		arcListIter = arcListIter->mNext;
	}

	struct ArcListNode* tempNode = malloc(sizeof *tempNode);
	struct GraphArc* tempArc = malloc(sizeof *tempArc);
	
	tempArc->mNode = pTo;
	tempArc->mWeight = pWeight;

	tempNode->mArc = tempArc;
	tempNode->mNext = NULL;
	
	arcListIter->mNext = tempNode;
}

void createRootArc(struct GraphNode* pFrom, struct GraphNode* pTo, int pWeight) {
	
	struct ArcListNode* tempNode = malloc(sizeof *tempNode);
	struct GraphArc* tempArc = malloc(sizeof *tempArc);
	
	tempArc->mNode = pTo;
	tempArc->mWeight = pWeight;

	tempNode->mArc = tempArc;
	tempNode->mNext = NULL;
	
	pFrom->mArcListRoot = tempNode;
}

#endif
