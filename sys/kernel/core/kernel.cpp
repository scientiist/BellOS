#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif

#include <stddef.h>
#include <stdint.h>


// include kernel systems
#include "../video/videobuffer.h"
#include "asm/asm.h"

/* Check if the compiler thinks we are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This will only work for the 32-bit ix86 targets. */
#if !defined(__i386__)
#error "This needs to be compiled with a ix86-elf compiler"
#endif

extern "C" {
    // initialize the terminal
    VideoBuffer kernelVB;
    /*
    int counter = 0;
    char command[64];

    void clearCommandBuffer() {
        for (int i = 0; i < 64; i++) {
            command[i] = 0;
        }
    }

    char last = 0;
    bool upperCase = false;

    char getScancode() {
        
        char c=inb(0x60);
        if(c!=0) {
            
            if (c!= last) {
                last = c;
                if (c>0) {
                    if (keyset[c] == '\n') {
                        //term.WriteString("(Enter Pressed)");
                    } else if (keyset[c] == '\b') {
                        if (counter > 0) {
                            counter--;
                            command[counter] = 0;
                            term.terminal_column--;
                            term.PutChar(0);
                            term.terminal_column--;
                            update_cursor(term.terminal_row, term.terminal_column);
                        }
                    } else if (keyset[c] == 127) { // caps lock
                        upperCase = !upperCase;
                    } else {
                        if (upperCase == true) {
                            term.PutChar(strLib.Upper(keyset[c]));
                        } else {
                            term.PutChar(keyset[c]);
                        }
                        command[counter] = keyset[c];
                        counter++;
                        update_cursor(term.terminal_row, term.terminal_column);
                    }
                    return keyset[c];
                }
            }
        }
    }
    */
    /*
    void prompt() {
        clearCommandBuffer();
        term.PutChar('>');
        update_cursor(term.terminal_row, term.terminal_column);
        
        char input=0;
        counter = 0;
        while (input != '\n'){
            input = getScancode();
        }
        term.PutChar('\n');
    }

    */
    void kernel_main(void) {

        kernelVB.Initialize();
    
        /* Newline support is left as an exercise. */
        kernelVB.WriteString("> BellOS educational operating system.\n");
        kernelVB.WriteString("> Revision 15 (May 7 2017)\n");
        kernelVB.WriteString("> Starting kernel...\n");
        
        String bruh("ayy lmao");

        kernelVB.WriteString(bruh);
    }
}