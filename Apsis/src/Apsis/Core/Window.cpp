#include "apch.h"
#include "Window.h"

#include "Windows/WindowsWindow.h"
#include "OpenGL/OpenGLWindow.h"

namespace A {

	Unique<Window> Window::Create(MainFnArgs args, const std::string& name/* = "Window"*/, unsigned int width/* = 1280*/, unsigned int height/* = 720*/)
	{
		AP_PROFILE_FN();
		/*
		#ifdef AP_PLATFORM_WIN
			HINSTANCE hInstance = args.hInstance;
			HINSTANCE hPrevInstance = args.hPrevInstance;
			LPWSTR pCmdLine = args.pCmdLine;
			int nShowCmd = args.nShowCmd;
			return MakeUnique<WindowsWindow>(hInstance, hPrevInstance, pCmdLine, nShowCmd, name, width, height);
		#endif // AP_PLATFORM_WIN
		*/

		return MakeUnique<OpenGLWindow>(width, height, name);

		AP_ASSERT_C(false, "Unknown Platform");
		return nullptr;
	}

}