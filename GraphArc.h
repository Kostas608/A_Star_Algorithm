
#ifndef GRAPHARC_H
#define GRAPHARC_H

#include "GraphNode.h"

struct GraphArc {
	
	// Node the arc points to
	struct GraphNode* mNode;
	int mWeight;
};

#endif
