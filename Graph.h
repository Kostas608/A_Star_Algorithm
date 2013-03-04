
#ifndef GRAPH_H
#define GRAPH_H

#include "GraphNode.h"

/**
* @brief Graph containing an array of nodes
*/
typedef struct {
	
	/**
	* @brief Current number of nodes in the graph
	*/
	int mNodeCount;
	/**
	* @brief Maximum number of nodes in the graph
	*/
	int mMaxNodes;
	/**
	* @brief Array of nodes in the graph
	*/
	GraphNode** mNodes;

}Graph;

/**
* @brief Initializes the graph to a specified size
*
* @param pGraph The graph to initialize
* @param pSize The to initialize the grph to
*/
void initGraph(Graph* pGraph, int pSize) {
	
	pGraph->mNodeCount = 0;
	pGraph->mMaxNodes = pSize;
	pGraph->mNodes = malloc(pSize * sizeof *pGraph->mNodes);
}

/**
* @brief Adds a node to the graph
*
* @param pGraph The graph to add the node to
* @param pData The name of the node
* @param pX The x coordinate of the node
* @param pY The y coordinate of the node
* @param pIndex The index of the array to add the node to
*/
bool addNode(Graph* pGraph, char* pData, int pX, int pY, int pIndex) {

	if(pGraph->mNodes[pIndex] == NULL) {
		GraphNode* temp = malloc(sizeof *temp);
		initGraphNode(temp, pData, pX, pY);

		pGraph->mNodes[pIndex] = temp;
		pGraph->mNodeCount++;
		//printf("Added node %s to graph\n", pData);
		return true;
	}
	else {
		printf("WARNING: Attempted to create node %s at index %d. Index already in use\n", pData, pIndex);
		return false;
	}
}

/**
* @brief Adds an arc(edge) to the graph
*
* @param pGraph The graph to add the arc to
* @param pFrom The node the arc begins at
* @param pTo The node the arc ends at
* @param pWeight The weight of the arc
*/
bool addArc(Graph* pGraph, char* pFrom, char* pTo, int pWeight) {
	
	int fromIndex = -1;
	int toIndex = -1;

	int i;
	for(i = 0; i < pGraph->mNodeCount; ++i) {
		if(strcmp( pGraph->mNodes[i]->mData, pFrom ) == 0) {
			fromIndex = i;
		}
		else if(strcmp( pGraph->mNodes[i]->mData, pTo ) == 0) {
			toIndex = i;
		}
	}

	if(fromIndex == -1 || toIndex == -1) {
		// Nodes not found
		printf("WARNING: Attempted to create arc from nodes %s, to %s. One or more nodes not found\n", pFrom, pTo);
		return false;
	}
	else {
		
		if(pGraph->mNodes[fromIndex]->mArcListRoot == NULL) {
			// Create new arc root
			createRootArc(pGraph->mNodes[fromIndex], pGraph->mNodes[toIndex], pWeight);
			//printf("Created root arc at node %s, to node %s\n", pFrom, pTo);
			return true;
		}
		else {
			// Add new arc to list
			// Update pointer in existing arc
			createNewArc(pGraph->mNodes[fromIndex], pGraph->mNodes[toIndex], pWeight);
			//printf("Added new arc to node %s, to node %s\n", pFrom, pTo);
			return true;
		}
	}
}

/**
* @brief Resets the nodes in the graph to their initial values
*
* @param pGraph The graph to reset
*/
void resetGraph(Graph* pGraph) {

	int i;
	for(i = 0; i < pGraph->mNodeCount; i++) {
		pGraph->mNodes[i]->mPrevious = NULL;
		pGraph->mNodes[i]->mMarked = false;
		pGraph->mNodes[i]->mCost = 500;
		pGraph->mNodes[i]->mCostToEnd = 500;
	}
}

#endif

