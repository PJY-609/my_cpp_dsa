#pragma once

template <typename T>
T& List<T>::operator[] (Rank r) const {
	ListNodePosi(T) p = first();
	while (0 < r--)
		p = p->succ;
	return p->data;
}


template <typename T> 
void List<T>::init() {
	header = new ListNode<T>;
	trailer = new ListNode<T>;
	header->succ = trailer; header->pred = NULL;
	trailer->pred = header; trailer->succ = NULL;
	_size = 0;
}

template <typename T>
ListNodePosi(T) List<T>::insertAsFirst(T const &e) {
	_size++; return header->insertAsSucc(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertAsLast(T const &e) {
	_size++; return trailer->insertAsPred(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertA(ListNodePosi(T) p, T const &e) {
	_size++; return p->insertAsSucc(e);
}

template <typename T>
ListNodePosi(T) List<T>::insertB(ListNodePosi(T) p, T const &e) {
	_size++; return p->insertAsPred(e);
}

template <typename T>
T List<T>::remove(ListNodePosi(T) p) {
	T e = p->data;
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;
	delete p; // release space
	_size--;
	return e;
}

template <typename T>
void List<T>::copyNodes(ListNodePosi(T) p, int n) {
	init(); // initialization
	while (n--) {
		insertAsLast(p->data);
		p = p->succ;
	}
}

template <typename T>
int List<T>::clear() {
	int oldSize = _size;
	while (_size > 0) remove(header->succ);
	return oldSize;
}

template <typename T>
List<T>::List(List<T> const &L) {
	copyNodes(L.first(), L._size);
}

template <typename T>
List<T>::List(List<T> const &L, Rank r, int n) {
	ListNodePosi(T) p = L.first();
	while (r-- > 0) p = p->succ;
	copyNodes(p, n);
}

template <typename T>
List<T>::List(ListNodePosi(T) p, int n) {
	copyNodes(p, n);
}