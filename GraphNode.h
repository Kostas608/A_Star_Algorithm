#pragma once

#include "List.h"

typedef short bool;
#define true 1
#define false 0

struct GraphNode {

	char* mData;
	bool mMarked;
	struct GraphNode* mPrevious;
	struct ListNode* mArcListRoot;
};

void initGraphNode(struct GraphNode* pNode, char* pData) {

	pNode->mData = pData;
	pNode->mMarked = false;
	pNode->mPrevious = NULL;
	pNode->mArcListRoot = NULL;
}

void createNewArc(struct GraphNode* pFrom, struct GraphNode* pTo, int pWeight) {
	
	struct ListNode* arcListIter = pFrom->mArcListRoot;
	
	while(arcListIter->mNext != NULL) {
		arcListIter = arcListIter->mNext;
	}

	struct ListNode* tempNode = malloc(sizeof *tempNode);
	struct GraphArc* tempArc = malloc(sizeof *tempArc);
	
	tempArc->mNode = pTo;
	tempArc->mWeight = pWeight;

	tempNode->mArc = tempArc;
	tempNode->mNext = NULL;
	
	arcListIter->mNext = tempNode;
}

void createRootArc(struct GraphNode* pFrom, struct GraphNode* pTo, int pWeight) {
	
	struct ListNode* tempNode = malloc(sizeof *tempNode);
	struct GraphArc* tempArc = malloc(sizeof *tempArc);
	
	tempArc->mNode = pTo;
	tempArc->mWeight = pWeight;

	tempNode->mArc = tempArc;
	tempNode->mNext = NULL;
	
	pFrom->mArcListRoot = tempNode;
}
