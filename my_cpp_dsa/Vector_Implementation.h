#pragma once

template <typename T>
void Vector<T>::expand() {
	if (_size < _capacity) return;
	if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;

	T* oldElem = _elem;
	_elem = new T[_capacity <<= 1]; // double capacify strategy
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete [] oldElem;
}

template <typename T>
void Vector<T>::shrink() {
	if (_capacity < DEFAULT_CAPACITY << 1) return;
	if (_size << 2 > _capacity) return;

	T* oldElem = _elem;
	_elem = new T[_capacity >>= 1];

	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];

	delete [] oldElem;
}

template <typename T>
void Vector<T>::copyFrom(T const* A, Rank lo, Rank hi) {
	_elem = new T[_capacity = 2 * (hi - lo)];
	for (_size = 0; _size < (hi - lo); _size++)
		_elem[_size] = A[lo + _size];
}

template <typename T>
T& Vector<T>::operator[](Rank r) { return _elem[r]; }

template <typename T>
const T& Vector<T>::operator[](Rank r) const { return _elem[r]; }

template <typename T>
Vector<T>& Vector<T>::operator=(Vector<T> const& V) {
	if (_elem) delete[] _elem;
	copyFrom(V._elem, 0, V._size);
	return *this; // https://stackoverflow.com/questions/2750316/this-vs-this-in-c
}

template <typename T>
Rank Vector<T>::find(T const &e, Rank lo, Rank hi) const {
	while ((lo < hi--) && (e != _elem[hi]));
	return hi;
}

template <typename T>
Rank Vector<T>::binSearch1(T const &e, Rank lo, Rank hi) const {
	while (lo < hi) { // 3 judgement branches
		Rank mi = (lo + hi) >> 1;
		if (e < _elem[mi]) hi = mi;
		else if (_elem[mi] < e) lo = mi + 1;
		else return mi;
	}
	return -1;
} // cannot find the max Rank if multiple vals exist

template <typename T>
Rank Vector<T>::binSearch2(T const &e, Rank lo, Rank hi) const {
	while (lo < hi - 1) { // 2 judgement bracnhes
		Rank mi = (lo + hi) >> 1;
		(e < _elem[mi]) ? hi = mi : lo = mi;
	}
	return (e < _elem[lo]) ? lo - 1 : lo; // always return Rank whose val not larger than e
} // cannot find the max Rank if multiple vals exist


template <typename T>
Rank Vector<T>::binSearch3(T const &e, Rank lo, Rank hi) const {
	while (lo < hi) { // 2 judgement branches 
		Rank mi = (lo + hi) >> 1;
		(e < _elem[mi]) ? hi = mi : lo = mi + 1;
	}
	return lo - 1;
} // can find the max Rank if multiple vals exist

template <typename T>
Rank Vector<T>::fibSearch1(T const &e, Rank lo, Rank hi) const {
	Fib fib(hi - lo);
	while (lo < hi) {
		while ((hi - lo) < fib.get()) fib.prev();
		Rank mi = lo + fib.get() - 1;
		if (e < _elem[mi]) hi = mi;
		else if (_elem[mi] < e) lo = mi + 1;
		else return mi;
	}
	return -1;
} // can't find the max Rank if multiple vals exist


template <typename T>
Rank Vector<T>::fibSearch2(T const &e, Rank lo, Rank hi) const {
	Fib fib(hi - lo);
	while (lo < hi) {
		while ((hi - lo) < fib.get()) fib.prev();
		Rank mi = lo + fib.get() - 1;
		(e < _elem[mi]) ? hi = mi : lo = mi + 1;
	}
	return lo - 1;
} // can find the max Rank if multiple vals exist

template <typename T>
Rank Vector<T>::insert(T const &e, Rank r) {
	if (r >= _size || r < 0) return -1;
	expand();
	for (int i = _size; i > r; i--)
		_elem[i] = _elem[i - 1];
	_elem[r] = e;
	_size++;
	return r;
}

template <typename T>
T Vector<T>::remove(Rank r) {
	T e = _elem[r];
	remove(r, r + 1);
	return e;
}

template <typename T>
int Vector<T>::remove(Rank lo, Rank hi) {
	if (lo == hi) return 0;
	Rank interval = (hi - lo);
	for (int i = lo; i < hi; i++)
		_elem[i] = _elem[i + interval];
	_size -= hi - lo;
	shrink();
	return hi - lo;
}

template <typename T>
int Vector<T>::deduplicate1() {
	int oldSize = _size;
	int i = 0;
	while (i < _size - 1) {
		int j = i + 1;
		while (j < _size)
			(_elem[i] == _elem[j]) ? remove(j) : j++;
		i++;
	}
	shrink();
	return oldSize - _size;
}

template <typename T>
int Vector<T>::deduplicate2() {
	int oldSize = _size;
	int i = 1;
	while (i < _size)
		// Find the same val in previous elems. Would find only one at most.
		(find(_elem[i], 0, i) < 0) ? i++ : remove(i);
	shrink();
	return oldSize - _size;
}

template <typename T>
int Vector<T>::uniquify1() {
	int oldSize = _size;
	int i = 1;
	while (i < _size)
		(_elem[i - 1] == _elem[i]) ? remove(i) : i++;
	shrink();
	return oldSize - _size;
}

template <typename T>
int Vector<T>::uniquify2() {
	int i = 0, j = 0;
	while (++j < _size) {
		if (_elem[i] != _elem[j])
			_elem[++i] = _elem[j];
	}
	_size = ++i;
	shrink();
	return j - i;
}