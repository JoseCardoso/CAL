/*
 * Graph.h
 *
 *  Created on: 27 de Abr de 2014
 *      Author: José
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "Includer.h"
#include "Edge.h"
#include "Vertex.h"


using namespace std;


class Graph {
	vector <Vertex> vertexSet,res;
	vector <Edge> edgeSet;
	int numCycles;
	int index;
	stack<Vertex *> stk;
public:

	Graph()
	{
		numCycles = 0;
		index = 0;
}
	void addVertex(Vertex v)
	{
		vertexSet.push_back(v);
	}

	void addEdge (Vertex * source , Vertex * dest)
	{
		Edge edge(source , dest);
		source->addEdgeOut(edge);
		dest->addEdgeIn(edge);

		for (unsigned int i = 1 ; i < vertexSet.size() ; i++)
		{
			if (vertexSet[i].name == source->name)
			{
				vertexSet[i].indegree++;
			}
		}

		edgeSet.push_back(edge);
	}



	void removeVertex(Vertex v)
	{

		for (unsigned int i = 1 ; i < vertexSet.size() ; i++)
		{
			if (vertexSet[i].name == v.name)
			{
				Vertex v = vertexSet[i];

				vertexSet.erase( vertexSet.begin() + i);

				for (unsigned int j = 0 ; j < edgeSet.size(); j++)
				{
					if(edgeSet[j].dest->name == v.name )
					{
						edgeSet[j].dest->indegree--;
						edgeSet.erase(edgeSet.begin() + j);
						j--;
					}
					else if (edgeSet[j].source->name == v.name)
					{
						edgeSet.erase(edgeSet.begin() + j);
						j--;
					}

				}
			}

		}
	}

	int getNumCycles() {
		numCycles = 0;
		dfsVisit();
		return this->numCycles;
	}

	void resetIndegrees() {
		//colocar todos os indegree em 0;
		for(unsigned int i = 1; i < vertexSet.size(); i++)
			vertexSet[i].indegree = 0;

		//actualizar os indegree
		for(unsigned int i = 1; i < vertexSet.size(); i++) {
			//percorrer o vetor de Edges, e atualizar indegree
			for(unsigned int j = 1; j < vertexSet[i].out.size(); j++) {
				vertexSet[i].out[j].dest->indegree++;
			}
		}
	}

	void resetVertex()
	{
		for(unsigned int i = 1; i < vertexSet.size(); i++) {
			//percorrer o vetor de Edges, e tirar o visited
			for(unsigned int j = 1; j < vertexSet[i].out.size(); j++) {
				vertexSet[i].visited = false;
				vertexSet[i].processing = false;
				vertexSet[i].inStack = false;
				vertexSet[i].index=0;
				vertexSet[i].lowlink=0;
			}
		}

	}

	void removeEdge(Vertex* source, Vertex* dest)
	{
		for (unsigned int i = 0 ; i < edgeSet.size() ; i++)
		{
			if (edgeSet[i].dest == dest && edgeSet[i].source == source)
			{
				edgeSet[i].source->removeEdgeTo(edgeSet[i].dest);
				edgeSet[i].dest->indegree--;
				edgeSet.erase(edgeSet.begin() + i);
				i--;

				for (unsigned int j = 0 ; j < edgeSet[i].dest->in.size() ; j++)
				{
					if (edgeSet[i].dest->in[j].source == source)
					{
						edgeSet[i].dest->in.erase(edgeSet[i].dest->in.begin() + j);
						j--;
					}
				}

			}

		}
	}

	void dfsVisit(Vertex *v) {
		v->processing=true;
		v->visited = true;
		vector<Edge >::iterator it= (v->out).begin();
		vector<Edge >::iterator ite= (v->out).end();
		for (; it !=ite; it++) {
			if ( it->dest->processing == true) numCycles++;
			if ( it->dest->visited == false ){
				dfsVisit(it->dest);
			}
		}
		v->processing=false;
	}

	void dfsVisit() {
		for ( unsigned int i = 1 ; i < vertexSet.size() ; i++)
		{
			vertexSet[i].setVisited(false);

		}
		for (unsigned int i = 1 ; i < vertexSet.size() ; i++)
		{
			if (!vertexSet[i].isVisited())
				dfsVisit(&vertexSet[i]);
		}
	}

	vector<Vertex> topologicalOrder() {

		//vetor com o resultado da ordenacao
		vector<Vertex> res;

		//verificar se ee um DAG
		if( getNumCycles() > 0 ) {
			cout << "Ordenacao Impossivel!" << endl;
			return res;
		}

		//garantir que os "indegree" estao inicializados corretamente
		//this->resetIndegrees();

		priority_queue<Vertex> q;

		vector<Vertex> sources = vertexSet;
		sources.erase(sources.begin());
		while( !sources.empty() ) {
			q.push( sources.back() );
			sources.pop_back();
		}

		//processar fontes
		while( !q.empty() ) {
			Vertex v = q.top();
			q.pop();

			res.push_back(v);

			for(unsigned int i = 0; i < v.out.size(); i++) {
				v.out[i].dest->indegree--;
				if( v.out[i].dest->indegree == 0) q.push( (*v.out[i].dest));
			}
		}

		//testar se o procedimento foi bem sucedido
		/*	if ( res.size() != vertexSet.size() -1 ) {
			while( !res.empty() ) res.pop_back();
		}
		 */
		//garantir que os "indegree" ficam atualizados no final
		//this->resetIndegrees();
		return res;
	}

	void scc(Vertex * v)
	{

		v->visited  = true;
		stk.push(v);
		v->inStack = true;
		v->index = index;
		v->lowlink = index;
		index++;
		for(unsigned int j=0;j<edgeSet.size();j++)
		{

			if(edgeSet[j].source->name == v->name)
			{
				Vertex * w = edgeSet[j].dest;
				if( !(w->visited )){
					scc( w );
					v->lowlink = min( v->lowlink,w->lowlink );
				}
				else if((*v).inStack ){
					v->lowlink = min( v->lowlink,w->index );
				}
			}
		}
		if(v->lowlink!=v->index ) return;
		// found new component
		int i = 1, p = v->priority;
		string tname = "{";
		while( stk.top()->name!= v->name ){
			Vertex * v = stk.top();
			stk.pop();
			p += v->priority;
			tname += v->name;
			tname += "-";
			i++;
			for(unsigned k = 0; k < res.size(); k++)
				if(res[k].name == v->name)
					res.erase(res.begin()+k);
		}
		stk.pop();
		tname += v->name;
		tname += "}";
		p = p/i;
		v->name = tname;
		v->priority = p;
	}

	void stronglyConnected()
	{
		res = vertexSet;
		for(unsigned int i=1;i< res.size();i++)
		{
			if( res[i].visited )
				continue;

			scc( &res[i] );

		}

		vertexSet = res;
		resetVertex();
	}

	vector<Edge> getEdgeSet() const {
		return edgeSet;
	}

	void setEdgeSet(vector<Edge> edgeSet) {
		this->edgeSet = edgeSet;
	}

	vector<Vertex> getVertexSet() const {
		return vertexSet;
	}

	void setVertexSet(vector<Vertex> vertexSet) {
		this->vertexSet = vertexSet;
	}
};








#endif /* GRAPH_H_ */
