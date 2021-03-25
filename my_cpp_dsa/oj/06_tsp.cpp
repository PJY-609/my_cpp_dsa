/*Description*/
/*
Shrek is a postman working in the mountain, whose routine work is sending mail to n villages.Unfortunately, road between villages is out of repair for long time, such that some road is one - way road.There are even some villages that can¡¯t be reached from any other village.In such a case, we only hope as many villages can receive mails as possible.

Shrek hopes to choose a village A as starting point(He will be air - dropped to this location), then pass by as many villages as possible.Finally, Shrek will arrived at village B.In the travelling process, each villages is only passed by once.You should help Shrek to design the travel route.
*/

/*Input*/
/*
There are 2 integers, n and m, in first line.Stand for number of village and number of road respectively.

In the following m line, m road is given by identity of villages on two terminals.From v1 to v2.The identity of village is in range[1, n].
*/

/*Output*/
/*
Output maximum number of villages Shrek can pass by.
*/

/*Example*/
/*
Input

4 3
1 4
2 4
4 3
Output

3
*/

/*Restrictions*/
/*
1 <= n <= 1, 000, 000

0 <= m <= 1, 000, 000

These is no loop road in the input.

Time: 2 sec

Memory : 256 MB
*/

/*Hints*/
/*Topological sorting*/

// referece:
// Brilliant idea to add dynamic programming into topological sorting
// https://blog.csdn.net/qq_37729102/article/details/83177125

#include <iostream>
#include <cstdio>

#define N 1000000
#define MAX(a, b) (a > b) ? a : b

struct Edge {
	int targetVertex;
	Edge* nextEdge;
};

struct Vertex {
	int inDegree;
	int maxLen; // max length to vertex with zero in-degree
	Edge* firstEdge;
};

Vertex AdjList[N];
Vertex Stack[N]; int top = 0;

int TSort(int n) {
	int maxLength = 0;
	for (int i = 0; i < n; i++) {
		if (AdjList[i].inDegree == 0)
			Stack[++top] = AdjList[i];
	}

	while (top) {
		Vertex v = Stack[top--];
		for (Edge* p = v.firstEdge; p; p = p->nextEdge) {
			AdjList[p->targetVertex].maxLen = MAX(v.maxLen + 1, AdjList[p->targetVertex].maxLen);
			maxLength = MAX(AdjList[p->targetVertex].maxLen, maxLength);
			if (!(--AdjList[p->targetVertex].inDegree))
				Stack[++top] = AdjList[p->targetVertex];
		}
	}
	return maxLength + 1;
}


int main() {
	int n; int m;
	scanf("%d%d", &n, &m);

	int i; int j;
	for (int k = 0; k < m; k++) {
		scanf("%d%d", &i, &j); i--; j--;
		Edge * p = new Edge(); p->targetVertex = j; AdjList[j].inDegree++;
		p->nextEdge = AdjList[i].firstEdge; AdjList[i].firstEdge = p;
	}

	int ret = TSort(n); 
	printf("%d\n", ret);

	return 0;
}