#include <stddef.h>
#include <stdint.h>


// include kernel systems
#include "../video/videobuffer.h"
#include "asm/asm.h"
#include "../../opt/terminal/terminal.h"
#include "../../libraries/time/time.h"


extern "C" {
    
    void kernel_main(void) {
        VideoBuffer kernelVB;

        kernelVB.Initialize();
    
        /* Newline support is left as an exercise. */
        kernelVB.SetBackgroundColor(VGA_COLOR_WHITE);

        kernelVB.SetColor(VGA_COLOR_BLACK);
        kernelVB.WriteString("> BellOS educational operating system.\n");
        kernelVB.WriteString("> Revision 15 (May 7 2017)\n");
        kernelVB.WriteString("> Starting kernel...\n\n");

        for (int i = 0; i < 256; i++) {

            kernelVB.PutChar(i);
            kernelVB.PutChar(' ');
        }

        kernelVB.WriteString("\nHello, trent!");

        Terminal t;
        t.Initialize();
        

       while(true) {
      t.Run();
      }
        
    }
}