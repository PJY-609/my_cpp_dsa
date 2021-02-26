#pragma once

#define BinNodePosi(T) BinNode<T>*
#define stature(p) ((p) ? p->height : -1) // if empty tree, height is -1


template <typename T> struct BinNode {
	BinNodePosi(T) parent; BinNodePosi(T) lc; BinNodePosi(T) rc; // parent, left child, right child
	T data;
	int height;
	int size(); // size of subtree

	BinNode() : parent(NULL), lc(NULL), rc(NULL){}
	BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL) :
		data(e), parent(p), lc(lc), rc(rc){}

	BinNodePosi(T) insertAsLC(T const &e);
	BinNodePosi(T) insertAsRC(T const &e);

	BinNodePosi(T) succ(); // in the sense of inorder
	BinNodePosi(T) pred(); // in the sense of inorder

	template <typename VST> void travPre(VST &visit, int travType=2); // O(n)
	template <typename VST> void travIn(VST &visit, int travType=1); // O(n)
	template <typename VST> void travPost(VST &visit, int travType=1); // O(n)
	template <typename VST> void travLevel(VST &visit); // O(n)
};

#include "..\bintree\BinNode_Implementation.h"