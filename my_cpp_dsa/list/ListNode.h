#pragma once

// list node position
typedef int Rank;
#define ListNodePosi(T) ListNode<T>* // template alias: #define APtr(T) A<T>*

template <typename T> struct ListNode {
	T data;
	ListNodePosi(T) pred;
	ListNodePosi(T) succ; // predecessor and successor

	ListNode(){} // for header and trailer
	ListNode(T e, ListNodePosi(T) p = NULL, ListNodePosi(T) s = NULL): // initialization list for constructor
		data(e), pred(p), succ(s){} 

	ListNodePosi(T) insertAsPred(T const &e);
	ListNodePosi(T) insertAsSucc(T const &e);
};

#include "..\list\ListNode_Implementation.h"