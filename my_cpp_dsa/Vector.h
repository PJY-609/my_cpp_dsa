#pragma once

#include "Fib.h"

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

	// read only accessor
	Rank size() const { return _size; }
	int capacity() const { return _capacity; }
	bool empty() const { return !_size; }

	// operator
	T& operator[] (Rank r);
	const T& operator[] (Rank r) const;
	Vector<T>& operator= (Vector<T> const &);

	// find elem in random vector
	// linear find: O(n)
	Rank find(T const &e, Rank lo, Rank hi) const;
	Rank find(T const &e) const { return find(e, 0, _size); }

	// search elem in ordered vector
	// binary search: O(logn)
	Rank binSearch1(T const &e, Rank lo, Rank hi) const;
	Rank binSearch1(T const &e) const 
	{ return (0 >= _size) ? -1 : binSearch1(e, 0, _size); }
	Rank binSearch2(T const &e, Rank lo, Rank hi) const;
	Rank binSearch2(T const &e) const 
	{ return (0 >= _size) ? -1 : binSearch2(e, 0, _size); }
	Rank binSearch3(T const &e, Rank lo, Rank hi) const;
	Rank binSearch3(T const &e) const
	{ return (0 >= _size) ? -1 : binSearch3(e, 0, _size); }
	// fib search: O(logn)
	// https://stackoverflow.com/questions/4247111/is-golden-section-search-better-than-binary-search
	// https://stackoverflow.com/questions/22877763/is-fibonacci-search-faster-than-binary-search
	Rank fibSearch1(T const &e, Rank lo, Rank hi) const;
	Rank fibSearch1(T const &e) const 
	{ return (0 >= _size) ? -1 : fibSearch1(e, 0, _size); }
	Rank fibSearch2(T const &e, Rank lo, Rank hi) const;
	Rank fibSearch2(T const &e) const
	{ return (0 >= _size) ? -1 : fibSearch2(e, 0, _size); }

	Rank insert(T const &e, Rank r);
	Rank insert(T const &e) { return insert(e, _size); }

	T remove(Rank r);
	int remove(Rank lo, Rank hi);
	
	// deduplicate random vector
	int deduplicate1();
	int deduplicate2(); // more efficient
	
};

#include "Vector_Implementation.h"


