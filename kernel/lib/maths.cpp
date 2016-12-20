#include "maths.h"

double PI = 3.14159;



double Maths::Pow(int base, double exp) {
	double result = 1;
	while (exp) {
		if (exp & 1) {
			result *= base;
		}

		exp >>= 1;
		base *= base;
	}

	return result;
}

double Maths::Sqrt(double number) {
	return this->Pow(number, 0.5);
}

int Maths::Abs(int number) {
    int y = (number >> 31);
    return (number ^ y) - y;
}

double Maths::Round(double num, int decimalPlaces) {
	float y = 1/decimalPlaces;
	return int((num+(1/(y+y)))*y)/y;
}


char* Maths::ToString(int num, int base) {
	static char* result;

    if (base < 2 || base > 36) { *result = '\0'; return result; }

    char* ptr = result, *ptr1 = result, tmp_char;
    int tmp_value;

    do {
        tmp_value = value;
        value /= base;
        *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
    } while ( value );

    // Apply negative sign
    if (tmp_value < 0) *ptr++ = '-';
    *ptr-- = '\0';
    while (ptr1 < ptr) {
        tmp_char = *ptr;
        *ptr--= *ptr1;
        *ptr1++ = tmp_char;
    }
    return result;

	
}