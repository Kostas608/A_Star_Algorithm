
#ifndef LIST_H
#define LIST_H

typedef struct GraphArc GraphArc;

#include "GraphArc.h"

struct ArcListNode {

	GraphArc* mArc;
	ArcListNode* mNext;
};

#endif
