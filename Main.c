#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"

void testGraphConnections(Graph* pGraph);

int main(int argc, char** argv) {


	FILE * fp;
	char* fileName = "graphData.txt";
	char * line = NULL;
	size_t len = 0;
	ssize_t read;

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

	read = getline(&title, &len, fp);
	read = getline(&nodeCount, &len, fp);

	initGraph(mGraph, (nodeCount[0]-'0'));

	int i;
	for(i = 0; i < (nodeCount[0]-'0'); i++) {

		char* pch;
		char nodeName;
		read = getline(&line, &len, fp);
		pch = strtok (line," ");
		nodeName = *pch;
		char* nodePtr = malloc(sizeof *nodePtr);
		*nodePtr = nodeName;
		xPos = strtok(NULL, " ")[0] - '0';
		yPos = strtok(NULL, " ")[0] - '0';
		
		addNode(mGraph, nodePtr, xPos, yPos, i);
	}

	read = getline(&title, &len, fp);
	read = getline(&edgeCount, &len, fp);

	for(i = 0; i < (edgeCount[0]-'0'); i++) {
		char to, from;
		
		char* pch;
		read = getline(&line, &len, fp);
		pch = strtok (line," ");
		from = *pch;
		pch = strtok (NULL," ");
		to = *pch;
		weight = strtok(NULL, " ")[0] - '0';

		addArc(mGraph, from, to, weight);
	}

	testGraphConnections(mGraph);

	fclose(fp);

	return 0;
}

void testGraphConnections(Graph* pGraph) {

	printf("\n");
	struct GraphNode* tempNode;

	int i;
	for(i = 0; i < pGraph->mNodeCount; i++) {
	
		tempNode = pGraph->mNodes[i];
		struct ArcListNode* arcIter = tempNode->mArcListRoot;
		printf("Node %s is connected to nodes: ", tempNode->mData);

		while(arcIter != NULL) {
			
			printf("%s, ", arcIter->mArc->mNode->mData);
			arcIter = arcIter->mNext;
		}

		printf("\n");
	}
}
