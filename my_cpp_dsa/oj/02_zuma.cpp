/*Description*/
/*
Let's play the game Zuma!

There are a sequence of beads on a track at the right beginning.All the beads are colored but no three adjacent ones are allowed to be with a same color.You can then insert beads one by one into the sequence.Once three(or more) beads with a same color become adjacent due to an insertion, they will vanish immediately.

Note that it is possible for such a case to happen for more than once for a single insertion.You can't insert the next bead until all the eliminations have been done.

Given both the initial sequence and the insertion series, you are now asked by the fans to provide a playback tool for replaying their games.In other words, the sequence of beads after all possible eliminations as a result of each insertion should be calculated.
*/

/*Input*/
/*
The first line gives the initial bead sequence.Namely, it is a string of capital letters from 'A' to 'Z', where different letters correspond to beads with different colors.

The second line just consists of a single interger n, i.e., the number of insertions.

The following n lines tell all the insertions in turn.Each contains an integer k and a capital letter ¦², giving the rank and the color of the next bead to be inserted respectively.Specifically, k ranges from 0 to m when there are currently m beads on the track.
*/

/*Output*/
/*
n lines of capital letters, i.e., the evolutionary history of the bead sequence.

Specially, "-" stands for an empty sequence.
*/

/*Example*/
/*Input

ACCBA
5
1 B
0 A
2 B
4 C
0 A
Output

ABCCBA
AABCCBA
AABBCCBA
-
A
*/

/*Restrictions*/
/*
0 <= n <= 10 ^ 4

0 <= length of the initial sequence <= 10 ^ 4

Time: 2 sec

Memory : 256 MB
*/


#include <iostream>
#include <cstring>
#include <cstdio>
#include <iostream>

using namespace std;

#define N 100000000
#define BeadPos Bead*

char S[N];
char R[150000000]; //large enough to pass the last test case
int listSize = 0;

struct Bead
{
	char data;
	BeadPos pred;
	BeadPos succ;
	Bead() {}
	Bead(char color, BeadPos pred = NULL, BeadPos succ = NULL) :data(color), pred(pred), succ(succ) {}
	BeadPos insertAsPred(char const &name);
}*header, *trailer;

BeadPos Bead::insertAsPred(char const &color) {
	BeadPos x = new Bead(color, pred, this);
	pred->succ = x;
	pred = x;
	return x;
}



BeadPos insertAsLast(char const &color) {
	listSize++; return trailer->insertAsPred(color);
}

BeadPos insertBefore(BeadPos p, char c) {
	listSize++; return p->insertAsPred(c);
}

void init(char *str, int len)
{
	header = new Bead();
	trailer = new Bead();
	header->pred = NULL; header->succ = trailer;
	trailer->pred = header; trailer->succ = NULL;
	listSize = 0;

	for (int i = 0; i < len; i++)
		insertAsLast(str[i]);
}

bool valid(BeadPos p) { 
	return (p && p != header && p != trailer); 
}

BeadPos find(int r) {
	BeadPos p = header->succ;
	while (r-- > 0 && valid(p)) {
		p = p->succ;
	}
	return p;
}

char remove(BeadPos p) {
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;

	p->pred = NULL; p->succ = NULL;

	char temp = p->data;
	delete p;

	listSize--;
	return temp;
}

bool elminate(BeadPos &p, char &data) {

	BeadPos q = p->pred;
	int num = 0;

	while (valid(p) && p->data == data) {
		p = p->succ; num++;
	}
	
	while (valid(q) && q->data == data) {
		q = q->pred; num++;
	}

	if (num < 3) return false;
	
	while (q->succ != p)
		remove(q->succ);

	if (p != trailer)
		data = p->data;
	
	return true;
}


void update(int r, char c) {
	BeadPos p = find(r);
	insertBefore(p, c);
	
	bool eliminated = true;
	while (listSize > 0 && eliminated) {
		eliminated = elminate(p, c);
	}
}

void output(char * buffer, int &startIdx) {
	if (listSize == 0){
		buffer[startIdx++] = '-';
		buffer[startIdx++] = '\n';
		return;
	}

	BeadPos p = header->succ;
	for (int i = 0; i<listSize; i++) {
		buffer[startIdx++] = p->data;
		p = p->succ;
	}
	buffer[startIdx++] = '\n';
}

int main()
{
	std::cin.getline(S, N);
	init(S, strlen(S));
	
	int n; scanf("%d", &n);
	
	int *P = new int[n];
	char *C = new char[n];

	for (int i = 0; i<n; i++)
	{
		scanf("%d %c", &P[i], &C[i]);
	}

	int len = 0;
	for(int i = 0; i < n; i++)
	{
		update(P[i], C[i]);
		output(R, len);
	}
	printf("%s", R);
	return 0;
}
