/*
	The BellOS Timing Class. Clocks, halting, etc.

	Written by J. O'Leary, last modified 7 May, 2017.
	MIT license, refer to <LICENSE.txt> for full info.

*/

#ifndef __TIMELIB_INCLUDED__
#define __TIMELIB_INCLUDED__

#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>

class Time {
	public:
		void GetUnixTime();
		void Sleep(unsigned int milliseconds);
};

#endif
