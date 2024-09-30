#ifndef CLIPBOARD_H
#define CLIPBOARD_H
//#############################################################################


#include <windows.h>
#include <string>

namespace NS_CLIPBOARD
{
	//===================================================
	class Clipboard
	{
		public:
		bool SetData(const std::string& str);		
	};	
	//===================================================
}


//#############################################################################
#endif
