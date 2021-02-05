#include "rpn.h"
#include <ctype.h>

char* removeSpace(char* s) {
	char* p = s, *q = s;
	while (true) {
		while (isspace(*q)) q++;
		if ('\0' == *q) { *p = '\0'; return s; }
		*p++ = *q++;
	}
}

// caculate the resulte of expression S (space removed) and convert it to RPN
double evaluate(char *S, char *&RPN) {
	Stack<double> opnd; Stack<char> optr;

	optr.push('\0'); // trailer node

	while (!optr.empty()) {
		if (isdigit(*S)) {
			readNumber(S, opnd);
			//append(RPN, opnd.top());
		}
		switch (orderBetween(optr.top(), *S))
		{
		case '<': // if priority of stack top is lower, push to stack
			optr.push(*S); S++;
			break;
		case '=': // if stack top's priority is equivalent to current operator, pop
			optr.pop(); S++;
			break;
		case '>': {// if stack top's superior than current operator, pop and caculate
			char op = optr.pop();
			//append(RPN, op);
			if (op == '!')
				opnd.push(calcu(op, opnd.pop()));
			else {
				double opnd2 = opnd.pop(), opnd1 = opnd.pop();
				opnd.push(calcu(opnd1, op, opnd2));
			}
			break;
		}
		default:
			exit(-1);
		} // switch
	} // while
	return opnd.pop();
}

void readNumber(char *& p, Stack<double> &stk) {
	if (isdigit(*p)) stk.push((double)(*p - '0'));
	
	// if n >-10
	while (isdigit(*(++p))) {
		stk.push(stk.pop() * 10 + (*p - '0'));
	}

	if ('.' != *p) return;

	// if contains decimals
	float fraction = 1.;
	while (isdigit(*(++p))) {
		stk.push(stk.pop() + (*p - '0') * (fraction /= 10));
	}

}

Operator optr2rank(char op) {
	switch (op) {
	case '+': return ADD;
	case '-': return SUB;
	case '*': return MUL;
	case '/': return DIV;
	case '^': return POW;
	case '!': return FAC;
	case '(': return L_P;
	case ')': return R_P;
	case '\0': return EOE;
	default: exit(-1);
	}
}

char orderBetween(char op1, char op2)
{
	return pri[optr2rank(op1)][optr2rank(op2)];
}

double calcu(double a, char op, double b) {
	switch (op) {
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/': if (0 == b) exit(-1); return a / b;
	case '^': return pow(a, b);
	default: exit(-1);
	}
}

double calcu(char op, double b) {
	switch (op) {
	case '!': return (double)facI((int)b);
	default: exit(-1);
	}
}

__int64 facI(int n) { __int64 f = 1; while (n > 1) f *= n--; return f; }


//void append(char*& rpn, double opnd) {
//	char buf[64];
//	if (opnd - (int)opnd > 0.0)
//		sprintf(buf, "%f \0", opnd);
//	else
//		sprintf(buf, "%d \0", (int)opnd);
//	rpn = (char *) realloc(rpn, sizeof(char) * (strlen(rpn) + strlen(buf) + 1));
//	strcat(rpn, buf);
//}
//
//void append(char*& rpn, char optr) {
//	int n = strlen(rpn);
//	rpn = (char *)realloc(rpn, sizeof(char) * (n + 3));
//	sprintf(rpn + n, "%c ", optr);
//	rpn[n + 2] = '\0';
//}