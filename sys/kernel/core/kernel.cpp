// BellOS main - kernel startup thingy.

// some junk
#include <stddef.h>
#include <stdint.h>

#include "../video/videobuffer.h" // videobuffer class
#include "../../opt/terminal/terminal.h" // terminal program, run this after starting kernel stuff...

extern "C" {
    
    void kernel_main(void) {

        // build videobuffer
        VideoBuffer kernelVB;
        kernelVB.Initialize();
        kernelVB.SetBackgroundColor(VGAColor::BLACK);

        kernelVB.SetColor(VGAColor::WHITE);
        kernelVB.WriteString("> Started VideoBuffer");

        for (int i = 0; i < 256; i++) {

            kernelVB.PutChar(i);
            kernelVB.PutChar(' ');
        }

        // make terminal and run it
        Terminal t;
        t.Initialize();
        while(true) {
            t.Run();
        } 
    }
}