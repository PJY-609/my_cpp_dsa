#pragma once
#include <vector>
#include <algorithm>

using namespace std;

// Reference:
// https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-using-stl-in-c/

typedef  pair<int, int> iPair;

struct Graph
{
	int V, E;
	vector<pair<int, iPair>> edges;

	Graph(int V, int E):V(V), E(E){}

	void addEdge(int u, int v, int w)
	{
		edges.push_back({ w,{ u, v } });
	}

	// Function to find MST using Kruskal's
	// MST algorithm
	int kruskalMST();
};

struct DisjointSets {
	int *parent; int *rank;
	int n;

	DisjointSets(int n) {
		this->n = n;
		parent = new int[n + 1];
		rank = new int[n + 1];
		for (int i = 0; i < n; i++) {
			// i's parent is itself
			parent[i] = i;

			rank[i] = 0;
		}
	}

	// Find parent and path compression
	int find(int u) {
		if (u != parent[u]) parent[u] = find(parent[u]);
		return parent[u];
	}

	// Union by rank
	void merge(int x, int y) {
		x = find(x); y = find(y);

		/* Make tree with smaller height a subtree of the other tree  */
		if (rank[x] > rank[y])
			parent[y] = x;
		else // rank[x] <= rank[y]
			parent[x] = y;

		if (rank[x] == rank[y])
			rank[y]++;
	}
};

int Graph::kruskalMST() {
	int mst_wt = 0;

	sort(edges.begin(), edges.end());

	DisjointSets ds(V);

	vector<pair<int, iPair>>::iterator it;
	for (it = edges.begin(); it != edges.end(); it++) {
		int v = it->second.first;
		int w = it->second.second;

		int set_v = ds.find(v);
		int set_w = ds.find(w);

		if (set_v != set_w) {

			// current edge would be in the MST
			printf("%d-%d\n", v, w);

			mst_wt += it->first;

			ds.merge(set_v, set_w);
		}
	}

	return mst_wt;
}

void test() {
	int V = 9, E = 14;
	Graph g(V, E);

	g.addEdge(0, 1, 4);
	g.addEdge(0, 7, 8);
	g.addEdge(1, 2, 8);
	g.addEdge(1, 7, 11);
	g.addEdge(2, 3, 7);
	g.addEdge(2, 8, 2);
	g.addEdge(2, 5, 4);
	g.addEdge(3, 4, 9);
	g.addEdge(3, 5, 14);
	g.addEdge(4, 5, 10);
	g.addEdge(5, 6, 2);
	g.addEdge(6, 7, 1);
	g.addEdge(6, 8, 6);
	g.addEdge(7, 8, 7);

	int mst_wt = g.kruskalMST();

	printf("\nWeight of MST is %d\n", mst_wt);
}