#pragma once


#define DEFAULT_CAPACITY 3
typedef int Rank;

template <typename T> class Vector {
protected:
	Rank _size;
	T* _elem;
	int _capacity;

	void expand();
	void shrink();
	void copyFrom(T const* A, Rank lo, Rank hi);

public:
	Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0)
	{
		_elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v);
	}
	Vector(T const* A, Rank n) { copyFrom(A, 0, n); }
	Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); }
	Vector(Vector<T> const& V, Rank n) { copyFrom(V._elem, 0, n); }
	Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); }

	~Vector() { delete[] _elem; }

	//read only
	Rank size() const { return _size; }
	int capacity() const { return _capacity; }
	bool empty() const { return !_size; }


	
};

#include "Vector_Implementation.h"


