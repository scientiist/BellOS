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

size_t VideoBuffer_row;
size_t VideoBuffer_ypos;
size_t VideoBuffer_column;
uint8_t VideoBuffer_color;
uint16_t* VideoBuffer_buffer;



void VideoBuffer::Initialize(void) {
	VideoBuffer_row = 0;
	VideoBuffer_ypos = 0;
	VideoBuffer_column = 0;
	VideoBuffer_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	VideoBuffer_buffer = (uint16_t*) 0xB8000;
	for (size_t y = 0; y < VGA_HEIGHT; y++) {
		for (size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_WIDTH + x;
			VideoBuffer_buffer[index] = vga_entry(' ', VideoBuffer_color);
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
            VideoBuffer_buffer[i * VGA_WIDTH + m] = VideoBuffer_buffer[(i + 1) * VGA_WIDTH + m];
        }
    }
}

void VideoBuffer::Clear(void) {
	VideoBuffer_row = 0;
	VideoBuffer_column = 0;
	VideoBuffer_ypos = 0;

	for (int i = 0; i<VGA_HEIGHT; i++) {
		for (int x = 0; x < VGA_HEIGHT; x++) {
			this->WriteString(" ");
		}
	}
	for (int i = 0; i<VGA_HEIGHT; i++) {
		VideoBuffer_buffer[i] = 0;
	}

	VideoBuffer_row = 0;
	VideoBuffer_column = 0;
	VideoBuffer_ypos = 0;
	this->SetCursor(0, 0);

}

 
void VideoBuffer::SetColor(uint8_t color) {
	VideoBuffer_color = color;
}
 
void VideoBuffer::PutEntryAt(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	VideoBuffer_buffer[index] = vga_entry(c, color);
}
 
void VideoBuffer::PutChar(char c) {
	if (c == '\n') {
		VideoBuffer_row++;
		VideoBuffer_column = 0;
		if (VideoBuffer_row >= VGA_HEIGHT) {
			this->Scroll();
			VideoBuffer_row--;
		}
	} else {

		this->PutEntryAt(c, VideoBuffer_color, VideoBuffer_column, VideoBuffer_row);
		if (++VideoBuffer_column == VGA_WIDTH) {
			VideoBuffer_column = 0;
			if (++VideoBuffer_row == VGA_HEIGHT)
				VideoBuffer_row = 0;
		}


	}
	this->SetCursor(VideoBuffer_row, VideoBuffer_column);
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