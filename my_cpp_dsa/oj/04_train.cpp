/*Description*/
/*
Figure 1 shows the structure of a station for train dispatching.

Figure 1

In this station, A is the entrance for each train and B is the exit.S is the transfer end.All single tracks are one - way, which means that the train can enter the station from A to S, and pull out from S to B.Note that the overtaking is not allowed.Because the compartments can reside in S, the order that they pull out at B may differ from that they enter at A.However, because of the limited capacity of S, no more that m compartments can reside at S simultaneously.

Assume that a train consist of n compartments labeled{ 1, 2, ¡­, n }.A dispatcher wants to know whether these compartments can pull out at B in the order of{ a1, a2, ¡­, an } (a sequence).If can, in what order he should operate it ?

*/

/*Input*/
/*
Two lines :

1st line : two integers n and m;

2nd line : n integers separated by spaces, which is a permutation of{ 1, 2, ¡­, n }.This is a compartment sequence that is to be judged regarding the feasibility.
*/

/*Output*/
/*
If the sequence is feasible, output the sequence.¡°Push¡± means one compartment goes from A to S, while ¡°pop¡± means one compartment goes from S to B.Each operation takes up one line.

If the sequence is infeasible, output a ¡°no¡±.
*/

/*Example 1*/
/*
Input

5 2
1 2 3 5 4
Output

push
pop
push
pop
push
pop
push
push
pop
pop
*/

/*Example 2*/
/*
Input

5 5
3 1 2 4 5
Output

No
*/

/*Restrictions*/
/*
1 <= n <= 1, 600, 000

0 <= m <= 1, 600, 000

Time: 2 sec

	Memory : 256 MB
*/

#include <iostream>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <string.h>

#define NodePos Node*
using namespace std;

int A[20000000];
char R[50000000];

int stackSize = 0;

struct Node {
	int label;
	NodePos pred;
	NodePos succ;
	Node() {}
	Node(int label, NodePos pred = NULL, NodePos succ = NULL) :label(label), pred(pred), succ(succ) {}
	void insertAsPred(int const &label);
}*header, *trailer;

void Node::insertAsPred(int const &label) {
	NodePos x = new Node(label, pred, this);
	pred->succ = x;
	pred = x;
}

void push(int const &label) {
	stackSize++; trailer->insertAsPred(label);
}

int pop() {
	NodePos p = trailer->pred;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;

	p->pred = NULL; p->succ = NULL;

	int temp = p->label;
	delete p;

	stackSize--;
	return temp;
}

int& top() {
	return trailer->pred->label;
}

void init() {
	header = new Node();
	trailer = new Node();
	header->pred = NULL; header->succ = trailer;
	trailer->pred = header; trailer->succ = NULL;
	stackSize = 0;
}

bool isStackPermutation(int S[], int n, int capacity, char *C, int &len) {
	init();// init Stack
	
	int i = 1;
	for (int k = 0; k < n; k++) {
		while (stackSize < 1 || top() != S[k]) {
			push(i++); strcpy(C + len, "push\n"); len += 5;
			if (i > n + 1 || stackSize > capacity) return false;
		}

		if (stackSize < 1 || top() != S[k]) return false;

		pop(); strcpy(C + len, "pop\n"); len += 4;
		
	}
	return true;
}

int main() {
	int n; int m;
	scanf("%d%d", &n, &m);
	
	for (int i = 0; i < n; i++) scanf("%d", &A[i]);

	int resultLen = 0;
	bool isPermute = isStackPermutation(A, n, m, R, resultLen);

	if (isPermute) printf("%s", R);
	else printf("No\n");
	return 0;
}