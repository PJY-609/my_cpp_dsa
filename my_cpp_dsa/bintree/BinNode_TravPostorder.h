#pragma once
#include "../stack/stack.h"

template <typename T, typename VST>
void travPost_R(BinNodePosi(T) x, VST &visit) {
	if (!x) return;
	travPost_R(x->lc, visit);
	travPost_R(x->rc, visit);
	visit(x->data);
}

template <typename T>
static void goToLeftmostLeaf(Stack<BinNodePosi(T)>& S) {
	BinNodePosi(T) x;
	while (x = S.top()) {
		if (HasLChild(*x)) { // go to leftmose as deep as possible
			if (HasRChild(*x)) // if r child exists
				S.push(x->rc); // first pushed
			S.push(x->lc);
		}
		else { // if no left child
			S.push(x->rc);
		}
	}
	S.pop(); // pop the top empty elem
}

template <typename T, typename VST>
void travPost_I(BinNodePosi(T) x, VST &visit) {
	Stack<BinNodePosi(T)> S;
	if (x) S.push(x);
	while (!S.empty()) {
		if (!(S.top() == x->parent))
			goToLeftmostLeaf(S);
		x = S.pop();
		visit(x->data);
	}
}