#ifndef __TERMINAL_INCLUDED__
#define __TERMINAL_INCLUDED__

#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>

class Terminal {
	public:
		size_t terminal_row;
		size_t terminal_ypos;
		size_t terminal_column;
		uint8_t terminal_color;
		uint16_t* terminal_buffer;
		void Initialize(void);
		void Scroll(void);
		void SetColor(uint8_t color);
		void PutEntryAt(char c, uint8_t color, size_t x, size_t y);
		void PutChar(char c);
		void Write(const char* data, size_t size);
		void WriteString(const char* data);
		void Clear();

};

#endif