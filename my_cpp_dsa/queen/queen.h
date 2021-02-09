#pragma once
#include <cmath>
#include "../stack/stack.h"

// demo only for solution of N Queens
// not yet tested for sanity


struct Queen {
	int x, y;
	Queen(int xx, int yy): x(xx), y(yy){}
	bool operator== (Queen const& q) const {
		return (x == q.x) || (y == q.y) || (x + y == q.x + q.y) || (abs(x - y) == abs(q.x - q.y));
	}
	bool operator!= (Queen const & q) const { return !(*this == q); }
};

// backtracing
int placeQueens(int N) {
	Stack<Queen> solu;
	Queen q(0, 0);
	int nSolu = 0;
	do {
		if (N <= solu.size() || q.y >= N) { // if solu full or y out of bound
			q = solu.pop(); q.y++; // trace back and probe next col
		}
		else { // probe next row
			// probe lawful position col by col
			while (q.y < N && solu.find(q)) { q.y++; }
			if (q.y <= N) {
				solu.push(q);
				// meet N queens, count to nSolu
				if (solu.size() >= N) nSolu++;
				// next row, start from col 0
				q.x++; q.y = 0;
			}
		}
	} while (q.x > 0 || q.y < N);
	return nSolu;
}