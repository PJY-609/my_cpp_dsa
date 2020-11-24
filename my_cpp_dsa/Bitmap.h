#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>
#include <iostream>

class Bitmap {
private:
	char* M;
	int N;

protected:
	void init(int n) { M = new char[N = (n + 7) / 8]; memset(M, 0, N); }

public:
	Bitmap(int n = 8) { init(n); }
	~Bitmap() { delete[] M; M = NULL; }
	
	// k >> 3: do the integer division by 8 
	// k & 0x07: remainder divided by 8
	bool test(int k)  { expand(k); return M[k >> 3] &   (0x80 >> (k & 0x07)); }
	void set(int k)   { expand(k);        M[k >> 3] |=  (0x80 >> (k & 0x07)); }
	void clear(int k) { expand(k);        M[k >> 3] &= ~(0x80 >> (k & 0x07)); }

	void expand(int k) { // if k out of bound, expand space
		if (k < 8 * N) return;
		int oldN = N; char* oldM = M;
		init(2 * k);
		memcpy_s(M, N, oldM, oldN);
		delete[] oldM;
	}

	void print(int n) {
		expand(n);
		for (int i = 0; i < n; i++)
			printf(test(i) ? "1" : "0");
	}
};