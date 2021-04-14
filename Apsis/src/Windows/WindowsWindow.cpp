#include "apch.h"
#include "WindowsWindow.h"

namespace A {

	WindowsWindow::WindowsWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pCmdLine, int nShowCmd, const std::string& name, unsigned int width, unsigned int height)
		: m_Width(width), m_Height(height)
	{
		AP_PROFILE_FN();

		// Convert std::string& name into wchar_t*
		wchar_t* className;
		{
			const char* orig = name.c_str();
			// newsize describes the length of the
			// wchar_t string called wcstring in terms of the number
			// of wide characters, not the number of bytes.
			size_t newsize = strlen(orig) + 1;

			// The following creates a buffer large enough to contain
			// the exact number of characters in the original string
			// in the new format. If you want to add more characters
			// to the end of the string, increase the value of newsize
			// to increase the size of the buffer.
			className = new wchar_t[newsize];

			// Convert char* string to a wchar_t* string.
			size_t convertedChars = 0;
			mbstowcs_s(&convertedChars, className, newsize, orig, _TRUNCATE);
		}

		// Register window class
		m_WindowClass = { 0 };
		// Set parameters
		m_WindowClass.lpfnWndProc = WindowProc;
		m_WindowClass.hInstance = hInstance;
		m_WindowClass.lpszClassName = className;
		// Register
		RegisterClass(&m_WindowClass);

		// Create instance
		m_WindowHandle = CreateWindowEx(
			0,						// Optional window styles.
			className,				// Window class
			className,				// Window text (what appears in the title bar), set same as name.
			WS_OVERLAPPEDWINDOW,	// Window style

			// Size and position
			CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

			NULL,		// Parent window    
			NULL,		// Menu
			hInstance,	// Instance handle
			NULL		// Additional application data
		);
		AP_ASSERT_C(m_WindowHandle, "Failed to create instance of window class.\n CreateWindowEx() returned NULL");

		// Show window
		if (m_WindowHandle)
			ShowWindow(m_WindowHandle, nShowCmd);

		AP_INFO_C("Created Windows window");
	}

	WindowsWindow::~WindowsWindow()
	{
		AP_PROFILE_FN();
	}

	bool WindowsWindow::PollEvents() const
	{
		bool eventsExist = false;

		MSG msg;
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)  // PeekMessage is non blocking so use over GetMessage which is blocking
		{
			eventsExist = true;
			TranslateMessage(&msg);		// Turns keystrokes into chars
			DispatchMessage(&msg);		// Dispatch to WindowProc for handling
		}

		return eventsExist;
	}
	
	LRESULT WindowsWindow::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		AP_PROFILE_FN();

		switch (uMsg)
		{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hwnd, &ps);



			FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

			EndPaint(hwnd, &ps);
		}
		return 0;

		}
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

}