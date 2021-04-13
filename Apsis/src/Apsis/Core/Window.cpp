#include "apch.h"
#include "Window.h"

#include "Windows/WindowsWindow.h"

namespace A {

	Unique<Window> Window::Create(WindowArgs args)
	{
		#ifdef AP_PLATFORM_WIN
			HINSTANCE hInstance = args.hInstance;
			HINSTANCE hPrevInstance = args.hPrevInstance;
			LPWSTR pCmdLine = args.pCmdLine;
			int nShowCmd = args.nShowCmd;
			return MakeUnique<WindowsWindow>(hInstance, hPrevInstance, pCmdLine, nShowCmd);
		#endif // AP_PLATFORM_WIN

		AP_ASSERT_C(false, "Unknown Platform");
		return nullptr;
	}

}