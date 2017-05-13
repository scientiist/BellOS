#ifndef __VIDEOBUFFER_INCLUDED__
#define __VIDEOBUFFER_INCLUDED__

#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>

#include "vga_color.h"
#include "../../libraries/string/string.h"

class VideoBuffer {
		enum vga_color fgColor = VGA_COLOR_LIGHT_GREY;
		enum vga_color bgColor = VGA_COLOR_BLACK;
		uint8_t textColor;
		uint16_t* buffer;
	public:
		size_t row;
		size_t ypos;
		size_t column;
		void Initialize(void);
		void Scroll(void);
		void SetCursor(int row, int col);
		void SetColor(vga_color color);
		void SetBackgroundColor(vga_color color);
		void MoveTo(size_t x, size_t y);
		void PutEntryAt(char c, uint8_t color, size_t x, size_t y);
		void PutChar(char c);
		void Write(const char* data, size_t size);
		void WriteString(const char* data);
		void WriteString(String c);
		void Clear();

};

#endif