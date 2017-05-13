#include "keyset.h"
#include "../core/asm/asm.h"
#include "../../libraries/string/string.h"

char last = 0;

char getScancode() {
        
    char c = inb(0x60);

    if(c!=0) {
        if (c != last) {
            last = c;
            if (c & 0x80) {
    
            } else {
                return keyset[c];
            }
        }
    }
    return 0;
}

