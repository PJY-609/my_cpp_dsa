#pragma once

#include "../graph_matrix/Graph.h"
#include <vector>
#include <stdio.h>
// Adjacency Matrix
// pro: widely used for various types of graph
// con: space-O(n^2), but v − e + f = 2 (Euler's formula) -> e <= O(n)


// Adjacency Matrix vs Adjacency List
// Matrix: frequent request of edge existence, frequent removal / insertion of edge, fixed graph scale, dense graph
// List: frequent request of vertex's degree, flexible number of vertices, frequent traversal, sparse graph

template <typename Tv> struct Vertex {
	Tv data; int inDegree; int outDegree; VStatus status;
	int dTime; int fTime;
	int parent; int priority;

	Vertex(Tv const &d = (Tv) 0): 
		data(d), inDegree(0), outDegree(0), status(UNDISCOVERED), 
		dTime(-1), fTime(-1), parent(-1), priority(INT_MAX){}
};

template <typename Te> struct Edge {
	Te data; int weight; EType type;
	Edge(Te const &d, int w): data(d), weight(w), type(UNDETERMINED){}
};

template <typename Tv, typename Te>
class GraphMatrix: public Graph<Tv, Te> {
private:
	std::vector<Vertex<Tv>> V;
	std::vector<std::vector<Edge<Te> *>> E;

public:
	GraphMatrix() { n = e = 0; }
	~GraphMatrix() {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				delete E[i][j];
			}
		}
	}

	virtual int insert(Tv const& vertex) {
		for (int j = 0; j < n; j++) E[j].push_back(NULL); n++; // create position for potential link with the new vertex
		E.push_back(std::vector<Edge<Te>*>(n, (Edge<Te>*) NULL)); // create new edge link relation list for the new vertex
		V.push_back(Vertex<Tv>(vertex));
		return V.size() - 1;
	}

	virtual Tv remove(int i) { // remove vertex i and involved edges
		for (int j = 0; j < n; j++){
			if (exists(i, j)) {
				delete E[i][j]; V[j].inDegree--; e--;
			}
		}
		E.erase(E.begin() + i); n--;
		Tv vBak = vertex(i); 
		V.erase(V.begin() + i);
		for (int j = 0; j < n; j++) {
			if (E[j][i]) {
				delete E[j][i]; V[j].outDegree--; e--;
			}
			E[j].erase(E[j].begin() + i);
		}
		return vBak;
	}

	virtual Tv& vertex(int i) { return V[i].data; }
	virtual int inDegree(int i) { return V[i].inDegree; }
	virtual int outDegree(int i) { return V[i].outDegree; }
	virtual VStatus& status(int i) { return V[i].status; }
	virtual int& dTime(int i) { return V[i].dTime; }
	virtual int& fTime(int i) { return V[i].fTime; }
	virtual int& parent(int i) { return V[i].parent; }
	virtual int& priority(int i) { return V[i].priority; }

	virtual int firstNbr(int i) { return nextNbr(i, n); }
	virtual int nextNbr(int i, int j) {
		while ((-1 < j) && !exists(i, --j));
		return j;
	} 

	virtual bool exists(int i, int j) // check if edge ij exists
	{	
		return (0 <= i) && (i < n) && (0 <= j) && (j < n) && E[i][j] != NULL;
	}

	virtual void insert(Te const &edge, int w, int i, int j) {
		if (exists(i, j)) return;
		E[i][j] = new Edge<Te>(edge, w);
		e++; V[i].outDegree++; V[j].inDegree++;
	}

	virtual Te remove(int i, int j) {
		Te eBak = edge(i, j); delete E[i][j]; E[i][j] = NULL; 
		e--; V[i].outDegree--; V[j].inDegree--; 
		return eBak;
	}

	virtual EType& type(int i, int j) { return E[i][j]->type; }
	virtual Te& edge(int i, int j) { return E[i][j]->data; }
	virtual int& weight(int i, int j) { return E[i][j]->weight; }
};


