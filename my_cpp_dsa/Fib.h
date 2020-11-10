#pragma once

class Fib { //Fibonacci
private:
	int f, g; //f = fib(k - 1), g = fib(k)
	// would overflow soon
public:
	Fib(int n) 
	{
		f = 1; g = 0; while (g < n) next();
	} //fib(-1), fib(0)£¬O(log_phi(n))
	int get() { return g; } //O(1)
	int next() { g += f; f = g - f; return g; } //O(1)
	int prev() { f = g - f; g -= f; return g; } //O(1)
};