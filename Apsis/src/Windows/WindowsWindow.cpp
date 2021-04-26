#include "apch.h"
#include "WindowsWindow.h"

#include <windowsx.h>

#include "Apsis/Event/EventDispatcher.h"
//#include "Apsis/Core/InputCodes.h"		Included in EventDispatcher.h

namespace A {

	std::map<unsigned int, int> WindowsWindow::m_MessageTally = {};

	WindowsWindow::WindowsWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pCmdLine, int nShowCmd, const std::string& name, unsigned int width, unsigned int height)
		: m_DeviceContexHandle(nullptr), m_PixelFormatDescriptor({ 0 }), m_Width(width), m_Height(height)
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
		m_WindowClass.cbSize = sizeof(WNDCLASSEX);
		m_WindowClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS | CS_OWNDC;
		m_WindowClass.lpfnWndProc = WindowProc;
		m_WindowClass.hInstance = hInstance;
		m_WindowClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
		m_WindowClass.lpszClassName = className;
		// Register
		ATOM registerClassRet = RegisterClassEx(&m_WindowClass);
		AP_ASSERT_C(registerClassRet, "Failed to register window class.\n RegisterClassEx() returned {0}\n Error: {1}", registerClassRet, GetLastError());

		// Don't include title bar and border in width and height
		RECT windowRect{ 0, 0, width, height };
		AdjustWindowRectEx(&windowRect, WS_OVERLAPPEDWINDOW, false, WS_EX_OVERLAPPEDWINDOW);

		// Create instance
		m_WindowHandle = CreateWindowEx(
			WS_EX_OVERLAPPEDWINDOW,	// Optional window styles.
			className,				// Window class
			className,				// Window text (what appears in the title bar), set same as name.
			WS_OVERLAPPEDWINDOW,	// Window style

			// Size and position
			CW_USEDEFAULT, CW_USEDEFAULT, windowRect.right - windowRect.left, windowRect.bottom - windowRect.top,

			NULL,		// Parent window    
			NULL,		// Menu
			hInstance,	// Instance handle
			NULL		// Additional application data
		);
		AP_ASSERT_C(m_WindowHandle, "Failed to create instance of window class.\n Error: {0}", GetLastError());
		if (!m_WindowHandle) return;

		m_PixelFormatDescriptor = {// Set pixel format descriptor
			sizeof(PIXELFORMATDESCRIPTOR),
				1,
				PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
				PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
				32,                   // Colordepth of the framebuffer.
				0, 0, 0, 0, 0, 0,
				0,
				0,
				0,
				0, 0, 0, 0,
				24,                   // Number of bits for the depthbuffer
				8,                    // Number of bits for the stencilbuffer
				0,                    // Number of Aux buffers in the framebuffer.
				PFD_MAIN_PLANE,
				0,
				0, 0, 0
		};

		m_DeviceContexHandle = GetDC(m_WindowHandle);
		AP_ASSERT_C(m_DeviceContexHandle, "Failed to get device context handle");
		if (m_DeviceContexHandle == 0) return;

		int pixelFormatIndex = ChoosePixelFormat(m_DeviceContexHandle, &m_PixelFormatDescriptor);
		AP_ASSERT_C(pixelFormatIndex != 0, "Failed to match an appropriate pixel format, Error: {0}", GetLastError());
		SetPixelFormat(m_DeviceContexHandle, pixelFormatIndex, &m_PixelFormatDescriptor);

		// Show window
		if (m_WindowHandle)
			ShowWindow(m_WindowHandle, nShowCmd);

		AP_INFO_C("Created Windows window: {0}x{1}", width, height);
	}

	WindowsWindow::~WindowsWindow()
	{
		AP_PROFILE_FN();
	}

	bool WindowsWindow::PollEvents() const
	{
		AP_PROFILE_FN();

		bool messagesExist = false;

		MSG msg;
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) > 0)  // PeekMessage is non blocking so use over GetMessage which is blocking
		{
			messagesExist = true;
			TranslateMessage(&msg);		// Turns keystrokes into chars
			DispatchMessage(&msg);		// Dispatch to WindowProc for handling
		}

		return messagesExist;	
	}
	
	LRESULT WindowsWindow::WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		AP_PROFILE_FN();

		// Trace windows messages
		#define AP_TRACE_WINMSG 1
		{
			#if defined(AP_TRACE_WINMSG)
			auto insertret = m_MessageTally.insert({ (unsigned int)uMsg, 1 });
			if (!insertret.second)
				insertret.first->second++;
			#endif // defined(AP_TRACE_WINMSG)
		}


		switch (uMsg)
		{
			// ---   Mouse   ---
			case WM_LBUTTONDOWN:
			{
				int x = GET_X_LPARAM(lParam);
				int y = GET_Y_LPARAM(lParam);
				EventDispatcher::DispatchEvent(MakeShared<MouseButtonDownEvent>(x, y, Mouse::Left));
				return 0;
			}

			case WM_LBUTTONUP:
			{
				int x = GET_X_LPARAM(lParam);
				int y = GET_Y_LPARAM(lParam);
				EventDispatcher::DispatchEvent(MakeShared<MouseButtonUpEvent>(x, y, Mouse::Left));
				return 0;
			}

			case WM_MBUTTONDOWN:
			{
				int x = GET_X_LPARAM(lParam);
				int y = GET_Y_LPARAM(lParam);
				EventDispatcher::DispatchEvent(MakeShared<MouseButtonDownEvent>(x, y, Mouse::Middle));
				return 0;
			}

			case WM_MBUTTONUP:
			{
				int x = GET_X_LPARAM(lParam);
				int y = GET_Y_LPARAM(lParam);
				EventDispatcher::DispatchEvent(MakeShared<MouseButtonUpEvent>(x, y, Mouse::Middle));
				return 0;
			}

			case WM_RBUTTONDOWN:
			{
				int x = GET_X_LPARAM(lParam);
				int y = GET_Y_LPARAM(lParam);
				EventDispatcher::DispatchEvent(MakeShared<MouseButtonDownEvent>(x, y, Mouse::Right));
				return 0;
			}

			case WM_RBUTTONUP:
			{
				int x = GET_X_LPARAM(lParam);
				int y = GET_Y_LPARAM(lParam);
				EventDispatcher::DispatchEvent(MakeShared<MouseButtonUpEvent>(x, y, Mouse::Right));
				return 0;
			}

			case WM_XBUTTONDOWN:
			{
				int x1or2 = GET_Y_LPARAM(wParam);
				int x = GET_X_LPARAM(lParam);
				int y = GET_Y_LPARAM(lParam);
				EventDispatcher::DispatchEvent(MakeShared<MouseButtonDownEvent>(x, y, x1or2 == 1 ? Mouse::X1 : Mouse::X2));
				return 0;
			}

			case WM_XBUTTONUP:
			{
				int x1or2 = GET_Y_LPARAM(wParam);
				int x = GET_X_LPARAM(lParam);
				int y = GET_Y_LPARAM(lParam);
				EventDispatcher::DispatchEvent(MakeShared<MouseButtonUpEvent>(x, y, x1or2 == 1 ? Mouse::X1 : Mouse::X2));
				return 0;
			}

			case WM_MOUSEMOVE:
			{
				int x = GET_X_LPARAM(lParam);
				int y = GET_Y_LPARAM(lParam);
				EventDispatcher::DispatchEvent(MakeShared<MouseMoveEvent>(x, y));
				return 0;
			}

			case WM_MOUSEWHEEL:
			{
				int delta = GET_WHEEL_DELTA_WPARAM(wParam) / 120;
				int x = GET_X_LPARAM(lParam);
				int y = GET_Y_LPARAM(lParam);
				EventDispatcher::DispatchEvent(MakeShared<MouseWheelEvent>(x, y, delta));
				return 0;
			}


			// ---   Keyboard   ---
			case WM_INPUT:
			{
				// 0 if app is in foreground --> continue with event
				// 1 if app is in background --> yield to DefWindowProc
				if (GET_RAWINPUT_CODE_WPARAM(wParam) == 1)
					break;

				// Find size of buffer needed to store input data, set in dwSize
				UINT dwSize = 0;
				GetRawInputData((HRAWINPUT)lParam, RID_INPUT, NULL, &dwSize, sizeof(RAWINPUTHEADER));
				LPBYTE lpb = new BYTE[dwSize];	// Create the buffer

				if (lpb == NULL) { return 0; } // buffer was Null

				if (GetRawInputData((HRAWINPUT)lParam, RID_INPUT, lpb, &dwSize, sizeof(RAWINPUTHEADER)) != dwSize)
					AP_CRIT_C("GetRawInputData does not return correct size !");

				RAWINPUT* rawInput = (RAWINPUT*)lpb;

				if (rawInput->header.dwType == RIM_TYPEKEYBOARD)	// If raw input comes from a keyboard
				{
					unsigned short scanCode = rawInput->data.keyboard.MakeCode;
					unsigned short flags = rawInput->data.keyboard.Flags;
					unsigned short virtualKeyCode = rawInput->data.keyboard.VKey;	// Legacy virtual keycode: https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes
					unsigned int message = rawInput->data.keyboard.Message;		// WM_KEYDOWN, WM_SYSKEYDOWN, and so forth
					unsigned long extraInfo = rawInput->data.keyboard.ExtraInformation;
					// Proccess flags
					bool down = (flags & 1) == 0;
					bool up = (flags & BIT_AT(0));
					bool E0 = (flags & BIT_AT(1));
					bool E1 = (flags & BIT_AT(2));
					bool repeat = (GetKeyState(virtualKeyCode) & 0x8000) * down;

					KeyCode keyCode = RawInput::ScanCodeToKeyCode(scanCode, E0, E1);
					// Get key char
					UINT key = (scanCode << 16) | (E0 << 24);
					char buffer[30] = {};
					GetKeyNameTextA((LONG)key, buffer, sizeof(buffer));

					//std::cout << KeyCodeToString(keyCode) << ' ' << up << ' ' << down << ' ' << repeat << '\n';
					//std::cout << scanCode << E0 << E1 << '\n';
					//std::cout << virtualKeyCode << '\n';

					if (up)
						EventDispatcher::DispatchEvent(MakeShared<KeyUpEvent>(keyCode));
					else if (down)
					{
						EventDispatcher::DispatchEvent(MakeShared<KeyDownEvent>(keyCode, repeat));
						if (strlen(buffer) == 1)
						{
							char* character = buffer;
							EventDispatcher::DispatchEvent(MakeShared<KeyCharEvent>(keyCode, *character, repeat));
						}
					}
				}

				delete[] lpb;		// delete buffer to avoid mem leaks
				break;	// must call DefWindowProc so the system can perform cleanup
			}

			// --- Window   ---
			case WM_CREATE:
			{
				// Setup of raw input devices
				// Keyboard
				RAWINPUTDEVICE rawInputDevices[1] = {};
				rawInputDevices[0].dwFlags = RIDEV_INPUTSINK;	// adds keyboard and also ignores legacy keyboard messages
				rawInputDevices[0].hwndTarget = hWnd;
				rawInputDevices[0].usUsagePage = 0x01;				// HID_USAGE_PAGE_GENERIC
				rawInputDevices[0].usUsage = 0x06;					// HID_USAGE_GENERIC_KEYBOARD

				// Register
				if (RegisterRawInputDevices(rawInputDevices, 1, sizeof(rawInputDevices[0])) == FALSE)
					AP_ASSERT_C(false, "Failed to register raw input devices: {0}", GetLastError());

				AP_TRACE_C("Registered raw input devices");
				return 0;
			}

			case WM_CLOSE:
			{
				EventDispatcher::DispatchEvent(MakeShared<WindowCloseEvent>());
				break;	// Continue with the closing of the window
			}

			case WM_DESTROY:
			{
				EventDispatcher::DispatchEvent(MakeShared<WindowDestroyEvent>());
#if AP_TRACE_WINMSG
				for (auto& element : m_MessageTally)
					AP_TRACE_C("Message: {0},\t{1} times", element.first, element.second);
#endif // AP_TRACE_WINMSG
				PostQuitMessage(0);
				return 0;
			}

			case WM_SIZE:
			{
				UINT width = LOWORD(lParam);
				UINT height = HIWORD(lParam);
				EventDispatcher::DispatchEvent(MakeShared<WindowResizeEvent>(width, height));
				return 0;
			}


			// --- App   ---
			case WM_QUIT:
			{
				EventDispatcher::DispatchEvent(MakeShared<AppQuitEvent>());
				return 0;
			}


			// ---   Other   ---
			case WM_PAINT:
			{
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);
				EventDispatcher::DispatchEvent(MakeShared<WindowPaintEvent>());
				EndPaint(hWnd, &ps);
			}
		}

		return DefWindowProc(hWnd, uMsg, wParam, lParam);	// Unhandled message, DefWindowProc performs default action
	}


	namespace RawInput {

		KeyCode ScanCodeToKeyCode(unsigned short scan_code, bool E0/* = false*/, bool E1/* = false*/)
		{
			switch (scan_code)
			{
				case 0x1E:			return Key::A;
				case 0x30:			return Key::B;
				case 0x2E:			return Key::C;
				case 0x20:			return Key::D;
				case 0x12:			return Key::E;
				case 0x21:			return Key::F;
				case 0x22:			return Key::G;
				case 0x23:			return Key::H;
				case 0x17:			return Key::I;
				case 0x24:			return Key::J;
				case 0x25:			return Key::K;
				case 0x26:			return Key::L;
				case 0x32:			return Key::M;
				case 0x31:			return Key::N;
				case 0x18:			return Key::O;
				case 0x19:			return Key::P;
				case 0x10:			return Key::Q;
				case 0x13:			return Key::R;
				case 0x1F:			return Key::S;
				case 0x14:			return Key::T;
				case 0x16:			return Key::U;
				case 0x2F:			return Key::V;
				case 0x11:			return Key::W;
				case 0x2D:			return Key::X;
				case 0x15:			return Key::Y;
				case 0x2C:			return Key::Z;

				case 0x02:			return Key::Num1;	// also ! (shift 1)
				case 0x03:			return Key::Num2;	// etc
				case 0x04:			return Key::Num3;	// .
				case 0x05:			return Key::Num4;	// .
				case 0x06:			return Key::Num5;	// .
				case 0x07:			return Key::Num6;
				case 0x08:			return Key::Num7;
				case 0x09:			return Key::Num8;
				case 0x0A:			return Key::Num9;
				case 0x0B:			return Key::Num0;

				case 0x1C:			if (E0) return Key::NumpadEnter;	else return Key::Enter;
				case 0x01:			return Key::Escape;
				case 0x0E:			return Key::Backspace;
				case 0x0F:			return Key::Tab;
				case 0x39:			return Key::Space;

				case 0x0C:			return Key::Hyphen;
				case 0x0D:			return Key::Equal;
				case 0x1A:			return Key::OpenSquareBracket;
				case 0x1B:			return Key::CloseSquareBracket;
				//case 0x2B:			return Key::Backslash;
				case 0x2B:			return Key::Europe1;	// #(~) on my keyboard
				case 0x27:			return Key::Semicolon;
				case 0x28:			return Key::SingleQuote;
				case 0x29:			return Key::Grave;
				case 0x33:			return Key::Comma;
				case 0x34:			return Key::Dot;
				case 0x35:			if (E0) return Key::NumpadDivide;	else return Key::Slash;

				case 0x3A:			return Key::CapsLock;
				case 0x3B:			return Key::F1;
				case 0x3C:			return Key::F2;
				case 0x3D:			return Key::F3;
				case 0x3E:			return Key::F4;
				case 0x3F:			return Key::F5;
				case 0x40:			return Key::F6;
				case 0x41:			return Key::F7;
				case 0x42:			return Key::F8;
				case 0x43:			return Key::F9;
				case 0x44:			return Key::F10;
				case 0x57:			return Key::F11;
				case 0x58:			return Key::F12;

				case 0x37:			if (E0) return Key::PrintScreen;	else			return Key::NumpadMultiply;
				case 0x46:			if (E0) return Key::Break;			else			return Key::ScrollLock;
				case 0xC6:			if (E0) return Key::Break;			else			return Key::Unknown;
				case 0x1D:			if (E0) return Key::RightControl;	else if (E1)	return Key::Pause;				else return Key::LeftControl;
				case 0x9D:			if (E1) return Key::Pause;			else			return Key::Unknown;
				case 0xC5:					return Key::Pause;
				case 0x52:			if (E0) return Key::Insert;			else return Key::Numpad0;
				case 0x47:			if (E0) return Key::Home;			else return Key::Numpad7;
				case 0x49:			if (E0) return Key::PageUp;			else return Key::Numpad9;
				case 0x53:			if (E0) return Key::Delete;			else return Key::NumpadDecimal;
				case 0x4F:			if (E0) return Key::End;			else return Key::Numpad1;
				case 0x51:			if (E0) return Key::PageDown;		else return Key::Numpad3;

				case 0x4D:			if (E0) return Key::Right;			else return Key::Numpad6;
				case 0x4B:			if (E0) return Key::Left;			else return Key::Numpad4;
				case 0x50:			if (E0) return Key::Down;			else return Key::Numpad2;
				case 0x48:			if (E0) return Key::Up;				else return Key::Numpad8;

				case 0x45:			return Key::NumLock;
				case 0x4A:			return Key::NumpadSubtract;
				case 0x4E:			return Key::NumpadPlus;
				case 0x4C:			return Key::Numpad5;

				case 0x56:			return Key::Europe2;	// \(|) on my keyboard
				case 0x5D:			if (E0) return Key::Menu;			else return Key::Unknown;
				//case 0x5E:			if (E0) return Key::KeyboardPower;	else return Key::Unknown;	// What is KeyboardPower?
				case 0x59:			return Key::NumpadEqual;
				case 0x64:			return Key::F13;
				case 0x65:			return Key::F14;
				case 0x66:			return Key::F15;
				case 0x67:			return Key::F16;
				case 0x68:			return Key::F17;
				case 0x69:			return Key::F18;
				case 0x6A:			return Key::F19;
				case 0x6B:			return Key::F20;
				case 0x6C:			return Key::F21;
				case 0x6D:			return Key::F22;
				case 0x6E:			return Key::F23;
				case 0x76:			return Key::F24;

				case 0x2A:					return Key::LeftShift;
				case 0x38:			if (E0) return Key::RightAlt;		else return Key::LeftAlt;
				case 0x5B:			if (E0) return Key::LeftSuper;		else return Key::Unknown;
				case 0x36:					return Key::RightShift;
				case 0x5C:			if (E0) return Key::RightSuper;		else return Key::Unknown;


				default:			return Key::Unknown;
			}
		}

	}

}