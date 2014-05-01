#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "Graph.h"


int main() {

	Graph graph2;


	Vertex v1(0 ,"T1", 1);
	Vertex v2(1, "T2", 3);
	Vertex v3(2,"T3",1);
	Vertex v4(3,"T4",3);
	/*	Vertex v5(4,"T5",3);
	Vertex v6(5 ,"T6", 3);
	Vertex v7(6, "T7", 2);
	Vertex v8(7,"T8",3);
	Vertex v9(8,"T9",1);
	 */
	graph2.addVertex(v1);
	graph2.addVertex (v2);
	graph2.addVertex (v3);
	graph2.addVertex (v4);


	graph2.addEdge((&(graph2.getVertexSet()[0])),(&(graph2.getVertexSet()[1])));
	graph2.addEdge((&(graph2.getVertexSet()[1])),(&(graph2.getVertexSet()[2])));
	graph2.addEdge((&(graph2.getVertexSet()[2])),(&(graph2.getVertexSet()[3])));
	graph2.addEdge((&(graph2.getVertexSet()[3])),(&(graph2.getVertexSet()[1])));

	/*	graph2.addVertex (v5);
	graph2.addVertex (v6);
	graph2.addVertex (v7);
	graph2.addVertex (v8);
	graph2.addVertex (v9);
	 */
	/*Edge * edge1;
	Edge * edge2;
	Edge * edge3;
	Edge * edge4;
	Edge * edge5;
	edge1 = new Edge(&(graph2.getVertexSet()[3]),&(graph2.getVertexSet()[5]));
	edge2 = new Edge(&(graph2.getVertexSet()[1]),&(graph2.getVertexSet()[3]));
	edge3 = new Edge(&(graph2.getVertexSet()[5]),&(graph2.getVertexSet()[1]));
	edge4 = new Edge(&(graph2.getVertexSet()[4]),&(graph2.getVertexSet()[5]));
	edge5 = new Edge(&(graph2.getVertexSet()[2]),&(graph2.getVertexSet()[4]));

	cout<< graph2.getVertexSet()[0].getName()<<endl;

	graph2.addEdge(*edge1);
	graph2.addEdge(*edge2);
	graph2.addEdge(*edge3);
	graph2.addEdge(*edge4);
	graph2.addEdge(*edge5);
	 */
	/*
	graph2.addEdge((&(graph2.getVertexSet()[0])),(&(graph2.getVertexSet()[1])));
	graph2.addEdge((&(graph2.getVertexSet()[0])),(&(graph2.getVertexSet()[5])));
	graph2.addEdge((&(graph2.getVertexSet()[4])),(&(graph2.getVertexSet()[5])));
	graph2.addEdge((&(graph2.getVertexSet()[5])),(&(graph2.getVertexSet()[8])));
	graph2.addEdge((&(graph2.getVertexSet()[8])),(&(graph2.getVertexSet()[7])));
	graph2.addEdge((&(graph2.getVertexSet()[1])),(&(graph2.getVertexSet()[2])));
	graph2.addEdge((&(graph2.getVertexSet()[2])),(&(graph2.getVertexSet()[3])));
	graph2.addEdge((&(graph2.getVertexSet()[3])),(&(graph2.getVertexSet()[6])));
	//graph2.addEdge((&(graph2.getVertexSet()[6])),(&(graph2.getVertexSet()[2])));
	graph2.addEdge((&(graph2.getVertexSet()[6])),(&(graph2.getVertexSet()[7])));
	//
	 */
	graph2.stronglyConnected();
	//vector<Vertex> output = graph2.topologicalOrder();
	vector<Vertex> output = graph2.getVertexSet();
	for(unsigned int i =0; i <output.size();i++)
	{
		if(i == output.size()-1)
			cout << output[i].getName() << endl;
		else
			cout << output[i].getName() << " - ";
	}


	return 0;
}
