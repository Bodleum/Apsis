#pragma once
#include "Apsis/Core/Input.h"

namespace A {

	class WindowsInput : public Input
	{
	public:
		WindowsInput() {};

		// Inherited via Input
		virtual bool IsKeyDown(KeyCode key_code) override;
		virtual bool WasKeyDown(KeyCode key_code) override;
		virtual bool IsMouseButtonDown(MouseCode mouse_code) override;
		virtual bool WasMouseButtonDown(MouseCode mouse_code) override;
		virtual std::array<int, 2> GetMousePos() override;
		virtual int GetMouseX() override;
		virtual int GetMouseY() override;

	private:
		int KeyCodeToVirtualKeyCode(KeyCode key_code);
		int MouseCodeToVirtualKeyCode(MouseCode mouse_code);
	};

}