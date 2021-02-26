#pragma once

#include "../bintree/BinNode_macro.h"
#include "../bintree/BinNode_TravPreorder.h"
#include "../bintree/BinNode_TravInorder.h"
#include "../bintree/BinNode_TravPostorder.h"
#include "../queue/queue.h"

template <typename T> 
int BinNode<T>::size() {
	int s = 1;
	if (lc) s += lc->size();
	if (rc) s += rc->size();
	return s;
}

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsLC(T const &e) {
	return lc = new BinNode<T>(e, this);
}

template <typename T>
BinNodePosi(T) BinNode<T>::insertAsRC(T const &e) {
	return rc = new BinNode<T>(e, this);
}

template <typename T>
BinNodePosi(T) BinNode<T>::succ() {
	BinNodePosi(T) s = this;
	if (rc) { // if the current node has right child
		s = rc;
		while (HasLChild(*s)) s = s->lc; // the direct successor is the deepest left child
	}
	else { 
		while (IsRChild(*s)) s = s->parent;
		s = s->parent;
	}
	return s;
}

template <typename T>
BinNodePosi(T) BinNode<T>::pred() {
	BinNodePosi(T) s = this;
	if (lc) {
		s = lc;
		while (HasRChild(*s)) s = s->rc;
	}
	else {
		while (IsLChild(*s)) s = s->parent;
		s = s->parent;
	}
	return s;
}

template <typename T> template <typename VST>
void BinNode<T>::travPre(VST &visit, int travType) { 
	switch (travType)
	{
	case 0: travPre_R(this, visit); break;
	case 1: travPre_I1(this, visit); break;
	case 2: travPre_I2(this, visit); break;
	default: travPre_I2(this, visit); break;
	}
}

template <typename T> template <typename VST>
void BinNode<T>::travIn(VST &visit, int travType) {
	switch (travType)
	{
	case 0: travIn_R(this, visit); break;
	case 1: travIn_I1(this, visit); break;
	default: travIn_I1(this, visit); break;
	}
}

template <typename T> template <typename VST>
void BinNode<T>::travPost(VST &visit, int travType) {
	switch (travType)
	{
	case 0: travPost_R(this, visit); break;
	case 1: travPost_I(this, visit); break;
	default: travPost_I(this, visit);  break;
	}
}

template <typename T> template <typename VST>
void BinNode<T>::travLevel(VST &visit) {
	Queue<BinNodePosi(T)> Q;
	Q.enqueue(this);
	BinNodePosi(T) x;
	while (!Q.empty()) {
		x = Q.dequeue();
		visit(x->data);
		if (HasLChild(*x)) Q.enqueue(x->lc);
		if (HasRChild(*x)) Q.enqueue(x->rc);
	}
}