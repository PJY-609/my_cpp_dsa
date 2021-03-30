#pragma once
#include "../queue/queue.h"

template <typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int s) { // 0 <= s < n
	reset(); int clock = 0; int v = s;
	do {
		if (status(v) == UNDISCOVERED)
			BFS(v, clock);
	} while (s != (v = (++v) % n)); // check every vertex
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::BFS(int v, int &clock) {
	Queue<int> Q;
	status(v) = DISCOVERED; Q.enqueue(v); 
	while (!Q.empty()) {
		v = Q.dequeue(); dTime(v) = ++clock;
		for (int u = firstNbr(v); u > -1; u = nextNbr(v, u)) {
			if (UNDISCOVERED == status(u)) {
				status(u) = DISCOVERED; Q.enqueue(u);
				type(v, u) = TREE; parent(u) = v;
			}
			else {
				type(v, u) = CROSS;
			}
		}
		status(v) = VISITED; 
	}
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::dfs(int s) { // 0 <= s < n
	reset(); int clock = 0; int v = s;
	do {
		if (UNDISCOVERED == status(v))
			DFS(v, clock);
	} while (s != (v = (++v) % n));
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::DFS(int v, int &clock) {
	status(v) = DISCOVERED; dTime(v) = ++clock;
	for (int u = firstNbr(v); u > -1; u = nextNbr(v, u)) {
		switch (status(u))
		{
		case UNDISCOVERED:
			type(v, u) = TREE; parent(u) = v; DFS(u, clock); break;
		case DISCOVERED:
			type(v, u) = BACKWARD; break;
		default: // VISITED
			type(v, u) = dTime(v) < dTime(u) ? FORWARD : CROSS; break;
		}
		
	}
	status(v) = VISITED; fTime(v) = ++clock;
}

template <typename Tv, typename Te>
Stack<Tv>* Graph<Tv, Te>::tSort(int s) { // 0 <= s < n
	reset(); int clock = 0; int v = s;
	Stack<Tv> * S = new Stack<Tv>;
	do {
		if (UNDISCOVERED == status(v)) {
			if (!TSort(v, clock, S)) {
				while (!S->empty())
					S->pop();
				break;
			}
		}
	} while (s != (v = (++v) % n));
	return S;
}

template <typename Tv, typename Te>
bool Graph<Tv, Te>::TSort(int v, int &clock, Stack<Tv> *S) {
	status(v) = DISCOVERED; dTime(v) = ++clock;
	for (int u = firstNbr(v); u > -1; u = nextNbr(v, u)) {
		switch (status(u))
		{
		case UNDISCOVERED:
			type(v, u) = TREE; parent(u) = v;
			if (!TSort(u, clock, S)) return false; break;
		case DISCOVERED:
			type(v, u) = BACKWARD; return false; break;
		default: // VISITED
			type(v, u) = (dTime(v) < dTime(u)) ? FORWARD : CROSS; break;
		}
	}
	status(v) = VISITED; fTime(v) = ++clock; S->push(vertex(v));
	return true;
}

template <typename Tv, typename Te>
template <typename PU>
void Graph<Tv, Te>::pfs(int s, PU prioUpdater) {
	reset(); int v = s;
	do {
		if (status(v) == UNDISCOVERED)
			PFS(v, prioUpdater);
	} while (s != (v = (++v % n)));
}

template <typename Tv, typename Te>
template <typename PU>
void Graph<Tv, Te>::PFS(int s, PU prioUpdater) {
	priority(s) = 0; status(s) = VISITED; parent(s) = -1;
	while (1) {
		for (int w = firstNbr(s); w > -1; w = nextNbr(s, w)) {
			prioUpdater(this, s, w);
		}
		for (int shortest = INT_MAX, w = 0; w < n; w++) {
			if (status(w) == UNDISCOVERED) { // any undiscovered w found
				if (shortest > priority(w)) { // find the one with highest priority
					shortest = priority(w); s = w; // set as next s
				}
			}
		}
		if (status(s) == VISITED) break;
		status(s) = VISITED; type(parent(s), s) = TREE;
	}
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::prim(int s) {
	reset(); priority(s) = 0;
	for (int i = 0; i < n; i++) {
		status(s) = VISITED;
		if (parent(s) != -1) type(parent(s), s) = TREE;
		for (int j = firstNbr(s); j > -1; j = nextNbr(s, j)) {
			if (status(j) == UNDISCOVERED && priority(j) > weight(s, j)) {
				priority(j) = weight(s, j); parent(j) = s;
			}
		}
		for (int shortest = INT_MAX, j = 0; j < n; j++) {
			if (status(j) == UNDISCOVERED && shortest > priority(j) {
				shortest = priority(j); s = j;
			}
		}
	}
}

template <typename Tv, typename Te>
void Graph<Tv, Te>::dijkstra(int s) {
	reset(); priority(s) = 0;
	for (int i = 0; i < n; i++) {
		status(s) = VISITED;
		if (parent(s) != -1) type(parent(s), s) = TREE;
		for (int j = firstNbr(s); j > -1; j = nextNbr(s, j)) {
			if (status(j) == UNDISCOVERED && priority(j) > priority(s) + weight(s, j)) {
				priority(j) = priority(s) + weight(s, j); parent(j) = s;
			}
		}
		for (int shortest = INT_MAX, j = 0; j < n; j++) {
			if (status(j) == UNDISCOVERED && shortest > priority(j)) {
				shortest = priority(j); s = j;
			}
		}
	}
}
