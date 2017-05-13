#include "terminal.h"
#include "../../kernel/video/videobuffer.h"
#include "../../kernel/video/vga_color.h"
#include "../../kernel/keyboard/input.h"

#include "../../libraries/string/string.h"
#include "../../libraries/time/time.h"

void Terminal::Initialize() {
    this->termVB.Initialize();

    for (int i = 0; i <80; i++) {
        this->termVB.PutEntryAt(' ', 48, i, 0);
    }
  this->termVB.MoveTo(0, 0);
   this->termVB.SetColor(VGA_COLOR_BLACK);
    this->termVB.SetBackgroundColor(VGA_COLOR_CYAN);
   this->termVB.WriteString("[] Terminal - BellOS command line ");
   this->termVB.PutChar(186);

   this->termVB.WriteString(" Rev. 13-May-2017\n");
   this->termVB.SetColor(VGA_COLOR_LIGHT_GREY);
    this->termVB.SetBackgroundColor(VGA_COLOR_BLACK);
}

String Terminal::GetInput() {

    char inp = 0;
    int placeCounter = 0;
    char nigga[30];
    while(inp != '\n') {
        
        inp = getScancode();


        if (inp == '\b') {
            if (placeCounter > 0) {
                this->termVB.column--;
                this->termVB.PutChar(' ');
                this->termVB.column--;
                this->termVB.SetCursor(this->termVB.row, this->termVB.column);
                placeCounter--;
            }
       /* } else if (inp == '\L') {
            if (placeCounter > 0) {
                 placeCounter--;
                this->termVB.column--;
                this->termVB.SetCursor(this->termVB.row, this->termVB.column);
            }
        } else if (inp == '\R') {
                placeCounter++;
                this->termVB.column++;
                this->termVB.SetCursor(this->termVB.row, this->termVB.column);
        */} else if (inp != 0 && inp != '\n') {
            nigga[placeCounter] = inp;
            placeCounter++;
            this->termVB.PutChar(inp);
        }
    }
    nigga[placeCounter] = '\0';
    this->termVB.PutChar('\n');
    String ret(nigga);
    return ret;
    
}


bool Terminal::Run() {
    this->termVB.SetColor(VGA_COLOR_CYAN);
    this->termVB.WriteString("terminal@bellOS $ ");
    this->termVB.SetColor(VGA_COLOR_LIGHT_GREY);
 
    this->lastInp = this->GetInput();

    if (this->lastInp == "dumpchars") {
        this->termVB.SetColor(VGA_COLOR_LIGHT_BROWN);
            for (int i = 0; i < 256; i++) {
                
                if (i == 10) {
                this->termVB.PutChar('N');
                 this->termVB.PutChar(' ');
                } else {
                    this->termVB.PutChar(i);
                    this->termVB.PutChar(' ');
                }
                
        }
        this->termVB.PutChar('\n');
        return true;
    } else if (this->lastInp == "clear") {
        for (int i = 1; i < 24; i++) {
            for (int y = 0; y < 80; y++) {
                this->termVB.MoveTo(i, y);
                this->termVB.PutChar(' ');
                this->termVB.MoveTo(1, 0);
            }
        }
        return true;
    } else if (this->lastInp == "commands") {
        this->termVB.WriteString("[] Command List:\n");
        this->termVB.SetColor(VGA_COLOR_LIGHT_RED);
        this->termVB.WriteString("clear dumpchars commands kill\n");
    }

    if (this->termVB.row >= 24) {
        for (int i = 1; i < 24; i++) {
            for (int y = 0; y < 80; y++) {
                this->termVB.MoveTo(i, y);
                this->termVB.PutChar(' ');
                this->termVB.MoveTo(1, 0);
            }
        }
    }
    return false;
}