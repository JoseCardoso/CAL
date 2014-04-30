
#ifndef VERTEX_H_
#define VERTEX_H_

#include "Includer.h"

class Edge;

class Vertex {

	string name;
	int id;
	int indegree;
	int priority;
	int index, lowlink;
	vector< Edge > out;
	vector< Edge > in;
	bool visited;
	bool processing;
	bool inStack;
public:

	friend class Graph;

	Vertex ( int id ,string name , int priority){
		this->id = id;
		this->name = name;
		this->priority = priority;
		indegree = 0;
		visited = false;
		processing = false;
		index = 0;
		lowlink = 0;
		inStack = false;
	}

	bool operator< (const Vertex &v2) const
	{
		if ( indegree != v2.indegree)
			return indegree > v2.indegree;
		else
			return priority < v2.priority;
	}

	
	bool removeEdgeTo(Vertex *d) {
		d->indegree--;//adicionado do exercicio 5
		vector<Edge >::iterator it = out.begin();
		vector<Edge >::iterator ite= out.end();
	while (it!=ite) {
		if (it->dest == d) {
			out.erase(it);
			return true;
		}
		else it++;
	}
	return false;
}

	void addEdgeOut ( Edge edge )
	{
		out.push_back(edge);

	}

	void addEdgeIn ( Edge edge )
	{
		in.push_back(edge);
		indegree++;
	}

	int getId() const {
		return id;
	}

	void setId(int id) {
		this->id = id;
	}

	vector<Edge> getIn() const {
		return in;
	}

	void setIn(const vector<Edge> in) {
		this->in = in;
	}

	int getIndegree() const {
		return indegree;
	}

	void setIndegree(int indegree) {
		this->indegree = indegree;
	}

	string getName() const {
		return name;
	}

	void setName(string name) {
		this->name = name;
	}

	vector<Edge > getOut() const {
		return out;
	}

	void setOut(vector<Edge> out) {
		this->out = out;
	}

	int getPriority() const {
		return priority;
	}

	void setPriority(int priority) {
		this->priority = priority;
	}

	bool isVisited() const {
		return visited;
	}

	void setVisited(bool visited) {
		this->visited = visited;
	}
};






#endif /* VERTEX_H_ */
