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

int main(int argc, char** argv) {


	FILE * fp;
	char* fileName = "graphData.txt";
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
	char* title = malloc(sizeof *title);

	getline(&title, &len, fp);
	getline(&nodeCount, &len, fp);

	initGraph(mGraph, (nodeCount[0]-'0'));

	int i;
	for(i = 0; i < (nodeCount[0]-'0'); i++) {

		char* nodePtr = malloc(sizeof *nodePtr);
		getline(&line, &len, fp);
		nodePtr = strdup(strtok (line," "));
		xPos = strtok(NULL, " ")[0] - '0';
		yPos = strtok(NULL, " ")[0] - '0';
		
		addNode(mGraph, nodePtr, xPos, yPos, i);
	}

	getline(&title, &len, fp);

	getline(&edgeCount, &len, fp);
	printf("%d", (int *)edgeCount -'0');
	for(i = 0; i < (*edgeCount -'0'); i++) {

		char* to = malloc(sizeof *to);
		char* from = malloc(sizeof *from);;
		getline(&line, &len, fp);
		from = strdup(strtok (line," "));
		to = strdup(strtok (NULL," "));
		weight = strtok(NULL, " ")[0] - '0';

		addArc(mGraph, from, to, weight);
	}

	aStarSearch(mGraph, "a", "i");
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

	printf("%s %s", start->mData, end->mData);

	start->mCost = 0;
	start->mCostToEnd = getStraightLineDist(start, end);

	openList[openListCount] = start;
	openListCount++;

	while(openListCount != 0) {

		GraphNode* currentNode = openList[0];

		if(currentNode->mData == end->mData) {
			//Path found
			printf("found");
			return;
		}

		openListCount--;
		currentNode->mMarked = true;

		ArcListNode* arcIter = currentNode->mArcListRoot;
		while(arcIter != NULL) {
			
			if(arcIter->mArc->mNode->mMarked == false) {

				int cost = currentNode->mCost + getStraightLineDist(currentNode, arcIter->mArc->mNode);
 
				if(isNodeInArray(openList, openListCount, arcIter->mArc->mNode->mData) == false) {

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
}

void sortArray(GraphNode* pArray[], int pArraySize) {

	bool sorting = true;
	
	while(sorting) {

		sorting = false;
		int i;
		for(i = 0; i < pArraySize; ++i) {
			if(i+1 < pArraySize) {
				if( (pArray[i+1]->mCost + pArray[i+1]->mCostToEnd) > (pArray[i]->mCost + pArray[i]->mCostToEnd) ) {
					
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
		if(pArray[i]->mData == pNodeName) {
			return true;
		}
	}

	return false;
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
