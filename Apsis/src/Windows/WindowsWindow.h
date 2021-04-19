#pragma once
#include "apch.h" // Windows.h
#include "Apsis/Core/Window.h"

namespace A {

	typedef enum class KeyCode : unsigned short;

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pCmdLine, int nShowCmd, const std::string& name, unsigned int width, unsigned int height);
		virtual ~WindowsWindow();

		// Inherited via Window
		virtual bool PollEvents() const override;

	private:
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		WNDCLASSEX m_WindowClass;
		HWND m_WindowHandle;

		unsigned int m_Width, m_Height;

		// message type, tally
		static std::map<unsigned int, int> m_MessageTally;
	};

	namespace RawInput {

		KeyCode ScanCodeToKeyCode(unsigned short scan_code, bool E0 = false, bool E1 = false);

	}
	
}