#pragma once

#include "GraphNode.h"

struct GraphArc {
	
	// Node the arc points to
	struct GraphNode* mNode;
	int mWeight;
};
