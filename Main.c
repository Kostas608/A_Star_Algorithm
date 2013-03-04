#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Graph.h"

void testGraphEdges(Graph* pGraph);
void aStarSearch(Graph* pGraph, char* pTo, char* pFrom);
void sortArray(GraphNode* pArray[], int pArraySize);
int getStraightLineDist(GraphNode* pTo, GraphNode* pFrom);
bool isNodeInArray(GraphNode* pArray[], int pArraySize, char* pNodeName);
void shiftArrayLeft(GraphNode* pArray[], int pArraySize);

/**
* @brief Main. Creates graph from text file and tests paths
*/
int main(int argc, char** argv) {


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
	
	// Test paths
	for(i = 0; i < atoi(pathCount); i++) {

		char* to = malloc(sizeof *to);
		char* from = malloc(sizeof *from);
		getline(&line, &len, fp);
		from = strdup(strtok (line," "));
		to = strdup(strtok (NULL," "));
		to[strcspn(to, "\n")] = '\0';
		
		aStarSearch(mGraph, from, to);
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
*/
void aStarSearch(Graph* pGraph, char* pStart, char* pEnd) {
	
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

			// Print path to terminal
			printf("\nPath found from %s to %s:\n%s",pStart, pEnd, pEnd);
			while(currentNode->mPrevious != NULL) {
				printf("%s", currentNode->mPrevious->mData);
				currentNode = currentNode->mPrevious;
			}
			printf("\n");
			return;
		}

		// loop through all edges from current node
		ArcListNode* arcIter = currentNode->mArcListRoot;
		while(arcIter != NULL) {
			
			if(arcIter->mArc->mNode->mMarked == false) {
				int cost = currentNode->mCost + (getStraightLineDist(currentNode, arcIter->mArc->mNode)*arcIter->mArc->mWeight);
 
				if(isNodeInArray(openList, openListCount, arcIter->mArc->mNode->mData) == false /*|| cost < arcIter->mArc->mNode->mCost*/) {

					arcIter->mArc->mNode->mPrevious = currentNode;
					arcIter->mArc->mNode->mCost = cost;
					arcIter->mArc->mNode->mCostToEnd = cost + getStraightLineDist(arcIter->mArc->mNode, end);
					openList[openListCount] = arcIter->mArc->mNode;
					openListCount++;
				}
				else if(isNodeInArray(openList, openListCount, arcIter->mArc->mNode->mData) == true) {
					// Check costs and update if new cost is lower
					
					for(i = 0; i < openListCount; i++) {
						
						if( strcmp(arcIter->mArc->mNode->mData, openList[i]->mData) == 0) {

							if(arcIter->mArc->mNode->mCost + arcIter->mArc->mNode->mCostToEnd < openList[i]->mCost + openList[i]->mCostToEnd) {

								arcIter->mArc->mNode->mPrevious = currentNode;
								arcIter->mArc->mNode->mCost = cost;
								arcIter->mArc->mNode->mCostToEnd = cost + getStraightLineDist(arcIter->mArc->mNode, end);
								openList[openListCount] = arcIter->mArc->mNode;
								openListCount++;
							}
						}		
					}
				}
			}
			
			arcIter = arcIter->mNext;
		}

		sortArray(openList, openListCount);
	}
	
	printf("\nNo path found from %s to %s\n",pStart, pEnd);
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
int getStraightLineDist(GraphNode* pFrom, GraphNode* pTo) {

	int distance = 0;

	int x1=0;
	int y1=0;
	int x2=0;
	int y2=0;

	x1 = pFrom->xPos;
	y1 = pFrom->yPos;
	x2 = pTo->xPos;
	y2 = pTo->yPos;

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
