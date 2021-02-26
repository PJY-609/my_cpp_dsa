#pragma once

#include "..\bintree\BinNode_macro.h"
//#include "..\bintree\BinTree.h"
#include "..\bintree\release.h"

template <typename T>
int BinTree<T>::updateHeight(BinNodePosi(T) x) {
	return x->height = 1 + __max(stature(x->lc), stature(x->rc));
}

template <typename T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x) {
	while (x) {
		updateHeight(x); x = x->parent;
	}
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRoot(T const &e) {
	_size = 1; return _root = new BinNode<T>(e);
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const &e) {
	_size++;
	updateHeightAbove(x);
	x->insertAsLC(e);
	return x->lc;
}

template <typename T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const &e) {
	_size++;
	updateHeightAbove(x);
	x->insertAsRC(e);
	return x->rc;
}

template <typename T>
BinNodePosi(T) BinTree<T>::attachAsLC(BinNodePosi(T) x, BinTree<T>* &S) {
	if (x->lc = S->_root)
		x->lc->parent = x;
	_size += S->size();
	updateHeightAbove(x);
	S->_root = NULL; S->_size = 0;
	release(S); S = NULL;
	return x;
}

template <typename T>
BinNodePosi(T) BinTree<T>::attachAsRC(BinNodePosi(T) x, BinTree<T>* &S) {
	if (x->rc = S->_root)
		x->rc->parent = x;
	_size += S->size();
	updateHeightAbove(x);
	S->_root = NULL; S->_size = 0;
	release(S); S = NULL;
	return x;
}

template <typename T>
static int removeAt(BinNodePosi(T) x) {
	if (!x) return 0;
	int n = 1 + removeAt(x->lc) + removeAt(x->rc);
	release(x->data); release(x); return n;
}

template <typename T>
int BinTree<T>::remove(BinNodePosi(T) x) {
	FromParentTo(*x) = NULL;
	updateHeightAbove(x->parent);
	int n = removeAt(x); _size -= n; return n;
}

template <typename T>
BinTree<T>* BinTree<T>::secede(BinNodePosi(T) x) {
	FromParentTo(*x) = NULL;
	updateHeightAbove(x->parent);

	BinTree<T>* S = new BinTree<T>;
	S->_root = x; x->parent = NULL;
	S->_size = x->size(); _size -= S->size();
	return S;
}