#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "Graph.h"



int main() {

	Graph graph;
	ifstream inFile;

	//Ler o ficheiro nos.txt
	inFile.open("nos.txt");

	if (!inFile) {
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}

	std::string   line;

	int idNo=0;
	string info;
	int priority = 0;
	while(std::getline(inFile, line))
	{
		std::stringstream linestream(line);
		std::string         data;


		linestream >> idNo;

		std::getline(inFile, data);
		info = data;
		std::getline(inFile, data);
		stringstream linestream2 (data);
		linestream2 >> priority;

		Vertex vertex(idNo,info,priority);
		graph.addVertex(vertex);
	}

	inFile.close();


	//Ler o ficheiro arestas.txt
	inFile.open("arestas.txt");

	if (!inFile) {
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}

	int idAresta=0;
	int idNoOrigem=0;
	int idNoDestino=0;

	while(std::getline(inFile, line))
	{
		std::stringstream linestream(line);
		std::string data;

		linestream >> idAresta;

		std::getline(inFile, data);
		stringstream linestream2 (data);
		linestream2 >> idNoOrigem;
		std::getline(inFile, data);
		stringstream linestream3 (data);
		linestream3 >> idNoDestino;

		Vertex * ori ;
		ori = &(graph.getVertexSet()[1]);
		Vertex * desti;
		desti= &(graph.getVertexSet()[1]);
		for(unsigned int i = 1; i < graph.getVertexSet().size(); i++)
		{
			if(idNoOrigem == graph.getVertexSet()[i].getId())
				(*ori) = graph.getVertexSet()[i];
			if(idNoDestino == graph.getVertexSet()[i].getId())
				(*desti) = graph.getVertexSet()[i];
		}
		graph.addEdge(ori,desti);
	}

	inFile.close();

	/*Graph graph2;


	Vertex v1(0,"T1",1);
	Vertex v2(1,"T2",3);
	Vertex v3(2,"T3",1);
	Vertex v4(3,"T4",3);
	Vertex v5(4,"T5",3);
	Vertex v6(5,"T6",3);
	Vertex v7(6,"T7",2);
	Vertex v8(7,"T8",3);
	Vertex v9(8,"T9",1);

	graph2.addVertex(v1);
	graph2.addVertex(v2);
	graph2.addVertex(v3);
	graph2.addVertex(v4);
	graph2.addVertex(v5);
	graph2.addVertex(v6);
	graph2.addVertex(v7);
	graph2.addVertex(v8);
	graph2.addVertex(v9);


	graph2.addEdge((&(graph2.getVertexSet()[0])),(&(graph2.getVertexSet()[1])));
	graph2.addEdge((&(graph2.getVertexSet()[0])),(&(graph2.getVertexSet()[5])));
	graph2.addEdge((&(graph2.getVertexSet()[4])),(&(graph2.getVertexSet()[5])));
	graph2.addEdge((&(graph2.getVertexSet()[5])),(&(graph2.getVertexSet()[8])));
	graph2.addEdge((&(graph2.getVertexSet()[8])),(&(graph2.getVertexSet()[7])));
	graph2.addEdge((&(graph2.getVertexSet()[1])),(&(graph2.getVertexSet()[2])));
	graph2.addEdge((&(graph2.getVertexSet()[2])),(&(graph2.getVertexSet()[3])));
	graph2.addEdge((&(graph2.getVertexSet()[3])),(&(graph2.getVertexSet()[6])));
	graph2.addEdge((&(graph2.getVertexSet()[6])),(&(graph2.getVertexSet()[2])));
	graph2.addEdge((&(graph2.getVertexSet()[6])),(&(graph2.getVertexSet()[7])));
	*/

	graph.stronglyConnected();
	vector<Vertex> output = graph.topologicalOrder();
	for(unsigned int i =0; i <output.size();i++)
	{
		if(i == output.size()-1)
			cout << output[i].getName() << endl;
		else
			cout << output[i].getName() << " - ";
	}


	return 0;
}
