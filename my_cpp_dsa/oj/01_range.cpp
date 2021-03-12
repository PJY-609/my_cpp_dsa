/*Descriptioin*/
/*
Let S be a set of n integral points on the x - axis.For each given interval[a, b], you are asked to count the points lying inside.
*/

/*Input*/
/*The first line contains two integers : n(size of S) and m(the number of queries).

The second line enumerates all the n points in S.

Each of the following m lines consists of two integers a and b and defines an query interval[a, b].
*/

/*Output*/
/*
The number of points in S lying inside each of the m query intervals.
*/

/*Example*/
/*
Input

5 2
1 3 7 9 11
4 6
7 12
Output

0
3
*/

/*Restrictions*/
/*
0 <= n, m <= 5 * 10 ^ 5

For each query interval[a, b], it is guaranteed that a <= b.

Points in S are distinct from each other.

Coordinates of each point as well as the query interval boundaries a and b are non - negative integers not greater than 10 ^ 7.

Time: 2 sec

Memory : 256 MB
*/

#include <iostream>
#include <stdlib.h>

#define N 500005
int A[N];

int compare(const void *a, const void *b){
	int *pa = (int*)a;
	int *pb = (int*)b;
	return (*pa) - (*pb);
}


// reference: python standard lib bisect
int binSearchRight(int e, int *A, int lo, int hi) {
	while (lo < hi) {
		int mi = (hi + lo) >> 1;
		e > A[mi] ? lo = mi + 1 : hi = mi;
	}
	return lo - 1;
}

int binSearchLeft(int e, int *A, int lo, int hi) {
	while (lo < hi) {
		int mi = (hi + lo) >> 1;
		e < A[mi] ? hi = mi : lo = mi + 1;
	}
	return lo - 1;
}


int main() {
	int n; int m;
	scanf("%d %d", &n, &m);

	for (int i = 0; i < N; i++) A[i] = 0;

	for (int i = 0; i < n; i++)
		scanf("%d", &A[i]);

	qsort(A, n, sizeof(int), compare);

	int a; int b;
	int l; int h;
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);

		if (a > b) std::swap(a, b);

		l = binSearchRight(a, A, 0, n);
		h = binSearchLeft(b, A, 0, n);

		printf("%d\n", h - l);
	}
	return 0;
}