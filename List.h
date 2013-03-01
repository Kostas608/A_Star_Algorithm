#pragma once

#include "GraphArc.h"

/**
* @brief A list node containing an arc and a pointer to the next node in the list
*/
struct ListNode {
	
	/**
	* @brief The arc contained at this node
	*/
	struct GraphArc* mArc;
	/**
	* @brief Pointer to next listNode in the list
	*/
	struct ListNode* mNext;
};
