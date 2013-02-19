#include<stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char** argv) {

	struct Graph* mGraph = malloc(sizeof *mGraph);
	
	initGraph(mGraph, 10);

	addNode(mGraph, "a", 0);
	addNode(mGraph, "b", 1);
	addNode(mGraph, "c", 2);

	addArc(mGraph, "a", "b", 1);
	addArc(mGraph, "a", "c", 1);

	//printf("%c", mGraph->mNodes[0]->mArcListRoot->mNext->mArc->mNode->mData[0]);

	return 0;
}
