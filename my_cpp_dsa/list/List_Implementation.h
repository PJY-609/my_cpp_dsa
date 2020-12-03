#pragma once

template <typename T>
T& List<T>::operator[] (Rank r) const {
	ListNodePosi(T) p = first();
	while (0 < r--)
		p = p->succ;
	return p->data;
}


template <typename T> void List<T>::init() {
	header = new ListNode<T>;
	trailder = new ListNode<T>;
	header->succ = trailer; header->pred = NULL;
	trailer->pred = header; trailer->succ = NULL;
	_size = 0;
}

//template <typename T>
//void List<T>::copyNodes(ListNodePosi(T) p, int n) { // p is legal and p must have n - 1 successors
//	init();
//	while (n--) {
//
//	}
//}