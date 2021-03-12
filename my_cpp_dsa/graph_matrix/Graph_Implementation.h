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