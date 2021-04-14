#pragma once
#include "apch.h" // Windows.h
#include "Apsis/Core/Window.h"

namespace A {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR pCmdLine, int nShowCmd, const std::string& name, unsigned int width, unsigned int height);
		virtual ~WindowsWindow();

		// Inherited via Window
		virtual bool PollEvents() const override;
		virtual unsigned int GetWidth() const override { return 0; }
		virtual unsigned int GetHeight() const override { return 0; }

	private:
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		WNDCLASS m_WindowClass;
		HWND m_WindowHandle;
	};
	
}