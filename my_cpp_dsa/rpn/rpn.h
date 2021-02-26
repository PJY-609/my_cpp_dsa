#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include "../stack/stack.h"
#include <stdlib.h>
#include <cstring>
#include <string.h>
#include <cmath>
#include <stdio.h>


#define N_OPTR 9
typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE } Operator;
//addition, subtraction, multipilcation, division, power, factorization, left parenthesis, right parenthesis, end

const char pri[N_OPTR][N_OPTR] = { //[stack top] [current]
	/*              |--------------------------------------------------------| */
	/*              +      -      *      /      ^      !      (      )      \0 */
	/* --  + */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
	/* |   - */    '>',   '>',   '<',   '<',   '<',   '<',   '<',   '>',   '>',
	/* |   * */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
	/* |   / */    '>',   '>',   '>',   '>',   '<',   '<',   '<',   '>',   '>',
	/* |   ^ */    '>',   '>',   '>',   '>',   '>',   '<',   '<',   '>',   '>',
	/* |   ! */    '>',   '>',   '>',   '>',   '>',   '>',   ' ',   '>',   '>',
	/* |   ( */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   '=',   ' ',
	/* |   ) */    ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',   ' ',
	/* -- \0 */    '<',   '<',   '<',   '<',   '<',   '<',   '<',   ' ',   '='
};


char* removeSpace(char* s);

double evaluate(char *S, char *&RPN);

void readNumber(char *& p, Stack<double> &stk);

Operator optr2rank(char op);
char orderBetween(char op1, char op2);

__int64 facI(int n);
double calcu(double a, char op, double b);
double calcu(char op, double b);

// these two fns do not work for certain reasons, therefore rpn conversion is not yet available
//void append(char*&rpn, double opnd);
//void append(char*&rpn, char optr);