#pragma once
#include "../stack/stack.h"

template <typename T, typename VST>
void travIn_R(BinNodePosi(T) x, VST &visit) {
	if (!x) return;
	travIn_R(x->lc, visit);
	visit(x->data);
	travIn_R(x->rc, visit);
}

template <typename T>
static void goAlongVine(BinNodePosi(T) x, Stack<BinNodePosi(T)> &S) {
	while (x) {
		S.push(x);
		x = x->lc;
	}
}

template <typename T, typename VST>
void travIn_I1(BinNodePosi(T) x, VST &visit) {
	Stack<BinNodePosi(T)> S;
	while (true) {
		goAlongVine(x, S);
		if (S.empty()) break;
		x = S.pop();
		visit(x->data);
		x = x->rc;
	}
}

