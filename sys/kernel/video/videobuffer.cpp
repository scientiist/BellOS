#include "videobuffer.h"
#include "vga_color.h"
#include "../core/asm/asm.h"
#include "../../libraries/string/string.h"

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





void VideoBuffer::Initialize(void) {
	this->row = 0;
	this->ypos = 0;
	this->column = 0;
	this->textColor = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	this->buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			this->buffer[index] = vga_entry(' ', this->textColor);
		}
	}
}

void VideoBuffer::SetCursor(int row, int col) {
    unsigned short position=(row*80) + col;
    
    // cursor LOW port to vga INDEX register
    outb(0x3D4, 0x0F);
    outb(0x3D5, (unsigned char)(position&0xFF));
    // cursor HIGH port to vga INDEX register
    outb(0x3D4, 0x0E);
    outb(0x3D5, (unsigned char )((position>>8)&0xFF));
}

void VideoBuffer::Scroll(void){
    for(int i = 0; i < VGA_HEIGHT; i++){
        for (int m = 0; m < VGA_WIDTH; m++){
            this->buffer[i * VGA_WIDTH + m] = this->buffer[(i + 1) * VGA_WIDTH + m];
        }
    }
}

void VideoBuffer::MoveTo(size_t x, size_t y) {
	this->row = x;
	this->column = y;
}

void VideoBuffer::Clear(void) {
	this->row = 0;
	this->column = 0;
	this->ypos = 0;

	for (int i = 0; i<VGA_HEIGHT; i++) {
		for (int x = 0; x < VGA_HEIGHT; x++) {
			this->WriteString(" ");
		}
	}
	for (int i = 0; i<VGA_HEIGHT; i++) {
		this->buffer[i] = 0;
	}

	this->row = 0;
	this->column = 0;
	this->ypos = 0;
	this->SetCursor(0, 0);

}

 
void VideoBuffer::SetColor(enum vga_color color) {
	this->fgColor = color;
}

void VideoBuffer::SetBackgroundColor(enum vga_color bgcolor) {
	this->bgColor = bgcolor;
}
 
void VideoBuffer::PutEntryAt(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	this->buffer[index] = vga_entry(c, color);
}
 
void VideoBuffer::PutChar(char c) {
	if (c == '\n') {
		this->row++;
		this->column = 0;
		if (this->row >= VGA_HEIGHT) {
			this->Scroll();
			this->row--;
		}
	} else {

		this->PutEntryAt(c, vga_entry_color(this->fgColor, this->bgColor), this->column, this->row);
		if (++this->column == VGA_WIDTH) {
			this->column = 0;
			if (++this->row == VGA_HEIGHT)
				this->row = 0;
		}


	}
	this->SetCursor(this->row, this->column);
}
 
void VideoBuffer::Write(const char* data, size_t size) {
	for (size_t i = 0; i < size; i++)
		this->PutChar(data[i]);
}

void VideoBuffer::WriteString(const char* data) {
	this->Write(data, strlen(data));

}

void VideoBuffer::WriteString(String str) {
	this->WriteString(str.toCharArray());
}