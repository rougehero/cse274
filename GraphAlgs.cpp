#include "GraphAlgs.h"

using namespace std;


EdgeWeight findWeightTotal(int* vertexArray, Graph* G){

	EdgeWeight weightTotal = 0;
	for(int i=0;i<G->size()-1;i++){
		weightTotal += G->weight(vertexArray[i], vertexArray[i+1]);
	}
	weightTotal += G->weight(vertexArray[G->size()-1], vertexArray[0]);
	return weightTotal;
}


pair<vector<NodeID>, EdgeWeight> TSP(Graph* G){
	int num_nodes = G->size();
	int* vertexArray = new int[num_nodes];

	for(int i = 0; i<num_nodes;i++){
		vertexArray[i]=i;
	}

	vector<NodeID> shortest(num_nodes); 
	EdgeWeight weight = 0;
	EdgeWeight shortTemp = DBL_MAX;
	for(int i=0;i<num_nodes;i++){
	do{

		weight = findWeightTotal(vertexArray, G);
		if(weight < shortTemp){
			shortTemp = weight;
			for(int i = 0;i<num_nodes;i++){
				shortest[i] = vertexArray[i];
			}
		}
	} while (next_permutation(vertexArray, vertexArray+num_nodes));
}
	return pair<vector<NodeID>, EdgeWeight>(shortest ,shortTemp);

}
