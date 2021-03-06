#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Graph.h"

void testGraphEdges(Graph* pGraph);
GraphNode** aStarSearch(Graph* pGraph, char* pTo, char* pFrom);
void sortArray(GraphNode* pArray[], int pArraySize);
float getStraightLineDist(GraphNode* pTo, GraphNode* pFrom);
bool isNodeInArray(GraphNode* pArray[], int pArraySize, char* pNodeName);
void shiftArrayLeft(GraphNode* pArray[], int pArraySize);

/**
* @brief Main. Creates graph from text file and tests paths
*/
int main(int argc, char** argv) {

	/*printf("Enter name of data file:\n");

	char strvar[100];
	fgets (strvar, 100, stdin);*/

	FILE * fp;
	char* fileName = "graphData2.txt";
	char * line = NULL;
	size_t len = 0;

	fp = fopen(fileName, "r");
	if(fp == NULL) {
		printf("ERROR: Couldn't open %s for reading\n", fileName);
		exit(0);
	}

	int  xPos, yPos, weight;
	char* 	nodeCount 	= malloc(sizeof *nodeCount);
	char* 	edgeCount 	= malloc(sizeof *edgeCount);
	char* 	pathCount 	= malloc(sizeof *pathCount);
	char* 	title 		= malloc(sizeof *title);
	Graph* 	mGraph 		= malloc(sizeof *mGraph);

	// Read line NODES from file
	getline(&title, &len, fp);
	// Read number of nodes from file
	getline(&nodeCount, &len, fp);
	// Init graph to size nodeCount
	initGraph(mGraph, atoi(nodeCount));

	// Add nodes to graph
	int i;
	for(i = 0; i < atoi(nodeCount); i++) {

		char* nodePtr = malloc(sizeof *nodePtr);
		getline(&line, &len, fp);
		nodePtr = strdup(strtok (line," "));
		xPos = atoi(strtok(NULL, " "));
		yPos = atoi(strtok(NULL, " "));
		
		addNode(mGraph, nodePtr, xPos, yPos, i);
	}

	// Read line EDGES from file
	getline(&title, &len, fp);
	// Read number of edges from file
	getline(&edgeCount, &len, fp);
	
	// Add edges to graph nodes
	for(i = 0; i < atoi(edgeCount); i++) {

		char* to = malloc(sizeof *to);
		char* from = malloc(sizeof *from);;
		getline(&line, &len, fp);
		from = strdup(strtok (line," "));
		to = strdup(strtok (NULL," "));
		weight = atoi(strtok(NULL, " "));

		addArc(mGraph, from, to, weight);
	}

	// Read line PATHS from file
	getline(&title, &len, fp);
	// Read number of paths from file
	getline(&pathCount, &len, fp);
	
	GraphNode** path;
	
	// Test paths
	for(i = 0; i < atoi(pathCount); i++) {

		char* to = malloc(sizeof *to);
		char* from = malloc(sizeof *from);
		getline(&line, &len, fp);
		from = strdup(strtok (line," "));
		to = strdup(strtok (NULL," "));
		to[strcspn(to, "\n")] = '\0';
		
		path = aStarSearch(mGraph, from, to);

		// Print the path
		if(path != NULL) {		
			int index = 0;
			while(path[index]->mPrevious != NULL) {
				printf("%s", path[index]->mData);
				index++;
			}
			printf("%s\n", path[index]->mData);
		}

		resetGraph(mGraph);
	}

	//testGraphEdges(mGraph);

	fclose(fp);

	return 0;
}

