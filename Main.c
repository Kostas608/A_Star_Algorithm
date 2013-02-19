#include<stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main(int argc, char** argv) {

	struct Graph* mGraph = malloc(sizeof *mGraph);
	
	initGraph(mGraph, 10);

	addNode(mGraph, "a", 0);
	addNode(mGraph, "b", 1);

	return 0;
}
