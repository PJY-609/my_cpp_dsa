#include <iostream> 
#include "..\parenthesis_matching\parenthesis.h"
#include "..\stack\stack.h"

typedef std::pair<char, char> bracket;

const bracket parentheses = bracket('(', ')');
const bracket curly_brackets = bracket('{', '}');
const bracket chevron_brackets = bracket('<', '>');
const bracket square_brackets = bracket('[', ']');

bool match_parenthesis(const char exp[], int lo, int hi) {
	Stack<char> S;
	for (int i = lo; i < hi; i++) {
		if (exp[i] == parentheses.first ||
			exp[i] == curly_brackets.first ||
			exp[i] == chevron_brackets.first ||
			exp[i] == square_brackets.first)
			S.push(exp[i]);
		
		if (exp[i] == parentheses.second)
			if (S.empty() || parentheses.first != S.pop())
				return false;
		if (exp[i] == curly_brackets.second)
			if (S.empty() || curly_brackets.first != S.pop())
				return false;
		if (exp[i] == chevron_brackets.second)
			if (S.empty() || chevron_brackets.first != S.pop())
				return false;
		if (exp[i] == square_brackets.second)
			if (S.empty() || square_brackets.first != S.pop())
				return false;

	}
	return S.empty();
}