
#ifndef GRAPHARC_H
#define GRAPHARC_H

typedef struct GraphNode GraphNode;

#include "GraphNode.h"

struct GraphArc {
	
	// Node the arc points to
	GraphNode* mNode;
	int mWeight;
};

#endif
