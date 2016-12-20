/*
	The BellOS Math Class. Maths stuff Idk.

	Written by J. O'Leary, last modified 17 December, 2016.
	MIT license, refer to <LICENSE.txt> for full info.

*/

#ifndef __MATHLIB_INCLUDED__
#define __MATHLIB_INCLUDED__

#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>

class Maths {
	public:
		double pi;
		double Pow(int base, double exp);
		double Sqrt(double number);
		int Abs(int number);
		double Round(double num, int decimalPlaces);
		char* ToString(int num, int base);
		//int Maths::Random(int min, int max);
		//double Maths::Random();
};

#endif
