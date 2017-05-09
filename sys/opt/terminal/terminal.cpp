#include "terminal.h"
#include "../../kernel/video/videobuffer.h"
#include "../../kernel/video/vga_color.h"

#include "../../libraries/string/string.h"
#include "../../libraries/time/time.h"

void Terminal::Initialize() {
    this->termVB.Initialize();

    this->termVB.WriteString("Intializing Terminal...");
}

void Terminal::Run() {
    //for (int i = 0; i <80; i++) {
   //     this->termVB.PutEntryAt(' ', 48, i, 0);
  //  }
  //  this->termVB.MoveTo(0, 0);
   // this->termVB.SetColor(VGA_COLOR_BLACK);
    //this->termVB.SetBackgroundColor(VGA_COLOR_CYAN);
   // this->termVB.WriteString("[] Terminal - BellOS command line\n");
     
       String nigga(2);
        this->termVB.WriteString(nigga);
        this->termVB.WriteString("lol ok");
    
   // this->termVB.SetColor(VGA_COLOR_LIGHT_GREY);
   // this->termVB.SetBackgroundColor(VGA_COLOR_BLACK);
}


void Terminal::Prompt() {
    
}