#ifndef __KEYBOARD_INCLUDED__
#define __KEYBOARD_INCLUDED__

#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>


class Keyboard {
	public:
		unsigned char keyset[128];

};

#endif