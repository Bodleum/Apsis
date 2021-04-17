#pragma once
#include "Apsis/Core/Input.h"

namespace A {

	class WindowsInput : public Input
	{
	public:
		// Inherited via Input
		virtual bool IsKeyDownImpl(KeyCode key_code) override;
		virtual bool WasKeyDownImpl(KeyCode key_code) override;
		virtual bool IsMouseButtonDownImpl(MouseCode mouse_code) override;
		virtual bool WasMouseButtonDownImpl(MouseCode mouse_code) override;
		virtual std::array<int, 2> GetMousePosImpl() override;
		virtual int GetMouseXImpl() override;
		virtual int GetMouseYImpl() override;

	private:
		int KeyCodeToVirtualKeyCode(KeyCode key_code);
		int MouseCodeToVirtualKeyCode(MouseCode mouse_code);
	};

}