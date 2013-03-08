
#ifndef GRAPHNODE_H
#define GRAPHNODE_H

typedef struct ArcListNode ArcListNode;

#include "ArcList.h"

typedef short bool;
#define true 1
#define false 0

/**
* @brief A graph node
*/
struct GraphNode {

	/**
	* @brief The name of the node
	*/
	char* mData;
	/**
	* @brief Has the node been visited
	*/
	bool mMarked;
	/**
	* @brief The x coordinate of the node
	*/
	int xPos;
	/**
	* @brief The y coordinate of the node
	*/
	int yPos;
	/**
	* @brief The cost to get to this node
	*/
	float mCost;
	/**
	* @brief The cost to get from this node to the destination
	*/
	float mCostToEnd;
	/**
	* @brief Pointer to previous node visited
	*/
	GraphNode* mPrevious;
	/**
	* @brief Pointer to the root of the list of arcs(edges) this node has
	*/
	ArcListNode* mArcListRoot;
};

/**
* @brief Initializes a graph node
*
* @param pNode The graph node to initialize
* @param pData The name of the node
* @param pX The x coordinate of the node
* @param pY The y coordinate of the node
*/
void initGraphNode(GraphNode* pNode, char* pData, int pX, int pY) {

	pNode->mData = pData;
	pNode->mMarked = false;
	pNode->mPrevious = NULL;
	pNode->mArcListRoot = NULL;
	pNode->xPos = pX;
	pNode->yPos = pY;
	pNode->mCost = 500;
	pNode->mCostToEnd = 500;
}

/**
* @brief Creates a new arc
*
* @param pFrom The graph node the erc begins at
* @param pTo The graph node the arc ends at
* @param pWeight The weight of the arc
*/
void createNewArc(GraphNode* pFrom, GraphNode* pTo, int pWeight) {
	
	ArcListNode* arcListIter = pFrom->mArcListRoot;
	
	while(arcListIter->mNext != NULL) {
		arcListIter = arcListIter->mNext;
	}

	ArcListNode* tempNode = malloc(sizeof *tempNode);
	GraphArc* tempArc = malloc(sizeof *tempArc);
	
	tempArc->mNode = pTo;
	tempArc->mWeight = pWeight;

	tempNode->mArc = tempArc;
	tempNode->mNext = NULL;
	
	arcListIter->mNext = tempNode;
}

/**
* @brief Creates a new root arc
*
* @param pFrom The graph node the erc begins at
* @param pTo The graph node the arc ends at
* @param pWeight The weight of the arc
*/
void createRootArc(GraphNode* pFrom, GraphNode* pTo, int pWeight) {
	
	ArcListNode* tempNode = malloc(sizeof *tempNode);
	GraphArc* tempArc = malloc(sizeof *tempArc);
	
	tempArc->mNode = pTo;
	tempArc->mWeight = pWeight;

	tempNode->mArc = tempArc;
	tempNode->mNext = NULL;
	
	pFrom->mArcListRoot = tempNode;
}

#endif
