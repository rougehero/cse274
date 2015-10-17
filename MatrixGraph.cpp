#include "MatrixGraph.h"
#include <iostream>



using namespace std;

	MatrixGraph::MatrixGraph(unsigned numNodes){

		M=vector<vector<EdgeWeight>>(numNodes,vector<EdgeWeight>(numNodes, 0));
		num_edges = 0;
		
	}

  MatrixGraph::~MatrixGraph(){


  }

  void MatrixGraph::addEdge(NodeID u, NodeID v, EdgeWeight weight){

	  M[u][v]=weight;
	  M[v][u]=weight;
	  num_edges++;
  }
  
  EdgeWeight MatrixGraph::weight(NodeID u, NodeID v) const{

		  return M[u][v];

  }

  list<NWPair> MatrixGraph::getAdj(NodeID u) const{
	  
	  list<NWPair> tempList;
	  NWPair temp;
	  for(int i=0;i<M[u].size();i++){

		  if(M[u][i]>0){
			  temp = NWPair(i, M[u][i]);
			  tempList.push_back(temp);
		  }
	  }
	  return tempList;

  }

  unsigned MatrixGraph::degree(NodeID u) const{
	  
	  EList i=getAdj(u);
	  return i.size();
  }

  unsigned MatrixGraph::size() const{

	  return M.size();
  }

  unsigned MatrixGraph::numEdges() const{

	  return num_edges;

  }
