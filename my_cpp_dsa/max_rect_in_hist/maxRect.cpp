#include "../stack/stack.h"
// find the largest rectangle in a histogram
// H[r] * (t - s)
// all algorithms here are not tested for correctness
// demo only

// brute force solution O(n^2)
__int64 mr_BRUTE(int H[], int n, int& mr_s, int& mr_r, int& mr_t) {
	__int64 maxRect = 0;
	for (int s = 0, r = 0, t = 0; r < n; r++, s = t = r) {
		do s--; while (s > -1 && H[s] >= H[r]); s++;
		do t++; while (t < n  && H[t] >= H[r]); 
		__int64 rect = (__int64) H[r] * (t - s);
		if (maxRect < rect) {
			maxRect = rect; mr_s = s; mr_r = r; mr_t = t;
		}
	}
	return maxRect;
}

// use stack O(n)
__int64 mr_STACK(int H[], int n, int& mr_s, int& mr_r, int& mr_t) {
	Stack<__int64> SR;
	__int64 maxRect = 0;
	for (int t = 0; t <= n; t++) {
		while (!SR.empty() && (t == n || H[SR.top()] >= H[t])) {
			int r = SR.pop(); int s = SR.empty() ? 0 : SR.top() + 1;
			__int64 rect = (__int64)H[r] * (t - s);
			if (maxRect < rect) {
				maxRect = rect; mr_s = s; mr_r = r; mr_t = t;
			}
		}
		if (t < n) SR.push(t);
	}
	return maxRect;
}