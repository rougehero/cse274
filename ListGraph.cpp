#include <vector>
#include "ListGraph.h"
#include "assert.h"
using namespace std;


 
ListGraph::ListGraph(int numNodes)
{
	edgeList= vector<EList>(numNodes);
	num_edges=0;

}
 ListGraph::~ListGraph()
{

}


 void ListGraph::addEdge(NodeID u, NodeID v,EdgeWeight w)
{
	edgeList[u].push_back(NWPair(v,w));
	edgeList[v].push_back(NWPair(u,w));
	num_edges++;

}
  

EdgeWeight ListGraph::weight(NodeID u,NodeID v) const
{
	
	EList i=edgeList[u];

	EList::const_iterator it;
	for(it=i.begin(); it!=i.end();++it)
	{
		if(it->first==v)
		{
			return it->second;
		}
	}
	return 0;
}
EList ListGraph::getAdj(NodeID u) const
{
	return edgeList[u];

}
unsigned ListGraph::degree(NodeID u) const
{
	return edgeList[u].size();

}
unsigned ListGraph::size() const
{
	return edgeList.size();

}
unsigned ListGraph::numEdges() const
{
	return num_edges;

}
