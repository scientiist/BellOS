#include "keyset.h"
#include "../core/asm/asm.h"
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