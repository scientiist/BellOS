#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif
#include <stddef.h>
#include <stdint.h>
#include "terminal.h"
#include "keyboard.h"




/* Check if the compiler thinks we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This needs to be compiled with a ix86-elf compiler"
#endif

unsigned char keyset[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', /* 9 */
  '9', '0', '-', '=', '\b', /* Backspace */
  '\t',         /* Tab */
  'q', 'w', 'e', 'r',   /* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', /* Enter key */
    0,          /* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', /* 39 */
 '\'', '`',   0,        /* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',            /* 49 */
  'm', ',', '.', '/',   0,              /* Right shift */
  '*',
    0,  /* Alt */
  ' ',  /* Space bar */
    0,  /* Caps lock */
    0,  /* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,  /* < ... F10 */
    0,  /* 69 - Num lock*/
    0,  /* Scroll Lock */
    0,  /* Home key */
    0,  /* Up Arrow */
    0,  /* Page Up */
  '-',
    0,  /* Left Arrow */
    0,
    0,  /* Right Arrow */
  '+',
    0,  /* 79 - End key*/
    0,  /* Down Arrow */
    0,  /* Page Down */
    0,  /* Insert Key */
    0,  /* Delete Key */
    0,   0,   0,
    0,  /* F11 Key */
    0,  /* F12 Key */
    0,  /* All other keys are undefined */
};

bool isEqual(char string1[], char string2[]) {

    for(int i = 0; i < 64; i++) {
        if(string1[i] != string2[i]) {
            return false;
        }
    }
    return true;
}




#if defined(__cplusplus)
extern "C" { /* Use C linkage for kernel_main. */
#endif

static inline void outb(uint16_t port, uint8_t val) {
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}



// initialize the terminal
Terminal term;

int counter = 0;
char command[64];

void clearCommandBuffer() {
    for (int i = 0; i < 64; i++) {
        command[i] = 0;
    }
}


char last = 0;

char getScancode() {
	
    char c=inb(0x60);
	if(c!=0) {
		
        if (c!= last) {
            last = c;
            if (c>0) {
                if (keyset[c] == '\n') {
                    //term.WriteString("(Enter Pressed)");
                } else {
                    term.PutChar(keyset[c]);
                    command[counter] = keyset[c];
                    counter++;
                }
                return keyset[c];
            }
		}
	}
}

char *prompt() {
    clearCommandBuffer();
	term.PutChar('>');
	
	char input=0;
    counter = 0;
	while (input != '\n'){
        input = getScancode();
    }
    term.PutChar('\n');

}

void kernel_main(void) {
	/* Initialize terminal interface */
	

	term.Initialize();
 
	/* Newline support is left as an exercise. */
	term.WriteString("|Starting BellOS (0.12)...\n");
	term.WriteString("|Initializing keyboard...\n");
	term.WriteString("|Ready!\n");

    

    while(true) {
        prompt();

        char ass[64] = "faggot";
        if (isEqual(command, ass) == true) {
            term.WriteString("I got broads in atlanta.\n");
        } else if (command[0] == 0) {
            continue;
        } else {
            term.WriteString("error: command \"");
            term.WriteString(command);
            term.WriteString("\" not found...\n");
        }
    }

}}