#include "clipboard.h"


namespace NS_CLIPBOARD
{
	//=====================================================
	bool Clipboard::SetData(const std::string& str)
	{
		const char* data = str.c_str();
		size_t size = (str.length() + 1) * sizeof(char);
	  
		HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, size);
		if (hMem == NULL)
		{
			return false;
		}  

		char* pMem = static_cast<char*>(GlobalLock(hMem));
		if (!pMem)
		{
			GlobalFree(hMem);
			return false;
		}

		memcpy(pMem, data, size);
		GlobalUnlock(hMem);

		if (OpenClipboard(NULL))
		{
			EmptyClipboard();
			if (SetClipboardData(CF_TEXT, hMem) == NULL)
			{
				GlobalFree(hMem);
			}
			CloseClipboard();
			return true;
		}
		else
		{
			GlobalFree(hMem);
			return false;
		}
	}
	
	//=====================================================
}