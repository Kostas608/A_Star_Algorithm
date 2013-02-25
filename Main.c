#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

void testGraphEdges(Graph* pGraph);
void aStarSearch(Graph* pGraph, char* pTo, char* pFrom);
void sortArray(GraphNode* pArray[], int pArraySize);

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
	for(i = 0; i < (edgeCount[0]-'0'); i++) {

		char* to = malloc(sizeof *to);
		char* from = malloc(sizeof *from);;
		getline(&line, &len, fp);
		from = strdup(strtok (line," "));
		to = strdup(strtok (NULL," "));
		weight = strtok(NULL, " ")[0] - '0';

		addArc(mGraph, from, to, weight);
	}

	aStarSearch(mGraph, "c", "a");
	//testGraphEdges(mGraph);

	fclose(fp);

	return 0;
}

void aStarSearch(Graph* pGraph, char* pTo, char* pFrom) {

	GraphNode* openList[pGraph->mNodeCount];
	GraphNode* closedList[pGraph->mNodeCount];

	int openListCount = 0;
	int closedListCount = 0;

	GraphNode* to;
	GraphNode* from;

	int i;
	for(i = 0; i < pGraph->mNodeCount; ++i) {
		if(strcmp( pGraph->mNodes[i]->mData, pFrom ) == 0) {
			from = pGraph->mNodes[i];
		}
		else if(strcmp( pGraph->mNodes[i]->mData, pTo ) == 0) {
			to = pGraph->mNodes[i];
		}
	}

	openList[openListCount] = from;
	openListCount++;

	while(openListCount != 0) {

		GraphNode* tempNode = openList[0];
		openListCount--;
		closedList[closedListCount] = tempNode;
		closedListCount++;

		ArcListNode* arcIter = tempNode->mArcListRoot;
		while(arcIter != NULL) {
			
			openList[openListCount] = arcIter->mArc->mNode;
			openListCount++;
			arcIter = arcIter->mNext;
		}

		sortArray(openList, openListCount);
	}




	//sortArray(openList, openListCount);
	//printf("%s", openList[0]->mData);
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
