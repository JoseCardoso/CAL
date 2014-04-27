
#ifndef EDGE_H_
#define EDGE_H_

#include "Includer.h"

class Vertex;

class Edge {
	Vertex* source;
	Vertex* dest;

public:
	friend class Graph;
	friend class Vertex;
	Edge (Vertex *s ,Vertex *d)
{
		source = s;
		dest = d;
}

	Vertex* getDest() const {
		return dest;
	}

	void setDest( Vertex* d) {
		dest = d;
	}

	Vertex* getSource() const {
		return source;
	}

	void setSource(Vertex* s) {
		source = s;
	}
};



#endif /* EDGE_H_ */