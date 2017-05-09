#include <stddef.h>
#include <stdint.h>


// include kernel systems
#include "../video/videobuffer.h"
#include "asm/asm.h"
#include "../../opt/terminal/terminal.h"


extern "C" {
    
    void kernel_main(void) {
        VideoBuffer kernelVB;

        kernelVB.Initialize();
    
        /* Newline support is left as an exercise. */
        kernelVB.SetColor(VGA_COLOR_LIGHT_GREY);
        kernelVB.WriteString("> BellOS educational operating system.\n");
        kernelVB.WriteString("> Revision 15 (May 7 2017)\n");
        kernelVB.WriteString("> Starting kernel...\n\n");

        kernelVB.SetColor(VGA_COLOR_GREEN);
        for (int i = 0; i < 256; i++) {
            kernelVB.PutChar(i);
            kernelVB.PutChar(' ');
        }

        //Terminal t;
        //t.Initialize();
        //t.Run();


        
    }
}