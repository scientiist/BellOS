/*
	The BellOS String object

	Written by J. O'Leary, last modified 16 December, 2016.
	MIT license, refer to <LICENSE.txt> for full info.
*/

#ifndef __STRINGLIB_INCLUDED__
#define __STRINGLIB_INCLUDED__

#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>

class String {
		const char* str = NULL;
	public:
		String();
		String(char c);
		String(const char* str);
		String(String& s);
		String(int s);
		String(bool b);
		int getLength();
		bool equals(const char* str);
		bool equals(String& compare);
		const char* toCharArray();
		String toLowerCase();
		String toUpperCase();
		char operator[] (int j);
		bool operator== (const char* str);
		bool operator== (String& lhs);
		String& operator+= (String& s);
};

#endif
