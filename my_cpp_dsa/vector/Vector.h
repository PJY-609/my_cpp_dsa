#pragma once

#include "fib/Fib.h"

#define DEFAULT_CAPACITY 3
typedef int Rank;

namespace my_vector {
	enum SortEnum {
		BUBBLESORT1, BUBBLESORT2, BUBBLESORT3, BUBBLESORT4,
		SELECTIONSORT,
		MERGESORT,
		INSERTSORT,
		SHELLSORT,
		QUICKSORT
	};

	enum PartitionEnum {
		LUG, LUG1,
		LGU,
		DUP, DUP1
	};
}


template <typename T> class Vector {
protected:
	Rank _size;
	T* _elem;
	int _capacity;

	void expand();
	void shrink();
	void copyFrom(T const* A, Rank lo, Rank hi);

	/* |    Sort Type   | Best Time | Avg Time | Worst Time |  Space  | Stability | */
	/* |   Bubble Sort  |   O(n)    |  O(n^2)  |   O(n^2)   |   O(1)  |   Stable  | */
	/* | Selection Sort |  O(n^2)   |  O(n^2)  |   O(n^2)   |   O(1)  |   Stable  | */
	/* |   Insert Sort  |   O(n)    |  O(n^2)  |   O(n^2)   |   O(1)  |   Stable  | */
	/* |   Merge Sort   |  O(nlogn) | O(nlogn) |  O(nlogn)  | O(logn) |   Stable  | */

	void bubbleSort1(Rank lo, Rank hi); // basic
	void bubbleSort2(Rank lo, Rank hi); // early stop
	void bubbleSort3(Rank lo, Rank hi); // jumping
	int bubble(Rank lo, Rank hi, bool inverse);
	void bubbleSort4(Rank lo, Rank hi); // for partly ordered vector

	Rank max(Rank lo, Rank hi);
	void selectionSort(Rank lo, Rank hi);

	void merge(Rank lo, Rank mi, Rank hi); // merge two ordered subset
	void mergeSort(Rank lo, Rank hi);

	void insertSort(Rank lo, Rank hi, int step);
	void insertSort(Rank lo, Rank hi) { insertSort(lo, hi, 1); }

	void shellSort(Rank lo, Rank hi);

	Rank partition1(Rank lo, Rank hi); // LUG
	Rank partition2(Rank lo, Rank hi); // LUG1, the equivalent of LUG
	Rank partition3(Rank lo, Rank hi); // DUP
	Rank partition4(Rank lo, Rank hi); // DUP1
	Rank partition5(Rank lo, Rank hi); // LGU
	Rank partition(Rank lo, Rank hi, my_vector::PartitionEnum partitionType);
	void quickSort(Rank lo, Rank hi, my_vector::PartitionEnum paritionType = my_vector::LGU); // iterative

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
	// bin search: O(1.50logn) vs fib search: O(1.44logn)


	// insert: O(n)
	Rank insert(T const &e, Rank r);
	Rank insert(T const &e) { return insert(e, _size); }

	//remove: O(n)
	T remove(Rank r);
	int remove(Rank lo, Rank hi);
	
	// deduplicate random vector
	// O(n^2), time most consumed by find() and remove()
	int deduplicate1();
	int deduplicate2(); // more efficient

	// uniquify ordered vector
	int uniquify1(); // O(n^2)
	int uniquify2(); // O(n), take advantage of the orderedness

	void sort(Rank lo, Rank hi, my_vector::SortEnum sortType);
	void sort(my_vector::SortEnum sortType) { sort(0, _size, sortType); }

	// randomize elements: O(n)
	void unsort(Rank lo, Rank hi);
	void unsort() { unsort(0, _size); }
	
	//traverse: O(n)
	void traverse(void (*visit)(T &e)); // function pointer
	template <typename VST> void traverse(VST &); // function object
};

namespace my_vector {

	// function object
	template <typename T> struct Increase {
		virtual void operator() (T &e) { e++; }
	};

	template <typename T> void increase(Vector<T> &V) {
		V.traverse(Increase<T>());
	}

	template <typename T> struct Decrease {
		virtual void operator() (T &e) { e--; }
	};

	template <typename T> void decrease(Vector<T> &V) {
		V.traverse(Decrease<T>());
	}
}
#include "Vector_Implementation.h"


