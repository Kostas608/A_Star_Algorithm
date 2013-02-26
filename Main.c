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

	Graph* mGraph = malloc(sizeof *mGraph);
	
	int  xPos, yPos, weight;
	char* nodeCount = malloc(sizeof *nodeCount);
	char* edgeCount = malloc(sizeof *edgeCount);
	char* pathCount = malloc(sizeof *pathCount);
	char* title = malloc(sizeof *title);

	getline(&title, &len, fp);
	getline(&nodeCount, &len, fp);

	initGraph(mGraph, atoi(nodeCount));

	int i;
	for(i = 0; i < atoi(nodeCount); i++) {

		char* nodePtr = malloc(sizeof *nodePtr);
		getline(&line, &len, fp);
		nodePtr = strdup(strtok (line," "));
		xPos = atoi(strtok(NULL, " "));
		yPos = atoi(strtok(NULL, " "));
		
		addNode(mGraph, nodePtr, xPos, yPos, i);
	}

	getline(&title, &len, fp);

	getline(&edgeCount, &len, fp);
	
	for(i = 0; i < atoi(edgeCount); i++) {

		char* to = malloc(sizeof *to);
		char* from = malloc(sizeof *from);;
		getline(&line, &len, fp);
		from = strdup(strtok (line," "));
		to = strdup(strtok (NULL," "));
		weight = atoi(strtok(NULL, " "));

		addArc(mGraph, from, to, weight);
	}

	getline(&title, &len, fp);

	getline(&pathCount, &len, fp);

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

void aStarSearch(Graph* pGraph, char* pStart, char* pEnd) {
	
	GraphNode* openList[pGraph->mNodeCount];
	int openListCount = 0;

	GraphNode* end;
	GraphNode* start;

	int i;
	for(i = 0; i < pGraph->mNodeCount; ++i) {
		if(strcmp( pGraph->mNodes[i]->mData, pStart ) == 0) {
			start = pGraph->mNodes[i];
		}
		else if(strcmp( pGraph->mNodes[i]->mData, pEnd ) == 0) {
			end = pGraph->mNodes[i];
		}
	}

	start->mCost = 0;
	start->mCostToEnd = getStraightLineDist(start, end);

	openList[openListCount] = start;
	openListCount++;

	while(openListCount != 0) {

		GraphNode* currentNode = openList[0];
		shiftArrayLeft(openList, pGraph->mNodeCount);
		openListCount--;

		if( strcmp(currentNode->mData, pEnd) == 0 ) {

			//Path found	
			printf("\nPath found from %s to %s:\n%s",pStart, pEnd, pEnd);
			while(currentNode->mPrevious != NULL) {
				printf("%s", currentNode->mPrevious->mData);
				currentNode = currentNode->mPrevious;
			}
			printf("\n");
			return;
		}

		currentNode->mMarked = true;

		ArcListNode* arcIter = currentNode->mArcListRoot;
		while(arcIter != NULL) {
			
			if(arcIter->mArc->mNode->mMarked == false) {

				int cost = currentNode->mCost + (getStraightLineDist(currentNode, arcIter->mArc->mNode)*arcIter->mArc->mWeight);
 
				if(isNodeInArray(openList, openListCount, arcIter->mArc->mNode->mData) == false || cost < arcIter->mArc->mNode->mCost) {

					arcIter->mArc->mNode->mPrevious = currentNode;
					arcIter->mArc->mNode->mCost = cost;
					arcIter->mArc->mNode->mCostToEnd = getStraightLineDist(arcIter->mArc->mNode, end);
					openList[openListCount] = arcIter->mArc->mNode;
					openListCount++;
				}
			}

			arcIter = arcIter->mNext;
		}
		
		sortArray(openList, openListCount);
	}

	printf("\nNo path found from %s to %s\n",pStart, pEnd);
}

void sortArray(GraphNode* pArray[], int pArraySize) {

	bool sorting = true;
	
	while(sorting) {

		sorting = false;
		int i;
		for(i = 0; i < pArraySize; ++i) {
			if(i+1 < pArraySize) {
				if( (pArray[i+1]->mCost + pArray[i+1]->mCostToEnd) < (pArray[i]->mCost + pArray[i]->mCostToEnd) ) {
					
					GraphNode temp = *pArray[i+1];
					*pArray[i+1] = *pArray[i];
					*pArray[i] = temp;
			
					sorting = true;
				}
			}
		}
	}
}

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

bool isNodeInArray(GraphNode* pArray[], int pArraySize, char* pNodeName) {

	int i;
	for(i = 0; i < pArraySize; ++i) {
		if( strcmp(pArray[i]->mData, pNodeName) == 0 ) {
			return true;
		}
	}

	return false;
}

void shiftArrayLeft(GraphNode* pArray[], int pArraySize) {

	int i;
	for(i = 0; i < pArraySize; ++i) {
		if(i+1 < pArraySize) {
			pArray[i] = pArray[i+1];
		}
	}
}

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
