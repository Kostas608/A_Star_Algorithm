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
