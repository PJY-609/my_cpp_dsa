#pragma once


#include "..\list\ListNode.h"
#include <stddef.h>

namespace my_list {
	enum SortEnum{
		SELECTIONSORT,
		INSERTSORT,
		MERGESORT,
		RADIXSORT
	};
}

template <typename T> class List {
private:
	int _size;
	ListNodePosi(T) header;
	ListNodePosi(T) trailer;

protected:
	void init();
	int clear();
	void copyNodes(ListNodePosi(T) p, int n); // copy n nodes, starting from p

	void selectionSort1(ListNodePosi(T) p, int n);
	void selectionSort2(ListNodePosi(T) p, int n);

	void insertSort(ListNodePosi(T) p, int n);
	
	ListNodePosi(T) merge(ListNodePosi(T) p, int n, List<T> &L, ListNodePosi(T) q, int m);
	void mergeSort(ListNodePosi(T) &p, int n);

	void radixSort(ListNodePosi(T) p, int n);

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

	ListNodePosi(T) max(ListNodePosi(T) p, int n) const;
	ListNodePosi(T) max() const { return max(first(), _size); }
	
	// unsorted list find
	// O(n)
	ListNodePosi(T) find(T const &e) const { return find(e, _size, trailer); }
	ListNodePosi(T) find(T const &e, int n, ListNodePosi(T) p) const;

	// sorted list search
	ListNodePosi(T) search(T const &e) const { return search(e, _size, trailer); }
	ListNodePosi(T) search(T const &e, int n, ListNodePosi(T) p) const;

	int deduplicate(); // unsorted list O(n^2)
	int uniquify(); // sorted list O(n)

	// O(n), not recommended
	T& operator[] (Rank r) const;

	/* accessible */
	ListNodePosi(T) insertAsFirst(T const &e);
	ListNodePosi(T) insertAsLast(T const &e);
	ListNodePosi(T) insertA(ListNodePosi(T) p, T const &e); // insert after
	ListNodePosi(T) insertB(ListNodePosi(T) p, T const &e); // insert before
	T remove(ListNodePosi(T) p);

	ListNodePosi(T) selectMax(ListNodePosi(T) p, int n);
	ListNodePosi(T) selectMax() { return selectMax(first(), _size); }

	void traverse(void (*visit)(T &e));
	template <typename VST> void traverse(VST &);

	void sort(ListNodePosi(T) p, int n, my_list::SortEnum sortType = my_list::SELECTIONSORT);
	void sort(my_list::SortEnum sortType = my_list::SELECTIONSORT) { sort(first(), _size, sortType); }

	void reverse();

};

#include "..\list\List_Implementation.h"

