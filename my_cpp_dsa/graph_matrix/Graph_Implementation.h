#pragma once
#include "../queue/queue.h"

template <typename Tv, typename Te>
void Graph<Tv, Te>::bfs(int s) { // 0 < s <= n
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