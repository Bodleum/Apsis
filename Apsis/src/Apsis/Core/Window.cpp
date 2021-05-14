#include "apch.h"
#include "Window.h"
#include "Apsis/Core/SystemInfo.h"
#include "OpenGL/OpenGLWindow.h"

#if defined(AP_PLATFORM_WIN)
	#include "Windows/WindowsWindow.h"
#endif // defined(AP_PLATFORM_WIN)


namespace A {

	Unique<Window> Window::Create(MainFnArgs args, const char* name/* = "Window"*/, unsigned int width/* = 1280*/, unsigned int height/* = 720*/)
	{
		AP_PROFILE_FN();

		switch (SystemInfo::RendererAPI)
		{
			#if defined(AP_PLATFORM_WIN)
			case RendererAPI::Direct2D:
			{
				HINSTANCE hInstance = args.hInstance;
				HINSTANCE hPrevInstance = args.hPrevInstance;
				LPWSTR pCmdLine = args.pCmdLine;
				int nShowCmd = args.nShowCmd;
				return MakeUnique<WindowsWindow>(hInstance, hPrevInstance, pCmdLine, nShowCmd, name, width, height);
			}
			#endif // defined(AP_PLATFORM_WIN)
			case RendererAPI::OpenGL:	return MakeUnique<OpenGLWindow>(width, height, name);
			default:					break;
		}

		AP_ASSERT_C(false, "Unknown renderer API");
		return nullptr;
	}

}