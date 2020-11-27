#include "Bitmap.h"

void Eratosthenes(int n, char* file) {
	/******************************************************************************************
	* Outer loop: O(n)
	* Inner loop, number of iterations is O(n / i). Time spent:
	*       n/2 + n/3 + n/5 + n/7 + n/11 + ...
	*    <  n/2 + n/3 + n/4 + n/6 + n/7 + ... + n/(n/ln(n))
	*    =  O(n(ln(n/ln(n)) - 1))
	*    =  O(nln(n) - nln(ln(n)) - 1)
	*    =  O(nlog(n))
	* if inner loop starts from i * i (not i + i)£¬number of iterations reduce from O(n / i) to O(max(1, n / i - i))
	******************************************************************************************/
	Bitmap B(n); B.set(0); B.set(1);
	for (int i = 2; i < n; i++)
		if (!B.test(i))
			for (int j = __min(i, 46340) * __min(i, 46340); j < n; j += i)
				B.set(j);
	B.dump(file);
}

int primeNLT(int c, int n, char* file) {
	Bitmap B(file, n);
	while (c < n) {
		if (B.test(c)) c++;
		else return c;
	}
	return c;
}
