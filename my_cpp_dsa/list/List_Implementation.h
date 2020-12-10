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

template <typename T>
ListNodePosi(T) List<T>::find(T const &e, int n, ListNodePosi(T) p) const { // find the last node in n predeccessors of p (p could be trailer)
	while (n-- > 0) { //£¨0 <= n <= rank(p) < _size£©
		p = p->pred;
		if (p->data == e) return p;
	}
	return NULL;
}

template <typename T>
int List<T>::deduplicate() {
	int oldSize = _size;
	ListNodePosi(T) p = first();
	for (Rank r = 0; p != trailer; p = p->succ) {
		if (ListNodePosi(T) q = find(p->data, r , p))
			remove(q);
		else 
			r++;
	}
	return oldSize - _size;
}

template <typename T>
void List<T>::traverse(void (*visit)(T &e)) {
	for (ListNodePosi(T) p = first(); p != trailer; p = p->succ)
		visit(p->data);
}

template <typename T> template <typename VST>
void List<T>::traverse(VST &visit) {
	for (ListNodePosi(T) p = first(); p != trailer; p = p->succ)
		visit(p->data);
}

template <typename T>
int List<T>::uniquify() {
	if (_size < 2) return 0;
	int oldSize = _size;
	ListNodePosi(T) p = first(); ListNodePosi(T) q;
	while ((q = p->succ) != trailer) {
		if (q->data == p->data)
			remove(q);
		else p = q;
	}
	return oldSize - _size;
}

template <typename T>
ListNodePosi(T) List<T>::search(T const &e, int n, ListNodePosi(T) p) const {
	while (n-- > 0 && (p = p->pred)->data >= e) {
		if (p->data == e) return p;
	}
	return NULL;
}