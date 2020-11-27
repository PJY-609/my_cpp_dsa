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


// middle point of fib search can be determined as
// mi = floor(0.382 * lo + 0.618 * hi)
// or 
// mi = (lo + (lo << 1) + hi + (hi << 2)) >> 3
// That makes the init of fib sequence more concise

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
	if (r > _size || r < 0) return -1;
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

template <typename T>
void Vector<T>::bubbleSort1(Rank lo, Rank hi) {
	while (lo < hi--)
		for (int i = lo; i < hi; i++)
			if (_elem[i] > _elem[i + 1])
				std::swap(_elem[i], _elem[i + 1]);
}

template <typename T>
void Vector<T>::bubbleSort2(Rank lo, Rank hi) {
	for (bool sorted = false; sorted = !sorted; ) {
		for (int i = lo; i < hi - 1; i++) {
			if (_elem[i] > _elem[i + 1]) {
				std::swap(_elem[i], _elem[i + 1]);
				sorted = false;
			}
		}
	}
}

template <typename T>
void Vector<T>::bubbleSort3(Rank lo, Rank hi) {
	for (int last = --hi; lo < last; hi = last) 
		for (int i = last = lo; i < hi; i++) 
			if (_elem[i] > _elem[i + 1])
				std::swap(_elem[last = i], _elem[i + 1]);
}

template <typename T>
Rank Vector<T>::max(Rank lo, Rank hi) {
	Rank mx = hi;
	while (lo < hi--)
		if (_elem[hi] > _elem[mx]) 
			mx = hi;
	return mx;
}

template <typename T>
void Vector<T>::selectionSort(Rank lo, Rank hi) {
	while (lo < --hi)
		std::swap(_elem[max(lo, hi)], _elem[hi]);
}

template <typename T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi) {
	int i = 0; 
	T* A = _elem + lo;
	
	int j = 0, lb = mi - lo;
	T* B = new T[lb]; 
	for (int i = 0; i < lb; i++) B[i] = A[i];
	
	int k = 0, lc = hi - mi;
	T* C = _elem + mi;

	while (j < lb && k < lc)
		A[i++] = (B[j] <= C[k]) ? B[j++] : C[k++];
	while (j < lb) // if C runs out first
		A[i++] = B[j++]; // fill the rest with B's elements
	// if B runs out first
	// C's elements remain their positions

	delete[] B;
}

template <typename T>
void Vector<T>::mergeSort(Rank lo, Rank hi) {
	if (hi - lo < 2) return; // single elem doesn't need to be merger (will cause error in merge())

	Rank mi = (hi + lo) >> 1;
	mergeSort(lo, mi); mergeSort(mi, hi);
	merge(lo, mi, hi);
}

template <typename T>
void Vector<T>::insertSort(Rank lo, Rank hi, int step) {
	for (int i = lo + step; i < hi; i++) {
		int j = i - step;
		T x = _elem[i];
		while (j >= 0 && _elem[j] > x) {
			_elem[j + step] = _elem[j];
			j -= step;
		}
		_elem[j + step] = x;
	}
}

template <typename T>
void Vector<T>::shellSort(Rank lo, Rank hi) { //0 <= lo < hi <= size <= 2^30
	for (int d = 0x3FFFFFFF; d > 0; d >>= 1) //PS Sequence: { 1, 3, 7, 15, ..., 1073741823 }
		insertSort(lo, hi, d);
}

template <typename T>
Rank Vector<T>::partition1(Rank lo, Rank hi) { // LUG
	std::swap(_elem[lo], _elem[lo + std::rand() % (hi - lo)]); // randomly select an element as pivot
	hi--;
	T pivot = _elem[lo];

	while (lo < hi) {
		while (lo < hi && pivot <= _elem[hi])
			hi--;
		_elem[lo] = _elem[hi];
		while (lo < hi && _elem[lo] <= pivot)
			lo++;
		_elem[hi] = _elem[lo];
	}
	_elem[lo] = pivot;
	return lo;
}

template <typename T>
Rank Vector<T>::partition2(Rank lo, Rank hi) { // LUG1, the equivalent of LUG
	std::swap(_elem[lo], _elem[lo + std::rand() % (hi - lo)]); // randomly select an element as pivot
	hi--;
	T pivot = _elem[lo];

	while (lo < hi) {
		while (lo < hi && pivot <= _elem[hi])
			hi--;
		if (lo < hi) _elem[lo++] = _elem[hi];
		while (lo < hi && _elem[lo] <= pivot)
			lo++;
		if (lo < hi) _elem[hi--] = _elem[lo];
	}
	_elem[lo] = pivot;
	return lo;
}

