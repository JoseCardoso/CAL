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

		/*for (unsigned int i = 0 ; i < vertexSet.size() ; i++)
		{
			if (vertexSet[i].name == dest->name)
			{
				vertexSet[i].addEdgeIn(edge);
			}
			if (vertexSet[i].name == source->name)
			{
				vertexSet[i].addEdgeOut(edge);
			}
		}
		 */
		edgeSet.push_back(edge);
	}

	void addEdge (Edge edge)
	{
		edge.source->addEdgeOut(edge);
		edge.dest->addEdgeIn(edge);

		for (unsigned int i = 0 ; i < vertexSet.size() ; i++)
		{
			if (vertexSet[i].name == edge.source->name)
			{
				vertexSet[i].indegree++;
			}
		}

		edgeSet.push_back(edge);
	}



	void removeVertex(Vertex v)
	{

		for (unsigned int i = 0 ; i < vertexSet.size() ; i++)
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
		for(unsigned int i = 0; i < vertexSet.size(); i++)
			vertexSet[i].indegree = 0;

		//actualizar os indegree
		for(unsigned int i = 0; i < vertexSet.size(); i++) {
			//percorrer o vetor de Edges, e atualizar indegree
			vertexSet[i].indegree = vertexSet[i].in.size();
		}
	}

	void resetVertex()
	{
		for(unsigned int i = 0; i < vertexSet.size(); i++) {
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
		for ( unsigned int i = 0 ; i < vertexSet.size() ; i++)
		{
			vertexSet[i].setVisited(false);

		}
		for (unsigned int i = 0 ; i < vertexSet.size() ; i++)
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
		this->resetIndegrees();

		priority_queue<Vertex> q, qtemp;

		vector<Vertex> sources = vertexSet;

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

				while(!q.empty())
				{
					Vertex t = q.top();
					q.pop();
					if(t.name == v.out[i].dest->name)
						qtemp.push(*(v.out[i].dest));
					else
						qtemp.push(t);
				}
				q = qtemp;
				while(!qtemp.empty())
					qtemp.pop();
			}



		}

		//testar se o procedimento foi bem sucedido
		/*	if ( res.size() != vertexSet.size()  ) {
			while( !res.empty() ) res.pop_back();
		}
		 */
		//garantir que os "indegree" ficam atualizados no final
		this->resetIndegrees();
		return res;
	}

	void generateComponentVertex()
	{





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
		generateComponentVertex();
		int i = 1, p = v->priority;
		string tname = "{";
		while( stk.top()->name!= v->name ){
			Vertex * vS = stk.top();
			stk.pop();
			p += vS->priority;
			tname += vS->name;
			tname += "-";
			i++;
			/*for(unsigned int j = 0; j < vS->out.size();j++)
				if(vS->out[j].dest->lowlink != vS->lowlink)
				{
					Edge temp(v,vS->out[j].dest);
					v->addEdgeOut(temp);
				}*/

		}
		/*for(unsigned int j = 0; j < v->out.size();j++)
			if(v->out[j].dest->lowlink == v->lowlink)
			{
				v->removeEdgeTo(v->out[j].dest);
			}*/

		stk.pop();
		tname += v->name;
		tname += "}";
		p = p/i;
		v->name = tname;
		v->priority = p;

		res.push_back((*v));
	}

	void stronglyConnected()
	{


		for(unsigned int i=0; i< vertexSet.size();i++)
		{
			if( !vertexSet[i].visited )
				scc( &vertexSet[i] );

		}
		vertexSet = res;
		for(unsigned int i=vertexSet.size()-1; i>=0;i--)
		{
			Vertex v = vertexSet[i];
		}
		resetVertex();
	}

	vector<Edge> &getEdgeSet() {
		return edgeSet;
	}

	void setEdgeSet(vector<Edge> edgeSet) {
		this->edgeSet = edgeSet;
	}

	vector<Vertex> &getVertexSet()  {
		return vertexSet;
	}

	void setVertexSet(vector<Vertex> vertexSet) {
		this->vertexSet = vertexSet;
	}
};








#endif /* GRAPH_H_ */
