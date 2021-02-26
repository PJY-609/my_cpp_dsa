#pragma once
#include "../stack/stack.h"

template <typename T, typename VST>
void travPre_R(BinNodePosi(T) x, VST &visit) {
	if (!x) return;
	visit(x->data);
	travPre_R(x->lc, visit);
	travPre_R(x->rc, visit);
}

template <typename T, typename VST>
void travPre_I1(BinNodePosi(T) x, VST &visit) {
	Stack<BinNodePosi(T)> S;
	if (x) S.push(x);
	while (!S.empty()) {
		x = S.pop(); visit(x->data);
		if (HasRChild(*x)) S.push(x->rc); // right child first in, later out
		if (HasLChild(*x)) S.push(x->lc); // left child last in, earlier out
	}
}

template <typename T, typename VST>
static void visitAlongVine(BinNodePosi(T) x, VST &visit, Stack<BinNodePosi(T)> &S) {
	while (x) {
		visit(x->data);
		S.push(x->rc);
		x = x->lc;
	}
}

template <typename T, typename VST>
void travPre_I2(BinNodePosi(T) x, VST &visit) {
	Stack<BinNodePosi(T)> S;
	while (true) {
		visitAlongVine(x, visit, S);
		if (S.empty()) break;
		x = S.pop();
	}
}