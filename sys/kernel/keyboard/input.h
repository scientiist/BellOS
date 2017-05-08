#include "keyset.h"
#include "../core/asm/asm.h"


char getScancode() {
        
    char c=inb(0x60);
    if(c!=0) {
        if (c!= last) {
            last = c;
            if (c>0) {
                return keyset[c];
            }
        }
    }
}