template <typename T>
Rank Vector<T>::partition3(Rank lo, Rank hi) { // DUP, better handle duplicate elements
	std::swap(_elem[lo], _elem[lo + std::rand() % (hi - lo)]); // randomly select an element as pivot
	hi--;
	T pivot = _elem[lo];

	while (lo < hi) {
		while (lo < hi) {
			if (pivot <= _elem[hi]) 
				hi--;
			else {
				_elem[lo++] = _elem[hi];
				break;
			}
		}
		while (lo < hi) {
			if (_elem[lo] <= pivot) 
				lo++;
			else {
				_elem[hi--] = _elem[lo];
				break;
			};
		}
	}
	_elem[lo] = pivot;
	return lo;
}

template <typename T>
Rank Vector<T>::partition4(Rank lo, Rank hi) { // DUP1, the equivalent of DUP
	std::swap(_elem[lo], _elem[lo + std::rand() % (hi - lo)]); // randomly select an element as pivot
	hi--;
	T pivot = _elem[lo];

	while (lo < hi) {
		while (lo < hi && pivot < _elem[hi])
			hi--;
		if (lo < hi) _elem[lo++] = _elem[hi];
		while (lo < hi && _elem[lo] < pivot)
			lo++;
		if (lo < hi) _elem[hi--] = _elem[lo];
	}
	_elem[lo] = pivot;
	return lo;
}

template <typename T>
Rank Vector<T>::partition5(Rank lo, Rank hi) { // LGU
	std::swap(_elem[lo], _elem[lo + std::rand() % (hi - lo)]); // randomly select an element as pivot
	T pivot = _elem[lo];
	Rank mi = lo;
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//   ---- L < [lo] ----- ] ----- [lo] <= G --- ] [ ----- Unknown -------
	// X x . . . . . . . . . x . . . . . . . . . . . x . . . . . . . . . . x X
	// |                     |                       |                       |
	// lo (pivot candidate)  mi                      k                       hi
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	for (int k = lo + 1; k < hi; k++)
		if (_elem[k] < pivot)
			std::swap(_elem[++mi], _elem[k]);
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	//   --------- L < [lo] ---------- ] ------------- [lo] <= G ----------]
	// X x . . . . . . . . . . . . . . x . . . . . . . . . . . . . . . . . x X
	// |                               |                                     |
	// lo (pivot candidate)            mi                                    hi
	//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
	std::swap(_elem[mi], _elem[lo]);
	return mi;
}

template <typename T>
Rank Vector<T>::partition(Rank lo, Rank hi, my_vector::PartitionEnum partitionType) {
	switch (partitionType) {
	case (my_vector::LUG):
		return partition1(lo, hi);
	case (my_vector::LUG1):
		return partition2(lo, hi);
	case (my_vector::DUP):
		return partition3(lo, hi);
	case (my_vector::DUP1):
		return partition4(lo, hi);
	case (my_vector::LGU):
		return partition5(lo, hi);
	default:
		return -1;
	}
}

template <typename T>
void Vector<T>::quickSort(Rank lo, Rank hi, my_vector::PartitionEnum paritionType) {
	if (hi - lo < 2) return;
	Rank mi = partition(lo, hi, paritionType);
	quickSort(lo, mi, paritionType); 
	quickSort(mi + 1, hi, paritionType);
}


template <typename T>
void Vector<T>::sort(Rank lo, Rank hi, my_vector::SortEnum sortType) {
	switch (sortType) {
	case (my_vector::BUBBLESORT1):
		bubbleSort1(lo, hi); break;
	case (my_vector::BUBBLESORT2):
		bubbleSort2(lo, hi); break;
	case (my_vector::BUBBLESORT3):
		bubbleSort3(lo, hi); break;
	case (my_vector::SELECTIONSORT):
		selectionSort(lo, hi); break;
	case (my_vector::MERGESORT):
		mergeSort(lo, hi); break;
	case (my_vector::INSERTSORT):
		insertSort(lo, hi); break;
	case (my_vector::SHELLSORT):
		shellSort(lo, hi); break;
	case (my_vector::QUICKSORT):
		quickSort(lo, hi); break;
	default:
		break;
	}
}

template <typename T>
void Vector<T>::unsort(Rank lo, Rank hi) {
	T* V = _elem + lo;
	for (int i = 0; i < hi - lo; i++)
		std::swap(V[i], V[std::rand() % (hi - lo)]);
}

template <typename T>
void Vector<T>::traverse(void (*visit)(T &e)) {
	for (int i = 0; i < _size; i++)
		visit(_elem[i]);
}

template <typename T> template <typename VST>
void Vector<T>::traverse(VST& visit) {
	for (int i = 0; i < _size; i++) 
		visit(_elem[i]);
}