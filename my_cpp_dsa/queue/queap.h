#pragma once

#include "../stack/steap.h"

// Queap = Queue + Heap = 2 Steaps

template <typename T> class Queap {
private:
	Steap<T> _s1;
	Steap<T> _s2;
public:
	void push(T const &e) { _s1.push(e); }

	T pop() {
		if (_s2.empty()) {
			while (!_s1.empty()) _s2.push(_s1.pop());
		}
		return _s2.pop();
	}

	T getMax() {
		if (_s1.empty() && !_s2.empty())
			return _s2.getMax();
		else if (!_s1.empty() && _s2.empty())
			return _s1.getMax();
		else
			return std::max(_s1.getMax(), _s2.getMax());
	}

	T& front() {
		if (_s2.empty()) {
			while (!_s1.empty()) _s2.push(_s1.pop());
		}
		return _s2.top();
	}
};