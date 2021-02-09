#pragma once
#include "../stack/stack.h"

/*Stack Permutation*/
/*
Stack with n elements has SP(n) types of permutation

SP(1) = 1
SP(n) = sum_(k = 1)^(n)SP(k - 1)SP(n - k)
      = catalan(n)
	  = (2n)! / ((n + 1)! * n!)

Legal stack permutation: not contain {..., k, ..., i, ..., j, ...} when 1 <= i < j < k <= n

*/

// check if any 1 to n sequence is legal stack permutation of <1, 2, ..., n]
bool isStackPermutation(int Seq[], int n) { // O(n)
	Stack<int> S; // intermediate stack
	int i = 1; // i for the original 1 to n stack
	for (int k = 0; k < n; k++) {
		while (S.empty() || Seq[k] != S.top()) {
			S.push(i++);
			// the original stack overflows
			if (i > n + 1) return false;
		}
			
		// S is empty or S top is not Seq[k]
		if (S.empty() || S.top() != Seq[k]) return false;

		S.pop();
	}
	return true;
}