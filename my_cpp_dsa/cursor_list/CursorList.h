#pragma once
#include <assert.h>

typedef int Rank;
#define DEFAULT_CAPACITY 3

template <typename T> class CursorList {
protected:
	Rank _size; int _capacity;
	Rank *_link; T *_elem;
	Rank _data, _free;

public:
	CursorList(int c = DEFAULT_CAPACITY) {
		_link = new Rank[_capacity = c];
		for (int i = 0; i < c - 1; i++) _link[i] = i + 1;
		_link[c - 1] = -1;

		_elem = new T[_capacity = c]; memset(_elem, 0, c * sizeof(T));
		_data = -1; _size = 0;
		_free = 0;
	}

	~CursorList() { delete[] _link; delete[] _elem; }

	Rank size() { return _size; }
	bool empty() { return !_size; }

	Rank find(T const &e) {
		Rank i = _data;
		while ((i >= 0) && (e != _elem[i])) i = _link[i];
		return i;
	}

	Rank insert(T const &e) {
		assert(_free >= 0);
		Rank k = _free;
		_elem[k] = e; _free = _link[k];
		_link[k] = _data; _data = k;
		_size++;
		return k;
	}

	Rank remove(Rank k) {
		assert(k >= 0);
		if (k == _data) { // k is first node
			_data = _link[k];
		}
		else {
			Rank i = _data;
			while (k != _link[i]) i = _link[i]; // find k == _link[i]
			_link[i] = _link[k];
		}
		_link[k] = _free; _free = k; _elem[k] = 0;
		_size--;
		return k;
	}
};