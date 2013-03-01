
#ifndef LIST_H
#define LIST_H

typedef struct GraphArc GraphArc;

#include "GraphArc.h"

/**
* @brief A list node containing an arc and a pointer to the next node in the list
*/
struct ArcListNode {

	/**
	* @brief The arc contained at this node
	*/
	GraphArc* mArc;
	/**
	* @brief Pointer to next listNode in the list
	*/
	ArcListNode* mNext;
};

#endif
