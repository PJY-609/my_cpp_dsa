#pragma once


#include "ListNode.h"

template <typename T> class List {
private:
	int _size;
	ListNodePosi(T) header, trailer;

protected:
	void init();
	void clear();
	void copyNodes(ListNodePosi(T) p, int n);

public:
	/* read only */
	Rank size() const { return _size; }
	bool empty() const { return (_size <= 0); }
	ListNodePosi(T) first() const { return header->succ; } // first node
	ListNodePosi(T) last() const { return trailer->pred; } // last node
	
	// O(n), not recommended
	T& operator[] (Rank r) const;
};

#include "List_Implementation.h"

