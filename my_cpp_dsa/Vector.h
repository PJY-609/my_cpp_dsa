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

	T& operator[] (Rank r);
	const T& operator[] (Rank r) const;
	Vector<T>& operator= (Vector<T> const &);

	// find elem in random vector
	Rank find(T const &e, Rank lo, Rank hi) const;
	Rank find(T const &e) const { return find(e, 0, _size); }

	//search elem in ordered vector
	Rank binSearch1(T const &e, Rank lo, Rank hi) const;
	Rank binSearch1(T const &e) const 
	{ return (0 >= _size) ? -1 : binSearch1(e, 0, _size); }
	Rank binSearch2(T const &e, Rank lo, Rank hi) const;
	Rank binSearch2(T const &e) const 
	{ return (0 >= _size) ? -1 : binSearch2(e, 0, _size); }
	Rank binSearch3(T const &e, Rank lo, Rank hi) const;
	Rank binSearch3(T const &e) const
	{ return (0 >= _size) ? -1 : binSearch3(e, 0, _size); }


	
};

#include "Vector_Implementation.h"