/**
* @brief Performs and A Star search of the graph and prints the shortest path (If found) to the terminal
*
* @param pGraph The graph to search
* @param pStart The node at which to begin the search. 
* @param pEnd The destination node 
* @return GraphNode** The path found or NULL if no path was found
*/
GraphNode** aStarSearch(Graph* pGraph, char* pStart, char* pEnd) {

	GraphNode** openList = NULL;
	openList =  malloc(pGraph->mNodeCount *(sizeof *openList));
	int openListCount = 0;

	GraphNode* end = NULL;
	GraphNode* start = NULL;

	// Find start and end nodes
	int i;
	for(i = 0; i < pGraph->mNodeCount; ++i) {
		if(strcmp( pGraph->mNodes[i]->mData, pStart ) == 0) {
			start = pGraph->mNodes[i];
		}
		else if(strcmp( pGraph->mNodes[i]->mData, pEnd ) == 0) {
			end = pGraph->mNodes[i];
		}
	}
	// Set costs of start node
	start->mCost = 0;
	start->mCostToEnd = getStraightLineDist(start, end);

	// Add start node to the openList
	openList[openListCount] = start;
	openListCount++;
	
	while(openListCount != 0) {

		// Remove top node from the open list
		GraphNode* currentNode = openList[0];
		shiftArrayLeft(openList, openListCount);
		openListCount--;
		// Mark node as visited
		currentNode->mMarked = true;

		// If currentNode is the end a path has been found
		if( strcmp(currentNode->mData, pEnd) == 0 ) {

			// Place path nodes in an array and return it
			GraphNode** path = malloc(pGraph->mNodeCount * (sizeof *pGraph->mNodes));
			int index = 1;
			path[0] = end;
			printf("\nPath found from %s to %s:\n",pStart, pEnd);
			while(currentNode->mPrevious != NULL) {
				currentNode = currentNode->mPrevious;
				path[index] = currentNode;
				index++;
			}
			path[index] = start;

			return path;
		}

		// loop through all edges from current node
		ArcListNode* arcIter = currentNode->mArcListRoot;
		while(arcIter != NULL) {
			
			// If node is not in closed list
			if(arcIter->mArc->mNode->mMarked == false) {

				float cost = currentNode->mCost + (getStraightLineDist(currentNode, arcIter->mArc->mNode)*arcIter->mArc->mWeight);
 
				// If node is not in open list
				if(isNodeInArray(openList, openListCount, arcIter->mArc->mNode->mData) == false /*|| cost < arcIter->mArc->mNode->mCost*/) {

					arcIter->mArc->mNode->mPrevious = currentNode;
					arcIter->mArc->mNode->mCost = cost;
					arcIter->mArc->mNode->mCostToEnd = cost + getStraightLineDist(arcIter->mArc->mNode, end);
					openList[openListCount] = arcIter->mArc->mNode;
					openListCount++;
				}
				else if(isNodeInArray(openList, openListCount, arcIter->mArc->mNode->mData) == true) {
					// If the node is in the open list
					// Find the index of the node
					int index = -1;
					for(i = 0; i < openListCount; i++) {
						if( strcmp(arcIter->mArc->mNode->mData, openList[i]->mData) == 0) {
							index = i;
						}
					}
			
					if(index != -1) {
						// Check costs and update if new cost is lower
						if(cost < openList[index]->mCost) {

							openList[index]->mPrevious = currentNode;
							openList[index]->mCost = cost;
							openList[index]->mCostToEnd = cost + getStraightLineDist(arcIter->mArc->mNode, end);
						}		
					}		
				}
			}
			// Get next edge
			arcIter = arcIter->mNext;
		}

		sortArray(openList, openListCount);
	}
	
	printf("\nNo path found from %s to %s\n",pStart, pEnd);
	return NULL;
}

/**
* @brief Sorts array of nodes based on the nodes total cost
*
* @param pArray The array to sort
* @param pArraySize the lenght of the array to be sorted
*/
void sortArray(GraphNode* pArray[], int pArraySize) {

	bool sorting = true;
	
	while(sorting) {

		sorting = false;
		int i;
		for(i = 0; i < pArraySize; ++i) {
			if(i+1 < pArraySize) {
				if( (pArray[i+1]->mCost + pArray[i+1]->mCostToEnd) < (pArray[i]->mCost + pArray[i]->mCostToEnd) ) {
					
					GraphNode* temp = pArray[i+1];
					pArray[i+1] = pArray[i];
					pArray[i] = temp;
			
					sorting = true;
				}
			}
		}
	}
}

/**
* @brief Gets the straight line distance between two nodes
*
* @param pFrom Node from which to begin
* @param pTo Node at which to end
*/
float getStraightLineDist(GraphNode* pFrom, GraphNode* pTo) {

	float distance = 0;

	int x1 = pFrom->xPos;
	int y1 = pFrom->yPos;
	int x2 = pTo->xPos;
	int y2 = pTo->yPos;

	distance = sqrt( ((x2-x1)*(x2-x1)) + ((y2-y1)*(y2-y1)) );

	return distance;
}

/**
* @brief Checks if a node is present is an array
*
* @param pArray The array to search
* @param pArraySize The size of the array to search
* @param pNodeName The node to search for 
*/
bool isNodeInArray(GraphNode* pArray[], int pArraySize, char* pNodeName) {

	int i;
	for(i = 0; i < pArraySize; ++i) {
		if( strcmp(pArray[i]->mData, pNodeName) == 0 ) {
			return true;
		}
	}

	return false;
}

/**
* @brief Shifts all elements in the array one index left
*
* @param pArray The array to modify
* @param pArraySize The size of the array
*/
void shiftArrayLeft(GraphNode* pArray[], int pArraySize) {

	int i;
	for(i = 0; i < pArraySize; ++i) {
		if(i+1 < pArraySize) {
			pArray[i] = pArray[i+1];
		}
	}
}

/**
* @brief Prints all graph connections to the terminal
*
* @param pGraph The graph to test
*/
void testGraphEdges(Graph* pGraph) {

	printf("\nEdge Tests:\n");
	GraphNode* tempNode;

	int i;
	for(i = 0; i < pGraph->mNodeCount; i++) {
	
		tempNode = pGraph->mNodes[i];
		ArcListNode* arcIter = tempNode->mArcListRoot;
		printf("Node %s is connected to nodes: ", tempNode->mData);

		while(arcIter != NULL) {
			
			printf("%s, ", arcIter->mArc->mNode->mData);
			arcIter = arcIter->mNext;
		}

		printf("\n");
	}
}
