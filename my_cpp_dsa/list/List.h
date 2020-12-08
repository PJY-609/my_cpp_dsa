#pragma once


#include "ListNode.h"

template <typename T> class List {
private:
	int _size;
	ListNodePosi(T) header;
	ListNodePosi(T) trailer;

protected:
	void init();
	int clear();
	void copyNodes(ListNodePosi(T) p, int n); // copy n nodes, starting from p 

public:
	List() { init(); }
	List(List<T> const &L);
	List(List<T> const &L, Rank r, int n);
	List(ListNodePosi(T) p, int n);
	~List() { clear(); delete header; delete trailer; }

	/* read only */
	Rank size() const { return _size; }
	bool empty() const { return (_size <= 0); }
	ListNodePosi(T) first() const { return header->succ; } // first node
	ListNodePosi(T) last() const { return trailer->pred; } // last node
	bool valid(ListNodePosi(T) p) { return p && (header != p) && (trailer != p); } // check if position is valid
	
	// O(n), not recommended
	T& operator[] (Rank r) const;

	/* accessible */
	ListNodePosi(T) insertAsFirst(T const &e);
	ListNodePosi(T) insertAsLast(T const &e);
	ListNodePosi(T) insertA(ListNodePosi(T) p, T const &e); // insert after
	ListNodePosi(T) insertB(ListNodePosi(T) p, T const &e); // insert before
	T remove(ListNodePosi(T) p);
};

#include "List_Implementation.h"

