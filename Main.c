#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

void testGraphEdges(Graph* pGraph);

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

	testGraphEdges(mGraph);

	fclose(fp);

	return 0;
}

void testGraphEdges(Graph* pGraph) {

	printf("\n");
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
