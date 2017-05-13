#ifndef __TERMINAL_INCLUDED__
#define __TERMINAL_INCLUDED__
#include "../../kernel/video/videobuffer.h"

class Terminal {
		VideoBuffer termVB;
		String lastInp;
	public:
		void Initialize();
		bool Run();
		void Prompt();
		String GetInput();
};

#endif