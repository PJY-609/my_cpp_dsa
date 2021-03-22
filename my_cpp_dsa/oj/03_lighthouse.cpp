/*Description*/
/*
As shown in the following figure, If another lighthouse is in gray area, they can beacon each other.

For example, in following figure, (B, R) is a pair of lighthouse which can beacon each other, while (B, G), (R, G) are NOT.
*/

/*Input*/
/*
1st line : N

2nd ~(N + 1)th line : each line is X Y, means a lighthouse is on the point(X, Y).
*/

/*Output*/
/*
How many pairs of lighthourses can beacon each other

(For every lighthouses, X coordinates won't be the same , Y coordinates won't be the same)
*/


/*Example*/
/*
Input

3
2 2
4 3
5 1

Output

1
*/

/*Restrictions*/
/*
For 90 % test cases : 1 <= n <= 3 * 105

For 95 % test cases : 1 <= n <= 106

For all test cases : 1 <= n <= 4 * 106

For every lighthouses, X coordinates won't be the same , Y coordinates won't be the same.

1 <= x, y <= 10 ^ 8

Time : 2 sec

Memory : 256 MB
*/

/*Hints*/
/*
The range of int is usually[-231, 231 - 1], it may be too small.
*/

#include <stdio.h>
#include <stdlib.h>
#define N 4000010
struct Point
{
	long x;
	long y;
} points[N];

long count = 0;

int partition(Point P[], int lo, int hi) {
	hi--;
	Point pivot = P[lo];
	while (lo < hi) {
		while (lo < hi && P[hi].x > pivot.x) hi--;
		if (lo < hi) P[lo++] = P[hi];
		while (lo < hi && P[lo].x < pivot.x) lo++;
		if (lo < hi) P[hi--] = P[lo];
	}
	P[lo] = pivot;
	return lo;
}


void quickSort(Point P[], int lo, int hi) {
	if (hi - lo < 2) return;
	int mi = partition(P, lo, hi);
	quickSort(P, lo, mi);
	quickSort(P, mi + 1, hi);
}

void merge(Point P[], int lo, int mi, int hi) {
	int i = 0;
	Point* A = P + lo;

	int j = 0; int lb = mi - lo;
	Point* B = new Point[lb]; 
	for (int m = 0; m < lb; m++) B[m] = A[m];

	int k = 0; int lc = hi - mi;
	Point* C = P + mi;

	while (j < lb && k < lc) {
		if (B[j].y < C[k].y){ 
			A[i++] = B[j++]; count += lc - k; 
		}
		else {
			A[i++] = C[k++];
		}
	}

	while (j < lb) A[i++] = B[j++];

	delete[] B;
}

int mergeSort(Point P[], int lo, int hi) {
	if (hi - lo < 2) return 0;
	int mi = (hi + lo) >> 1;
	mergeSort(P, lo, mi); mergeSort(P, mi, hi);
	merge(P, lo, mi, hi);
}

int main() {
	int n;
	int i;
	scanf("%d", &n);

	for (i = 0; i < n; ++i)
		scanf("%ld %ld", &points[i].x, &points[i].y);
	
	quickSort(points, 0, n);
	count = 0;
	mergeSort(points, 0, n);

	printf("%ld\n", count);
	return 0;
}
