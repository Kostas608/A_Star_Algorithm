
#ifndef GRAPHARC_H
#define GRAPHARC_H

typedef struct GraphNode GraphNode;

#include "GraphNode.h"

/**
* @brief An arc containing a weight and a pointer to the node the arc points to
*/
struct GraphArc {
	
	/**
	* @brief The node the arc points to
	*/
	GraphNode* mNode;
	/**
	* @brief The weight of the arc
	*/
	int mWeight;
};

#endif
