
#ifndef LIST_H
#define LIST_H

#include "GraphArc.h"

struct ArcListNode {

	struct GraphArc* mArc;
	struct ArcListNode* mNext;
};

#endif
