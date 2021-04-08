#pragma once
#include <limits.h>

typedef enum { UNDISCOVERED, DISCOVERED, VISITED } VStatus;
typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } EType;

template <typename Tv, typename Te>
class Graph {
private:
	void reset() {
		for (int i = 0; i < n; i++) {
			status(i) = UNDISCOVERED; dTime(i) = fTime(i) = -1;
			parent(i) = -1; priority(i) = INT_MAX;
			for (int j = 0; j < e; j++) {
				if (exists(i, j)) type(i, j) = UNDETERMINED;
			}
		}
	}
	
	// for single connected component
	void BFS(int v, int & clock); 
	void DFS(int v, int & clock);

	// Topology Sort for Directed Acyclic Graph (DAG) based on DFS (single round)
	bool TSort(int v, int &clock, Stack<Tv> *S);

	// Priority First Search for single connected component
	template <typename PU> void PFS(int s, PU prioUpdater);

	// for single component
	void BCC(int v, int &clock, Stack<int>& S);

public:
	// Vertex
	int n;
	virtual int insert(Tv const &v) = 0;
	virtual Tv remove(int i) = 0;
	virtual Tv& vertex(int i) = 0; // called pure virtual or abstract function and requires to be overwritten in an derived class.
	virtual int inDegree(int i) = 0;
	virtual int outDegree(int i) = 0;
	virtual VStatus& status(int i) = 0;
	virtual int& dTime(int i) = 0;
	virtual int& fTime(int i) = 0;
	virtual int& parent(int i) = 0;
	virtual int& priority(int i) = 0;
	virtual int firstNbr(int i) = 0;
	virtual int nextNbr(int i, int j) = 0;

	// Edge
	int e;
	virtual void insert(Te const &e, int w, int i, int j) = 0;
	virtual Te remove(int i, int j) = 0;
	virtual bool exists(int i, int j) = 0;
	virtual EType& type(int i, int j) = 0;
	virtual Te& edge(int i, int j) = 0;
	virtual int& weight(int i, int j) = 0;
	
	// for whole graph with multiple connected components
	void bfs(int s); 
	void dfs(int s);

	// Topology Sort for Directed Acyclic Graph (DAG) based on DFS
	// O(n^2) -> O(n + e)
	Stack<Tv>* tSort(int s);

	// O(n^2) -> O(n + e)
	template <typename PU> void pfs(int s, PU prioUpdater);

	// Minimum Spanning Tree
	// total number trees (Cayley's formula) n vertices, n ^ (n - 2) trees
	// The minimum crossing edge for ANY cut is part of the MST.
	// O(n^2) -> O(n + e)
	void prim(int s);

	// Shortest Path Tree
	// SPT != MST
	// The crossing edge which constitues the shortest path to origin for ANY cut is part of the MST.
	// O(n^2) -> O(n + e)
	void dijkstra(int s);
	// Floyd-Warshall's algorithm
	// finding shortest paths in a directed weighted graph 
	// with positive or negative edge weights (but with no negative cycles)

	// Bi-Connected Components
	// Articulation point (cut-vertex): iff removing it (and edges through it) disconnects the graph. 
	// Bi-connectivity: Graph without articulation point (cut-vertex)
	void bcc(int s);
	// Strong-Connected Components
	// Kosraju's algorithm
	// Tarjan's algorithm


};

template <typename Tv, typename Te>
struct PrimPU {
	virtual void operator()(Graph<Tv, Te> *g, int uk, int v) {
		if (g->status(v) != UNDISCOVERED) return;
		if (g->priority(v) > g->weight(uk, v)) {
			g->priority(v) = g->weight(uk, v); g->parent(v) = uk;
		}
	}
};

template <typename Tv, typename Te>
struct DijkPU {
	virtual void operator()(Graph<Tv, Te> *g, int uk, int v) {
		if (g->status(v) != UNDISCOVERED) return;
		if (g->priority(v) > g->priority(uk) + g->weight(uk, v)) {
			g->priority(v) = g->priority(uk) + g->weight(uk, v); g->parent(v) = uk;
		}
	}
};

#include "../graph_matrix/Graph_Implementation.h"


// Parenthesis Lemma
// active(u) = [dTime(u), fTime(u)]
// u is v's predeccessor: active(v) \subseteq active(u)
// u is v's successor:    active(v) \supseteq active(u)
// u is unrelated to v: active(v) \cap active(u) = \empty

