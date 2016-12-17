/*
	The BellOS String Class. This class contains methods for manipulating and
	modifying 'strings' (character arrays).

	Written by J. O'Leary, last modified 16 December, 2016.
	MIT license, refer to <LICENSE.txt> for full info.

	API Functions:

		+ size_t GetLength(const char* string)
			- summary
				+ Returns the length (in characters) of the provided string.
			- arguments
				+ const char* string: 
			- returns:
				+ size_t: represent number of characters in the given string
		______________________________________________________________________

		+ int GetChar(const char* string, char findme)
			- summary
				+ Returns the length (in characters) of the provided string.
			- arguments
				+ const char* string: 
			- returns:
				+ size_t: represent number of characters in the given string
		______________________________________________________________________

		+ bool GetEquals(const char* string)
			- summary
				+ Returns the length (in characters) of the provided string.
			- arguments
				+ const char* string: 
			- returns:
				+ size_t: represent number of characters in the given string
		______________________________________________________________________

		+ char* Append(const char* string)
			- summary
				+ Returns the length (in characters) of the provided string.
			- arguments
				+ const char* string: 
			- returns:
				+ size_t: represent number of characters in the given string
		______________________________________________________________________

		+ char* Upper(const char* string)
			-summary
				+ Returns the length (in characters) of the provided string.
			-arguments
				+ const char* string: 
			-returns:
				+ size_t: represent number of characters in the given string


*/

#ifndef __STRINGLIB_INCLUDED__
#define __STRINGLIB_INCLUDED__

#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>

class String {
	public:
		size_t GetLength(const char* string);
		int GetChar(const char* string, char findme);
		bool GetEquals(const char* string1, const char* string2);
		char* Append(const char* string1, const char* string2);
		char Upper(char c);
		char Lower(char c);
		char* Upper(const char* string);
		char* Lower(const char* string);
};

#endif
