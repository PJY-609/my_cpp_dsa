#pragma once

template <typename T>
void Vector<T>::expand() {
	if (_size < _capacity) return;
	if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;

	T* oldElem = _elem;
	_elem = new T[_capacity <<= 1]; // double capacify strategy
	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];
	delete[] oldElem;
}

template <typename T>
void Vector<T>::shrink() {
	if (_capacity < DEFAULT_CAPACITY << 1) return;
	if (_size << 2 > _capacity) return;

	T* oldElem = _elem;
	_elem = new T[_capacity >>= 1];

	for (int i = 0; i < _size; i++)
		_elem[i] = oldElem[i];

	delete[] oldElem;
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