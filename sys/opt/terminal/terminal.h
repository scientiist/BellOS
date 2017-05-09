#ifndef __TERMINAL_INCLUDED__
#define __TERMINAL_INCLUDED__
#include "../../kernel/video/videobuffer.h"

class Terminal {
		VideoBuffer termVB;
	public:
		void Initialize();
		void Run();
		void Prompt();
};

#endif