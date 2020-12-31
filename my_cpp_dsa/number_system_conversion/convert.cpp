#include "..\number_system_conversion\convert.h"

void convert(Stack<char> &S, __int64 n, int base) { // 2 <= base <= 16
	char digit[] = "0123456789ABCDEF";
	while (n > 0) {
		S.push(digit[n % base]);
		n /= base;
	}
}