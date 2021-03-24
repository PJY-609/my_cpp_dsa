/*Description*/
/*
In general, given the preorder traversal sequence and postorder traversal sequence of a binary tree, we cannot determine the binary tree.

Figure 1

In Figure 1 for example, although they are two different binary tree, their preorder traversal sequence and postorder traversal sequence are both of the same.

But for one proper binary tree, in which each internal node has two sons, we can uniquely determine it through its given preorder traversal sequence and postorder traversal sequence.

Label n nodes in one binary tree using the integers in[1, n], we would like to output the inorder traversal sequence of a binary tree through its preorder and postorder traversal sequence.
*/

/*Input*/
/*
The 1st line is an integer n, i.e., the number of nodes in one given binary tree,

The 2nd and 3rd lines are the given preorder and postorder traversal sequence respectively.
*/

/*Output*/
/*
The inorder traversal sequence of the given binary tree in one line.
*/

/*Example*/
/*
Input

5
1 2 4 5 3
4 5 2 3 1
Output

4 2 5 1 3
*/

/*Restrictions*/
/*
For 95 % of the estimation, 1 <= n <= 1, 000, 00

For 100 % of the estimation, 1 <= n <= 4, 000, 000

The input sequence is a permutation of{ 1,2...n }, corresponding to a legal binary tree.

Time: 2 sec

Memory : 256 MB
*/

/*Hints*/
/*
Figure 2

In Figure 2, observe the positions of the left and right children in preorder and postorder traversal sequence.
*/
	

// Reference:
// https://github.com/zhousoft/TsingHuaDataStructOj/blob/master/BinaryTreeRebuild/binaryTreeRebuild.cpp

#include <iostream>
#include <cstdio>

#define MAX 10000001
using namespace std;

int preSeq[MAX];
int pstSeq[MAX];


int find(int seq[], int len, int e) {
	int count;
	for (count = 0; count < len; count++) {
		if (seq[count] == e) return count;
	}
	return len;
}


void properRebuildToInOrder(int preOrder[], int pstOrder[], int len) {
	if (len == 1) { printf("%d ", preOrder[0]); return; }

	int pivot = find(pstOrder, len, preOrder[1]);
	
	// lst: left sub-tree, rst: right sub-tree
	int lstLen = pivot + 1; 
	int rstLen = len - lstLen - 1;

	int* lstPrePos = preOrder + 1;
	int* rstPrePos = preOrder + lstLen + 1;
	int* lstPstPos = pstOrder;
	int* rstPstPos = pstOrder + lstLen;

	properRebuildToInOrder(lstPrePos, lstPstPos, lstLen);
	printf("%d ", preOrder[0]);
	properRebuildToInOrder(rstPrePos, rstPstPos, rstLen);
}


int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i<n; i++)
	{
		scanf("%d", &preSeq[i]);
	}
	for (int i = 0; i<n; i++)
	{
		scanf("%d", &pstSeq[i]);
	}

	properRebuildToInOrder(preSeq, pstSeq, n);

	return 0;
}