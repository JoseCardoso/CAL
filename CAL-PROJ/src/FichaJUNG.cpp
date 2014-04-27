#include <cstdio>
#include "graphviewer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include "Graph.h"

void exercicio1();
void exercicio2();
void exercicio3();


void exercicio1()
{
	GraphViewer *gv = new GraphViewer(600, 600, true);

	gv->setBackground("background.jpg");

	gv->createWindow(600, 600);


	gv->defineVertexColor("blue");
	gv->defineEdgeColor("black");

	gv->addNode(0);
	gv->addNode(1);
	gv->addEdge(0, 0, 1, EdgeType::UNDIRECTED);

	Sleep(100); // use sleep(1) in linux ; Sleep(100) on Windows

	gv->removeEdge(0);
	gv->removeNode(1);
	gv->addNode(2);

	gv->rearrange();

	Sleep(100);

	gv->addEdge(1, 0, 2, EdgeType::UNDIRECTED);

	gv->setVertexLabel(0, "Isto e um no");
	gv->setEdgeLabel(1, "Isto e uma aresta");

	gv->setVertexColor(2, "green");
	gv->setEdgeColor(1, "yellow");

	gv->rearrange();

}

void exercicio2()
{
	GraphViewer *gv = new GraphViewer(600, 600, false);

	gv->createWindow(600, 600);

	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");

	gv->addNode(0,300,50);
	gv->addNode(1,318,58);
	gv->addNode(4,300,100);
	gv->addNode(7,282,58);
	gv->addNode(2,325,75);
	gv->addNode(3,318,93);
	gv->addNode(6,275,75);
	gv->addNode(5,282,93);

	gv->addNode(8,150,200);

	gv->setVertexColor(8, "green");
	gv->setVertexColor(9, "blue");
	gv->setVertexColor(10, "green");
	gv->setVertexColor(11, "blue");
	gv->setVertexColor(12, "green");
	gv->setVertexColor(13, "green");
	gv->addNode(9,300,200);
	gv->addNode(10,450,200);
	gv->addNode(11,300,400);

	gv->addNode(12,200,550);
	gv->addNode(13,400,550);

	gv->addEdge(0, 0, 1, EdgeType::UNDIRECTED);
	gv->addEdge(1, 1, 2, EdgeType::UNDIRECTED);
	gv->addEdge(2, 2, 3, EdgeType::UNDIRECTED);
	gv->addEdge(3, 3, 4, EdgeType::UNDIRECTED);
	gv->addEdge(4, 4, 5, EdgeType::UNDIRECTED);
	gv->addEdge(5, 5, 6, EdgeType::UNDIRECTED);
	gv->addEdge(6, 6, 7, EdgeType::UNDIRECTED);
	gv->addEdge(7, 7, 0, EdgeType::UNDIRECTED);

	gv->addEdge(8, 4, 9, EdgeType::UNDIRECTED);
	gv->addEdge(9, 9, 8, EdgeType::UNDIRECTED);
	gv->addEdge(10, 9, 10, EdgeType::UNDIRECTED);
	gv->addEdge(11, 9, 11, EdgeType::UNDIRECTED);
	gv->addEdge(12, 11, 12, EdgeType::UNDIRECTED);
	gv->addEdge(13, 11, 13, EdgeType::UNDIRECTED);


	gv->rearrange();
	bool first=true;

	while(1)
	{
		Sleep(100);
		if (first)
		{
			gv->removeNode(12);
			gv->removeNode(13);
			first=false;
		}
		else
		{
			gv->removeNode(20);
			gv->removeNode(21);
		}
		gv->addNode(14,250,550);
		gv->addNode(15,350,550);
		gv->addEdge(14, 11, 14, EdgeType::UNDIRECTED);
		gv->addEdge(15, 11, 15, EdgeType::UNDIRECTED);
		gv->rearrange();

		Sleep(100);
		gv->removeNode(14);
		gv->removeNode(15);
		gv->addNode(16,300,550);
		gv->addNode(17,300,550);
		gv->addEdge(16, 11, 16, EdgeType::UNDIRECTED);
		gv->addEdge(17, 11, 17, EdgeType::UNDIRECTED);
		gv->rearrange();
		Sleep(100);

		gv->removeNode(16);
		gv->removeNode(17);
		gv->addNode(18,250,550);
		gv->addNode(19,350,550);
		gv->addEdge(18, 11, 18, EdgeType::UNDIRECTED);
		gv->addEdge(19, 11, 19, EdgeType::UNDIRECTED);
		gv->rearrange();
		Sleep(100);

		gv->removeNode(18);
		gv->removeNode(19);
		gv->addNode(20,200,550);
		gv->addNode(21,400,550);
		gv->addEdge(20, 11, 20, EdgeType::UNDIRECTED);
		gv->addEdge(21, 11, 21, EdgeType::UNDIRECTED);
		gv->rearrange();
	}
}

