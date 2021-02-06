#pragma once
#include "../stack/stack.h"
#include <algorithm>

// Steap = Stack + Heap
template <typename T> class Steap {
private:
	Stack<T> _stack; // for pushed elems
	Stack<T> _heap; // for max elems

public:
	void push(T const& e) { 
		_stack.push(e); 	
		if (_heap.empty()) _heap.push(e);
		else _heap.push(std::max(_heap.top(), e)); 
	}

	T pop() { _heap.pop(); return _stack.pop(); }

	T& top() { return _stack.top(); }

	T getMax() { return _heap.top(); }

	bool empty() { return _stack.empty(); }
};
