#include "terminal.h"
#include "../vga_color.h"



static inline uint8_t vga_entry_color(enum vga_color fg, enum vga_color bg) {
	return fg | bg << 4;
}
 
static inline uint16_t vga_entry(unsigned char uc, uint8_t color) {
	return (uint16_t) uc | (uint16_t) color << 8;
}
 
size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}
 
static const size_t VGA_WIDTH = 80;
static const size_t VGA_HEIGHT = 25;

size_t terminal_row;
size_t terminal_ypos;
size_t terminal_column;
uint8_t terminal_color;
uint16_t* terminal_buffer;



void Terminal::Initialize(void) {
	terminal_row = 0;
	terminal_ypos = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}

void Terminal::Scroll(void){
    for(int i = 0; i < VGA_HEIGHT; i++){
        for (int m = 0; m < VGA_WIDTH; m++){
            terminal_buffer[i * VGA_WIDTH + m] = terminal_buffer[(i + 1) * VGA_WIDTH + m];
        }
    }
}

void Terminal::Clear(void) {
	terminal_row = 0;
	terminal_column = 0;
	terminal_ypos = 0;

	for (int i = 0; i<VGA_HEIGHT; i++) {
		for (int x = 0; x < VGA_HEIGHT; x++) {
			this->WriteString(" ");
		}
	}
	for (int i = 0; i<VGA_HEIGHT; i++) {
		terminal_buffer[i] = 0;
	}

	terminal_row = 0;
	terminal_column = 0;
	terminal_ypos = 0;

}

 
void Terminal::SetColor(uint8_t color) {
	terminal_color = color;
}
 
void Terminal::PutEntryAt(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}
 
void Terminal::PutChar(char c) {
	if (c == '\n') {
		terminal_row++;
		terminal_column = 0;
		if (terminal_row >= VGA_HEIGHT) {
			this->Scroll();
			terminal_row--;
		}
	} else {

		this->PutEntryAt(c, terminal_color, terminal_column, terminal_row);
		if (++terminal_column == VGA_WIDTH) {
			terminal_column = 0;
			if (++terminal_row == VGA_HEIGHT)
				terminal_row = 0;
		}


	}
}
 
void Terminal::Write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		this->PutChar(data[i]);
}

void Terminal::WriteString(const char* data) {
	this->Write(data, strlen(data));

}