void exercicio3()
{
	/*
	GraphViewer *gv = new GraphViewer(600, 600, false);

	gv->createWindow(600, 600);

	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");

	 */
	Graph graph1;
	ifstream inFile;

	//Ler o ficheiro nos.txt
	inFile.open("nos.txt");

	if (!inFile) {
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}

	std::string   line;

	int idNo=0;
	string info;//X = 0,Y= 0;
	int priority;
	Vertex pointerProtector(-1,"info",0);//este vertice serve para preencher o elemento 0 do vector, que da erro a passar para apontador
	graph1.addVertex(pointerProtector);
	while(std::getline(inFile, line))
	{
		std::stringstream linestream(line);
		std::string         data;

		linestream >> idNo;

		std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> info;//X;
		std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> priority;//Y;
		Vertex vertex(idNo,info,priority);
		graph1.addVertex(vertex);
		//gv->addNode(idNo,X,Y);
		//gv->rearrange();

	}

	inFile.close();


	//Ler o ficheiro arestas.txt
	inFile.open("arestas.txt");

	if (!inFile) {
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}

	int idAresta=0;
	string idNoOrigem;
	string idNoDestino;

	while(std::getline(inFile, line))
	{
		std::stringstream linestream(line);
		std::string data;

		linestream >> idAresta;

		std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> idNoOrigem;
		std::getline(linestream, data, ';');  // read up-to the first ; (discard ;).
		linestream >> idNoDestino;
		// gv->addEdge(idAresta,idNoOrigem,idNoDestino, EdgeType::DIRECTED);
		// gv->rearrange();
		int lel = graph1.getVertexSet().size();
		Vertex * ori ;
		ori = &(graph1.getVertexSet()[1]);
		Vertex * desti;
		desti= &(graph1.getVertexSet()[1]);
		for(int i = 1; i < lel; i++)
		{
			if(idNoOrigem == graph1.getVertexSet()[i].getName())
				(*ori) = graph1.getVertexSet()[i];
			if(idNoDestino == graph1.getVertexSet()[i].getName())
				(*desti) = graph1.getVertexSet()[i];
		}
		graph1.addEdge(ori,desti);
	}

	inFile.close();

	//graph1.setVertexSet( graph1.topologicalOrder());
	vector<Vertex> lel = graph1.topologicalOrder();
	for( int i = lel.size()-1; i >-1;i--)
	{
		if(i == 0)
			cout << lel[i].getName();
		else
			cout << lel[i].getName() << " - ";
	}
	//graph1.printGraph();
	//gv->rearrange();
}

int main() {
	Graph graph2;
	Vertex v1(0 ,"T1", 1);
	Vertex v2(1, "T2", 2);
	Vertex v3(2,"T3",3);
	Vertex v4(3,"T4",2);
	Vertex v5(4,"T5",2);
	graph2.addVertex(v1);
	graph2.addVertex(v1);
	graph2.addVertex (v2);
	graph2.addVertex (v3);
	graph2.addVertex (v4);
	graph2.addVertex (v5);

	graph2.addEdge((&(graph2.getVertexSet()[3])),(&(graph2.getVertexSet()[5])));
	graph2.addEdge((&(graph2.getVertexSet()[1])),(&(graph2.getVertexSet()[3])));
	graph2.addEdge((&(graph2.getVertexSet()[4])),(&(graph2.getVertexSet()[5])));
	graph2.addEdge((&(graph2.getVertexSet()[2])),(&(graph2.getVertexSet()[3])));

	vector<Vertex> lel = graph2.topologicalOrder();
	//cout << lel.size();
	for(unsigned int i =0; i <lel.size();i++)
	{
		if(i == lel.size()-1)
			cout << lel[i].getName();
		else
			cout << lel[i].getName() << " - ";
	}

	//exercicio1();
	//exercicio2();
	//exercicio3();
	//getchar();
	return 0;
}
