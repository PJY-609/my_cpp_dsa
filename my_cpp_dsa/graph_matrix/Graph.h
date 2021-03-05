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

	void BFS(int v, int & clock); // for single connected component

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

	void bfs(int s); // for whole graph with multiple connected components
};

#include "../graph_matrix/Graph_Implementation.h"