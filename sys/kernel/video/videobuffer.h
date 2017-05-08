#ifndef __TERMINAL_INCLUDED__
#define __TERMINAL_INCLUDED__

#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>

#include "../../libraries/string/string.h"

class VideoBuffer {
	public:
		size_t VideoBuffer_row;
		size_t VideoBuffer_ypos;
		size_t VideoBuffer_column;
		uint8_t VideoBuffer_color;
		uint16_t* VideoBuffer_buffer;
		void Initialize(void);
		void Scroll(void);
		void SetCursor(int row, int col);
		void SetColor(uint8_t color);
		void PutEntryAt(char c, uint8_t color, size_t x, size_t y);
		void PutChar(char c);
		void Write(const char* data, size_t size);
		void WriteString(const char* data);
		void WriteString(String c);
		void Clear();

};

#endif